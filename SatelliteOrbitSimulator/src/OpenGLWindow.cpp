#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>
#include "EarthSystem.h"
#include <QTimer>
#include <fstream>
#include <sstream>
#include <QFile>
#include <QTextStream>

OpenGLWindow::OpenGLWindow (const QColor& background, QWidget* parent) : mBackground(background)
{
	setParent(parent);
	setMinimumSize(500, 250);
	mZoomFactor = 1.25;
    solar = new EarthSystem();
	timer = new QTimer(this);
	
	const QStringList list = { "vShader.glsl","fShader.glsl"};
	mShaderWatcher = new QFileSystemWatcher(list, this);
	connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);

}

void OpenGLWindow::updateData(std::vector<float>& vertices, std::vector<float>& colors)
{
	mVertices.clear();
	mColors.clear();
	mVertices = vertices;
	mColors = colors;
	update();
}

void OpenGLWindow::startRendering(float& speed, float& size, float& altitude)
{
	solar->setSatelliteSpeed(speed);
	solar->setSatelliteRadius(size);
	solar->setSatelliteDistance(altitude);
	solar->calculateOrbitVelocity(altitude);
	connect(timer, &QTimer::timeout, this, &OpenGLWindow::updateSolarSystemData);
	timer->start(16); 
}

void OpenGLWindow::stopRendering()
{
	timer->stop();
}

OpenGLWindow::~OpenGLWindow()
{
	reset();
}

void OpenGLWindow::reset()
{
	makeCurrent();
	delete mProgram;
	mProgram = nullptr;
	doneCurrent();
	QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::updateSolarSystemData()
{
	mVertices.clear();
	mColors.clear();
	solar->drawPlanetSatelliteSystem(mVertices, mColors);
	update();
}

void OpenGLWindow::stopRevolving()
{
	timer->stop();
}

void OpenGLWindow::resetPositions()
{
	solar->resetPositions();
	updateSolarSystemData();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
		QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

		rotationAngle = rotX * rotY * rotationAngle;
		update();
	}
	lastPos = event->pos();
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mProgram->bind();

	QMatrix4x4 matrix;
	matrix.ortho(-16.0f , 16.0f , -16.0f , 16.0f , 0.1f, 100.0f);  // orthographic projection
	matrix.translate(0, 0, -2);
	matrix.rotate(rotationAngle);
	mProgram->setUniformValue(m_matrixUniform, matrix);

	mVerticesData = mVertices.data();
	mColorsData = mColors.data(); 

	int size = mVertices.size();

	glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mVerticesData);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mColorsData);

	glEnableVertexAttribArray(m_posAttr);
	glEnableVertexAttribArray(m_colAttr);

	glDrawArrays(GL_LINES, 0, size / 3);

	glDisableVertexAttribArray(m_colAttr);
	glDisableVertexAttribArray(m_posAttr);

}

void OpenGLWindow::shaderWatcher()
{
	QString vertexShaderSource = readShaderSource("vShader.glsl");
	QString fragmentShaderSource = readShaderSource("fShader.glsl");

	mProgram->release();
	mProgram->removeAllShaders();
	
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

	mProgram->link();
}


void OpenGLWindow::initializeGL()
{

	QString vertexShaderSource = readShaderSource("vShader.glsl");
	QString fragmentShaderSource = readShaderSource("fShader.glsl");

	initializeOpenGLFunctions();

	mProgram = new QOpenGLShaderProgram(this);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

	if (!mProgram->link())
	{
		qDebug() << "Shader program link error:" << mProgram->log();

	}

	m_posAttr = mProgram->attributeLocation("posAttr");
	m_colAttr = mProgram->attributeLocation("colAttr");
	m_matrixUniform = mProgram->uniformLocation("matrix");

	m_rotationAngleUniform = mProgram->uniformLocation("rotationAngle");  // Add this line


	if (m_posAttr == -1 || m_colAttr == -1 || m_matrixUniform == -1)
	{
		qDebug() << "Shader attribute or uniform location error.";

	}

	glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);
}

QString OpenGLWindow::readShaderSource(QString filePath)
{

	QFile* file = new QFile(filePath);

	if (!file->open(QFile::ReadOnly | QFile::Text))
	{
		std::cerr << "Invalid File !";
		return "Invalid File !";
	}

	QTextStream stream(file);
	QString fileString = stream.readLine();

	while (!stream.atEnd())
	{
		fileString.append(stream.readLine());
	}
	return fileString;
}