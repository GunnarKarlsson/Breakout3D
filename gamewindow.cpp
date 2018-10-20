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

    paddle = new Entity();
    paddle->setTextureId(assetManager->paddleTextureId, assetManager->paddleTexCounter);
    paddle->initialize(0, -5, 0.0, 0.0);

    ball = new Entity();
    ball->setTextureId(assetManager->ballTextureId, assetManager->ballTexCounter);
    ball->setVelocity(1.0);
    ball->initialize(0, 2, 0.2, 0.2);

    basicShader = new BasicShader();
    basicShader->compile();

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
}

void GameWindow::setViewport(float x, float y, int width, int height) {
    glViewport(x, x, width, height);
}

void GameWindow::renderScene(float x, float y, int worldWidth, int worldHeight) {
    qDebug() << "renderScene" << endl;
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    for (int i = 0; i < wallBricks.size(); i++) {
        wallBricks[i]->render(view, projection, basicShader);
    }

    paddle->render(view, projection, basicShader);
    ball->render(view, projection, basicShader);
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
