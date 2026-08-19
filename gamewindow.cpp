#include "gamewindow.h"
#include <QKeyEvent>
#include <math.h>
#include <string>
#include <string.h>
#include <sstream>
#include "collision.h"


GameWindow::GameWindow() : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate) {
    installEventFilter(this);
}

GameWindow::~GameWindow() {
    delete assetManager;
    delete basicShader;
    delete particleShader;
    delete timer;
    delete camera;
    delete paddle;
    delete ball;
    wallBricks.clear();
    bricks.clear();
    delete skybox;
    delete particleEffect;
}

void GameWindow::initializeGL() {

    initializeOpenGLFunctions();

    qDebug() << "version: " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    qDebug() << "GSLS version: " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

     lightPos = glm::vec3(0.0, 2.0, 1.0);
     lightColor = glm::vec3(1.0, 1.0, 1.0);

    assetManager = new AssetManager();
    assetManager->loadAssets();

    particleEffect = new ParticleEffect();

    camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));

    //create frame
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

    for (int j = 0; j < 11; j++) {
        for (int k = 0; k < 9; k++) {
            Entity *entityBack = new Entity();
            entityBack->setTextureId(assetManager->blockTextureId);
            entityBack->initialize(-4+k, -5+j, -11.0, 0.0, 0.0);
            wallBricks.push_back(entityBack);
        }
    }

    loadLevels();

    bricks.clear();
    //load level
    bricks = levels.at(0)->entities;

    paddle = new Entity();
    paddle->setTextureId(assetManager->paddleTextureId);
    paddle->initialize(0, -5, 0.0, 0.0);

    ball = new Entity();
    ball->setTextureId(assetManager->ballTextureId);
    ball->setVelocity(1.0);
    ball->initialize(0, 1.0, 0.05, 0.05);

    basicShader = new BasicShader();
    basicShader->compile();

    particleShader = new ParticleShader();
    particleShader->compile();

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

    bool hasVisibleBrick = false;
    for (int i = 0; i < bricks.size(); i++) {
        Entity *e = bricks[i];
        if (e->isVisible()) {
            hasVisibleBrick = true;
            if (haveCollided(e, ball)) {
                ball->dy *= -1.0;
                e->setVisible(false);
                if (!particleEffect->isActive()) {
                    qDebug() << "x: " << e->xPos << ", y:" << e->yPos << endl;
                    particleEffect->setPosition(e->xPos, e->yPos);
                    particleEffect->reset();
                    particleEffect->start();
                }
                break;
            }
        }
    }
    qDebug() << "bricks: " << bricks.size() << endl;
    qDebug() << "levels: " << levels.size() << endl;
    qDebug() << "level 1: " << levels[1]->entities.size() << endl;
    if (!hasVisibleBrick) {
        qDebug() << "bump level " << endl;
        ++levelIndex;
        if (levelIndex > (levelCount - 1)) {
            levelIndex = 0;//TODO: Do Game over
        }
        bricks.clear();
        bricks = levels.at(levelIndex)->entities;
        ball->setVelocity(0.5+levelIndex);
        ball->initialize(0, -2.0, 0.05, 0.05);
    }
    if (particleEffect->isActive()) {
        particleEffect->update();
    }
}

void GameWindow::setViewport(float x, float y, int width, int height) {
    glViewport(x, x, width, height);
}

void GameWindow::renderScene(float x, float y, int worldWidth, int worldHeight) {
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 700.0f);

    bool showPointLight = particleEffect->isActive();
    glm::vec3 pointLightPosition = particleEffect->getPointLightPosition();
    float intensity = particleEffect->getIntensity();


    for (int i = 0; i < wallBricks.size(); i++) {
        wallBricks[i]->render(view, projection, lightPos, lightColor, pointLightPosition, showPointLight, intensity, basicShader);
    }

    for (int i = 0; i < bricks.size(); i++) {
        bricks[i]->render(view, projection, lightPos, lightColor, pointLightPosition, showPointLight, intensity, basicShader);
    }

    paddle->render(view, projection, lightPos, lightColor, pointLightPosition, showPointLight, intensity, basicShader);
    ball->render(view, projection, lightPos, lightColor, pointLightPosition, showPointLight, intensity, basicShader);

    if (particleEffect->isActive()) {
        particleEffect->render(view, projection, lightPos, lightColor, particleShader);
    }

    glm::mat4 skyboxView = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
    skybox->update(skyboxView, projection);//TODO: rename to skybox->render
}

void GameWindow::startParticleEffect() {
    qDebug() << "start particle effect" << endl;
    if (!particleEffect->isActive()) {
        particleEffect->start();
    }
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
        case Qt::Key_P:
           startParticleEffect();
            break;
        case Qt::Key_Escape:
            exit(0);
            break;
        default:
            break;
        }
    }
        return true;
    }
}

void GameWindow::loadLevels() {

    for (int index = 0; index < levelCount; ++index) {

        QString data;
        QString filename(":/assets/level" + QString::number(index+1) + ".txt");

        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            qDebug()<<"file not opened"<<endl;
        }
        else
        {
            qDebug()<<"file opened"<<endl;
            data = file.readAll();
        }

        file.close();

        qDebug()<<data<<endl;

        std::istringstream iss(data.toStdString());

        Level *level = new Level();

        std::string line = "";
        int y = 5.0;
        int row = 0;
        while (std::getline(iss, line)){
            QString aLine = QString::fromStdString(line);
            for (int i = 0; i < aLine.length(); i++) {
                if (aLine[i] == "1") {
                    Entity *targetTop = new Entity();
                    targetTop->setTextureId(assetManager->targetTextureId);
                    targetTop->initialize(-4+i, y, 0.0, 0.0);
                    level->entities.push_back(targetTop);
                }
            }
            --y;
        }
        levels.push_back(level);
    }
}
