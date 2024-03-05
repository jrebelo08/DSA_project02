#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
using namespace std;

/**
 * @brief Represents an airport entity with specific attributes.
 *
 * This class defines the properties of an airport such as its unique code,
 * name, city, country, latitude, and longitude. The class provides methods
 * to access and modify these properties. Additionally, it overloads certain
 * operators for comparison purposes.
 */
class Airport {
private:
    /**
     * @brief Unique code representing the airport.
     */
    string code;

    /**
     * @brief Full name of the airport.
     */
    string name;

    /**
     * @brief City where the airport is located.
     */
    string city;

    /**
     * @brief Country where the airport is located.
     */
    string country;

    /**
     * @brief Latitude coordinate of the airport.
     */
    double latitude;

    /**
     * @brief Longitude coordinate of the airport.
     */
    double longitude;

public:
    Airport(string code, string name, string city, string country, double latitude, double longitude);
    Airport();

    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

    void setCode(const string& newCode);
    void setName(const string& newName);
    void setCity(const string& newCity);
    void setCountry(const string& newCountry);
    void setLatitude(double newLatitude);
    void setLongitude(double newLongitude);

    bool operator==(const Airport& other) const;
    bool operator<(const Airport& other) const;

};

#endif // AIRPORT_H
