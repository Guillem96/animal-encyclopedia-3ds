#pragma once

#include <map> 
#include <string>

class AnimalImageMapper
{
    private:
        std::map<std::string, int> m_imgIds;

        void fillMap(const std::string& path);
    public:
        AnimalImageMapper(const std::string& path);
        ~AnimalImageMapper();

        int getImageId(const std::string& imageName);
};