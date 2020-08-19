/*************************************************************************
 *
 * Project: ImdbGraph implementation
 *
 * File Name: ImdbGraph.cpp
 * Name:      Mikhail Beresnev
 * Course:    CPTR 242
 *
 */
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

#include "Bridges.h"
#include "DataSource.h"
#include "GraphAdjList.h"
#include "ImdbGraph.h"
#include "SLelement.h"
#include "data_src/ActorMovieIMDB.h"
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace bridges;

// Constructor
ImdbGraph::ImdbGraph() {}

// Destructor
ImdbGraph::~ImdbGraph() {}

// Function: Adds a vertex to the graph.
// Pre:  Graph has been initialized.
// Post: The actor or movie will be added as a vertex.
//          No duplicate vertics will be created.
void ImdbGraph::AddVertex(string actorOrMovie) {
  unordered_map<string, Element<string> *> *vertices = graph.getVertices();
  if (vertices->find(actorOrMovie) == vertices->end()) {
    graph.addVertex(actorOrMovie);
    graph.getVisualizer(actorOrMovie)->setColor(Color("black"));
    graph.getVisualizer(actorOrMovie)->setSize(10);
    graph.getVisualizer(actorOrMovie)->setOpacity(0.5);
  }
}

// Function: Adds a edge to the graph.
// Pre:  Graph has been initialized.
//          Vertics have been already added to the graph.
// Post: The actor movie edge will be added to the graph.
//          No duplicate edges will be created.
void ImdbGraph::AddEdge(string actorOrMovie, string movieOrActor) {
  graph.addEdge(actorOrMovie, movieOrActor, "1");
  graph.addEdge(movieOrActor, actorOrMovie, "1");
}

// Function: Updates the visualization for to vertex.
// Pre:  Graph has been initialized.
//          Vertex is in the graph.
// Post: The vertex will display the new color.
void ImdbGraph::VisualizeVertex(string actorOrMovie, string color) {
  graph.getVisualizer(actorOrMovie)->setColor(Color(color));
  graph.getVisualizer(actorOrMovie)->setSize(50);
  graph.getVisualizer(actorOrMovie)->setOpacity(1.0);
}

// Function: Updates the visualization for to edge.
// Pre:  Graph has been initialized.
//          Edge is in the graph.
// Post: The edge will display the new color.
void ImdbGraph::VisualizeEdge(string actorOrMovie, string movieOrActor2,
                              string color) {
  graph.getLinkVisualizer(actorOrMovie, movieOrActor2)->setColor(Color(color));
  graph.getLinkVisualizer(movieOrActor2, actorOrMovie)->setColor(Color(color));
  graph.getLinkVisualizer(movieOrActor2, actorOrMovie)->setThickness(10.0);
  graph.getLinkVisualizer(movieOrActor2, actorOrMovie)->setThickness(10.0);
}

// Function: Resets all visualizations to the default.
// Pre:  Graph has been initialized.
// Post: The vertics and edges will display the default color.
void ImdbGraph::ResetVisualizer() {
  for (auto &vertex : *graph.getVertices()) {
    graph.getVisualizer(vertex.first)->setColor(Color("black"));

    auto sl_list = graph.getAdjacencyList(vertex.first);
    for (auto sle = sl_list; sle != NULL; sle = sle->getNext()) {
      auto destination = ((Edge<string>)sle->getValue()).to();
      graph.getLinkVisualizer(vertex.first, destination)
          ->setColor(Color("black"));
    }
  }
}

// Function: Calculates the Bacon Number for two actors.
//           In addition to returning the number, the graph is update to
//           highlight the path.
//           https://en.wikipedia.org/wiki/Six_Degrees_of_Kevin_Bacon
// Pre:  Graph has been initialized.
//          Vertices are in the graph.
//          Edges connect the actors in the graph.
// Post: The number returned will be lowest number of actor connections used to
// connect them.
//          The graph will visually show the path to connect the actors.
int ImdbGraph::GetBaconNumber(string sourceActor, string destinationActor) {
  map<string, string> findPath;
  queue<string> frontierQueue;
  set<string> discoveredSet;
  string currentV, previousV;
  bool found = false;

  // Standard rubric for the breadth first search
  // Keeps track of the bacon number depending on the layer
  frontierQueue.push(sourceActor);
  discoveredSet.insert(sourceActor);

  int baconNumber = -1;
  int counter = 1;

  while (!frontierQueue.empty()) {
    currentV = frontierQueue.front();
    frontierQueue.pop();

    if (currentV == destinationActor) {
      break;
    }

    counter--;
    if (counter == 0) {
      baconNumber++;
      found = true;
    }

    auto sl_list = graph.getAdjacencyList(currentV);

    for (auto sle = sl_list; sle != NULL; sle = sle->getNext()) {
      string vertex = ((Edge<string>)sle->getValue()).to();
      if (discoveredSet.find(vertex) == discoveredSet.end()) {
        findPath.emplace(vertex, currentV);
        frontierQueue.push(vertex);
        discoveredSet.emplace(vertex);
      }
      if (counter == 0) {
        counter = frontierQueue.size();
      }
    }
  }

  if (found) {
    string temp = currentV;
    string temp2 = findPath.at(temp);
    VisualizeVertex(temp, "green");
    VisualizeEdge(temp, temp2, "green");
    for (int i = 0; i < baconNumber - 1; i++) {
      temp = findPath.at(temp);
      temp2 = findPath.at(temp);
      VisualizeVertex(temp, "green");
      VisualizeEdge(temp, temp2, "green");
    }
    VisualizeVertex(temp2, "green");
    return baconNumber;
  }

  return -1;
}