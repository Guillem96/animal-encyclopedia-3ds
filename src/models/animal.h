#pragma once

#include <string>

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
  Animal(std::string image, 
          std::string commonName, 
          std::string scientificName, 
          std::string kingdom, 
          std::string diet, 
          std::string lifeSpan, 
          std::string weight, 
          std::string relativeSize, 
          std::string IUNC, 
          std::string description);
  ~Animal();

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
};
