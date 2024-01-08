#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QTimer>
#include <QComboBox>  
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

private:          
    QPushButton* mStartButton;
    QPushButton* mStopButton;
    QPushButton* mResetButton;

    QPushButton* mSpeedButton;
    QPushButton* mAltitudeButton;
    QPushButton* mSizeButton;

    QDoubleSpinBox* mSpeedInput;
    QDoubleSpinBox* mAltitudeInput;
    QDoubleSpinBox* mSizeInput;

    QLabel* mLabel;

    QTimer* mTimer;
    QWidget* mWidget;

    EarthSystem* solar;

    OpenGLWindow* mRenderer;

    float mVelocity;
    float mAltitude;
    float mSize;

    std::vector<float> mVertices;
    std::vector<float> mColors;

    QVector<GLfloat> ver;
    QVector<GLfloat> col;

private slots:
    void startBtn();
    void stopBtn();
    void resetBtn();
    void addVelocity();
    void addAltitude();
    void addSize();
};
