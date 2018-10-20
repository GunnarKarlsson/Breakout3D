#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QTimer>
#include <vector>
#include "assetmanager.h"
#include "basicshader.h"
#include "camera.h"
#include "entity.h"


class GameWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GameWindow();
    ~GameWindow();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    bool eventFilter(QObject *object, QEvent *event);

private:
    void setViewport(float x, float y, int w, int h);
    void updateScene(int worldWidth, int worldHeight);
    void renderScene(float x, float y, int worldWidth, int worldHeight);
    AssetManager *assetManager;
    BasicShader *basicShader;
    QTimer *timer;
    Camera *camera;
    std::vector<Entity*> wallBricks;
    Entity *paddle;
};

#endif // MAINWINDOW_H
