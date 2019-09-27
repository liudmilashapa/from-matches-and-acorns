#pragma once

#include <vector>
#include "Coordinate.hpp"

class Hex;

struct Node
{
public:

    Hex * m_hex;
    std::vector<Node *> m_neighbors;

    bool m_isCome = false;
    int m_path = -1;
};



class Grid
{
private:

    std::vector<Node*> m_nodes;
    
    bool IsNeighbours(Node * left, Node * right) const;
    void ClearNodeInfo(Node * pNode);

public:
    
    bool IsEmpty();

    void addNode(Hex * _hex);

    void addNodeWithotRecalculateHexGrid(Hex * _hex);

    void RecalculateHexGrid();
    
    void EscapeNodeFromPath(std::vector<Node *> nodeInPath);

    Node * findNode(Hex & source);

    std::vector<Node*>::iterator findNode(Node * source);

    std::vector<Node *>  GetNeighbors(Hex * hex);

    void Clear() { m_nodes.clear(); }

};