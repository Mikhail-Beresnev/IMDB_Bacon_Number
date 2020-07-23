/*************************************************************************
 *
 * Project: IMDB Actor and Movie Linked List
 *
 * File Name: ImdbDriver.cpp
 * Course:    CPTR 242
 * Date:      April 17, 2019
 */
#include "ImdbGraph.h"
#include "Array.h"
#include "Bridges.h"
#include "BridgesUser.h"
#include "DataSource.h"
#include "ImdbGraphTest.h"
#include "SLelement.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void ImdbGraphTest(std::string inFileName, std::string outFileName,
                   std::string outputLabel) {
  // Used for test driver functionality.
  std::ifstream inFile;
  std::ofstream outFile;
  std::string option;

  // Used to interact with Actor/Movie graph.
  std::string vertex;
  std::string vertex2;
  std::string color;

  ImdbGraph imdbGraph;
  bool found; // For use with GetActor
  int numOptions;

  // Prompt for file names, read file names, and prepare files
  inFile.open(inFileName.c_str());
  outFile.open(outFileName.c_str());
  outFile << outputLabel << std::endl;
  if (!inFile) {
    std::cout << "File not found." << std::endl;
    return;
  }

  inFile >> option;

  // create the Bridges object, set credentials
  BridgesUser bUser;
  Bridges bridges(bUser.getBridgesNumber(), bUser.getBridgesUserID(),
                  bUser.getBridgesAPIKey());

  bridges.setTitle("List with IMDB Actor/Movie Data");
  bridges.setDescription("Here the data is processed to be a graph of actors "
                         "with all movies they have been in.");

  // get the actor movie IMDB data
  DataSource ds(&bridges);
  vector<ActorMovieIMDB> am_imdb = ds.getActorMovieIMDBData();

  // Test driver menu and options
  numOptions = 0;
  while (option != "Quit") {
    std::cout << option;
    if (option == "Menu") {
      outFile << "Select options" << std::endl;
      outFile << "AddVertex. Add Vertex to the graph." << std::endl;
      outFile << "AddEdge. Add edge to the graph." << std::endl;
      outFile << "GetBaconNumber. Calculates the Bacon Number." << std::endl;
      outFile << "VisualizeVertex. Change the color of the vertex."
              << std::endl;
      outFile << "VisualizeEdge. Change the color of the edge." << std::endl;
      outFile << "ResetVisualize. Reset the visualization of all edges and "
                 "vertices."
              << std::endl;
      outFile
          << "Visualize. Builds the bridges visualization and prints the URL."
          << std::endl;
      outFile << "AddAll. Adds all actors and movies to the graph."
              << std::endl;
      outFile << "Quit. Quit application." << std::endl;
      outFile << "Menu. Display menu." << std::endl;
    } else if (option == "AddVertex") {
      inFile >> vertex;
      imdbGraph.AddVertex(vertex);
    } else if (option == "AddEdge") {
      inFile >> vertex;
      inFile >> vertex2;
      imdbGraph.AddEdge(vertex, vertex2);
    } else if (option == "GetBaconNumber") {
      inFile >> vertex;
      inFile >> vertex2;
      int baconNumber = imdbGraph.GetBaconNumber(vertex, vertex2);
      outFile << vertex << " and " << vertex2 << " have a Bacon Number of "
              << baconNumber << "." << std::endl;
    } else if (option == "VisualizeVertex") {
      inFile >> vertex;
      inFile >> color;
      imdbGraph.VisualizeVertex(vertex, color);
    } else if (option == "VisualizeEdge") {
      inFile >> vertex;
      inFile >> vertex2;
      inFile >> color;
      imdbGraph.VisualizeEdge(vertex, vertex2, color);
    } else if (option == "ResetVisualizer") {
      imdbGraph.ResetVisualizer();
    } else if (option == "Visualize") {
      GraphAdjList<string> *graph = imdbGraph.GetGraph();
      bridges.setDataStructure(graph);
      bridges.visualize();
      outFile << "Graph was visualized." << std::endl;
    } else if (option == "AddActor") {
      int movie_count = 0;
      inFile >> vertex;
      for (auto im : am_imdb) {
        string actor = im.getActor();
        if (actor.compare(vertex) == 0) {
          string movie = im.getMovie();
          imdbGraph.AddVertex(actor);
          imdbGraph.AddVertex(movie);
          imdbGraph.AddEdge(actor, movie);
          movie_count++;
        }
      }
      if (movie_count > 0) {
        outFile << "Actor " << vertex << " was found and " << movie_count
                << " movies have been added." << std::endl;
      } else {
        outFile << "Actor " << vertex << " was NOT found." << std::endl;
      }
    } else if (option == "AddAll") {
      for (auto im : am_imdb) {
        string actor = im.getActor();
        string movie = im.getMovie();
        imdbGraph.AddVertex(actor);
        imdbGraph.AddVertex(movie);
        imdbGraph.AddEdge(actor, movie);
      }
      outFile << "All actors and movies have been added." << std::endl;
    } else {
      std::cout << option << " is not a valid command." << std::endl;
    }
    numOptions++;
    std::cout << " Command number " << numOptions << " completed." << std::endl;
    inFile >> option;
  };

  std::cout << "Quit" << std::endl << "Testing completed." << std::endl;
  inFile.close();
  outFile.close();
}
