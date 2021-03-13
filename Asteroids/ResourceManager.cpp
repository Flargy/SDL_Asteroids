#include "ResourceManager.h"

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance; // Guaranteed to be destroyed.
                                     // Instantiated on first use.
    return instance;
}

void ResourceManager::AddFont(std::string key, std::string path, int fontSize)
{
    auto ptr = std::make_shared<Font>(path, fontSize);

    _fonts[key] = ptr;
}
