#include "animal.h"

Animal::Animal() {}

Animal::Animal(std::string image, 
          std::string commonName, 
          std::string scientificName, 
          std::string kingdom, 
          std::string diet, 
          std::string lifeSpan, 
          std::string weight, 
          std::string relativeSize, 
          std::string IUNC, 
          std::string description) : 
          m_image(image),
          m_commonName(commonName),
          m_scientificName(scientificName),
          m_kingdom(kingdom),
          m_diet(diet),
          m_lifeSpan(lifeSpan),
          m_weight(weight),
          m_relativeSize(relativeSize),
          m_IUNC(IUNC),
          m_IUNCDesc(description) {}

Animal::~Animal() {}