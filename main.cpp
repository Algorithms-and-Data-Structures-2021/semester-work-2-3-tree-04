#include <iostream>

#include "data_structure.hpp"
#include "traversalAlgorithm.h"

using namespace itis;
using namespace std;

int main(int argc, char *argv[]) {
  TwoThreeTree tree;

  for(int i = 1; i < 5; i++){
    tree.Insert(i);
  }
//  for(int i = 1; i < 5; i++){
//    tree.Remove(i);
//  }
  tree.Remove(2);
  tree.Remove(4);
  tree.Remove(3);


  TraversalAlgorithm *algorithm = new BreadthFirstTraversalAlgorithm;

  std::cout << "Level-order (BFS): ";
  tree.Traverse(*algorithm);
  std::cout << std::endl;

  delete algorithm;

  for (int index = 0; index < argc; index++) {
    cout << index << ": " << argv[index] << endl;
  }
  return 0;
}