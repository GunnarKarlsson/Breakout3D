#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <QString>
#include <vector>

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

    unsigned int skyboxTextureId;

private:
    unsigned char *loadImageData(const QString &path, int *width, int *height, int *nrChannels, int desiredChannels);
    void loadTexture(const QString &path, unsigned int &textureId);
    unsigned int loadSkyboxTextures(const std::vector<QString> &faces);
};

#endif // ASSETMANAGER_H
