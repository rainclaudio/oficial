#include <vector>
#include "IntervalTree.h"

typedef struct {
  std::pair<int,int> minXY;
  std::pair<int,int> maxXY;
} Square;
typedef std::vector<Square> SQvector;

class SolverOverlaps{
private:
  IntervalTree* intervalTree;
  SQvector sqvector;
  void printSQvector(SQvector);
  void delete_previous(int);

public:
  SolverOverlaps(SQvector);
  ~SolverOverlaps();
  void solveOverlaps();
};
// EMOJIS🤣
// opt + potencia
