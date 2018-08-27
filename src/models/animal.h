#pragma once

#include <string>
#include <vector>

class Animal
{
  private:
    std::string m_image;
    std::string m_commonName;
    std::string m_scientificName;
    std::string m_kingdom;
    std::string m_diet;
    std::string m_lifeSpan;
    std::string m_weight;
    std::string m_relativeSize;
    std::string m_IUNC;
    std::string m_IUNCDesc;

  public:
    Animal();
    Animal(const std::string &image,
           const std::string &commonName,
           const std::string &scientificName,
           const std::string &kingdom,
           const std::string &diet,
           const std::string &lifeSpan,
           const std::string &weight,
           const std::string &relativeSize,
           const std::string &IUNC,
           const std::string &description);
    ~Animal();

    // Getters
    std::string getImage();
    std::string getCommonName();
    std::string getScientificName();
    std::string getKingdom();
    std::string getDiet();
    std::string getLifeSpan();
    std::string getWeight();
    std::string getRelativeSize();
    std::string getIUNC();
    std::string getIUNCDescription();

    // Fill data of an animal from a csv line splited by ,
    void fromCsv(const std::vector<std::string>& tokens);

    const char* toCStr(); 
};
