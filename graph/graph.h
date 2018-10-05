/***********************************************************************
 * Header:
 *    Graph
 * Summary:
 *    Contains a Graph. 
 * Author
 *    Sam Haymond, Emily Peck, Emily Barrera
 ************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include <set>
#include "list.h"

class Graph
{
public:
   Graph(const int & verticies) { this->verticies = verticies; 
                                 s = new std::set <Vertex> [verticies]; }
   Graph(const Graph & rhs) throw (const char *);
   ~Graph() { clear(); }

   Graph & operator = (const Graph & rhs) throw (const char *);

   int  size   () const { return verticies;    }
   bool empty  () const { return size() == 0; }
   int capacity() const { return -1;          }
   void clear  ();

   bool isEdge(const Vertex & v1, const Vertex & v2) const;
   std::set <Vertex> findEdges(const Vertex & v1);
   //list <Vertex> findPath(const Vertex & v1, const Vertex & v2) {}
   void add(const Vertex & v1, const Vertex & v2);
   void add(const Vertex & v1, const std::set<Vertex> & v2);

private:
   int verticies;
   std::set <Vertex> * s;
};

#endif
