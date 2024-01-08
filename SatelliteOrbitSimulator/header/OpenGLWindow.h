#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <cmath>
#include <QTimer>
#include "EarthSystem.h"

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
    void updateSolarSystemData();
    void startRendering(float& speed, float& size, float& altitude);
    void stopRendering();
    void updateData(std::vector<float>& vertices, std::vector<float>& colors);

protected:
    void paintGL() override;
    void initializeGL() override;
  
private:
    void reset();
    QString readShaderSource(QString filePath);
    void mouseMoveEvent(QMouseEvent* event);
    void shaderWatcher();

private:
    QTimer* timer;
    EarthSystem* solar;

    QOpenGLShaderProgram* mProgram = nullptr;
    QColor mBackground;

    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    GLint m_rotationAngleUniform;  

    float* mVerticesData;
    float* mColorsData;

    GLfloat mZoomFactor = 1.25;

    std::vector<float> mVertices;
    std::vector<float> mColors;

    QVector<GLfloat> verticesOfOrignalLine;
    QVector<GLfloat> colorOfOrignalLine;

    QQuaternion rotationAngle;
    QPoint lastPos;

    QFileSystemWatcher* mShaderWatcher;
};
