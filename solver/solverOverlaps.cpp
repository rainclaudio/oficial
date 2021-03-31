#include "SolverOverlaps.h"
#include <iostream>
#include <utility>
#include <algorithm>
SolverOverlaps::SolverOverlaps(SQvector sqvector){
  this->sqvector = sqvector;
  this->intervalTree = new IntervalTree();
}
SolverOverlaps::~SolverOverlaps(){

}
void SolverOverlaps:: printSQvector(SQvector sqvector){
  for(auto it : sqvector){
    std::cout << it.minXY.first << ' ';
    std::cout << it.minXY.second << '\n';
    std::cout << it.maxXY.first << ' ';
    std::cout << it.maxXY.second << '\n';
    std::cout << '\n';
  }
}
// nlog(n) time
void SolverOverlaps::delete_previous(int pos){
  int getMinX = sqvector[pos].minXY.first;
  int i = 0;
  while(i < pos){
    if(sqvector[i].maxXY.first < getMinX){
      intervalTree->deleteInterval(sqvector[i].minXY.second,sqvector[i].maxXY.second,sqvector[i].minXY.first,sqvector[i].maxXY.first);
    }
    i++;
  }
}
void SolverOverlaps::solveOverlaps(){
  std::sort(sqvector.begin(),sqvector.end(), [](Square a, Square b){
    return a.minXY.first < b.minXY.first;
  });
  int i = 0;
  int currentMin = 100;
  for(auto it : sqvector){
    if(it.maxXY.second < currentMin){
      currentMin = it.maxXY.first;
    }
    if(it.maxXY.first > currentMin){
      delete_previous(i);
    }
    intervalTree->search(it.minXY.second,it.maxXY.second,it.minXY.first,it.maxXY.first);
    intervalTree->insert(it.minXY.second,it.maxXY.second,it.minXY.first,it.maxXY.first);
    i++;
  };
  printSQvector(sqvector);
}
