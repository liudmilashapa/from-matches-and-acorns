#pragma once

#include <vector>
#include "Coordinate.hpp"
#include "TransformCoordinate.hpp"



class Grid;
struct Node;

class PathSearch
{

private:

    Grid & m_grid;
    std::vector<Node *> m_pPath;
    //bool IsCoordinateValid(Coordinate &_coordinate);
    //void addNeighbors(Coordinate * _coordinate, Node & node);

    void SetPathNeighbours(Node & sourceNode);

    void SetAllPathes(Node * source);

    void ConstructorPath(Node & sourceNode, Node & destinationNode, std::vector<Node *>& inputPathVector);
    void ConstructorPath(Hex * sourceHex, Hex * destinationHex, std::vector< Hex *>& inputPathVector);
    
 

public:

    //void findPath(const Coordinate & _coordinate);

    PathSearch(Grid & grid);

    bool IsPathEmpty();
      
    void CreatePath(Hex * source, Hex * destination);

    std::vector<Node *> GetPath();

    std::vector<Hex *> GetHexInPath();

//    Coordinate & setPath(Coordinate & _coordinate);
};
