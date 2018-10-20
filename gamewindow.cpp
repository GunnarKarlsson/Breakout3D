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

    entity = new Entity();

    basicShader = new BasicShader();
    basicShader->compile();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void GameWindow::resizeGL(int width, int height) {

}

void GameWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 0.3, 0.5, 1.0);
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::ortho(x, (float)worldWidth, (float)worldHeight, y, (float)NEAR_LIMIT, (float)FAR_LIMIT);

    entity->render(view, projection, basicShader);
}
