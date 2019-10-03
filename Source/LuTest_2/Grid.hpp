#pragma once

#include <vector>
#include "Coordinate.hpp"

class Hex;

enum StepAccessibility
{
    Empty,
    haveBarriers
};

struct Node
{
public:

    Hex * m_hex;
    std::vector<Node *> m_neighbors;

    StepAccessibility m_acces;
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

    void addNode(Hex * _hex, StepAccessibility & access);

    void addNode(Hex * _hex, bool access);

    void addNodeWithotRecalculateHexGrid(Hex * _hex, StepAccessibility & access);

    void addNodeWithotRecalculateHexGrid(Hex * _hex, bool access);

    void RecalculateHexGrid();
    
    void EscapeNodeFromPath(std::vector<Node *> nodeInPath);

    Node * findNode(Hex & source);

    std::vector<Node*>::iterator findNode(Node * source);

    Node * GetNodeForCoordinates(Coordinate & _logicCoordinate);

    std::vector<Node *>  GetNeighbors(Hex * hex);

    void Clear() { m_nodes.clear(); }

};