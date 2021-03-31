#include <utility>
#include <string>
typedef struct Node{
  std::pair<int,int> interval;
  int key;
  int height;
  Node* left;
  Node* right;
  Node* father;
} Node;

class IntervalTree{
private:
  Node** root;
  Node* createNode(int,int,Node*);

  void printNode(Node*);

  void insertWithFather(int,int,Node*,Node**);
  void updateKey(Node*);
  // funciones útiles para balancear un árbol
  bool balanced(int,int);
  void balanceTree(Node*,Node*,Node*,bool,bool);
  int comp_keys(int,int);

  void  right_right_Solve(Node*, Node*, Node* );
  void  left_left_Solve(Node*, Node*, Node* );
  void  right_left_Solve(Node*, Node*, Node* );
  void  left_right_Solve(Node*, Node*, Node*);

  Node* getNode(Node*, bool*);

  void updateHeight(Node*);

  // actualiza la altura como la key
  void updateNode(Node*,bool);
  bool isExternal(Node*);
  Node* getSucessor(Node*);
  // funciones para eliminar un nodo
  void destroyNode(Node*);
  void swapAndDestroy(Node*,Node*,bool,bool);
  bool areClose(Node*,Node* );
  void deleteInterval(Node*,int,int);
  void printIntevalTree(Node*,std::string);

  bool search(int,int,Node*);
public:
  IntervalTree();
  ~IntervalTree();
  void insert(int,int);
  void deleteInterval(int,int);
  bool search(int,int);
  void printIntevalTree();
};
