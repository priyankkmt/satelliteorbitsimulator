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
    connect(mSimulateButton, &QPushButton::clicked, this, &Simulator::simulateBtn);
    connect(mStopButton, &QPushButton::clicked, this, &Simulator::stopBtn);
    connect(mResetButton, &QPushButton::clicked, this, &Simulator::resetBtn);
}

Simulator::~Simulator()
{
}

void Simulator::setupUi()
{
    // Create the central widget with a horizontal layout
    mWidget = new QWidget(this);

    QHBoxLayout* centralLayout = new QHBoxLayout(mWidget);

    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);

    QMargins margins(50, 10, 50, 50);
    QMargins marginsCentralLayout(10, 10, 10, 10);

    // Create an OpenGL rendering window
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), mWidget);
    centralLayout->addWidget(mRenderer, 1); 

    // Set margins around the OpenGLWidget
    centralLayout->setContentsMargins(marginsCentralLayout);

    // Create a vertical layout for the buttons on the right side
    QVBoxLayout* rightSideLayout = new QVBoxLayout(mWidget);
    rightSideLayout->setContentsMargins(margins);

    mSpeedLabel = new QLabel("Km/s");
    mAltitudeLabel = new QLabel("x100 Km");
    mSizeLabel = new QLabel("Meter");

    applyCustomStyleLabel(mSpeedLabel);
    applyCustomStyleLabel(mAltitudeLabel);
    applyCustomStyleLabel(mSizeLabel);

    mSpeedInput = new QDoubleSpinBox(mWidget);
    mAltitudeInput = new QDoubleSpinBox(mWidget);
    mSizeInput = new QDoubleSpinBox(mWidget);

    applyCustomStyleDoubleSpinBox(mSpeedInput);
    applyCustomStyleDoubleSpinBox(mAltitudeInput);
    applyCustomStyleDoubleSpinBox(mSizeInput);

    rightSideLayout->addWidget(mSpeedInput);
    rightSideLayout->addWidget(mSpeedLabel);
    rightSideLayout->addWidget(mAltitudeInput);
    rightSideLayout->addWidget(mAltitudeLabel);
    rightSideLayout->addWidget(mSizeInput);
    rightSideLayout->addWidget(mSizeLabel);

    mSimulateButton = new QPushButton("Start", mWidget);
    mStopButton = new QPushButton("Stop", mWidget);
    mResetButton = new QPushButton("Reset", mWidget);

    mSimulateButton->setSizePolicy(sizePolicy1);
    mStopButton->setSizePolicy(sizePolicy1);
    mResetButton->setSizePolicy(sizePolicy1);

    applyCustomStyleButton(mSimulateButton);
    applyCustomStyleButton(mStopButton);
    applyCustomStyleButton(mResetButton);

    rightSideLayout->addWidget(mSimulateButton);
    rightSideLayout->addWidget(mStopButton);
    rightSideLayout->addWidget(mResetButton);

    rightSideLayout->setAlignment(Qt::AlignTop);

    centralLayout->addLayout(rightSideLayout);

    setCentralWidget(mWidget);
    //showMaximized();
    setWindowTitle(QCoreApplication::translate("Simulator", "Simulator", nullptr));
}

// custom style function for label
void Simulator::applyCustomStyleLabel(QLabel* label) {
    QString styleSheet = R"(
        QLabel {
            color: black;
            font-size: 16px;
            font-weight: bold;
            padding: 2px;
        }
    )";
    label->setStyleSheet(styleSheet);
}

// custom style function for double spin box
void Simulator::applyCustomStyleDoubleSpinBox(QDoubleSpinBox* doubleSpinBox) {
    QString styleSheet = R"(
        QDoubleSpinBox {
            background-color: lightgray;
            border: 2px solid darkgray;
            border-radius: 5px;
            padding: 2px;
        }
    )";

    doubleSpinBox->setStyleSheet(styleSheet);
}

// custom style function for button
void Simulator::applyCustomStyleButton(QPushButton* button) {
    QString styleSheet = R"(
        QPushButton {
            font-size: 14pt;
            background-color: #1E90FF;   
            color: white;                
            border: 2px solid #4169E1;   
            border-radius: 8px;           
            padding: 8px 16px;        
        }
        QPushButton:hover {
            background-color: #3F88C5;   
        }
        QPushButton:pressed {
            background-color: #2A6496;  
        }
    )";
    button->setStyleSheet(styleSheet);
}

// Start button click event handler
void Simulator::simulateBtn()
{
    mVelocity = mSpeedInput->value();
    mAltitude = mAltitudeInput->value();
    mSize = mSizeInput->value();
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