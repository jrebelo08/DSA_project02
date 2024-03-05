/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <climits>
#include <limits>
#include "Airline.h"
#include "Airport.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;



template <class T>
class Vertex {
    T info;
    vector<Edge<T> > adj;
    bool visited;
    bool processing;
    int num;
    int low;

    void addEdge(Vertex<T> *dest, Airline w);

public:
    Vertex(T in);
    T getInfo() const;

    bool isVisited() const;
    void setVisited(bool v);

    const vector<Edge<T>> &getAdj() const;

    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
    friend class Graph<T>;


};

template <class T>
class Edge {

    Vertex<T> * dest;
    Airline weight;
public:
    Edge();
    Edge(Vertex<T> *d, Airline w);
    Vertex<T> *getDest() const;

    Airline getWeight() const;

    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;
    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;

public:
    Vertex<T> *findVertex(const T &in) const;

    bool addVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, Airline w);

    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;

    vector<vector<T>> caminhosDjiskra(const T &source, const T &destination) const;

    void construirCaminhos(Vertex<T> *source, Vertex<T> *destination,
                           const unordered_map<Vertex<T> *, vector<Vertex<T> *>> &predecessors,
                           vector<T> &currentPath, vector<vector<T>> &paths) const;


    vector<vector<pair<Vertex<T> *, Edge<T>>>> caminhosDjiskraEdges(const T &source, const T &destination) const;

    void construirCaminhosEdges(Vertex<T> *source, Vertex<T> *destination,
                                const unordered_map<Vertex<T> *, vector<pair<Vertex<T> *, Edge<T>>>> &predecessors,
                                vector<pair<Vertex<T> *, Edge<T>>> &currentPath,
                                vector<vector<pair<Vertex<T> *, Edge<T>>>> &paths) const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, Airline w): dest(d), weight(w) {}

template<class T>
Edge<T>::Edge() : dest(nullptr), weight(Airline()) {}


template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
Airline Edge<T>::getWeight() const {
    return weight;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}



template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}



template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, Airline w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, Airline w) {
    adj.push_back(Edge<T>(d, w));
}



template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    for (auto v : vertexSet) {
        if (!v->isVisited()) {
            dfsVisit(v, res);
        }
    }
    return res;
}



template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {

    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto it = v->getAdj().begin(); it != v->getAdj().end(); it++) {
        if (!(*it).getDest()->isVisited()) {
            dfsVisit((*it).getDest(), res);
        }
    }

}


template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    for (auto v : vertexSet){
        v->setVisited(false);
    }

    Vertex<T>* fonte = findVertex(source);
    dfsVisit(fonte,res);

    return res;
}

template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;

    for (auto v: vertexSet){
        v->setVisited(false);
    }

    Vertex<T>* v = findVertex(source);
    queue<Vertex<T>*> toVisit = {};
    toVisit.push(v);
    v->setVisited(true);
    res.push_back(v->getInfo());

    while (!toVisit.empty()){
        v = toVisit.front();
        toVisit.pop();
        for (auto it = v->getAdj().begin(); it != v->getAdj().end();it++){
            if (!(*it).getDest()->isVisited()){
                toVisit.push((*it).getDest());
                (*it).getDest()->setVisited(true);
                res.push_back((*it).getDest()->getInfo());
            }
        }
    }


    return res;
}


/**
 * Dijkstra's algorithm to find all minimum paths in a graph.
 * Modified to return only the minimum paths between the source and the destination.
 *
 * @param source - The origin from which paths are determined.
 * @param destination - The destination up to which paths are determined.
 * @return Vector containing the minimum paths from the source to the destination.
 * If either the source or destination vertex is not found, it returns an empty vector.
 *
 * This function has a time complexity of O((V+E)logV)
 *
 */


template <class T>
vector<vector<T>> Graph<T>::caminhosDjiskra(const T &source, const T &destination) const {

    //declaração de variáveis
    unordered_map<Vertex<T>*, int> distance;
    unordered_map<Vertex<T>*, vector<Vertex<T>*>> predecessors;
    vector<vector<T>> paths;

    Vertex<T>* sourceVertex = findVertex(source);
    Vertex<T>* destVertex = findVertex(destination);

    if (sourceVertex == nullptr || destVertex == nullptr)
        return paths;


    // Inicialização das distâncias e predecessores
    for (auto vertex : vertexSet) {
        distance[vertex] = numeric_limits<int>::max();
        predecessors[vertex] = vector<Vertex<T>*>();
    }
    distance[sourceVertex] = 0;

    //queue prioritária para organizar vertices em ordem crescente de distancia atravez do greater<>
    priority_queue<pair<int, Vertex<T>*>, vector<pair<int, Vertex<T>*>>, greater<pair<int, Vertex<T>*>>> pq;
    pq.push(make_pair(0, sourceVertex)); //colocar a fonte na pq


    //Algoritmo de Dijkstra para encontrar todos os caminhos
    while (!pq.empty()) {
        auto currentVertex = pq.top().second;
        auto currentDistance = pq.top().first;
        pq.pop(); //retirar o vertice com menor distancia

        if (currentDistance > distance[currentVertex])
            continue;

        for (auto edge : currentVertex->getAdj()) {
            auto neighbor = edge.getDest();
            int newDistance = distance[currentVertex] + 1; //calcular distancia


            if (newDistance < distance[neighbor]) {

                distance[neighbor] = newDistance;
                predecessors[neighbor] = {currentVertex};
                pq.push(make_pair(newDistance, neighbor));

            } else if (newDistance == distance[neighbor]) {
                predecessors[neighbor].push_back(currentVertex);
            }
        }
    }

    //cria um caminho vazio e chama a função que constroi apenas os paths desejados
    vector<T> currentPath;
    construirCaminhos(sourceVertex, destVertex, predecessors, currentPath, paths);

    return paths;
}


/**
 * This recursive function constructs paths from the destination vertex back to the source vertex.
 * When the minimum paths of the graph are identified, this function recursively constructs the desired path
 * and places it in the final paths vector. The function begins with a path containing the desired destination.
 *
 * It utilizes the predecessors map, obtained from previous steps, to identify the preceding vertex in the path.
 * During each recursive call, the most recently found predecessor is added to the current path.
 * Only paths starting from the destination and leading back to the source are added to the paths vector.
 * In the base case, paths are reversed since the desired output represents paths from source to destination
 * and not from destination to source.
 *
 * Essentially, this function generates all reversed paths leading to the destination vertex. However,
 * only paths terminating at the source are appended to the output vector.
 *
 * @param source - The starting vertex from which paths are initiated.
 * @param destination - The target destination vertex for which paths are determined.
 * @param predecessors - A map that provides predecessors for each vertex, essential for path reconstruction.
 * @param currentPath - The ongoing path being constructed during the recursive process.
 * @param paths - A vector accumulating valid paths from the destination back to the source.
 */

template <class T>
void Graph<T>::construirCaminhos(Vertex<T>* source, Vertex<T>* destination, const unordered_map<Vertex<T>*, vector<Vertex<T>*>>& predecessors,
                                 vector<T>& currentPath, vector<vector<T>>& paths) const {

    currentPath.push_back(destination->getInfo()); //adiciona o predecessor que foi encontrado

    //caso base, em que chegamos ao vertice inicial
    if (destination == source) { //retorna true se encontrou um dos caminhos desejados
        paths.push_back(currentPath);
        reverse(paths.back().begin(), paths.back().end());
        //inverte o resultado final para que o caminho nao esteja ao contrário
    } else {
        //caso recursivo que reconstroi todos os caminhos invertidos
        const vector<Vertex<T>*>& preds = predecessors.at(destination);
        for (Vertex<T>* pred : preds) {
            construirCaminhos(source, pred, predecessors, currentPath, paths);
        }
    }

    currentPath.pop_back();
}


/**
 * Algorithm similar to the previous one but adapted to filter based on Airlines.
 * It is necessary to have access to vertices to obtain the weight (Airline) of the respective edges used in the paths.
 * Additionally, it is crucial to have a way to access each edge associated with a vertex.
 *
 * Operates similarly to the previous algorithm, but modified to associate edges with vertices.
 *
 * This function has a time complexity of O((V+E)logV).
 *
 * @param source - The starting vertex from which the paths are initiated.
 * @param destination - The target vertex.
 * @return Vector of vectors, where each vector contains pairs of vertices and edges representing a path between source and destination.
 */

template <class T>
vector<vector<pair<Vertex<T>*, Edge<T>>>> Graph<T>::caminhosDjiskraEdges(const T &source, const T &destination) const {
    unordered_map<Vertex<T>*, int> distance;
    unordered_map<Vertex<T>*, vector<pair<Vertex<T>*, Edge<T>>>> anteriores;
    vector<vector<pair<Vertex<T>*, Edge<T>>>> paths;

    Vertex<T>* sourceVertex = findVertex(source);
    Vertex<T>* destVertex = findVertex(destination);

    if (sourceVertex == nullptr || destVertex == nullptr)
        return paths;

    for (auto v : vertexSet) {
        distance[v] = numeric_limits<int>::max();
        anteriores[v] = vector<pair<Vertex<T>*, Edge<T>>>();
    }
    distance[sourceVertex] = 0;

    priority_queue<pair<int, Vertex<T>*>, vector<pair<int, Vertex<T>*>>, greater<pair<int, Vertex<T>*>>> pq;
    pq.push(make_pair(0, sourceVertex));

    while (!pq.empty()) {
        auto currentVertex = pq.top().second;
        auto currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distance[currentVertex])
            continue;

        for (auto edge : currentVertex->getAdj()) {
            auto neighbor = edge.getDest();
            int newDistance = distance[currentVertex] + 1;

            if (newDistance < distance[neighbor]) {

                distance[neighbor] = newDistance;
                anteriores[neighbor] = {{currentVertex, edge}};
                pq.push(make_pair(newDistance, neighbor));

            } else if (newDistance == distance[neighbor]) {
                anteriores[neighbor].push_back({currentVertex, edge});
            }
        }
    }

    vector<pair<Vertex<T>*, Edge<T>>> currentPath;
    construirCaminhosEdges(sourceVertex, destVertex, anteriores, currentPath, paths);
    return paths;
}

/**
 * Version that constructs paths similarly, but with Edges associated with Vertices.
 *
 * @param source - The starting vertex of the paths being constructed.
 * @param destination - The ending vertex of the paths being constructed.
 * @param predecessors - A map that provides predecessors for each vertex to reconstruct the path.
 * @param currentPath - The current path being constructed during the recursive process.
 * @param paths - A vector that accumulates valid paths from the destination back to the source.
 */

template <class T>
void Graph<T>::construirCaminhosEdges(Vertex<T>* source, Vertex<T>* destination, const unordered_map<Vertex<T>*, vector<pair<Vertex<T>*, Edge<T>>>>& predecessors, vector<pair<Vertex<T>*, Edge<T>>>& currentPath, vector<vector<pair<Vertex<T>*, Edge<T>>>>& paths) const {

    if (destination == source) {
        paths.push_back(currentPath);
        reverse(paths.back().begin(), paths.back().end());

    } else {
        for (const auto& pred : predecessors.at(destination)) {

            const Edge<T>& edge = pred.second;
            currentPath.push_back({destination, edge});
            construirCaminhosEdges(source, pred.first, predecessors, currentPath, paths);

            currentPath.pop_back();
        }
    }
}

#endif /* GRAPH_H_ */