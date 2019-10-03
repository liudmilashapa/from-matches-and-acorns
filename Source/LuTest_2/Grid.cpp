
#include "Grid.hpp"

#include "Hex.hpp"


void Grid::ClearNodeInfo(Node * pNode)
{
    pNode->m_neighbors.clear();
    pNode->m_isCome = false;// ???
    pNode->m_path = -1;
}

bool Grid::IsEmpty()
{
    return m_nodes.size() == 0;
}

void Grid::addNode(Hex * _hex, bool access)
{
    addNodeWithotRecalculateHexGrid(_hex, access);
    RecalculateHexGrid();

}

void Grid::addNode(Hex * _hex, StepAccessibility & access)
{
    addNodeWithotRecalculateHexGrid(_hex, access);
    RecalculateHexGrid();

}

void Grid::addNodeWithotRecalculateHexGrid(Hex * _hex, StepAccessibility & access)
{
    if (!findNode(*_hex))
    {
        Node * node = new Node();
        node->m_hex = _hex;
        node->m_acces = access;
        m_nodes.push_back(node);
    }
}

void Grid::addNodeWithotRecalculateHexGrid(Hex * _hex, bool access)
{
    if (!findNode(*_hex))
    {
        Node * node = new Node();
        node->m_hex = _hex;
        node->m_acces = access ? StepAccessibility::Empty: StepAccessibility::haveBarriers;
        m_nodes.push_back(node);
    }
}

bool Grid::IsNeighbours(Node * left, Node * right) const
{
    Coordinate * lhsCoords = left->m_hex->GetLogicCoordinates();
    Coordinate * rhsCoords = right->m_hex->GetLogicCoordinates();

    //if (
    //       (abs(lhsCoords.GetX() - rhsCoords.GetX()) > 1)
    //    || (abs(lhsCoords.GetY() - rhsCoords.GetY()) > 1)
    //    || (abs(lhsCoords.GetZ() - rhsCoords.GetZ()) > 1)
    //    )
    //{
    //    return false;
    //}

    return
        (
           (
            abs(lhsCoords->GetX() - rhsCoords->GetX())
            + abs(lhsCoords->GetY() - rhsCoords->GetY())
            + abs(lhsCoords->GetZ() - rhsCoords->GetZ())
            )
            == 2
        &&
            (
                    left->m_acces == StepAccessibility::Empty 
                &&  right->m_acces == StepAccessibility::Empty
            )
        );
}

void Grid::RecalculateHexGrid()
{
    for (Node * pNode : m_nodes)
    {
        ClearNodeInfo(pNode);
    }

    int nodesCount = m_nodes.size();

    for (int i = 0; i < nodesCount; ++i)
    {
        for (int j = i + 1; j < nodesCount; ++j)
        {
            if (IsNeighbours(m_nodes[i], m_nodes[j])) 
            {
                m_nodes[i]->m_neighbors.push_back(m_nodes[j]);
                m_nodes[j]->m_neighbors.push_back(m_nodes[i]);
            }
        }
    }

}

void Grid::EscapeNodeFromPath(std::vector<Node *> nodeInPath)
{
    for (Node * node : nodeInPath)
    {
        auto it = findNode(node);
        if (it!=m_nodes.end())
        {
            (*it)->m_path = -1;
            (*it)->m_isCome = false;
        }
    }
}

Node * Grid::findNode(Hex & source)
{
    for (auto node : m_nodes)
    {
        if (node->m_hex == &source)
        {
            return node;
        }
    }
    return nullptr;
}

std::vector<Node*>::iterator Grid::findNode(Node * source)
{
    return std::find(m_nodes.begin(), m_nodes.end(), source);
}


Node * Grid::GetNodeForCoordinates(Coordinate & _logicCoordinate) 
{
    for (auto node : m_nodes)
    {
        if (*node->m_hex->Get2DCoordinates() == _logicCoordinate)
        {
            return node;
        }
    }
    return nullptr;
}

std::vector<Node *> Grid::GetNeighbors(Hex * hex)
{
    Node * sourceNode = findNode(*hex);
    return sourceNode->m_neighbors;
}
