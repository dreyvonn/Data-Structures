#include <iostream>
#include <set>
#include "graph.h"
using namespace std;
/***************************************************
 * GRAPH : COPY CONSTURCTOR
 **************************************************/
Graph :: Graph(const Graph & rhs) throw (const char *)
{  
   verticies = rhs.verticies;
   
   s = new std::set <Vertex> [rhs.verticies];
   
   for(int i = 0; i < verticies; i++)
   {
      s[i] = rhs.s[i];
   }
}

/***************************************************
 * GRAPH : ASSIGNMENT OPERATOR
 **************************************************/
Graph & Graph::operator = (const Graph & rhs) throw (const char *)
{
   if (!empty())
   {
      clear();
      delete [] s;
      s = NULL;
   }
   
   verticies = rhs.verticies;
   
   s = new std::set <Vertex> [rhs.verticies];
   
   for(int i = 0; i < verticies; i++)
   {
      s[i] = rhs.s[i];
   }
   
   return *this;
}

/***************************************************
 * GRAPH : CLEAR
 **************************************************/
void Graph::clear()
{
   if (s != NULL)
   {
      for (int i = 0; i < size(); i++)
      {
         s[i].clear();
      }
   }
}

/***************************************************
 * GRAPH : ADD
 **************************************************/
void Graph::add(const Vertex & v1, const Vertex & v2)
{
   s[v1.index()].insert(v2);
}

/***************************************************
 * GRAPH : ADD
 **************************************************/
void Graph::add(const Vertex & v1, const std::set<Vertex> & v2)
{
   for(std::set <Vertex>::iterator it = v2.begin(); it != v2.end(); ++it)
   {
      s[v1.index()].insert(*it);
   }
}

/***************************************************
 * GRAPH : IS EDGE
 **************************************************/
bool Graph::isEdge(const Vertex & v1, const Vertex & v2) const
{
   return s[v1.index()].find(v2) != s[v1.index()].end();
}

/***************************************************
 * GRAPH : FIND EDGES
 **************************************************/
std::set <Vertex> Graph :: findEdges(const Vertex & v1)
{
   return s[v1.index()];
}
