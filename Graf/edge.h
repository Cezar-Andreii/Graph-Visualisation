#ifndef EDGE_H
#define EDGE_H
#include "node.h"
#include<QColor>

class Edge
{
public:
    Edge();
    Edge(Node f,Node s,int cost=0): m_first(f),m_second(s),m_cost(cost){}
    Node getFirst() const {return m_first;};
    Node getSecond() const {return m_second;};
    int getCost() const { return m_cost; }
    void setCost(int cost) { m_cost = cost; }


    void setHighlighted(bool value) {
        highlighted = value;
    }
    bool isHighlighted() const { return highlighted; }

    bool operator==(const Edge& other) const {
        return (m_first.getValue() == other.m_first.getValue() && m_second.getValue() == other.m_second.getValue() && m_cost == other.m_cost);
    }

    bool isPartOfGreenMST() const {
        return m_isGreenMST;
    }

    void setGreenMST(bool value) {
        m_isGreenMST = value;
    }

    void setColor(const QColor& color) { m_color = color; }
    QColor getColor() const { return m_color; }



private:
    Node m_first, m_second;
    int m_cost;
    bool highlighted;
    bool m_isGreenMST = false;
    QColor m_color;



};

#endif // EDGE_H
