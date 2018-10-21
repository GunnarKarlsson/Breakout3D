#include "gamewindow.h"
#include <QKeyEvent>
#include <math.h>
#include <string>
#include <string.h>
#include "collision.h"


GameWindow::GameWindow() : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate) {
    installEventFilter(this);
}

GameWindow::~GameWindow() {
    delete basicShader;
    delete timer;
    delete camera;
    delete paddle;
    delete ball;
    wallBricks.clear();
}

void GameWindow::initializeGL() {

    initializeOpenGLFunctions();

    qDebug() << "version: " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    qDebug() << "GSLS version: " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

    assetManager = new AssetManager();
    assetManager->loadAssets();

    particleEffect = new ParticleEffect();

    camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));

    //create frame
    for (int i = 0; i < 11; i++) {
        //left wall
        Entity *entityLeft = new Entity();
        entityLeft->setTextureId(assetManager->blockTextureId, assetManager->blockTexCounter);
        entityLeft->initialize(-5, i-5, 0.0, 0.0);
        wallBricks.push_back(entityLeft);
        //right wall
        Entity *entityRight = new Entity();
        entityRight->setTextureId(assetManager->blockTextureId, assetManager->blockTexCounter);
        entityRight->initialize(5, i-5, 0.0, 0.0);
        wallBricks.push_back(entityRight);
        //top
        Entity *entityTop = new Entity();
        entityTop->setTextureId(assetManager->blockTextureId, assetManager->blockTexCounter);
        entityTop->initialize(i-5, 6, 0.0, 0.0);
        wallBricks.push_back(entityTop);
    }

    //create target bricks
    for (int i = 0; i < 9; i++) {
        Entity *targetTop = new Entity();
        targetTop->setTextureId(assetManager->targetTextureId, assetManager->targetTexCounter);
        targetTop->initialize(-4+i, 5.0, 0.0, 0.0);
        bricks.push_back(targetTop);
        Entity *targetMiddle = new Entity();
        targetMiddle->setTextureId(assetManager->targetTextureId, assetManager->targetTexCounter);
        targetMiddle->initialize(-4+i, 4.0, 0.0, 0.0);
        bricks.push_back(targetMiddle);
        Entity *targetBottom = new Entity();
        targetBottom->setTextureId(assetManager->targetTextureId, assetManager->targetTexCounter);
        targetBottom->initialize(-4+i, 3.0, 0.0, 0.0);
        bricks.push_back(targetBottom);
    }

    paddle = new Entity();
    paddle->setTextureId(assetManager->paddleTextureId, assetManager->paddleTexCounter);
    paddle->initialize(0, -5, 0.0, 0.0);

    ball = new Entity();
    ball->setTextureId(assetManager->ballTextureId, assetManager->ballTexCounter);
    ball->setVelocity(1.0);
    ball->initialize(0, 1.0, 0.05, 0.05);

    basicShader = new BasicShader();
    basicShader->compile();

    skybox = new Skybox();
    skybox->setTextureId(assetManager->skyboxTextureId);

    glEnable(GL_DEPTH_TEST);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void GameWindow::resizeGL(int width, int height) {

}

void GameWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4, 0.6, 0.8, 1.0);

    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    updateScene(SCREEN_WIDTH, SCREEN_HEIGHT);
    renderScene(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameWindow::updateScene(int worldWidth, int worldHeight) {
    ball->update(-5, -10, 5, 5);
    if (haveCollided(paddle, ball) && collisionCoolDown == 0) {
        ball->dy *= -1.0;
        hasCollided = true;
        collisionCoolDown = 30;//half sec or so
    } else if (collisionCoolDown > 0) {
        --collisionCoolDown;
    }
    for (int i = 0; i < bricks.size(); i++) {
        Entity *e = bricks[i];
        if (e->isVisible()) {
            if (haveCollided(e, ball)) {
                ball->dy *= -1.0;
                e->setVisible(false);
                break;
            }
        }
    }
}

void GameWindow::setViewport(float x, float y, int width, int height) {
    glViewport(x, x, width, height);
}

void GameWindow::renderScene(float x, float y, int worldWidth, int worldHeight) {
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 700.0f);

    for (int i = 0; i < wallBricks.size(); i++) {
        wallBricks[i]->render(view, projection, lightPos, lightColor, basicShader);
    }

    for (int i = 0; i < bricks.size(); i++) {
        bricks[i]->render(view, projection, lightPos, lightColor, basicShader);
    }

    paddle->render(view, projection, lightPos, lightColor, basicShader);
    ball->render(view, projection, lightPos, lightColor, basicShader);

    glm::mat4 skyboxView = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
    skybox->update(skyboxView, projection);
}

bool GameWindow::eventFilter( QObject* object, QEvent* event) {
    switch(event->type()) {
    case QEvent::KeyPress:{
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
            case Qt::Key_Right:
            paddle->moveRight();
            break;
        case Qt::Key_Left:
            paddle->moveLeft();
            break;
        default:
            break;
        }
    }
        return true;
    }
}
