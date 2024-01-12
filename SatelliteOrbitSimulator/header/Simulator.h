#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QTimer>
#include <QComboBox>  
#include <Windows.h>

#include "EarthSystem.h"

class OpenGLWindow;

class Simulator : public QMainWindow
{
    Q_OBJECT

public:
    Simulator(QWidget* parent = nullptr);
    ~Simulator();

private:
    void setupUi();
    void applyCustomStyleButton(QPushButton* button);
    void applyCustomStyleDoubleSpinBox(QDoubleSpinBox* doubleSpinBox);
    void applyCustomStyleLabel(QLabel* label);

private:          
    QPushButton* mSimulateButton;
    QPushButton* mStopButton;
    QPushButton* mResetButton;

    QDoubleSpinBox* mSpeedInput;
    QDoubleSpinBox* mAltitudeInput;
    QDoubleSpinBox* mSizeInput;

    QLabel* mLabel;
    QLabel* mSpeedLabel;
    QLabel* mAltitudeLabel;
    QLabel* mSizeLabel;
    

    QTimer* mTimer;
    QWidget* mWidget;

    EarthSystem* mSolar;

    OpenGLWindow* mRenderer;

    float mVelocity;
    float mAltitude;
    float mSize;

    std::vector<float> mVertices;
    std::vector<float> mColors;

    QVector<GLfloat> ver;
    QVector<GLfloat> col;

private slots:
    void simulateBtn();
    void stopBtn();
    void resetBtn();
};
