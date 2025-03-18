// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <map>
#include "../data_structures/CSV.h"
#include "../data_structures/MutablePriorityQueue.h" // not needed for now

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int in, int p);    // adicionamos info do parking no constructor
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    int getInfo() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setInfo(int info);
    void setVisited(bool visited);
    void setParking(int park);  //adicionamos o setter do parking
    void setProcessing(bool processing);

    int getLow() const;
    int getParking() const;  //adicionamos o getter do parking
    void setLow(int value);
    int getNum() const;
    void setNum(int value);

    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge* addEdge(Vertex *dest, double d, double w);
    bool removeEdge(int in);
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;
protected:
    int info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    int low = -1, num = -1; // used by SCC Tarjan
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    int parking; // adicionamos parking var (0 s/ park or 1 c/ park)

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double d, double w);

    Vertex * getDest() const;
    double getDrive() const;
    double getWalk() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    double drive; // edge weight when driving, can also be used for capacity
    double walk; // edge weight when walking, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const int &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &in, int &parking);
    bool removeVertex(const int &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double d, double w);
    bool removeEdge(const int &source, const int &dest);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double d, double w);

    int getNumVertex() const;

    bool constructCity();

    std::vector<Vertex *> getVertexSet() const;


protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &in) const;
    /**
    * Auxiliary function to set the "path" field to make a spanning tree.
    */

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


/************************* Vertex  **************************/

inline Vertex::Vertex(int in, int p): info(in), parking(p) {}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

inline Edge* Vertex::addEdge(Vertex *b, double d, double w) {
    auto newEdge = new Edge(this, b, d, w);
    adj.push_back(newEdge);
    b->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

inline bool Vertex::removeEdge(int in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
inline void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

inline bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

inline int Vertex::getInfo() const {
    return this->info;
}

inline int Vertex::getLow() const {
    return this->low;
}

inline void Vertex::setLow(int value) {
    this->low = value;
}

//adicionamos o setParking
inline void Vertex::setParking(int value) {
    this->parking = value;
}

//adicionamos o getParking
inline int Vertex::getParking() const {
    return this->low;
}

inline int Vertex::getNum() const {
    return this->num;
}

inline void Vertex::setNum(int value) {
    this->num = value;
}

inline std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

inline bool Vertex::isVisited() const {
    return this->visited;
}

inline bool Vertex::isProcessing() const {
    return this->processing;
}

inline unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

inline double Vertex::getDist() const {
    return this->dist;
}

inline Edge* Vertex::getPath() const {
    return this->path;
}

inline std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

inline void Vertex::setInfo(int in) {
    this->info = in;
}

inline void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

inline void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

inline void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

inline void Vertex::setDist(double dist) {
    this->dist = dist;
}

inline void Vertex::setPath(Edge *path) {
    this->path = path;
}

inline void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

inline Edge::Edge(Vertex *orig, Vertex *dest, double d, double w): orig(orig), dest(dest), drive(d), walk(w) {} //mudamos o construtor

inline Vertex* Edge::getDest() const {
    return this->dest;
}

inline double Edge::getDrive() const {
    return this->drive;
}

inline double Edge::getWalk() const {
    return this->walk;
}

inline Vertex* Edge::getOrig() const {
    return this->orig;
}

inline Edge* Edge::getReverse() const {
    return this->reverse;
}

inline bool Edge::isSelected() const {
    return this->selected;
}

inline double Edge::getFlow() const {
    return flow;
}

inline void Edge::setSelected(bool selected) {
    this->selected = selected;
}

inline void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

inline void Edge::setFlow(double flow) {
    this->flow = flow;
}

/********************** Graph  ****************************/

inline int Graph::getNumVertex() const {
    return vertexSet.size();
}

inline std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
inline Vertex* Graph::findVertex(const int &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
inline int Graph::findVertexIdx(const int &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
inline bool Graph::addVertex(const int &in, int& parking) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in, parking));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
inline bool Graph::removeVertex(const int &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
inline bool Graph::addEdge(const int &sourc, const int &dest, double d, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, d, w);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
inline bool Graph::removeEdge(const int &sourc, const int &dest) {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

inline bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double d, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, d, w);
    auto e2 = v2->addEdge(v1, d, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/*!
 * Function for constructing a city/graph
 * @retval true if the construction was successful
 * @retval false if it was not
 */
inline bool Graph::constructCity() {

    // read Locations.csv;

    Csv *csv_file = new Csv();
    // csv_file->readCSV("../data/Locations.csv");  uncomment for creating the real graph
    csv_file->readCSV("../data/Locations_test.csv");

    if (csv_file->getData().empty()) {
        std::cerr << "Failed to read Locations.csv or file is empty." << std::endl;
        return false;
    }

    std::map<std::string, int> loc_IdCode;      // maps each code to its id

    // create vertexes; create map
    for (auto loc_info : csv_file->getData()) {
        int locId = std::stoi(loc_info[1]); // Convert loc ID to int
        int parkingStatus = std::stoi(loc_info[3]); // Convert parking status to int

        this->addVertex(locId, parkingStatus);
        loc_IdCode[loc_info[2]] = locId;
    }

    // read distances

    // csv_file->readCSV("../data/Distances.csv");      // uncomment for the real graph
    csv_file->readCSV("../data/Distances_test.csv");

    if (csv_file->getData().empty()) {
        std::cerr << "Failed to read Distances.csv or file is empty." << std::endl;
        return false;
    }

    // create edges
    for (auto edge_info : csv_file->getData()) {
        auto source = loc_IdCode[edge_info[0]];
        auto dest = loc_IdCode[edge_info[1]];

        // handle the case when you cant drive
        this->addBidirectionalEdge(source, dest, edge_info[2] == "X" ? INF : stoi(edge_info[2]), stoi(edge_info[3]));
    }

    return true;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

#endif /* DA_TP_CLASSES_GRAPH */