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

private:
    void setViewport(float x, float y, int w, int h);
    void updateScene(int worldWidth, int worldHeight);
    void renderScene(float x, float y, int worldWidth, int worldHeight);
    AssetManager *assetManager;
    BasicShader *basicShader;
    QTimer *timer;
    Camera *camera;
    Entity *entity;
    std::vector<Entity*> wallBricks;
};

#endif // MAINWINDOW_H
