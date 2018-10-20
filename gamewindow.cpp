#include "gamewindow.h"
#include <math.h>
#include <string>
#include <string.h>


GameWindow::GameWindow() : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate) {

}

GameWindow::~GameWindow() {
    delete basicShader;
    delete timer;
    delete camera;
    delete entity;
}

void GameWindow::initializeGL() {

    initializeOpenGLFunctions();

    qDebug() << "version: " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    qDebug() << "GSLS version: " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

    assetManager = new AssetManager();
    assetManager->loadAssets();

    camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));

    for (int i = 0; i < 11; i++) {
        //left wall
        Entity *entityLeft = new Entity();
        entityLeft->setTextureId(assetManager->blockTextureId);
        entityLeft->initialize(-5, i-5, 0.0, 0.0);
        wallBricks.push_back(entityLeft);
        //right wall
        Entity *entityRight = new Entity();
        entityRight->setTextureId(assetManager->blockTextureId);
        entityRight->initialize(5, i-5, 0.0, 0.0);
        wallBricks.push_back(entityRight);
        //top
        Entity *entityTop = new Entity();
        entityTop->setTextureId(assetManager->blockTextureId);
        entityTop->initialize(i-5, 6, 0.0, 0.0);
        wallBricks.push_back(entityTop);
    }


    entity = new Entity();
    entity->setTextureId(assetManager->blockTextureId);

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
    glClearColor(1.0, 0.3, 0.5, 1.0);

    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    updateScene(0, 0);
    renderScene(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameWindow::updateScene(int worldWidth, int worldHeight) {

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
}
