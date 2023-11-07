
#pragma once

#include <DawnStar/DawnStar.hpp>

using namespace DawnStar;

class Utils
{
public:
    static std::vector<std::string> SplitPath(const std::string path, char sep) 
    {
        std::vector<std::string> out;
        std::stringstream stream(path);
        std::string temp;

        while (std::getline(stream, temp, sep)) 
        {   
            out.push_back(temp);
        }

        return out;
    }
    
    template<typename ... Args> 
    static std::string string_format(const std::string& format, Args ... args)    
    {
        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0' 
        if (size <= 0) {
            throw std::runtime_error("Error during formatting.");
        }
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside }
    }

    static glm::vec2 ToScreenCoord(glm::vec2 mousePos)
    {
        auto windowWidth = Application::Get().GetWindow().GetWidth();
        auto windowHeight = Application::Get().GetWindow().GetHeight();
        return {mousePos.x - windowWidth / 2, windowHeight - mousePos.y - windowHeight / 2};
    }

    static glm::vec2 ToScreenToWorldCoord(glm::vec2 screenPos, Entity cameraEntity)
    {
		auto viewProjection = cameraEntity.GetComponent<CameraComponent>().Cam.GetProjection() * 
                              glm::inverse(cameraEntity.GetWorldTransform());
        auto windowWidth    = Application::Get().GetWindow().GetWidth();
        auto windowHeight   = Application::Get().GetWindow().GetHeight();
        // Get inverse projection of camera's ViewProjection Matrix
        viewProjection = glm::inverse(viewProjection);

        // ScreenPos 자체가 중앙이 0, 좌하단이 -0.5, 우하단이 0.5로 설정이 되어 2를 곱해준다.
        glm::vec4 ret = {(screenPos.x / windowWidth) * 2.0f, 
                         (screenPos.y / windowHeight) * 2.0f,
                         0.0f, 1.0f};

        ret = viewProjection * ret;

        return {ret.x, ret.y};
    }
};