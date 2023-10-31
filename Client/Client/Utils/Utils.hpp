#pragma once

#include <vector>
#include <string>
#include <sstream>


namespace Utils
{
    std::vector<std::string> SplitPath(const std::string path, char sep) 
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
}