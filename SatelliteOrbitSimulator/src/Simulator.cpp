#include "stdafx.h"
#include "simulator.h"
#include "OpenGLWindow.h"
#include "EarthSystem.h"
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include <iostream>
#include <vector>

Simulator::Simulator(QWidget* parent) : QMainWindow(parent)
{
    // Set up the user interface
	setupUi();
    // Connect button clicks to corresponding functions
	connect(mStartButton, &QPushButton::clicked, this, &Simulator::startBtn);
	connect(mStopButton, &QPushButton::clicked, this, &Simulator::stopBtn);
	connect(mResetButton, &QPushButton::clicked, this, &Simulator::resetBtn);
    connect(speedButton, &QPushButton::clicked, this, &Simulator::addVelocity);
    connect(altitudeButton, &QPushButton::clicked, this, &Simulator::addAltitude);
    connect(sizeButton, &QPushButton::clicked, this, &Simulator::addSize);
}

Simulator::~Simulator()
{
}

void Simulator::setupUi()
{
    resize(1200, 900);

    // Create the central widget
    mWidget = new QWidget(this);
    setCentralWidget(mWidget);

    // Create buttons for Start, Stop, and Reset
    mStartButton = new QPushButton("Start", mWidget);
    mStopButton = new QPushButton("Stop", mWidget);
    mResetButton = new QPushButton("Reset", mWidget);

    // Create an OpenGL rendering window
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), mWidget);

    mRenderer->setGeometry(10, 50, 1000, 800);

    int rightSideX = mRenderer->geometry().right() + 10;

    mStartButton->setGeometry(rightSideX, 210, 75, 24);
    mStopButton->setGeometry(rightSideX, 250, 75, 24);
    mResetButton->setGeometry(rightSideX, 290, 75, 24);

    speedButton = new QPushButton("Speed", mWidget);
    speedButton->setObjectName("speedButton");
    speedButton->setGeometry(rightSideX + 80, 90, 75, 24);

    altitudeButton = new QPushButton("Altitude", mWidget);
    altitudeButton->setObjectName("altitudeButton");
    altitudeButton->setGeometry(rightSideX + 80, 130, 75, 24);

    sizeButton = new QPushButton("Size", mWidget);
    sizeButton->setObjectName("sizeButton");
    sizeButton->setGeometry(rightSideX + 80, 170, 75, 24);

    speedInput = new QDoubleSpinBox(mWidget);
    speedInput->setObjectName("speedInput");
    speedInput->setGeometry(rightSideX , 90, 75, 24);

    altitudeInput = new QDoubleSpinBox(mWidget);
    altitudeInput->setObjectName("altitudeInput");
    altitudeInput->setGeometry(rightSideX , 130, 75, 24);

    sizeInput = new QDoubleSpinBox(mWidget);
    sizeInput->setObjectName("sizeInput");
    sizeInput->setGeometry(rightSideX , 170, 75, 24);

    label = new QLabel(mWidget);
    label->setObjectName("label");
    label->setGeometry( 60, 10, 221, 31);

    // Set font and text for the title label
    QFont font;
    font.setPointSize(15);
    label->setFont(font);
    label->setText("Satellite Orbit Simulator");

    setWindowTitle(QCoreApplication::translate("Simulator", "Simulator", nullptr));
}

// Start button click event handler
void Simulator::startBtn()
{
	mRenderer->startRendering(mVelocity, mSize, mAltitude);
}

// Stop button
void Simulator::stopBtn()
{
	mRenderer->stopRevolving();
}

// Reset button
void Simulator::resetBtn()
{
	mRenderer->resetPositions();
}

// Handler for adding velocity from the input field
void Simulator::addVelocity()
{
    mVelocity = speedInput->value();
}

// Handler for adding altitude from the input field
void Simulator::addAltitude()
{
    mAltitude = altitudeInput->value();
}

// Handler for adding size from the input field
void Simulator::addSize()
{
    mSize = sizeInput->value();
}
