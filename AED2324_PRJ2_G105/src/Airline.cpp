#include "Airline.h"



Airline::Airline() : code(""), name(""), callsign(""), country("") {}

/**
 * @brief Constructs a new Airline object.
 * @param code The airline's code.
 * @param name The airline's name.
 * @param callsign The airline's callsign.
 * @param country The country the airline is based in.
 */
Airline::Airline(string code, string name, string callsign, string country) :
        code(std::move(code)),
        name(std::move(name)),
        callsign(std::move(callsign)),
        country(std::move(country)) {}

/**
 * @brief Gets the airline's code.
 * @return The airline's code.
 */
string Airline::getCode() const {
    return code;
}

/**
 * @brief Gets the airline's name.
 * @return The airline's name.
 */
string Airline::getName() const {
    return name;
}

/**
 * @brief Gets the airline's callsign.
 * @return The airline's callsign.
 */
string Airline::getCallsign() const {
    return callsign;
}

/**
 * @brief Gets the country the airline is based in.
 * @return The country the airline is based in.
 */
string Airline::getCountry() const {
    return country;
}

/**
 * @brief Sets the airline's code.
 * @param newCode The new code.
 */
void Airline::setCode(const string& newCode) {
    code = newCode;
}

/**
 * @brief Sets the airline's name.
 * @param newName The new name.
 */
void Airline::setName(const string& newName) {
    name = newName;
}

/**
 * @brief Sets the airline's callsign.
 * @param newCallsign The new callsign.
 */
void Airline::setCallsign(const string& newCallsign) {
    callsign = newCallsign;
}

/**
 * @brief Sets the country the airline is based in.
 * @param newCountry The new country.
 */
void Airline::setCountry(const string& newCountry) {
    country = newCountry;
}

/**
 * @brief Compares this airline to another for equality.
 * @param other The other airline.
 * @return True if the airlines are equal, false otherwise.
 */
bool Airline::operator==(const Airline& other) const {
    return code == other.code &&
           name == other.name &&
           callsign == other.callsign &&
           country == other.country;
}

/**
 * @brief Compares this airline to another.
 * @param other The other airline.
 * @return True if this airline's code is less than the other's, false otherwise.
 */
bool Airline::operator<(const Airline& other) const {
    return this->getCode() < other.getCode();
}