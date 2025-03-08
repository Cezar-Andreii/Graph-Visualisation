#ifndef NODE_H
#define NODE_H
#include<QPoint>

class Node
{
public:
    Node();
    Node(int value) : value(value) {}
    int getValue() const ;
    QPoint getPos() const {return m_pos;};
    void setValue(int n){m_value=n;};
    void setPos(QPoint p ){m_pos=p;};

    bool operator==(const Node& other) const {
        return id == other.id;
    }

    bool operator<(const Node& other) const {
        return id < other.id;
    }

private:
    int m_value;
    QPoint m_pos;
    int id;
    int value;
};

#endif // NODE_H
