#include "Airport.h"

/**
 * @brief Constructs an Airport object with the specified attributes.
 *
 * @param code Unique code representing the airport.
 * @param name Full name of the airport.
 * @param city City where the airport is located.
 * @param country Country where the airport is located.
 * @param latitude Latitude coordinate of the airport.
 * @param longitude Longitude coordinate of the airport.
 */
Airport::Airport(string code, string name, string city, string country, double latitude, double longitude)
        : code(std::move(code)), name(std::move(name)), city(std::move(city)), country(std::move(country)), latitude(latitude), longitude(longitude) {}

/**
 * @brief Default constructor initializing all attributes to default values.
 */
Airport::Airport()
        : code(""), name(""), city(""), country(""), latitude(0.0), longitude(0.0) {}

/**
 * @brief Retrieves the unique code of the airport.
 *
 * @return A string representing the code of the airport.
 */
string Airport::getCode() const {
    return code;
}

/**
 * @brief Retrieves the full name of the airport.
 *
 * @return A string representing the name of the airport.
 */
string Airport::getName() const {
    return name;
}

/**
 * @brief Retrieves the city where the airport is located.
 *
 * @return A string representing the city of the airport.
 */
string Airport::getCity() const {
    return city;
}

/**
 * @brief Retrieves the country where the airport is located.
 *
 * @return A string representing the country of the airport.
 */
string Airport::getCountry() const {
    return country;
}

/**
 * @brief Retrieves the latitude coordinate of the airport.
 *
 * @return A double value representing the latitude of the airport.
 */
double Airport::getLatitude() const {
    return latitude;
}

/**
 * @brief Retrieves the longitude coordinate of the airport.
 *
 * @return A double value representing the longitude of the airport.
 */
double Airport::getLongitude() const {
    return longitude;
}

/**
 * @brief Sets a new unique code for the airport.
 *
 * @param newCode A string representing the new code for the airport.
 */
void Airport::setCode(const string& newCode) {
    code = newCode;
}

/**
 * @brief Sets a new full name for the airport.
 *
 * @param newName A string representing the new name for the airport.
 */
void Airport::setName(const string& newName) {
    name = newName;
}

/**
 * @brief Sets a new city for the airport.
 *
 * @param newCity A string representing the new city for the airport.
 */
void Airport::setCity(const string& newCity) {
    city = newCity;
}

/**
 * @brief Sets a new country for the airport.
 *
 * @param newCountry A string representing the new country for the airport.
 */
void Airport::setCountry(const string& newCountry) {
    country = newCountry;
}

/**
 * @brief Sets a new latitude coordinate for the airport.
 *
 * @param newLatitude A double value representing the new latitude for the airport.
 */
void Airport::setLatitude(double newLatitude) {
    latitude = newLatitude;
}

/**
 * @brief Sets a new longitude coordinate for the airport.
 *
 * @param newLongitude A double value representing the new longitude for the airport.
 */
void Airport::setLongitude(double newLongitude) {
    longitude = newLongitude;
}

/**
 * @brief Overloaded equality operator for comparing airports.
 *
 * @param other Another Airport object to compare with.
 * @return true if both airports are equal; false otherwise.
 */
bool Airport::operator==(const Airport& other) const {
    return code == other.code &&
           name == other.name &&
           city == other.city &&
           country == other.country &&
           latitude == other.latitude &&
           longitude == other.longitude;
}

/**
 * @brief Overloaded less than operator for ordering airports based on their codes.
 *
 * @param other Another Airport object to compare with.
 * @return true if the current airport's code is less than the other; false otherwise.
 */
bool Airport::operator<(const Airport& other) const {
    return code < other.code;
}
