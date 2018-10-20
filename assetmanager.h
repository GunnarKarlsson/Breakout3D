#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <QFile>

class AssetManager
{
public:
    AssetManager();
    ~AssetManager();
    void loadAssets();

    unsigned int blockTextureId;
    int blockTexCounter = 0;

    unsigned int paddleTextureId;
    int paddleTexCounter = 1;

    unsigned int ballTextureId;
    int ballTexCounter = 2;

    unsigned int targetTextureId;
    int targetTexCounter = 3;

private:
    void loadTexture(const char* path, unsigned int &textureId);
};

#endif // ASSETMANAGER_H
