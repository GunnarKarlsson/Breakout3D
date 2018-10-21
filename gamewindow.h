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
#include "skybox.h"
#include "particleeffect.h"

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
    void startParticleEffect();
    AssetManager *assetManager;
    BasicShader *basicShader;
    QTimer *timer;
    Camera *camera;
    std::vector<Entity*> wallBricks;
    std::vector<Entity*> bricks;
    Entity *paddle;
    Entity *ball;
    bool hasCollided = false;
    int collisionCoolDown = 0;
    glm::vec3 lightPos = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);
    Skybox *skybox;
    ParticleEffect *particleEffect;
};

#endif // MAINWINDOW_H
