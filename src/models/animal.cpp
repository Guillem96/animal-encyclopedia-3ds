#include "animal.h"

Animal::Animal() {}

Animal::Animal(const std::string &image,
               const std::string &commonName,
               const std::string &scientificName,
               const std::string &kingdom,
               const std::string &diet,
               const std::string &lifeSpan,
               const std::string &weight,
               const std::string &relativeSize,
               const std::string &IUNC,
               const std::string &description) : m_image(image),
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

// Getters
std::string Animal::getImage() { return m_image; }
std::string Animal::getCommonName() { return m_commonName; }
std::string Animal::getScientificName() { return m_scientificName; }
std::string Animal::getKingdom() { return m_kingdom; }
std::string Animal::getDiet() { return m_diet; }
std::string Animal::getLifeSpan() { return m_lifeSpan; }
std::string Animal::getWeight() { return m_weight; }
std::string Animal::getRelativeSize() { return m_relativeSize; }
std::string Animal::getIUNC() { return m_IUNC; }
std::string Animal::getIUNCDescription() { return m_IUNCDesc; }

void Animal::fromCsv(const std::vector<std::string>& tokens)
{
    m_image = tokens[0];
    m_commonName = tokens[1];
    m_scientificName = tokens[2];
    m_kingdom = tokens[3];
    m_diet = tokens[4];
    m_lifeSpan = tokens[5];
    m_weight = tokens[6];
    m_relativeSize = tokens[7];
    m_IUNC = tokens[8];
    m_IUNCDesc = tokens[9];
}

const char* Animal::toCStr() { return m_commonName.c_str(); } 