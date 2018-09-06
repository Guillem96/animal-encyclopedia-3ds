#include "AnimalImageMapper.h"

AnimalImageMapper::AnimalImageMapper(const std::string &path)
{
    fillMap(path);
}

AnimalImageMapper::~AnimalImageMapper()
{
}

int AnimalImageMapper::getImageId(const std::string& imageName)
{
    return m_imgIds[imageName];
}

void AnimalImageMapper::fillMap(const std::string& path)
{
    FILE *f;
    f = fopen(path.c_str(), "r");

    if (f != NULL)
    {
        printf("Reading: %s\n", path.c_str());
        
        char line[512];
        int id = 0;
        fgets(line, 512, f); // Skip first line

        while (fgets(line, 512, f) != NULL)
        {
            std::string name(line);
            name = name.erase(name.find_last_not_of("\t\n\v\f\r ") + 1);
            m_imgIds[name] = id;
            id++;
        }
        fclose(f);
    }
    else
    {
        printf("ERROR: Reading file %s\n", path.c_str());
    }
}
