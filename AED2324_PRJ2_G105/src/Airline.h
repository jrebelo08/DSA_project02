#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <functional>
#include <utility>
using namespace std;

/**
 * @brief Represents an airline entity with specific attributes.
 *
 * The class defines the properties of an airline such as its code, name,
 * callsign, and country it is based in. Additionally, it provides methods to access and
 * modify these properties.
 */
class Airline {
private:

/**
     * @brief Unique code representing the airline.
     */
    string code;

    /**
     * @brief Full name of the airline.
     */
    string name;

    /**
     * @brief Callsign associated with the airline.
     */
    string callsign;

    /**
     * @brief Country where the airline is based.
     */
    string country;

    /**
     * @brief Friend declaration for the hash struct to access private members.
     */
    friend struct hash<Airline>;

public:
    Airline(string  code, string  name, string  callsign, string  country);

    string getCode() const;
    string getName() const;
    string getCallsign() const;
    string getCountry() const;

    void setCode(const string& newCode);
    void setName(const string& newName);
    void setCallsign(const string& newCallsign);
    void setCountry(const string& newCountry);

    bool operator==(const Airline& other) const;


    bool operator<(const Airline& other) const;

    Airline();
};

/**
 * @brief Hashing struct for Airline objects.
 *
 * This struct provides a hash function for Airline objects by combining
 * hashes of its individual attributes.
 */
struct AirlineHash {
    /**
     * @brief Computes the hash value for a given Airline object.
     *
     * @param airline The Airline object to compute the hash for.
     * @return A size_t value representing the hash of the airline.
     */
    size_t operator()(const Airline& airline) const {
        return hash<string>()(airline.getCode())
               ^ hash<string>()(airline.getName())
               ^ hash<string>()(airline.getCallsign())
               ^ hash<string>()(airline.getCountry());
    }
};

#endif // AIRLINE_H
