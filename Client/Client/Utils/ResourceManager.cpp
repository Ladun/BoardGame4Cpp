#include "ResourceManager.hpp"

#include "Utils.hpp"

#include <filesystem>



void ResourceManager::LoadTexture(std::string name, std::string path)
{
    if(!std::filesystem::exists(path))
    {
        DS_APP_ERROR("File path '{0}' does not exist!", path);
        return;
    }

    auto texture = DawnStar::CreateRef<DawnStar::Texture2D>(path);    
    m_TexturesMap.insert({name, texture});

    DS_APP_DEBUG("Texture '{0}' load from '{1}'", name, path);
}

void ResourceManager::LoadTexturesFromAssets()
{
    const std::string assetPath = "assets/resources";
    for(const auto& file : std::filesystem::recursive_directory_iterator(assetPath))
    {
        std::string path = file.path();

        if(std::filesystem::is_directory(path))
        {
            continue;
        }

        LoadTexture(path.substr(assetPath.length() + 1, path.length()), path);
    }
}

DawnStar::Ref<DawnStar::Texture2D> ResourceManager::GetTexture(std::string name)
{
    auto iter = m_TexturesMap.find(name);
    if(iter != m_TexturesMap.end())
    {
        return iter->second;
    }

    return nullptr;
}
