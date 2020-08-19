/*************************************************************************
 *
 * Project: Test driver
 *
 * File Name: ImdbListTest.h
 * Course:    CPTR 242
 */
#include "ImdbGraph.h"
#include <fstream>
#include <string>

using namespace bridges;

//  we will use this class to keep track of the number of movies that an
// 	actor has appeared in; we will use that to color/size the nodes
struct am_obj {
  std::string movies;
  int num_movies;
};

void ImdbGraphTest(std::string inFileName, std::string outFileName,
                  std::string outputLabel);


