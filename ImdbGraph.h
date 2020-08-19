/*************************************************************************
 *
 * Project: ImdbGraph header
 *
 * File Name: ImdbGraph.h
 * Course:    CPTR 242
 * Date:      April 17, 2019
 */

#include "Array.h"
#include "Bridges.h"
#include "DataSource.h"
#include "SLelement.h"

using namespace bridges;

#ifndef IMDB_LIST_H
#define IMDB_LIST_H

// File ItemType.h must be provided by the user of this class.
//  ItemType.h must contain the following definitions:
//  MAX_ITEMS:     the maximum number of items on the list
//  ItemType:      the definition of the objects on the list
//  RelationType:  {LESS, GREATER, EQUAL}
//  Member function ComparedTo(ItemType item) which returns
//       LESS, if self "comes before" item
//       GREATER, if self "comes after" item
//       EQUAL, if self and item are the same

class ImdbGraph {
public:
  ImdbGraph();
  // Constructor

  ~ImdbGraph();
  // Destructor

  void AddVertex(string actorOrMovie);
  // Function: Adds a vertex to the graph.
  // Pre:  Graph has been initialized.
  // Post: The actor or movie will be added as a vertex.
  //          No duplicate vertics will be created.

  void AddEdge(string actorOrMovie, string movieOrActor);
  // Function: Adds a edge to the graph.
  // Pre:  Graph has been initialized.
  //          Vertics have been already added to the graph.
  // Post: The actor movie edge will be added to the graph.
  //          No duplicate edges will be created.

  void VisualizeVertex(string actorOrMovie, string color);
  // Function: Updates the visualization for to vertex.
  // Pre:  Graph has been initialized.
  //          Vertex is in the graph.
  // Post: The vertex will display the new color.

  void VisualizeEdge(string actorOrMovie, string movieOrActor, string color);
  // Function: Updates the visualization for to edge.
  // Pre:  Graph has been initialized.
  //          Edge is in the graph.
  // Post: The edge will display the new color.

  void ResetVisualizer();
  // Function: Resets all visualizations to the default.
  // Pre:  Graph has been initialized.
  // Post: The vertics and edges will display the default color.

  int GetBaconNumber(string actor1, string actor2);
  // Function: Calculates the Bacon Number for two actors.
  //           In addition to returning the number, the graph is update to
  //           highlight the path.
  //           https://en.wikipedia.org/wiki/Six_Degrees_of_Kevin_Bacon
  // Pre:  Graph has been initialized.
  //          Vertices are in the graph.
  //          Edges connect the actors in the graph.
  // Post: The number returned will be lowest number of actor connections used
  // to connect them.
  //          The graph will visually show the path to connect the actors.

  void Print(std::ofstream &dataFile);

  GraphAdjList<string> *GetGraph() { return &graph; }

private:
  GraphAdjList<string> graph;
};

#endif // IMDB_LIST_H
