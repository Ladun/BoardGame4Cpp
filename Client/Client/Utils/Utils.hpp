
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
};