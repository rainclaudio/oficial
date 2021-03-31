#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <algorithm>
#include "SolverOverlaps.h"
//#include "IntervalTree.h"
/*
g++ main.cpp intervalTree.cpp -o ejecutable
.\ejecutable input.txt
*/
std::ifstream reader;
std::ofstream writer;

/*typedef struct {
  std::pair<int,int> minXY;
  std::pair<int,int> maxXY;
} Square;*/
//typedef std::vector<Square> SQvector;
void printSQvector2(SQvector sqvector){
  for(auto it : sqvector){
    std::cout << it.minXY.first << ' ';
    std::cout << it.minXY.second << '\n';
    std::cout << it.maxXY.first << ' ';
    std::cout << it.maxXY.second << '\n';
    std::cout << '\n';
  }
}
SQvector getSQvector(std::string input){
  SQvector sqvector;
  reader.open(input);
  std::cout << "todo bien" << '\n';

  if(!reader){
    std::cerr<<"couldn't read input";
    exit(1);
  }
  std::vector<int> v;
  int n,i = 0;
  Square var;
  while(reader >> n){
    if(i==3){
      v.push_back(n);
      var.minXY.first = v[0];
      var.minXY.second = v[1];
      var.maxXY.first = v[2];
      var.maxXY.second = v[3];
      sqvector.push_back(var);
      i = 0;
      v.clear();
    } else {
      v.push_back(n);
      i++;
    }

 }
/*  for(auto it : v){
    std::cout << it << '\n';
  }*/
  reader.close();
  return sqvector;
}

int main(int argc, char const *argv[]) {

  SQvector sqvector = getSQvector(argv[1]);

  std::cout << "ok" << '\n';
  printSQvector2(sqvector);
  SolverOverlaps* solverOverlaps = new SolverOverlaps(sqvector);
  solverOverlaps->solveOverlaps();
  std::cout << "sali" << '\n';

  return 0;
}
