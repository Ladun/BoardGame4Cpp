#pragma once

#include <unordered_map>
#include <DawnStar/DawnStar.hpp>

template<typename T> 
class Singleton
{
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
public:
    static T& instance()
    {
        static T singleton_;
        return singleton_;
    }
};

using namespace DawnStar;

class ResourceManager : public Singleton<ResourceManager>
{

public:
    void LoadTexture(std::string name, std::string path);
    void LoadTexturesFromAssets();
    
    Ref<Texture2D> GetTexture(std::string name);

private:
    std::unordered_map<std::string, Ref<Texture2D>> m_TexturesMap;
};