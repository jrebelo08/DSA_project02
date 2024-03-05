#include <iostream>
#include <limits>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <cmath>
#include "reader.h"
#include "App.h"

void StatisticsMenu(Graph<Airport> graph);

void displayGlobalNumbers(const Graph<Airport>& graph);

void displayFlightsFromAirport(const Graph<Airport>& graph);

void displayCountriesFromAirportCity(const Graph<Airport>& graph);

void displayReachableDestinationsXStops(Graph<Airport>& graph);

void calculateFlights(const Graph<Airport>& graph);

void displayDestinations(Graph<Airport>& graph);

void displayMaxStopsTrip(const Graph<Airport>& graph);

void displayEssentialAirports(const Graph<Airport>& graph);

void displayTopKAirTraffic(Graph<Airport>& graph);

void displaySourceMenu(const Graph<Airport> &graph,
                       const unordered_map<string, vector<Vertex<Airport> *>> &cityToAirportsMap,
                       const unordered_map<string, Vertex<Airport> *> &airportMap, const string& filterOption);


void displayDestinationMenu(const Graph<Airport> &graph, const unordered_map<string, vector<Vertex<Airport> *>> &map,
                            const unordered_map<string, Vertex<Airport> *> &airportMap,
                            const vector<Vertex<Airport> *> &possibleSources, const string& filterOption);

void findPaths(const Graph<Airport>& graph, const unordered_map<string, vector<Vertex<Airport> *>> &map,
               const unordered_map<string, Vertex<Airport> *> &map1, const vector<Vertex<Airport> *> &possibleSources,
               const vector<Vertex<Airport> *>& possibleDestinations);

void displayFilterMenu(const Graph<Airport> &graph, const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,
                       const unordered_map<string, Vertex<Airport> *> &cityToAirportMap);

void findPathsFiltered(const Graph<Airport>& graph,
                       const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,
                       const unordered_map<string, Vertex<Airport> *> &cityToAirportMap,
                       const vector<Vertex<Airport> *> &possibleSources,
                       const vector<Vertex<Airport> *> &possibleDestinations,
                       const set<string>& preferredAirlines);

void findPathsFilteredByAirlineChanges(const Graph<Airport>& graph,
                                       const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,
                                       const unordered_map<string, Vertex<Airport> *> &cityToAirportMap,
                                       const vector<Vertex<Airport> *> &possibleSources,
                                       const vector<Vertex<Airport> *> &possibleDestinations);


void findPathsFiltered2(const Graph<Airport>& graph,
                        const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,
                        const unordered_map<string, Vertex<Airport> *> &cityToAirportMap,
                        const vector<Vertex<Airport> *> &possibleSources,
                        const vector<Vertex<Airport> *> &possibleDestinations,
                        const set<string>& preferredAirlines);

using namespace std;

/**
 * @brief This function represents the main menu of the flight system application.
 *
 * The mainMenu function performs the following tasks:
 * 1. Loads data related to airports, airlines, and flights using the Reader class.
 * 2. Displays a user interface with multiple options for the user to choose from.
 * 3. Based on the user's choice, it either:
 *      - Directs the user to a statistics menu.
 *      - Displays a filter menu to find the best flight option.
 *      - Exits the main menu.
 *
 * @return int Returns 0 upon successful execution of the menu system.
 */
int mainMenu(){
    cout << "Loading...";

    Reader reader;
    reader.readAndParseAirports();
    reader.readAndParseAirlines();
    reader.readAndParseFlights();
    Graph graph = reader.getGraph();
    unordered_map<string, Vertex<Airport>*> airportMap = reader.getAirportMap();
    unordered_map<string, Airline> airlineMap = reader.getAirlineMap();
    unordered_map<string, vector<Vertex<Airport>*>> cityToAirportsMap = reader.getCityToAirportsMap();

    string choice;
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "\n-----------------------------\n";
        cout << "     Welcome to Main Menu       \n";
        cout << "-----------------------------\n";
        cout << "Enter the number of the option that suits your needs:\n";
        cout << "1. Search for flight/airport statistics\n";
        cout << "2. Find the best flight option for you\n";
        cout << "e. Exit\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {
            case '1':
                StatisticsMenu(graph);
                break;
            case '2':
                displayFilterMenu(graph, cityToAirportsMap, airportMap);
                break;
            case 'e':
                cout << "Exiting menu system...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }

    return 0;
}


/**
 * @brief This function represents the statistics menu of the flight system application.
 *
 * @param graph The Graph object.
 *
 * The menu options available in this function are as follows:
 * 1. Display global airport and flight availability statistics.
 * 2. Show flights from an airport and the airlines operating there.
 * 3. Explore flights per city/airline.
 * 4. Count countries served by a specific airport/city.
 * 5. View destinations available from a chosen airport (airports, cities, or countries).
 * 6. Find reachable destinations from an airport with a maximum number of layovers.
 * 7. Find the trip(s) with the greatest number of stops in between.
 * 8. Identify the top airport(s) with the greatest air traffic capacity.
 * 9. Identify essential airports for network circulation.
 * b. Go back to the previous menu.
 *
 * @return void This function does not return any value upon completion as it is a menu-based system.
 */
void StatisticsMenu(Graph<Airport> graph) {

    string choice;
    bool back = false;

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "            Statistics Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Display global airport and flight availability statistics\n";
        cout << "2. Show flights from an airport and the airlines operating there\n";
        cout << "3. Explore flights per city/airline\n";
        cout << "4. Count countries served by a specific airport/city\n";
        cout << "5. View destinations available from a chosen airport (airports, cities, or countries)\n";
        cout << "6. Find reachable destinations from an airport with a max number of layovers (airports, cities, or countries)\n";
        cout << "7. Find the trip(s) with the greatest number of stops in between\n";
        cout << "8. Identify the top airport(s) with the greatest air traffic capacity\n";
        cout << "9. Identify essential airports for network circulation\n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "(Note : The chosen source airport/city/airline is always included in searches)" << endl;
        cout << "Your choice: ";

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                displayGlobalNumbers(graph);
                break;
            case '2':
                displayFlightsFromAirport(graph);
                break;
            case '3':
                calculateFlights(graph);
                break;
            case '4':
                displayCountriesFromAirportCity(graph);
                break;
            case '5':
                displayDestinations(graph);
                break;
            case '6':
                displayReachableDestinationsXStops(graph);
                break;
            case '7':
                displayMaxStopsTrip(graph);
                break;
            case '8':
                displayTopKAirTraffic(graph);
                break;
            case '9':
                displayEssentialAirports(graph);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

/**
 * @brief Identify the top-K airports with the greatest number of flights.
 *
 * The function allows users to specify a value K to display the airports with
 * the highest air traffic capacity, determined by the total number of flights.
 * Calculates the sum of each Airport's in-degree and out-degree
 * Place the Airports in a vector, sorting them by the sum of indegree and outdegree
 *
 * @param graph A reference to the Graph.
 *
 * @return void This function does not return any value upon completion.
 *
 * @timecomplexity O(V log V) because of std::sort()
 */
void displayTopKAirTraffic(Graph<Airport> &graph) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Enter the amount of Airports to display : ";
        string choice;
        getline(cin, choice);

        if (choice == "b") {
            cout << "Going back... ";
            break;
        }

        try {
            int maxAirports = stoi(choice);
            if (maxAirports >= 0) {
                cout << "\n---------------------------------------------------------\n";
                cout << "            Top-K Airports by Number of Flights      \n";
                cout << "---------------------------------------------------------\n";

                unordered_map<string, size_t> inDegrees;
                unordered_map<string, size_t> outDegrees;
                vector<pair<string, size_t>> result;

                for (auto vertex : graph.getVertexSet()) {
                    string vertexCode = vertex->getInfo().getCode();
                    outDegrees[vertexCode] = vertex->getAdj().size();

                    for (const auto& edge : vertex->getAdj()) {
                        string destCode = edge.getDest()->getInfo().getCode();
                        inDegrees[destCode]++;
                    }
                }

                for (const auto& entry : outDegrees) {
                    result.emplace_back(entry.first, entry.second + inDegrees[entry.first]);
                }


                sort(result.begin(), result.end(),
                     [](const auto& a, const auto& b) {
                    return a.second > b.second;
                });

                for (int i = 0; i < min(maxAirports, static_cast<int>(result.size())); ++i) {
                    cout << "Rank: " << i + 1 << "\n";
                    cout << "Airport Code: " << result[i].first << "\n";
                    cout << "Number of Flights: " << result[i].second << "\n";
                    cout << "---------------------------------------------------------\n";
                }
            } else {
                cout << "\nInvalid input. Maximum number of Airports should be a non-negative integer.\n";
            }
        } catch (invalid_argument&) {
            cout << "\nInvalid input. Please enter a valid non-negative integer or 'b' to go back.\n";
        }
        catch (out_of_range&) {
            cout << "\nInvalid input. The number you entered is too high.\n";
        }
    }
}

/**
 * @brief Performs BFS from a given airport to determine reachable destinations.
 *
 * @param g Reference to the graph.
 * @param source The source airport from which BFS starts.
 * @timecomplexity O(V + E)
 */
void nodesAtDistanceBFS2(Graph<Airport>& g, const Airport &source){

    set<string> aeroportos;
    set<pair<string,string>> cidadespaises;
    set<string> paises;

    for (auto v : g.getVertexSet()){
        v->setVisited(false);
    }

    auto v = g.findVertex(source);
    queue<Vertex<Airport>*> q;
    q.emplace(v);
    v->setVisited(true);

    while(!q.empty()){
        auto current = q.front();
        q.pop();

        aeroportos.insert(current->getInfo().getCode());
        cidadespaises.insert(make_pair(current->getInfo().getCity(),current->getInfo().getCountry()));
        paises.insert(current->getInfo().getCountry());



        for (const auto& Edge : current->getAdj()){
            auto neighbour = Edge.getDest();
            if (!neighbour->isVisited()){
                q.emplace(neighbour);
                neighbour->setVisited(true);
            }
        }
    }

    cout << "----------------------------------------\n";
    cout << "Starting from the airport: " << source.getName() << " (Code: " << source.getCode() << ")\n";
    cout << "----------------------------------------\n";
    cout << "You can reach the following amounts of different destinations:" << endl;
    cout << "----------------------------------------\n";
    cout << "Airports: " << aeroportos.size() << "\n";
    cout << "Cities: " << cidadespaises.size() << "\n";
    cout << "Countries: " << paises.size() << "\n";
    cout << "----------------------------------------\n";
}

/**
 * @brief Performs BFS from a given airport up to a specified distance to determine reachable destinations.
 *
 * @param g Reference to the graph.
 * @param source The source airport from which BFS starts.
 * @param distancia The maximum number of layovers allowed for BFS traversal.
 * @timecomplexity O(V + E)
 */
void nodesAtDistanceBFS(Graph<Airport>& g,const Airport &source,const string& distancia){

    set<string> aeroportos;
    set<pair<string,string>> cidadespaises;
    set<string> paises;

    for (auto v : g.getVertexSet()){
        v->setVisited(false);
    }

    int k = stoi(distancia);
    auto v = g.findVertex(source);
    queue<pair<Vertex<Airport>*,int>> q;
    q.emplace(v,0);
    v->setVisited(true);

    while(!q.empty()){
        auto current = q.front().first;
        int distance = q.front().second;
        q.pop();

        if (distance <= k){
            aeroportos.insert(current->getInfo().getCode());
            cidadespaises.insert(make_pair(current->getInfo().getCity(),current->getInfo().getCountry()));
            paises.insert(current->getInfo().getCountry());
        }
        else{
            break;
        }

        for (const auto& Edge : current->getAdj()){
            auto neighbour = Edge.getDest();
            if (!neighbour->isVisited()){
                q.emplace(neighbour,distance + 1);
                neighbour->setVisited(true);
            }
        }
    }

    cout << "----------------------------------------\n";
    cout << "Starting from the airport: " << source.getName() << " (Code: " << source.getCode() << ")\n";
    cout << "----------------------------------------\n";
    cout << "You can reach the following amounts of different destinations within " << distancia << " layovers:\n";
    cout << "----------------------------------------\n";
    cout << "Airports: " << aeroportos.size() << "\n";
    cout << "Cities: " << cidadespaises.size() << "\n";
    cout << "Countries: " << paises.size() << "\n";
    cout << "----------------------------------------\n";
}



/**
 * @brief Allows users to input a source airport and a maximum number of stops
 * to determine the number of reachable destinations (airports, cities, or countries) from that source.
 * The function uses Breadth-First Search (BFS) to traverse the graph up to the specified number of stops.
 *
 * @param graph Reference to the graph representing airports and their connections.
 *
 * @timecomplexity O(V * (V + E))
 */
void displayReachableDestinationsXStops(Graph<Airport>& graph) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Enter the source airport's Name or Code ('b' to go back): ";
        string source;
        getline(cin, source);

        if (source == "b") {
            cout << "Going back... ";
            break;
        }

        bool airportFound = false;

        for (auto airport: graph.getVertexSet()) {
            if (airport->getInfo().getCode() == source || airport->getInfo().getName() == source) {
                airportFound = true;
                Airport aeroporto = airport->getInfo();
                while (true) {
                    cout << "Enter the maximum amount of stops: ";
                    string distance;
                    getline(cin, distance);

                    if (distance == "b") {
                        cout << "Going back... ";
                        break;
                    }

                    nodesAtDistanceBFS(graph, aeroporto, distance);

                    cout << "Enter any key to go back to the previous step.";
                    char choice;
                    cin >> choice;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (choice != '\0') {
                        break;
                    }
                }
            }

        }
        if (!airportFound) {
            cout << "Airport '" << source << "' not found. Please enter a valid airport name or code.\n";
        }

    }
}

/**
 * @brief Allows users to input either an airport's name or code or a city's name to display
 * the number of different countries to which flights are available from the specified airport or all airports in a city in only one step.
 *
 * @param graph Reference to the graph representing airports, cities, and their connections.
 *
 */
void displayCountriesFromAirportCity(const Graph<Airport>& graph) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Choose an option:\n";
        cout << "1. Enter airport's Name or Code\n";
        cout << "2. Enter city's Name\n";
        cout << "('b' to go back): ";

        string option;
        getline(cin, option);

        bool breaks = false;
        if (option == "b") {
            cout << "Going back... ";
            breaks = true;
            break;
        }

        if (option != "1" && option != "2") {
            cout << "Invalid option. Please enter '1', '2', or 'b'.\n";
            continue;
        }

        cout << "Enter the " << (option == "1" ? "airport's Name or Code" : "city's Name") << ": ";
        string input;
        getline(cin, input);

        bool found = false;

        for (auto vertex : graph.getVertexSet()) {
            if ((option == "1" && (vertex->getInfo().getCode() == input || vertex->getInfo().getName() == input)) ||
                (option == "2" && vertex->getInfo().getCity() == input)) {
                found = true;

                if (option == "1"){
                    set<string> countries;
                    for (const auto& edges : vertex->getAdj()){
                        countries.insert(edges.getDest()->getInfo().getCountry());
                    }
                    cout << "-----------------------------------------\n";
                    cout << "Airport: " << vertex->getInfo().getName() << " (" << vertex->getInfo().getCode() << ") ";
                    cout << "flies to " << countries.size() << " different countries." << endl;
                }

                if (option == "2"){
                    set<string> countries;
                    for (auto vertex2 : graph.getVertexSet()){
                        if(vertex2->getInfo().getCity() == input)
                        for (const auto& edges : vertex2->getAdj()){
                            countries.insert(edges.getDest()->getInfo().getCountry());
                        }
                    }
                    cout << "-----------------------------------------\n";
                    cout << "Airports in: " << vertex->getInfo().getCity() << endl;
                    cout << "have flights to " << countries.size() << " different countries." << endl;
                }


                cout << "Enter any key to go back to the previous step.";
                char choice;
                cin >> choice;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice != '\0') {
                    break;
                }
            }
        }

        if (breaks){
            break;
        }

        if (!found) {
            cout << (option == "1" ? "Airport" : "City") << " '" << input << "' not found or 'b' option selected. ";
            cout << " Going back to the previous step.";
        }
    }
}

/**
 * @brief Allows users to input an airport's name or code to display detailed flight information from that airport.
 * The function lists all the destinations reachable from the specified airport, along with the respective airlines operating those routes.
 * Additionally, it provides counts for the total number of flights and the distinct airlines serving those flights.
 *
 * @param graph Reference to the graph representing airports and their respective flight connections.
 *
 * @timecomplexity  O(V + E)
 */
void displayFlightsFromAirport(const Graph<Airport>& graph) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Enter the airport's Name or Code ('b' to go back): ";
        string Input;
        getline(cin, Input);

        if (Input == "b") {
            cout << "Going back... ";
            break;
        }

        bool airportFound = false;

        for (auto airport : graph.getVertexSet()) {
            if (airport->getInfo().getCode() == Input || airport->getInfo().getName() == Input) {
                airportFound = true;

                cout << "-----------------------------------------\n";
                cout << "Airport: " << airport->getInfo().getName() << " (" << airport->getInfo().getCode() << ")\n";

                size_t totalFlights = 0;
                set<string> airlines;

                for (const auto& flight : airport->getAdj()) {
                    cout << "-----------------------------------" << endl;
                    cout << "Destination: " << flight.getDest()->getInfo().getName() << endl;
                    cout << "  Airline: " << flight.getWeight().getName() << endl;
                    totalFlights++;
                    airlines.insert(flight.getWeight().getName());
                }

                cout << "-----------------------------------" << endl;
                cout << "Number of flights: " << totalFlights << endl;
                cout << "Number of different airlines: " << airlines.size() << endl;

                cout << "Enter any key to go back to the previous step.";
                char choice;
                cin >> choice;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice != '\0') {
                    break;
                }
            }
        }

        if (!airportFound) {
            cout << "Airport '" << Input << "' not found. Please enter a valid airport name or code.\n";
        }
    }
}

/**
 * @brief Provides a summary of global statistics related to the airports and flights in the graph.
 *
 * @param graph Reference to the graph representing airports and their respective flight connections.
 *
 *@timecomplexity  O(V + E)
 */
void displayGlobalNumbers(const Graph<Airport>& graph) {
    while (true) {
        cout << "-----------------------------------------\n";
        cout << "Global Number of Airports: " << graph.getVertexSet().size() << endl;

        size_t flightCount = 0;

        for (auto vertex : graph.getVertexSet()) {
            cout << "Airport Name: " << setw(50) << left << vertex->getInfo().getName();
            cout << "Number of Flights: " << vertex->getAdj().size() << endl;
            flightCount += vertex->getAdj().size();
        }
        cout << "----------------------------------------" << endl;
        cout << "Total number of airports: " << graph.getVertexSet().size() << endl;
        cout << "Total number of Available Flights: " << flightCount << endl;

        cout << "Enter any key to go back to the previous step.";
        char choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice != '\0') {
            break;
        }
    }
}

/**
 * @brief Provides functionality to calculate the number of flights based on user-selected criteria.
 * Users can choose to calculate either the total number of flights per city or per airline.
 * The function iterates over the graph's vertices and edges.
 * And calculates the given Airport(Vertex)/City (possibly multiple vertexes) out-degree.
 *
 * @param graph Reference to the graph representing airports, cities, airlines, and their respective connections.
 *
 * @timecomplexity O(V) for option 1 and O(V + E) for option 2
 */
void calculateFlights(const Graph<Airport>& graph) {
    int choice;
    string name;

    while (true) {
        cout << "Enter 1 to calculate flights per city, or 2 to calculate flights per airline (or any other key to go back): ";
        cin >> choice;

        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Going back to the previous menu." << endl;
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter the name of the city: ";
            getline(cin, name);

            int flightsPerCity = 0;

            for (Vertex<Airport>* vertex : graph.getVertexSet()) {
                if (vertex->getInfo().getCity() == name) {
                    flightsPerCity += vertex->getAdj().size();
                }
            }

            cout << "Flights from " << name << ": " << flightsPerCity << endl;
            break;
        } else if (choice == 2) {
            cout << "Enter the name of the airline: ";
            getline(cin, name);

            int flightsPerAirline = 0;

            for (Vertex<Airport>* vertex : graph.getVertexSet()) {
                for (const Edge<Airport>& edge : vertex->getAdj()) {
                    if (edge.getWeight().getCode() == name) {
                        flightsPerAirline++;
                    }
                }
            }

            cout << "Flights for airline " << name << ": " << flightsPerAirline << endl;
            break;
        }
    }
}

/**
 * @brief Allows users to input an airport's name or code to display destinations reachable from that airport.
 * If the specified airport is found in the graph, the function invokes a Breadth-First Search (BFS)
 * algorithm to determine and display the destinations reachable from that airport within an unlimited amount of steps.
 *
 * @param graph Reference to the graph representing airports and their respective flight connections.
 *
 */
void displayDestinations(Graph<Airport>& graph) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Enter the airport's Name or Code ('b' to go back): ";
        string input;
        getline(cin, input);

        if (input == "b") {
            cout << "Going back... ";
            break;
        }

        bool airportFound = false;

        for (auto airport : graph.getVertexSet()) {
            if (airport->getInfo().getCode() == input || airport->getInfo().getName() == input) {
                airportFound = true;

                nodesAtDistanceBFS2(graph,airport->getInfo());

                cout << "Enter any key to go back to the previous step.";
                char choice;
                cin >> choice;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice != '\0') {
                    break;
                }
            }
        }

        if (!airportFound) {
            cout << "Airport '" << input << "' not found. Please enter a valid airport name or code.\n";
        }
    }
}

/**
 * @brief Determines and displays trips with the maximum number of stops in the given graph of airports and flight connections.
 * For each vertex (airport) in the graph, the function performs a Breadth-First Search (BFS) to find the destination(s)
 * that are farthest away in terms of stops. It then outputs the airport pairs that represent these trips.
 *
 * Essentially, this function determines the graph's diameter.
 *
 * @param graph Reference to the graph representing airports and their respective flight connections.
 *
 */
void displayMaxStopsTrip(const Graph<Airport>& graph) {
    int maxStops = 0;
    vector<pair<Airport, Airport>> viagens;

    for (auto& vertex : graph.getVertexSet()) {
        queue<pair<Vertex<Airport>*, int>> q;
        unordered_map<Vertex<Airport>*, bool> mapavisitados;

        q.emplace(vertex, 0);
        mapavisitados[vertex] = true;

        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            auto v = current.first;
            int currentStops = current.second;

            if (currentStops > maxStops) {
                maxStops = currentStops;
                viagens.clear();
                viagens.emplace_back(vertex->getInfo(), v->getInfo());
            } else if (currentStops == maxStops) {
                viagens.emplace_back(vertex->getInfo(), v->getInfo());
            }

            for (auto& edge : v->getAdj()) {
                auto destino = edge.getDest();

                if (!mapavisitados[destino]) {
                    q.emplace(destino, currentStops + 1);
                    mapavisitados[destino] = true;
                }
            }
        }
    }


    for (const auto& viagem : viagens) {
        cout << "From: " << viagem.first.getName() << " (" << viagem.first.getCode() << ") to: " << viagem.second.getName() << " (" << viagem.second.getCode() << ")" << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "Total number of trips with the maximum amount of Stops: " << viagens.size() << endl;
    cout << "The trips with the most stops have " << maxStops << " stops (last stop included)." << endl;
    cout << "Total Number of Airports visited per trip (Source and Destination included): " << maxStops+1 << endl;
    cout << "Total Number of Layovers per trip: " << maxStops - 1 << endl;

}

/**
 * @brief Depth-First Search (DFS) algorithm to identify articulation points.
 * Articulation points are vertices such that their removal would increase the number of connected components in the graph.
 *
 * @param v Pointer to the current vertex being visited during the DFS traversal.
 * @param index Current index used for numbering vertices in DFS traversal.
 * @param s Stack to keep track of vertices visited in the current DFS traversal path.
 * @param stackado Set to keep track of vertices currently present in the DFS traversal stack.
 * @param res Set containing the vertices identified as articulation points.
 * @param isRoot Flag to indicate if the current vertex is the root of a DFS tree.
 *
 * @timecomplexity O(V + E)
 */
void dfsArt(Vertex<Airport>* v, int& index, stack<Vertex<Airport>*>& s, unordered_set<Vertex<Airport>*>& stackado, unordered_set<Vertex<Airport>*>& res, bool isRoot = false) {

    v->setNum(index);
    v->setLow(index);
    index++;

    s.push(v);
    stackado.insert(v);

    int children = 0;

    for (const auto& edge : v->getAdj()) {
        auto w = edge.getDest();

        if (w->getNum() == -1) {
            dfsArt(w, index, s, stackado, res);
            v->setLow(min(v->getLow(), w->getLow()));

            if (!isRoot && w->getLow() >= v->getNum()) {
                res.insert(v);
            }
            ++children;
        } else if (stackado.find(w) != stackado.end()) {
            v->setLow(min(v->getLow(),w->getNum()));
        }
    }

    if (isRoot && children > 1) {
        res.insert(v);
    }

    s.pop();
    stackado.erase(v);
}

/**
 * @brief Identifies essential airports (articulation points) in an undirected copy of the given graph of airports and flight connections.
 * An essential airport is a vertex in the graph such that its removal would increase the number of connected components in the graph.
 *
 * @param graph Reference to the graph representing airports and their respective flight connections.
 *
 * @timecomplexity O(V + E)
 */
void displayEssentialAirports(const Graph<Airport>& graph) {

    Graph<Airport> undirectedVersion = graph;


    stack<Vertex<Airport>*> s;
    unordered_set<Vertex<Airport>*> stackado;
    unordered_set<Vertex<Airport>*> res;
    int index = 0;
    bool foundRoot = false;

    for (auto v : undirectedVersion.getVertexSet()) {
        for (const auto& edge : v->getAdj()){
            undirectedVersion.addEdge(edge.getDest()->getInfo(),v->getInfo(),edge.getWeight());
        }
        v->setNum(-1);
    }

    for (auto v : undirectedVersion.getVertexSet()) {
        if (v->getNum() == -1) {
            dfsArt(v, index, s, stackado, res, !foundRoot);
            foundRoot = true;
        }
    }

    cout << "Essential Airports: " << endl;
    for (auto vertex : res) {
        cout << vertex->getInfo().getName() << " (" << vertex->getInfo().getCode() << ")" << endl;
    }
    cout << "Number of essential airports: " << res.size() << endl;
}

/**
 * @brief Convert an angle from degrees to radians.
 *
 * @param deg Angle in degrees.
 *
 * @return Angle converted to radians.
 */
double deg2rad(double deg) {
    return deg * (M_PI/180);
}

/**
 * @brief Calculate the great-circle distance between two points on the Earth's surface using the Haversine formula.
 *
 * @param lat_1 Latitude of the first point in degrees.
 * @param log_1 Longitude of the first point in degrees.
 * @param lat_2 Latitude of the second point in degrees.
 * @param log_2 Longitude of the second point in degrees.
 * @return Great-circle distance between the two points.
 */
double haversine(double lat_1, double log_1, double lat_2, double log_2) {

    lat_1 = deg2rad(lat_1);
    log_1 = deg2rad(log_1);
    lat_2 = deg2rad(lat_2);
    log_2 = deg2rad(log_2);

    double r = 6371;

    double dlat = lat_2 - lat_1;
    double dlon = log_2 - log_1;

    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat_1) * cos(lat_2) * sin(dlon / 2) * sin(dlon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = r * c;

    return d;
}

/**
 * @brief Find the airport(s) in the graph closest to the given coordinates using the Haversine distance formula.
 *
 * @param graph Reference to the graph representing airports and their respective latitude and longitude coordinates.
 * @param coordinates Pair containing the latitude and longitude coordinates (in degrees) to find the closest airport(s).
 * @return Vector containing pointers to the closest airport(s).
 *
 * @timecomplexity O(V)
 */
vector<Vertex<Airport>*> findClosestAirports(const Graph<Airport>& graph, const pair<double, double>& coordinates) {
    double minDistance = numeric_limits<double>::max();
    vector<Vertex<Airport>*> closestAirports;

    for (const auto& vertex : graph.getVertexSet()) {
        double distance = haversine(coordinates.first, coordinates.second, vertex->getInfo().getLatitude(), vertex->getInfo().getLongitude());

        if (distance < minDistance) {
            minDistance = distance;
            closestAirports.clear();
            closestAirports.push_back(vertex);
        } else if (distance == minDistance) {
            closestAirports.push_back(vertex);
        }
    }

    return closestAirports;
}

/**
 * @brief Displays the filter menu to the user and handles the user's filter choice.
 *
 * This function displays a menu of filter options to the user, reads the user's choice,
 * and calls the appropriate function based on the user's choice. The user can choose to
 * apply no filters, filter by preferred airlines, filter by least number of airline changes,
 * or filter to specific countries/cities. The user can also choose to go back to the previous step.
 *
 * @param graph The graph of airports.
 * @param airportMap A map from airport codes to vertices in the graph.
 * @param cityToAirportMap A map from city names to its airports.
 */
void displayFilterMenu(const Graph<Airport> &graph, const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,
                       const unordered_map<string, Vertex<Airport> *> &cityToAirportMap) {

    string filterOptionForCase1 = "NoFilter";
    string filterOptionForCase2 = "Filter1";
    string filterOptionForCase3 = "Filter2";
    string filterOptionForCase4 = "Filter3";

    while(true) {
        cout << "\n----------------------------------\n";
        cout << "          " << "Filter" << " Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose a " << "Filter" << " option:\n";
        cout << "1. No filters\n";
        cout << "2. Filter by preferred Airlines\n";
        cout << "3. Filter by least number of Airline changes\n";
        cout << "4. Filter to avoid certain Airlines\n";
        cout << "b. Go back to the previous step\n";
        cout << "----------------------------------\n";
        cout << "Your choice: ";

        string filterOption;
        cin >> filterOption;

        if (filterOption == "b" || filterOption == "B") {
            return;
        }

        if(filterOption.length() != 1){
            filterOption = "0";
        }

        switch (filterOption[0]) {
            case '1':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase1);
                break;
            case '2':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase2);
                break;
            case '3':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase3);
                break;
            case '4':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase4);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

/**
 * @brief Displays the source menu to the user and handles the user's source choice.
 *
 * This function displays a menu of source options to the user, reads the user's choice,
 * and calls the appropriate function based on the user's choice. The user can choose to
 * select a source airport by code or name, select a source city, or enter geographical coordinates
 * for the source. The user can also choose to go back to the previous step.
 *
 * @param graph The graph of airports.
 * @param cityToAirportsMap A map from city names to vectors of vertices airports in the graph.
 * @param airportMap A map from airport codes to vertices in the graph.
 * @param filterOption The filter option chosen by the user in the filter menu.
 */
void displaySourceMenu(const Graph<Airport>& graph, const unordered_map<string, vector<Vertex<Airport>*>>& cityToAirportsMap, const unordered_map<string, Vertex<Airport>*>& airportMap,const string& filterOption) {
    while(true) {

        string option;

        cout << "\n----------------------------------\n";
        cout << "          " << "Source" << " Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose a " << "Source" << " option:\n";
        cout << "1. Choose a " << "source" << " Airport (by Code or Name)\n";
        cout << "2. Choose a " << "source" << " City\n";
        cout << "3. Choose some " << "source" << " Geographical Coordinates\n";
        cout << "b. Go back to the previous step\n";
        cout << "----------------------------------\n";
        cout << "Your choice: ";
        cin >> option;

        if(option.length() != 1){
            option = "0";
        }

        string airportOption, cityOption, coordinateOption;
        vector<Vertex<Airport>*> possibleSources;
        double latitude, longitude;
        bool found = false;

        switch (option[0]) {
            case '1':
                while(true){
                    cout << "Enter " << "the source " << " Airport Code or Name (or 'b' to go back): ";
                    cin.ignore();
                    getline(cin,airportOption);
                    if (airportOption == "b"){
                        cout << "Going back to the previous step";
                        break;
                    }
                        auto codeIt = airportMap.find(airportOption);
                        if (codeIt != airportMap.end()) {
                            possibleSources.push_back(codeIt->second);
                            found = true;
                        }

                        for (const auto& entry : airportMap) {
                            if (entry.second->getInfo().getName() == airportOption) {
                                possibleSources.push_back(entry.second);
                                found = true;
                            }
                        }
                        if(found){
                            displayDestinationMenu(graph, cityToAirportsMap, airportMap, possibleSources, filterOption);
                            break;
                        }
                        else{
                            cout << "Airport " << airportOption << " not found. Please try again"
                                                                   " with an existing Airport Code.";
                            break;
                        }
                }

                break;

                case '2':
                while(true){
                    cout << "Enter " << "the source " << "City Name (or 'b' to go back): ";
                    cin.ignore();
                    getline(cin,cityOption);
                    if (airportOption == "b"){
                        cout << "Going back to the previous step";
                        break;
                    }
                    if (cityToAirportsMap.find(cityOption) != cityToAirportsMap.end()){
                        possibleSources = (cityToAirportsMap.at(cityOption));
                        displayDestinationMenu(graph, cityToAirportsMap, airportMap, possibleSources, filterOption);
                        break;
                    }
                    else{
                        cout << "City " << cityOption << " not found. Please try again"
                                                               " with an existing City Name.";
                        break;
                    }
                }
                break;
            case '3': {
                cout << "Enter the source Latitude and Longitude (comma-separated): ";
                string line;
                cin.ignore();
                getline(cin, line);
                stringstream ss(line);
                char comma;

                if (line == "b"){
                    cout << "Going back to the previous step";
                    break;
                }

                if (!(ss >> latitude >> comma >> longitude) || comma != ',') {
                    cout << "Invalid input. Please enter two numbers separated by a comma.\n";
                    break;
                }
                possibleSources = findClosestAirports(graph,make_pair(latitude,longitude));
                displayDestinationMenu(graph, cityToAirportsMap, airportMap, possibleSources, filterOption);
                break;
            }
                break;
            case 'b':
                cout << "Going back to the previous step.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

/**
 * @brief Displays a menu for the user to choose a destination.
 *
 * This function displays a menu to the user to choose a destination by either airport code/name, city name, or geographical coordinates.
 *
 * @param graph The graph representing the airports and their connections.
 * @param cityToAirportsMap A map from city names to the airports in those cities.
 * @param airportMap A map from airport code to the corresponding airport vertices in the graph.
 * @param possibleSources A vector of possible source airports for the journey.
 * @param filterOption A string representing the filter option chosen by the user.
 */
void displayDestinationMenu(const Graph<Airport> &graph, const unordered_map<string, vector<Vertex<Airport> *>> &cityToAirportsMap,
                            const unordered_map<string, Vertex<Airport> *> &airportMap, const vector<Vertex<Airport> *>& possibleSources,const string& filterOption) {
    while(true) {

        string option;

        cout << "\n----------------------------------\n";
        cout << "          " << "Destination" << " Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose a " << "Destination" << " option:\n";
        cout << "1. Choose a " << "destination" << " Airport (by Code or Name)\n";
        cout << "2. Choose a " << "destination" << " City\n";
        cout << "3. Choose some " << "destination" << " Geographical Coordinates\n";
        cout << "b. Go back to the previous step\n";
        cout << "----------------------------------\n";
        cout << "Your choice: ";
        cin >> option;

        if(option.length() != 1){
            option = "0";
        }

        string airportOption, cityOption, coordinateOption;
        vector<Vertex<Airport>*> possibleDestinations;
        double latitude, longitude;
        bool found = false;

        switch (option[0]) {
            case '1':
                while(true){
                    cout << "Enter " << "the destination " << " Airport Code or Name (or 'b' to go back): ";
                    cin.ignore();
                    getline(cin,airportOption);
                    if (airportOption == "b"){
                        cout << "Going back to the previous step";
                        break;
                    }
                    auto codeIt = airportMap.find(airportOption);
                    if (codeIt != airportMap.end()) {
                        possibleDestinations.push_back(codeIt->second);
                        found = true;
                    }

                    for (const auto& entry : airportMap) {
                        if (entry.second->getInfo().getName() == airportOption) {
                                possibleDestinations.push_back(entry.second);
                                found = true;
                        }
                    }
                    if(found){
                        if (filterOption == "NoFilter") {
                            findPaths(graph, cityToAirportsMap,airportMap, possibleSources, possibleDestinations);
                        }
                        else if (filterOption == "Filter1") {
                            cout << "Enter comma-separated airline codes for filtering (or press 'b' to go back): ";
                            string airlineCodesInput;
                            getline(cin, airlineCodesInput);

                            if (airlineCodesInput == "b") {
                                return;
                            }

                            set<string> preferredAirlines;
                            if (!airlineCodesInput.empty()) {
                                stringstream ss(airlineCodesInput);
                                string airlineCode;
                                while (getline(ss, airlineCode, ',')) {
                                    airlineCode.erase(remove_if(airlineCode.begin(), airlineCode.end(), ::isspace), airlineCode.end());
                                    preferredAirlines.insert(airlineCode);
                                }
                            }

                            findPathsFiltered(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations, preferredAirlines);
                        }
                        else if (filterOption == "Filter2") {
                            findPathsFilteredByAirlineChanges(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations);
                        }
                        else if (filterOption == "Filter3") {
                            cout << "Enter comma-separated airline codes for filtering (or press 'b' to go back): ";
                            string airlineCodesInput;
                            getline(cin, airlineCodesInput);

                            if (airlineCodesInput == "b") {
                                return;
                            }

                            set<string> preferredAirlines;
                            if (!airlineCodesInput.empty()) {
                                stringstream ss(airlineCodesInput);
                                string airlineCode;
                                while (getline(ss, airlineCode, ',')) {
                                    airlineCode.erase(remove_if(airlineCode.begin(), airlineCode.end(), ::isspace), airlineCode.end());
                                    preferredAirlines.insert(airlineCode);
                                }
                            }

                            findPathsFiltered2(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations, preferredAirlines);
                        }
                        break;
                    }
                    else{
                        cout << "Airport " << airportOption << " not found. Please try again"
                                                               " with an existing Airport Code.";
                        break;
                    }
                }

                break;
            case '2':
                while(true){
                    cout << "Enter " << "the destination " << "City Name (or 'b' to go back): ";
                    cin.ignore();
                    getline(cin,cityOption);
                    if (airportOption == "b"){
                        cout << "Going back to the previous step";
                        break;
                    }
                    if (cityToAirportsMap.find(cityOption) != cityToAirportsMap.end()){
                        possibleDestinations = (cityToAirportsMap.at(cityOption));
                        if (filterOption == "NoFilter") {
                            findPaths(graph, cityToAirportsMap,airportMap, possibleSources, possibleDestinations);
                        }
                        else if (filterOption == "Filter1") {
                            cout << "Enter comma-separated airline codes for filtering (or press 'b' to go back): ";
                            string airlineCodesInput;
                            getline(cin, airlineCodesInput);

                            if (airlineCodesInput == "b") {
                                return;
                            }

                            set<string> preferredAirlines;
                            if (!airlineCodesInput.empty()) {
                                stringstream ss(airlineCodesInput);
                                string airlineCode;
                                while (getline(ss, airlineCode, ',')) {
                                    airlineCode.erase(remove_if(airlineCode.begin(), airlineCode.end(), ::isspace), airlineCode.end());
                                    preferredAirlines.insert(airlineCode);
                                }
                            }

                            findPathsFiltered(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations, preferredAirlines);
                        }
                        else if (filterOption == "Filter2") {
                            findPathsFilteredByAirlineChanges(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations);
                        }
                        else if (filterOption == "Filter3") {
                            cout << "Enter comma-separated airline codes for filtering (or press 'b' to go back): ";
                            string airlineCodesInput;
                            getline(cin, airlineCodesInput);

                            if (airlineCodesInput == "b") {
                                return;
                            }

                            set<string> preferredAirlines;
                            if (!airlineCodesInput.empty()) {
                                stringstream ss(airlineCodesInput);
                                string airlineCode;
                                while (getline(ss, airlineCode, ',')) {
                                    airlineCode.erase(remove_if(airlineCode.begin(), airlineCode.end(), ::isspace), airlineCode.end());
                                    preferredAirlines.insert(airlineCode);
                                }
                            }

                            findPathsFiltered2(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations, preferredAirlines);
                        }
                        break;
                    }
                    else{
                        cout << "City " << cityOption << " not found. Please try again"
                                                         " with an existing City Name.";
                        break;
                    }
                }
                break;
            case '3': {
                cout << "Enter the destination Latitude and Longitude (comma-separated): ";
                cin.ignore();
                string line;
                getline(cin, line);
                stringstream ss(line);
                char comma;

                if (line == "b"){
                    cout << "Going back to the previous step";
                    break;
                }

                if (!(ss >> latitude >> comma >> longitude) || comma != ',') {
                    cout << "Invalid input. Please enter two numbers separated by a comma.\n";
                    break;
                }
                possibleDestinations = findClosestAirports(graph,make_pair(latitude,longitude));
                if (filterOption == "NoFilter") {
                    findPaths(graph, cityToAirportsMap,airportMap, possibleSources, possibleDestinations);
                }
                else if (filterOption == "Filter1") {
                    cout << "Enter comma-separated airline codes for filtering (or press 'b' to go back): ";
                    string airlineCodesInput;
                    getline(cin, airlineCodesInput);

                    if (airlineCodesInput == "b") {
                        return;
                    }

                    set<string> preferredAirlines;
                    if (!airlineCodesInput.empty()) {
                        stringstream ss(airlineCodesInput);
                        string airlineCode;
                        while (getline(ss, airlineCode, ',')) {
                            airlineCode.erase(remove_if(airlineCode.begin(), airlineCode.end(), ::isspace), airlineCode.end());
                            preferredAirlines.insert(airlineCode);
                        }
                    }

                    findPathsFiltered(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations, preferredAirlines);
                }
                else if (filterOption == "Filter2") {
                    findPathsFilteredByAirlineChanges(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations);
                }
                else if (filterOption == "Filter3") {
                    cout << "Enter comma-separated airline codes for filtering (or press 'b' to go back): ";
                    string airlineCodesInput;
                    getline(cin, airlineCodesInput);

                    if (airlineCodesInput == "b") {
                        return;
                    }

                    set<string> preferredAirlines;
                    if (!airlineCodesInput.empty()) {
                        stringstream ss(airlineCodesInput);
                        string airlineCode;
                        while (getline(ss, airlineCode, ',')) {
                            airlineCode.erase(remove_if(airlineCode.begin(), airlineCode.end(), ::isspace), airlineCode.end());
                            preferredAirlines.insert(airlineCode);
                        }
                    }

                    findPathsFiltered2(graph, cityToAirportsMap, airportMap, possibleSources, possibleDestinations, preferredAirlines);
                }
            }
                break;

            case 'b':
                cout << "Going back to the previous step.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

}

/**
 * @brief Find optimal flight paths between given source and destination airports.
 *
 * This function searches for optimal flight paths between a set of possible source airports
 * and a set of possible destination airports using a variation of Dijkstra's algorithm on a given graph to calculate the shortest path.
 *
 * @param graph A reference to the graph.
 * @param airportMap A map that associates airport code with corresponding airport vertices.
 * @param cityToAirportMap A map that maps city names to their respective airports.
 * @param possibleSources A vector containing possible source airport vertices.
 * @param possibleDestinations A vector containing possible destination airport vertices.
 *
 */
void findPaths(const Graph<Airport>& graph, const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,
               const unordered_map<string, Vertex<Airport> *> &cityToAirportMap, const vector<Vertex<Airport> *> &possibleSources,
               const vector<Vertex<Airport> *> &possibleDestinations) {



    vector<vector<Airport>> paths;

    set<vector<Airport>> res;
    for (auto source : possibleSources) {
        for (auto destination : possibleDestinations) {
            paths = graph.caminhosDjiskra(source->getInfo(), destination->getInfo());
            for (const auto& path : paths){
                res.insert(path);
            }
        }
    }

    if (paths.empty()) {
        cout << "No valid paths found between the selected source-destination pair." << endl;
    }
    else {

        if (res.size() > 1) {
            cout << "Multiple optimal flight paths found." << endl;
        } else {
            cout << "Single optimal flight path found." << endl;
        }

        cout << "\nOptimal Flight Paths:" << endl;

        for (const auto &path : res) {
            cout << "\nPath: ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i].getName() << " (" << path[i].getCode() << ")";
                if (i < path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;

            cout << "---------------------------------------" << endl;
        }

        int totalAirports = 0;
        int totalLayovers = 0;


        totalAirports = paths[0].size();
        totalLayovers = max(static_cast<int>(paths[0].size()) - 2, 0);

        cout << "Number of Optimal Paths Found: " << res.size() << endl;
        cout << "\nTotal Number of Airports Visited: " << totalAirports << endl;
        cout << "Total Number of Layovers: " << totalLayovers << endl;
    }
}

/**
 * @brief Find and filter optimal flight paths based on preferred airlines.
 *
 * This function identifies optimal flight paths between a set of possible source airports
 * and a set of possible destination airports, taking into consideration the user's preferred airlines.
 *
 * Given a minimal path of Airports, it identifies the paths with the maximum amount of preferred Airline's flights
 * Filters any path that doesn't reach the maximum amount that was just calculated
 *
 * @param graph A reference to the graph.
 * @param airportMap A map associating airport code with corresponding airports vertices.
 * @param cityToAirportMap A map that maps city names to their respective airport vertices.
 * @param possibleSources A vector containing possible source airport vertices for path finding.
 * @param possibleDestinations A vector containing possible destination airport vertices for path finding.
 * @param preferredAirlines A set containing airline codes representing the user's preferred airlines.
 *
 */
void findPathsFiltered(const Graph<Airport>& graph,const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,const unordered_map<string, Vertex<Airport> *> &cityToAirportMap,
                       const vector<Vertex<Airport> *> &possibleSources,
                       const vector<Vertex<Airport> *> &possibleDestinations,
                       const set<string>& preferredAirlines) {

    vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> paths;
    vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> res;


    Edge<Airport> fakeEdge = *new Edge<Airport>(); //criada para poder colocar o 1o elemento no printing

    for (auto source : possibleSources) {
        for (auto destination : possibleDestinations) {
            paths = graph.caminhosDjiskraEdges(source->getInfo(), destination->getInfo());

            for (const auto& path : paths) {

                vector<pair<Vertex<Airport>*, Edge<Airport>>> novoPath;
                novoPath.emplace_back(make_pair(source, fakeEdge));
                novoPath.insert(novoPath.end(), path.begin(), path.end());

                res.push_back(novoPath);
            }
        }
    }

    if (paths.empty()) {
        cout << "No valid paths found between the selected source-destination pair." << endl;
    }
    else {

        if (res.size() > 1) {
            cout << "Multiple optimal flight paths found." << endl;
        } else {
            cout << "Single optimal flight path found." << endl;
        }

        cout << "\nOptimal Flight Paths:" << endl;

        int maxFlightsWithPreferred = 0;
        vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> finalres;
        unordered_set<string> Airlines;

        //O proximo loop:
        //Conta a quantidade de edges com airlines iguais por caminho
        //Compara essa contagem com a do Path com o maximo de Airlines favoritas
        //Coloca no vector apenas paths com o maximo numero de airlines favoritas
        //reseta o vector resultante caso haja uma nova maxFlightsWithPreferred (caso encontre um count maior)
        for (const auto& path : res){
            int count = 0;
            for (const auto& par : path){
                auto Edge = par.second;
                if (preferredAirlines.find(Edge.getWeight().getCode()) != preferredAirlines.end()){
                    count++;
                }

            }
            if (count > maxFlightsWithPreferred){
                maxFlightsWithPreferred = count;
                finalres.clear();
                finalres.push_back(path);
            }
            else if (count == maxFlightsWithPreferred){
                finalres.push_back(path);
            }

        }


        for (const auto &path : finalres) {
            cout << "\nPath: ";

            for (size_t i = 0; i < path.size(); ++i) {
                if (i == 0){
                    cout << path[i].first->getInfo().getName() << " (Source) -> ";
                }
                else{
                    cout << path[i].first->getInfo().getName() << " (Through Airline: "  << path[i].second.getWeight().getCode() << ")";
                    if (i < path.size() - 1) {
                        cout << " -> ";
                    }
                }

            }
            cout << endl;

            cout << "---------------------------------------" << endl;
        }

        int totalAirports = 0;
        int totalLayovers = 0;


        totalAirports = paths[0].size() + 1;
        totalLayovers = max(static_cast<int>(paths[0].size()) - 2, 0) + 1;

        cout << "Airlines-FlightPath combinations found: " << res.size() << endl;
        cout << "Combinations filtered: " << res.size() - finalres.size() << endl;
        cout << "Post-Filter final amount of Flight Paths: " << finalres.size() << endl;
        cout << "\nTotal Number of Airports visited per path: " << totalAirports << endl;
        cout << "Total Number of Layovers per path: " << totalLayovers << endl;
        if (maxFlightsWithPreferred == 0){
            cout << "Unfortunately, there's not a way to choose your preferred airline(s) if you wish to fly the best path. ";
        }
        else{
            cout << "You can manage to choose your preferred Airline(s) in "<< maxFlightsWithPreferred << " flight(s) out of " << paths[0].size() << " per path" << endl;
        }
    }
}

/**
 * @brief Find optimal flight paths while minimizing airline changes.
 *
 * This function identifies optimal flight paths between a set of possible source airports
 * and a set of possible destination airports, with a focus on minimizing the number of
 * different airlines used during the path.
 *
 * Counts the minimal amount of Airline changes per path in a given vector of minimal Airport paths
 * The final vector will only contain paths that do not surpass the calculated amount
 *
 * @param graph A reference to the graph representing airports and flight connections.
 * @param airportMap A map associating airport code with corresponding airport vertices.
 * @param cityToAirportMap A map that maps city names to their respective airport vertices.
 * @param possibleSources A vector containing possible source airport vertices for path finding.
 * @param possibleDestinations A vector containing possible destination airport vertices for path finding.
 *
 */
void findPathsFilteredByAirlineChanges(const Graph<Airport>& graph, const unordered_map<string, vector<Vertex<Airport> *>> &airportMap, const unordered_map<string, Vertex<Airport> *> &cityToAirportMap, const vector<Vertex<Airport> *> &possibleSources, const vector<Vertex<Airport> *> &possibleDestinations) {

    vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> paths;
    vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> res;


    Edge<Airport> fakeEdge = *new Edge<Airport>(); //criada para poder colocar o 1o elemento no printing

    for (auto source : possibleSources) {
        for (auto destination : possibleDestinations) {
            paths = graph.caminhosDjiskraEdges(source->getInfo(), destination->getInfo());

            for (const auto& path : paths) {

                vector<pair<Vertex<Airport>*, Edge<Airport>>> novoPath;
                novoPath.emplace_back(make_pair(source, fakeEdge));
                novoPath.insert(novoPath.end(), path.begin(), path.end());

                res.push_back(novoPath);
            }
        }
    }

    if (paths.empty()) {
        cout << "No valid paths found between the selected source-destination pair." << endl;
    }
    else {

        if (res.size() > 1) {
            cout << "Multiple optimal flight paths found." << endl;
        } else {
            cout << "Single optimal flight path found." << endl;
        }

        cout << "\nOptimal Flight Paths:" << endl;


        size_t minSize = SIZE_MAX;
        vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> finalres;
        unordered_set<string> Airlines;

        //O proximo loop:
        //Conta a quantidade de edges diferentes por caminho
        //Compara unordered sets de codigos de airline com o minSize
        // e coloca no vector resultante apenas paths com sizes iguais ou menores
        //reseta o vector resultante caso haja uma nova minSize (caso encontre uma menor)
        for (const auto& path : res){
            for (const auto& par : path){
                auto Edge = par.second;
                Airlines.insert(Edge.getWeight().getCode());
            }
            if (Airlines.size() < minSize){
                finalres.clear();
                minSize = Airlines.size();
                finalres.push_back(path);
            }
            else if (Airlines.size() == minSize){
                finalres.push_back(path);
            }
            Airlines.clear();
        }


        for (const auto &path : finalres) {
            cout << "\nPath: ";

            for (size_t i = 0; i < path.size(); ++i) {
                if (i == 0){
                    cout << path[i].first->getInfo().getName() << " (Source) -> ";
                 }
                else{
                    cout << path[i].first->getInfo().getName() << " (Through Airline: "  << path[i].second.getWeight().getCode() << ")";
                    if (i < path.size() - 1) {
                        cout << " -> ";
                    }
                }

            }
            cout << endl;

            cout << "---------------------------------------" << endl;
        }

        int totalAirports = 0;
        int totalLayovers = 0;


        totalAirports = paths[0].size() + 1;
        totalLayovers = max(static_cast<int>(paths[0].size()) - 2, 0) + 1;

        cout << "Airlines-FlightPath combinations found: " << res.size() << endl;
        cout << "Combinations filtered: " << res.size() - finalres.size() << endl;
        cout << "Post-Filter final amount of Flight Paths: " << finalres.size() << endl;
        cout << "\nTotal number of Airports visited per path: " << totalAirports << endl;
        cout << "Total number of Layovers per path: " << totalLayovers << endl;
        cout << "Minimal number of Airlines used per path: " << minSize - 1;
    }
}

/**
 * @brief Find optimal flight paths while avoiding specific airlines.
 *
 * This function identifies optimal flight paths between a set of possible source airports
 * and a set of possible destination airports, with the capability to avoid specific airlines
 * as specified by the user.
 *
 * Given a vector of minimal Airport paths, it identifies the path with the minimal amount of the chosen Airlines.
 * The final vector only receives paths with the minimal amount of chosen Airlines to avoid
 *
 * @param graph A reference to the graph representing airports and flight connections.
 * @param airportMap A map associating city names with corresponding airport vertices.
 * @param cityToAirportMap A map that maps city names to their respective airport vertices.
 * @param possibleSources A vector containing possible source airport vertices for path finding.
 * @param possibleDestinations A vector containing possible destination airport vertices for path finding.
 * @param avoidingAirlines A set containing airline codes representing the airlines to avoid.
 *
 */
void findPathsFiltered2(const Graph<Airport>& graph,const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,const unordered_map<string, Vertex<Airport> *> &cityToAirportMap,
                        const vector<Vertex<Airport> *> &possibleSources,
                        const vector<Vertex<Airport> *> &possibleDestinations,
                        const set<string>& avoidingAirlines) {

    vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> paths;
    vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> res;


    Edge<Airport> fakeEdge = *new Edge<Airport>(); //criada para poder colocar o 1o elemento no printing

    for (auto source : possibleSources) {
        for (auto destination : possibleDestinations) {
            paths = graph.caminhosDjiskraEdges(source->getInfo(), destination->getInfo());

            for (const auto& path : paths) {

                vector<pair<Vertex<Airport>*, Edge<Airport>>> novoPath;
                novoPath.emplace_back(make_pair(source, fakeEdge));
                novoPath.insert(novoPath.end(), path.begin(), path.end());

                res.push_back(novoPath);
            }
        }
    }

    if (paths.empty()) {
        cout << "No valid paths found between the selected source-destination pair." << endl;
    }
    else {

        if (res.size() > 1) {
            cout << "Multiple optimal flight paths found." << endl;
        } else {
            cout << "Single optimal flight path found." << endl;
        }

        cout << "\nOptimal Flight Paths:" << endl;

        int minFlightsWithAvoiding = numeric_limits<int>::max();
        vector<vector<pair<Vertex<Airport>*, Edge<Airport>>>> finalres;
        unordered_set<string> Airlines;

        //O proximo loop:
        //Conta a quantidade de edges com airlines iguais por caminho
        //Compara essa contagem com a do Path com o minimo de Airlines a evitar
        //Coloca no vector apenas paths com o minimo numero de airlines a evitar
        //reseta o vector resultante caso haja uma nova minFlightsWithAvoiding (caso encontre um count menor)
        for (const auto& path : res){
            int count = 0;
            for (const auto& par : path){
                auto Edge = par.second;
                if (avoidingAirlines.find(Edge.getWeight().getCode()) != avoidingAirlines.end()){
                    count++;
                }
            }
            if (count < minFlightsWithAvoiding){
                minFlightsWithAvoiding = count;
                finalres.clear();
                finalres.push_back(path);
            }
            else if (count == minFlightsWithAvoiding){
                finalres.push_back(path);
            }

        }


        for (const auto &path : finalres) {
            cout << "\nPath: ";

            for (size_t i = 0; i < path.size(); ++i) {
                if (i == 0){
                    cout << path[i].first->getInfo().getName() << " (Source) -> ";
                }
                else{
                    cout << path[i].first->getInfo().getName() << " (Through Airline: "  << path[i].second.getWeight().getCode() << ")";
                    if (i < path.size() - 1) {
                        cout << " -> ";
                    }
                }

            }
            cout << endl;

            cout << "---------------------------------------" << endl;
        }

        int totalAirports = 0;
        int totalLayovers = 0;


        totalAirports = paths[0].size() + 1;
        totalLayovers = max(static_cast<int>(paths[0].size()) - 2, 0) + 1;

        cout << "Airlines-FlightPath combinations found: " << res.size() << endl;
        cout << "Combinations filtered: " << res.size() - finalres.size() << endl;
        cout << "Post-Filter final amount of Flight Paths: " << finalres.size() << endl;
        cout << "\nTotal Number of Airports visited per path: " << totalAirports << endl;
        cout << "Total Number of Layovers per path: " << totalLayovers << endl;
        if ((paths[0].size() - minFlightsWithAvoiding) == 0){
            cout << "Unfortunately, there's not a way to avoid the chosen airline(s) if you want to use the best flight path. " << endl;
        }
        else{
            cout << "You can manage to avoid the chosen Airline(s) in "<< paths[0].size() - minFlightsWithAvoiding << " flight(s) out of " << paths[0].size() << " per path" << endl;
        }
    }
}


void App::run() {
    mainMenu();
}
