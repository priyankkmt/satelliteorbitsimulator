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
    connect(mSpeedButton, &QPushButton::clicked, this, &Simulator::addVelocity);
    connect(mAltitudeButton, &QPushButton::clicked, this, &Simulator::addAltitude);
    connect(mSizeButton, &QPushButton::clicked, this, &Simulator::addSize);
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

    mSpeedButton = new QPushButton("Speed", mWidget);
    mSpeedButton->setObjectName("mSpeedButton");
    mSpeedButton->setGeometry(rightSideX + 80, 90, 75, 24);

    mAltitudeButton = new QPushButton("Altitude", mWidget);
    mAltitudeButton->setObjectName("mAltitudeButton");
    mAltitudeButton->setGeometry(rightSideX + 80, 130, 75, 24);

    mSizeButton = new QPushButton("Size", mWidget);
    mSizeButton->setObjectName("mSizeButton");
    mSizeButton->setGeometry(rightSideX + 80, 170, 75, 24);

    mSpeedInput = new QDoubleSpinBox(mWidget);
    mSpeedInput->setObjectName("mSpeedInput");
    mSpeedInput->setGeometry(rightSideX , 90, 75, 24);

    mAltitudeInput = new QDoubleSpinBox(mWidget);
    mAltitudeInput->setObjectName("mAltitudeInput");
    mAltitudeInput->setGeometry(rightSideX , 130, 75, 24);

    mSizeInput = new QDoubleSpinBox(mWidget);
    mSizeInput->setObjectName("mSizeInput");
    mSizeInput->setGeometry(rightSideX , 170, 75, 24);

    mLabel = new QLabel(mWidget);
    mLabel->setObjectName("mLabel");
    mLabel->setGeometry( 60, 10, 221, 31);

    // Set font and text for the title mLabel
    QFont font;
    font.setPointSize(15);
    mLabel->setFont(font);
    mLabel->setText("Satellite Orbit Simulator");

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
    mVelocity = mSpeedInput->value();
}

// Handler for adding altitude from the input field
void Simulator::addAltitude()
{
    mAltitude = mAltitudeInput->value();
}

// Handler for adding size from the input field
void Simulator::addSize()
{
    mSize = mSizeInput->value();
}
