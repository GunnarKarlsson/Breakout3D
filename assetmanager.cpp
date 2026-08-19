#include "assetmanager.h"
#include "common.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <QByteArray>
#include <QFile>


AssetManager::AssetManager(){}

AssetManager::~AssetManager() {}

void AssetManager::loadAssets() {
    loadTexture(":/Textures/minecraft_bricks.png", blockTextureId);
    loadTexture(":/Textures/pink.png", paddleTextureId);
    loadTexture(":/Textures/rainbow.png", ballTextureId);
    loadTexture(":/Textures/creeper.png", targetTextureId);

    std::vector<QString> faces {
        ":/Textures/SKY_LEFT.png",
        ":/Textures/SKY_RIGHT.png",
        ":/Textures/SKY_UP.png",
        ":/Textures/SKY_DOWN.png",
        ":/Textures/SKY_FRONT.png",
        ":/Textures/SKY_BACK.png"
    };
    skyboxTextureId = loadSkyboxTextures(faces);
}

unsigned char *AssetManager::loadImageData(const QString &path, int *width, int *height, int *nrChannels, int desiredChannels) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open texture" << path;
        return nullptr;
    }
    const QByteArray bytes = file.readAll();
    return stbi_load_from_memory(
        reinterpret_cast<const unsigned char*>(bytes.constData()),
        bytes.size(),
        width, height, nrChannels, desiredChannels);
}

void AssetManager::loadTexture(const QString &path, unsigned int &textureId) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = loadImageData(path, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        qDebug() << "Texture loaded successfully" << path;
    }
    else
    {
        qDebug() << "Failed to load texture" << path;
    }
    stbi_image_free(data);
}

unsigned int AssetManager::loadSkyboxTextures(const std::vector<QString> &faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = loadImageData(faces[i], &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            qDebug() << "Skybox texture loaded successfully" << faces[i];
        }
        else
        {
            qDebug() << "Skybox texture failed to load" << faces[i];
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
