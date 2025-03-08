#ifndef GRAPH_H
#define GRAPH_H
#include"edge.h"
#include<vector>
#include<QMessageBox>
#include <QFile>
#include <QTextStream>
#include<stack>
#include <algorithm>
#include<set>

class Graph
{
public:
    Graph();

    void setOrientation(bool oriented) { isOriented = oriented; }
    bool getOrientation() const { return isOriented; }

    std::vector<std::vector<int>>& getAdjacencyMatrix() { return m_adjacencyMatrix; }

    bool addNode(QPoint p)
    {
        for (auto &node : m_nodes) {
            int dx = node.getPos().x() - p.x();
            int dy = node.getPos().y() - p.y();
            if ((dx * dx + dy * dy) <= (10 * 10)) {
                return false;
            }
        }
        //verificare suprapunere noduri
        Node n;
        n.setPos(p);
        n.setValue(m_nodes.size()+1);
        m_nodes.push_back(n);

        // Actualizăm matricea de adiacență;
        size_t newSize = m_nodes.size();
        for (auto& row : m_adjacencyMatrix) {
            row.resize(newSize, 0);
        }
        // Salvăm matricea de adiacență în fișier
        m_adjacencyMatrix.resize(newSize, std::vector<int>(newSize, 0));
        saveAdjacencyMatrixToFile("adjacency_matrix.txt");
        return true;
    };



    void addEdge(Node f, Node s, int cost)
    {
        int fromIndex = f.getValue() - 1;
        int toIndex = s.getValue() - 1;

        if (fromIndex < 0 || fromIndex >= m_nodes.size() ||
            toIndex < 0 || toIndex >= m_nodes.size()) {
            QMessageBox::warning(nullptr, "Error", "Invalid edge index.");
            return;
        }


        if (m_adjacencyMatrix[fromIndex][toIndex] != 0) {
            QMessageBox::warning(nullptr, "Error", "Edge already exists between these two nodes.");
            return;
        }


        Edge e(f, s, cost);
        m_edges.push_back(e);


        m_adjacencyMatrix[fromIndex][toIndex] = cost;

        if (!isOriented) {
            m_adjacencyMatrix[toIndex][fromIndex] = cost;
        }


        saveAdjacencyMatrixToFile("adjacency_matrix.txt");
    }




    std::vector<Node>& getNodes(){return m_nodes;};
    std::vector<Edge>& getEdges(){return m_edges;};


    bool isTree() {
        if (m_nodes.empty()) return false;

        std::vector<bool> visited(m_nodes.size(), false);

        std::stack<std::pair<int, int>> stack;
        stack.push({0, -1});

        while (!stack.empty()) {
            auto [node, parent] = stack.top();
            stack.pop();

            if (visited[node]) return false;

            visited[node] = true;

            for (size_t i = 0; i < m_adjacencyMatrix[node].size(); ++i) {
                if (m_adjacencyMatrix[node][i]) {
                    if (!visited[i]) {
                        stack.push({i, node});
                    } else if ((int)i != parent) {
                        return false;
                    }
                }
            }
        }

        for (bool v : visited) {
            if (!v) return false;
        }

        return true;
    }

    int findRoot() {
        if (m_nodes.empty()) return -1;

        auto canReachAllNodes = [&](int start) -> bool {
            std::vector<bool> visited(m_nodes.size(), false);
            std::stack<int> stack;
            stack.push(start);

            int count = 0;
            while (!stack.empty()) {
                int current = stack.top();
                stack.pop();

                if (!visited[current]) {
                    visited[current] = true;
                    ++count;

                    for (size_t i = 0; i < m_adjacencyMatrix[current].size(); ++i) {
                        if (m_adjacencyMatrix[current][i] && !visited[i]) {
                            stack.push(i);
                        }
                    }
                }
            }

            return count == m_nodes.size();
        };

        for (size_t i = 0; i < m_nodes.size(); ++i) {
            if (canReachAllNodes(i)) {
                return m_nodes[i].getValue();
            }
        }

        return -1;
    }


    std::vector<std::vector<Node>> getConnectedComponents() {
        std::vector<bool> visited(m_nodes.size(), false);
        std::vector<std::vector<Node>> components;
        for (size_t i = 0; i < m_nodes.size(); ++i) {
            if (!visited[i]) {
                std::vector<Node> component;
                std::stack<int> stack;
                stack.push(i);

                while (!stack.empty()) {
                    int nodeIndex = stack.top();
                    stack.pop();

                    if (!visited[nodeIndex]) {
                        visited[nodeIndex] = true;
                        component.push_back(m_nodes[nodeIndex]);

                        for (size_t j = 0; j < m_adjacencyMatrix[nodeIndex].size(); ++j) {
                            if (m_adjacencyMatrix[nodeIndex][j] && !visited[j]) {
                                stack.push(j);
                            }
                        }
                    }
                }

                components.push_back(component);
            }
        }

        return components;
    }


    std::vector<Edge> findMSTWithKruskal() {
        std::vector<Edge> mstEdges;
        std::vector<int> parent(m_nodes.size());
        std::vector<int> rank(m_nodes.size(), 0);


        for (int i = 0; i < m_nodes.size(); ++i) {
            parent[i] = i;
        }


        std::vector<Edge> sortedEdges = m_edges;
        std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& a, const Edge& b) {
            return a.getCost() < b.getCost();
        });


        std::function<int(int)> find = [&](int node) -> int {
            if (parent[node] != node) {
                parent[node] = find(parent[node]);
            }
            return parent[node];
        };

        auto unionSets = [&](int u, int v) {
            int rootU = find(u);
            int rootV = find(v);

            if (rootU != rootV) {
                if (rank[rootU] > rank[rootV]) {
                    parent[rootV] = rootU;
                } else if (rank[rootU] < rank[rootV]) {
                    parent[rootU] = rootV;
                } else {
                    parent[rootV] = rootU;
                    rank[rootU]++;
                }
            }
        };


        for (const auto& edge : sortedEdges) {
            int u = edge.getFirst().getValue() - 1;
            int v = edge.getSecond().getValue() - 1;

            if (find(u) != find(v)) {
                mstEdges.push_back(edge);
                unionSets(u, v);

                if (mstEdges.size() == m_nodes.size() - 1) {
                    break;
                }
            }
        }

        return mstEdges;
    }



    void highlightMSTEdges(const std::vector<Edge>& mstEdges) {

        for (auto& edge : m_edges) {
            edge.setHighlighted(false);
        }


        for (const auto& edge : mstEdges) {
            auto it = std::find(m_edges.begin(), m_edges.end(), edge);
            if (it != m_edges.end()) {
                it->setHighlighted(true);
                it->setColor(Qt::green);
            }
        }
    }

    void highlightGenericTreeEdges(const std::vector<Edge>& genericEdges) {

        for (auto& edge : m_edges) {
            edge.setHighlighted(false);
            edge.setColor(Qt::black);
        }

        for (const auto& edge : genericEdges) {
            auto it = std::find_if(m_edges.begin(), m_edges.end(), [&edge](const Edge& e) {
                return e.getFirst().getValue() == edge.getFirst().getValue() &&
                       e.getSecond().getValue() == edge.getSecond().getValue() &&
                       e.getCost() == edge.getCost();
            });
            if (it != m_edges.end()) {
                it->setHighlighted(true);
                it->setColor(Qt::red);
            }
        }

    }

    void highlightBoruvkaMSTEdges() {

        std::vector<Edge> mstEdges = boruvkaMST();


        for (auto& edge : m_edges) {
            edge.setHighlighted(false);
            edge.setColor(Qt::black);
        }


        for (const auto& edge : mstEdges) {
            auto it = std::find_if(m_edges.begin(), m_edges.end(), [&edge](const Edge& e) {
                return e.getFirst().getValue() == edge.getFirst().getValue() &&
                       e.getSecond().getValue() == edge.getSecond().getValue() &&
                       e.getCost() == edge.getCost();
            });
            if (it != m_edges.end()) {
                it->setHighlighted(true);
                it->setColor(Qt::blue);
            }
        }
    }


    std::vector<Edge>getGenericTree() {
        std::vector<Edge> mst;
        size_t n = m_nodes.size();
        std::vector<bool> inMST(n, false);
        std::vector<float> minCost(n, std::numeric_limits<float>::max());
        std::vector<int> parent(n, -1);

        minCost[0] = 0;

        for (size_t i = 0; i < n - 1; ++i) {
            float minEdgeCost = std::numeric_limits<float>::max();
            int u = -1;

            for (size_t v = 0; v < n; ++v) {
                if (!inMST[v] && minCost[v] < minEdgeCost) {
                    minEdgeCost = minCost[v];
                    u = v;
                }
            }

            if (u == -1) break;

            inMST[u] = true;

            for (size_t v = 0; v < n; ++v) {
                if (!inMST[v] && m_adjacencyMatrix[u][v] > 0) {
                    float weight = m_adjacencyMatrix[u][v];
                    if (weight < minCost[v]) {
                        minCost[v] = weight;
                        parent[v] = u;
                    }
                }
            }
        }

        for (size_t v = 1; v < n; ++v) {
            if (parent[v] != -1) {
                Edge edge(m_nodes[parent[v]], m_nodes[v], m_adjacencyMatrix[parent[v]][v]);
                mst.push_back(edge);
            }
        }

        return mst;
    }





    std::vector<Edge> computePrimMST() {
        if (m_nodes.empty()) return {};

        size_t n = m_nodes.size();
        std::vector<bool> inMST(n, false);
        std::vector<int> minCost(n, INT_MAX);
        std::vector<int> parent(n, -1);

        minCost[0] = 0;
        std::vector<Edge> mstEdges;

        for (size_t count = 0; count < n; ++count) {
            int u = -1;


            for (size_t i = 0; i < n; ++i) {
                if (!inMST[i] && (u == -1 || minCost[i] < minCost[u])) {
                    u = i;
                }
            }


            if (u == -1 || minCost[u] == INT_MAX) break;
            inMST[u] = true;


            if (parent[u] != -1) {
                Node from = m_nodes[parent[u]];
                Node to = m_nodes[u];
                int cost = minCost[u];
                mstEdges.emplace_back(from, to, cost);
            }


            for (size_t v = 0; v < n; ++v) {
                if (m_adjacencyMatrix[u][v] && !inMST[v] && m_adjacencyMatrix[u][v] < minCost[v]) {
                    minCost[v] = m_adjacencyMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        return mstEdges;
    }

    int findSet(Node* node, const std::vector<std::vector<Node*>>& sets)
    {
        for (size_t index = 0; index < sets.size(); index++)
        {
            if (std::find(sets[index].begin(), sets[index].end(), node) != sets[index].end())
                return index;
        }
        return -1;
    }



    std::vector<Edge> boruvkaMST() {

        if (isOriented) {
            QMessageBox::warning(nullptr, "Eroare", "Borůvka se aplică doar pe grafuri neorientate.");
            return {};
        }

        int n = m_nodes.size();
        if (n == 0) return {};

        std::vector<std::set<int>> components(n);
        for (int i = 0; i < n; ++i) {
            components[i].insert(i);
        }

        std::vector<Edge> mstEdges;
        int mstSize = 0;

        while (mstSize < n - 1) {
            std::vector<int> cheapestEdge(n, -1);

            for (size_t i = 0; i < m_edges.size(); ++i) {
                const Edge& edge = m_edges[i];
                int u = edge.getFirst().getValue() - 1;
                int v = edge.getSecond().getValue() - 1;
                int cost = edge.getCost();

                int compU = -1, compV = -1;

                for (int j = 0; j < n; ++j) {
                    if (components[j].count(u)) compU = j;
                    if (components[j].count(v)) compV = j;
                }

                if (compU != compV) {
                    if (cheapestEdge[compU] == -1 || m_edges[cheapestEdge[compU]].getCost() > cost) {
                        cheapestEdge[compU] = i;
                    }
                    if (cheapestEdge[compV] == -1 || m_edges[cheapestEdge[compV]].getCost() > cost) {
                        cheapestEdge[compV] = i;
                    }
                }
            }

            for (int i = 0; i < n; ++i) {
                if (cheapestEdge[i] != -1) {
                    const Edge& edge = m_edges[cheapestEdge[i]];
                    int u = edge.getFirst().getValue() - 1;
                    int v = edge.getSecond().getValue() - 1;

                    int compU = -1, compV = -1;
                    for (int j = 0; j < n; ++j) {
                        if (components[j].count(u)) compU = j;
                        if (components[j].count(v)) compV = j;
                    }

                    if (compU != compV) {
                        mstEdges.push_back(edge);
                        mstSize++;

                        components[compU].insert(components[compV].begin(), components[compV].end());
                        components[compV].clear();
                    }
                }
            }
        }

        return mstEdges;
    }





private:
    /*
    void saveAdjacencyMatrixToFile(const QString& filename) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << m_nodes.size() << "\n"; // Prima linie: numărul de noduri

            for (size_t i = 0; i < m_adjacencyMatrix.size(); ++i) {
                const auto& row = m_adjacencyMatrix[i];
                for (size_t j = 0; j < row.size(); ++j) {
                    out << (row[j] ? 1 : 0); // 1 dacă există arc, 0 altfel
                    if (j < row.size() - 1) out << " "; // Spațiu între elemente
                }
                out << "\n"; // Linia următoare pentru următorul rând
            }

            file.close();
        } else {
            QMessageBox::warning(nullptr, "Eroare", "Nu s-a putut deschide fișierul pentru salvare.");
        }
    }
*/
    void saveAdjacencyMatrixToFile(const QString& filename) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << m_nodes.size() << "\n";


            for (size_t i = 0; i < m_adjacencyMatrix.size(); ++i) {
                const auto& row = m_adjacencyMatrix[i];
                for (size_t j = 0; j < row.size(); ++j) {
                    out << row[j];
                    if (j < row.size() - 1) out << " ";
                }
                out << "\n";
            }

            file.close();
        } else {
            QMessageBox::warning(nullptr, "Error", "Could not open the file for saving.");
        }
    }


    bool formsCycle(const Edge& edge, const std::vector<Node>& visitedNodes) {

        for (const auto& node : visitedNodes) {
            if (node.getValue() == edge.getFirst().getValue() || node.getValue() == edge.getSecond().getValue()) {
                return true;
            }
        }
        return false;
    }




    std::vector<Node> m_nodes;
    std::vector<Edge> m_edges;
    std::vector<std::vector<int>> m_adjacencyMatrix;
    bool isOriented;
    //std::vector<Edge>mstEdges;
    std::vector<Edge> edges;
};

#endif // GRAPH_H
