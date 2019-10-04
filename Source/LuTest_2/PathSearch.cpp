
#include <set>
#include "Grid.hpp"

#include "PathSearch.hpp"
#include "God.h"
#include"HexActor.h"
#include "TransformCoordinate.hpp"
#include"Hex.hpp"


PathSearch::PathSearch (Grid & grid)
:m_grid(grid){}

bool PathSearch::IsPathEmpty()
{
    return m_pPath.empty();
}

void PathSearch::SetPathNeighbours(Node & sourceNode)
{
    std::set<Node *> queOld;
    queOld.insert(&sourceNode);
    std::set<Node *>::iterator it=queOld.begin(); 
    std::set<Node *> queYang;
   
    while (!queOld.empty())
    {
        
        queYang.clear();
        for (Node * node : (*it)->m_neighbors)
        {
            if (node->m_isCome)
            {
                if (node->m_path > (*it)->m_path + 1)
                {
                    node->m_path = (*it)->m_path + 1;
                    queYang.insert(node);

                }
            }
            else
            {
                node->m_path = (*it)->m_path + 1;
                node->m_isCome = true;
                queYang.insert(node);
            }
        }
        queOld.erase(it);
        queOld.insert(queYang.begin(), queYang.end());
        it = queOld.begin();
    }

    /*for (Node * node : sourceNode.m_neighbors)
    {
        if (node->m_isCome)
        {
            if (node->m_path > sourceNode.m_path + 1)
            {
                node->m_path = sourceNode.m_path + 1;
                  sourceNode.m_isCome = true;
            }
        }
        else
        {
            node->m_path = sourceNode.m_path + 1;
            sourceNode.m_isCome = true;
            
        }
    } 
    for (Node * node : sourceNode.m_neighbors)
    {
        SetPathNeighbours(*node);
    }*/
}

//void PathSearch::SetPathNeighbours(Node & sourceNode)
//{
//    sourceNode.m_isCome = true;
//
//    for (Node * node : sourceNode.m_neighbors)
//    {
//        if (node->m_isCome)
//        {
//            if (node->m_path > sourceNode.m_path + 1)
//            {
//                node->m_path = sourceNode.m_path + 1;
//                SetPathNeighbours(*node);
//            }
//        }
//        else
//        {
//            node->m_path = sourceNode.m_path + 1;
//            SetPathNeighbours(*node);
//        }
//    }
//}



void PathSearch::SetAllPathes(Node * sourceNode)
{
    sourceNode->m_path = 0;
    sourceNode->m_isCome = true;
    SetPathNeighbours(*sourceNode);
}

void PathSearch::ConstructorPath(Node & sourceNode, Node & destinationNode, std::vector<Node *>& inputPathVector)
{

    for (auto node : destinationNode.m_neighbors)
    {
        if (node->m_path == destinationNode.m_path-1)
        {
            inputPathVector.push_back(node);
            if (inputPathVector.back()->m_path == 0)
            {
                return;
            }
            ConstructorPath( sourceNode, *node, inputPathVector);
            break;
        }
    } 
}

void PathSearch::ConstructorPath(Hex * sourceHex, Hex * destinationHex, std::vector< Hex *>& inputPathVector)
{
    Node * destinationNode = m_grid.findNode(*destinationHex);
    Node *sourceNode = m_grid.findNode(*sourceHex);

    for (auto node : destinationNode->m_neighbors)
    {
        if (node->m_path == destinationNode->m_path - 1)
        {
            inputPathVector.push_back(node->m_hex);
            if (node->m_path == 0)
            {
                return;
            }
            ConstructorPath( sourceNode->m_hex, node->m_hex,  inputPathVector);
            break;
        }
    }
}




void PathSearch::SetIsInPath()
{ 
    AGod * God = AGod::GetGodClass();
     
    for (auto node : m_pPath)
    {
        AHexActor * actor = &God->GetTransformCoordinate().getAHexActor(*node->m_hex);
        if (node->m_path == -1)
        {
            actor->SetInPath(EIsInPath::Empty);
        }
        else if (actor->HasEnemy())
        {
            actor->SetInPath(EIsInPath::EnemyNext);
        }
        else 
        {
            actor->SetInPath(EIsInPath::InPath);
        }
    }
}

void PathSearch::CreatePath(Hex * source, Hex * destination)
{
    m_grid.RecalculateHexGrid();
    Node * sourceNode = m_grid.findNode(*source);
    Node * destinationNode = m_grid.findNode(*destination);
    SetAllPathes(sourceNode);
    m_pPath.push_back(destinationNode);
    ConstructorPath(*sourceNode, *destinationNode, m_pPath);
    SetIsInPath();

 }


std::vector<Node *> PathSearch::GetPath()
{
    return m_pPath;
}

std::vector<Hex *> PathSearch::GetHexInPath()
{
    std::vector<Hex *> inputPath;
    for (Node * node : m_pPath)
    {
        inputPath.push_back(node->m_hex);
    }
    return inputPath;
}

//
//void PathSearch::ConstructorPathNeighboursSearch(Hex * sourceHex, Hex * destinationHex, std::vector< Hex *>& inputPathVector)
//{
//
//}


//Coordinate & PathSearch::setPath(Coordinate & _coordinate)
//{
// auto it = std::find_if(m_nodes.begin(), m_nodes.end(), [_coordinate](Node * node)
//        {
//            return (_coordinate.IsEqual(node->m_logicCoordinates));
//        });
//    check(it != m_nodes.end());
//    setPath(it->)
//
//}


//bool PathSearch::IsCoordinateValid(Coordinate & _coordinate)
//{
//    TransformCoordinate * transformCoordinate = TransformCoordinate::getInstance();
//    return transformCoordinate->IsLogicCoordinateValid(_coordinate);
//}

//void PathSearch::addNeighbors(Coordinate * _coordinate, Node & node)
//{
//    if (IsCoordinateValid(*_coordinate))
//    {
//        node.m_neighbors.push_back(Coordinate(*_coordinate));
//    }
//}
//

//void PathSearch::SetPath(Node & sourceNode)
//{
//    
//}
