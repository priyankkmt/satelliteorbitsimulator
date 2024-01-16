#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <cmath>
#include <QTimer>

#include "EarthSystem.h"
#include "ReadSTL.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;
class EarthSystem;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QWidget* parent);
    ~OpenGLWindow();

    void stopRevolving();
    void resetPositions();
    void updatePlanetSystemData();
    void startRendering(float& speed, float& size, float& altitude);
    void stopRendering();

protected:
    void paintGL() override;
    void initializeGL() override;
  
private:
    void reset();
    QString readShaderSource(QString filePath);
    void mouseMoveEvent(QMouseEvent* event);
    void shaderWatcher();
    void wheelEvent(QWheelEvent* event);

private:
    QTimer* timer;
    EarthSystem* mSolarObj;
    ReadSTL* mReadSTLObj;

    QOpenGLShaderProgram* mProgram = nullptr;
    QColor mBackground;

    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    GLint m_rotationAngleUniform;  

    float* mVerticesData;
    float* mColorsData;

    float mZoomFactor = 1.25;

    int spherePoints = 0;
    int pathPoints = 0;

    bool isReset = false;

    std::vector<float> mVertices;
    std::vector<float> mColors;

    QVector<GLfloat> verticesOfOrignalLine;
    QVector<GLfloat> colorOfOrignalLine;

    QQuaternion rotationAngle;
    QPoint lastPos;

    QFileSystemWatcher* mShaderWatcher;
};
