#include "IntervalTree.h"
#include <iostream>
#include <utility>
#include <string>

Node* IntervalTree::createNode(int ymin,int ymax,int xmin,int xmax, Node* father){
    Node* nNode = new Node();
    nNode->intervalY.first = ymin;
    nNode->intervalY.second = ymax;
    nNode->intervalX.first = xmin;
    nNode->intervalX.second = xmax;
    nNode->key = ymax;
    nNode->left = NULL;
    nNode->right = NULL;
    nNode->father = father;
    nNode->height = 1;
    return nNode;
  }


void IntervalTree::printNode(Node *node){
    if(node != NULL){
      std::cout<<"Y: "<<'('<< node->intervalY.first <<","<<node->intervalY.second<<" X,("<<node->intervalX.first<<','<<node->intervalX.second<<"): "<< '\t';
      std::cout << node->key <<'\t'<<node->height<<'\t';
      std::cout << node << '\t';
      if(node->father!=NULL)std::cout << node->father << '\n';
      else std::cout << "NULL" << '\n';
    } else std::cout << "NULL" << '\n';
  }

void IntervalTree::insertWithFather(int ymin,int ymax,int xmin,int xmax,Node *father, Node **node){
    if(*node == NULL){
      *node = createNode(ymin,ymax,xmin,xmax,father);
      updateNode(*node,true);
    } else if(ymin < (*node)->intervalY.first)insertWithFather(ymin,ymax,xmin,xmax,*node,&(*node)->left);
    else insertWithFather(ymin,ymax,xmin,xmax,*node,&(*node)->right);
}
void IntervalTree::updateKey(Node* node){
  std::cout << "IN updateKey" << '\n';
  printNode(node);
    if(node != NULL){
      if(node->right != NULL){
        printNode(node->right);
        if(node->key < node->right->key){
          node->key = node->right->key;
          std::cout << "im going to my father" << '\n';
        }
      } else {
        node->key = node->intervalY.second;
      }
      updateKey(node->father);
    }
}

bool IntervalTree::balanced(int l,int r){
    if(std::abs(l - r) <= 1)return true;
    else return false;
}
void IntervalTree::balanceTree(Node* x,Node* y, Node* z,bool isRight1,bool isRight2){
  if(isRight1){
    if(isRight2){
      right_right_Solve(x,y,z);
      updateNode(z,false);
      if(z == *root) *root = y;
    } else {
      right_left_Solve(x,y,z);
      updateNode(y,false);
      updateNode(z,false);
      if(z == *root) *root = x;
    }
  } else {
    if(isRight2){
      left_right_Solve(x,y,z);
      updateNode(y,false);
      updateNode(z,false);
      if(z == *root) *root = x;
    } else {
      left_left_Solve(x,y,z);
      updateHeight(z);
      if(z == *root) *root = y;
    }
  }
}
int IntervalTree::comp_keys(int a,int b){
  if(a>b)return a;
  return b;
}

void IntervalTree:: right_right_Solve(Node* x, Node* y, Node* z){
  std::cout << "right right case" << '\n';
  std::cout << "x,y,z: "<<x->intervalY.first<<" "<<y->intervalY.first<<" "<<z->intervalY.first << '\n';
  // step1: father child setup
  y->father = z->father;
  if(z->father != NULL){
    if(z->intervalY.first < z->father->intervalY.second) z->father->left = y;
    else z->father->right = y;
  }
  // step 2:
  z->right = y->left;
  if(y -> left != NULL){

    if(y->left->key > z->key){
      z->key = y->left->key;
    } else z->key = z->intervalY.second;

    y->left->father = z;
  } else {
    // si y no tiene right, entonces z->key = z->highInterval
    z->key = z->intervalY.second;
  }
  // step 3:
  y->left = z;
  z->father = y;


}
void IntervalTree:: left_left_Solve(Node* x, Node* y, Node* z){
  std::cout << "left left case" << '\n';

  // step1:
  y->father = z->father;
  if(z->father != NULL){
    if(z->intervalY.first < z->father->intervalY.second) z->father->left = y;
    else z->father->right = y;
  }
  // step2:
  z->left = y->right;
  if(y->right != NULL){
    y->right->father = z;
  }
  // step 3:
  y->right = z;
  y->key = z->key;
  z->father = y;
//  z->height--;

}
void IntervalTree:: right_left_Solve(Node* x, Node* y, Node* z){
  // PARTE 1
    // step 1:
    x->father = z;
    z->right = x;
    // step 2:
    y->left = x->right;
    if(x->right != NULL){
      x->right->father = y;
    }
    // step 2:
    x->right = y;
    y->father = x;
  //  x->key = y->key;
  //  x->height++;
  //  y->height--;
  // PARTE 2:
  right_right_Solve(y,x,z);

}
void IntervalTree:: left_right_Solve(Node* x, Node* y, Node* z){
  // PARTE 1
    // step1
    std::cout << "problem" << '\n';
    printNode(z);
    printNode(y);
    printNode(x);

    x->father = z;
    z->left = x;
    // step2
    y->right = x->left;
    int var = 0;
    if(x->left){
      x->left->father = y;
      var = x->left->key;
    }
    y->key = comp_keys(y->intervalY.second,var);
    // step 3:
    x->left = y;
    y->father = x;
  //  x->height = y->height;
  //  y->height--;
  // PARTE 2
  left_left_Solve(y,x,z);
}


Node* IntervalTree::getNode(Node* infoNode, bool* isRight){
    int currentValue1 = 0,currentValue2 = 0;
    // set-up x,y;
    if(infoNode->left != NULL)currentValue1 = infoNode->left->height;
    if(infoNode->right != NULL)currentValue2 = infoNode->right->height;

    if(currentValue1 > currentValue2){
      *isRight = false;
      return infoNode->left;
    } else{
      return infoNode->right;
    }
}

void IntervalTree::updateHeight(Node* node){

  int highest_value = 0,rightValue = 0,leftValue = 0;
  if(node != NULL){
      if(node->right != NULL)rightValue = node->right->height;
      if(node->left != NULL)leftValue = node->left->height;
      if(not balanced(leftValue,rightValue)){
          std::cout<<'\n'<< "----NOT BALANCED -----" << '\n';
          std::cout << "previous IntervalTree" << '\n';
          printIntevalTree(*root,"");
          Node *x;
          Node *y;
          Node *z;
          z = node;

          bool* isRight1 = new bool();
          bool* isRight2 = new bool();

          *isRight1 = true;
          *isRight2 = true;

          /* Por alguna razón la root cambia de dirección al momento en que a la función
             le pasamos una copia de la dirección de memoria del nodo a la que estaba apuntando
             es decir
             1. *Root apunta a 0xef6a8
             2. z apunta a 0xef6a8
             3. al pasarle una copia de z a la función, dejamos de ejecutarlo
          */
          if(z != *root){
            y = getNode(z,isRight1);
            x = getNode(y,isRight2);
          } else{
            Node *another;
            another = z;
            y = getNode(another,isRight1);
            x = getNode(y,isRight2);
          }
          balanceTree(x,y,z,*isRight1,*isRight2);

      } else {

        if(rightValue >= leftValue)highest_value = rightValue;
        else highest_value = leftValue;

        node->height = highest_value + 1;

        updateHeight(node->father);

      }
    }
  }

// tiene un problema, y es que va a hasta la raiz
// no es lo suficientemente inteligente para detenerse una vez que el árbol ya esté balanaceado
// se  asi por motivos de tiempo
void IntervalTree::updateNode(Node* node,bool isFather){
  if(isFather){
    updateKey(node->father);
    updateHeight(node->father);
  } else {
    updateKey(node);
    updateHeight(node);
  }
}

bool IntervalTree::isExternal(Node *node){
  bool isExternal = true;
  if(node->left != NULL && node->right != NULL){
    isExternal = false;
  }
  return isExternal;
}
Node* IntervalTree::getSucessor(Node *node){
  Node *retn = node->right;
  while(retn->left != NULL){
    retn = retn->left;
  }
  // sip queda en NULL, no puedes hacer retn = retn->father pq es NULL
  return retn;
}
//también podría ser entre hermanos, pero para este caso lo dejaremos exclusivamente
// para padre e hijo
void IntervalTree::destroyNode(Node *node){
  node->left = NULL;
  node->right = NULL;
  node->father = NULL;
  delete node;
}
void IntervalTree::swapAndDestroy(Node *father,Node *child, bool areClose,bool isLeft){
  if(*root == father)*root = child;
  if(areClose){
    child->father = father->father;
    if(isLeft){
      if(father->father != NULL){
          father->father->left = child;
      }
      child->right = father->right;
      if(father->right!=NULL)father->right->father = child;
      destroyNode(father);
      // INVESTIGAR KEY Y HEIGHT
    } else {
      if(father->father != NULL){
        father->father->right = child;
      }
      child->key = father->key;
      child->left = father->left;
      if(father->left != NULL)father->left->father = child;
      destroyNode(father);
    }
  } else {
    //father
      child->father->left = NULL;
      child->father = father->father;
    //right
      child->right = father->right;
      father->right->father = child;
    //left
      child->left = father->left;
      father->left->father = child;
      destroyNode(father);
  }
}
bool IntervalTree::areClose(Node* father, Node* child){
  if(father->left == child || father->right == child)return true;
  else return false;
}
void IntervalTree::deleteInterval(Node* node, int ymin,int ymax, int xmin, int xmax){
  if(node == NULL)std::cout << "NOT FOUND EXCEPTION" << '\n';
  else if(node->intervalY.first == ymin && node->intervalY.second == ymax
          && node->intervalX.first == xmin && node->intervalX.second == xmax){
    std::cout << "JUST FOUND" << '\n';
    printNode(node);
    if(isExternal(node)){
      Node* nr = node->right;
      Node* nl = node->left;
      if(nr == NULL){
        //case1:  isLeaf
        if(nl == NULL){
          Node* saveDir = node->father;
          if(node->father != NULL){
            if(node->father->left == node)node->father->left = NULL;
            if(node->father->right == node)node->father->right = NULL;
          }
          destroyNode(node);
          updateKey(saveDir);
          updateHeight(saveDir);
        }
        else {
          swapAndDestroy(node->father,node,true,true);
        }
      } else {
        swapAndDestroy(node->father,node,true,false);
      }
    } else {
      Node* swapVar = getSucessor(node);
      if(areClose(node,swapVar)){

        swapAndDestroy(node,swapVar,true,false);

      } else {
        Node* saveDir = swapVar->father;
        std::cout << "HOLANDASS saveDir:" << '\n';
        printNode(saveDir);
        swapAndDestroy(node,swapVar,false,false);
        std::cout << "saveDir: " << '\n';
        printNode(saveDir);
        updateKey(saveDir);
        updateHeight(saveDir);
        std::cout << "FINISHED" << '\n';
      }
    }



  } else if(node->intervalY.first > ymin) deleteInterval(node->left,ymin,ymax,xmin,xmax);
  else deleteInterval(node->right,ymin,ymax,xmin,xmax);
}

void IntervalTree::printIntevalTree(Node* node,std::string Tab){
    if(node == NULL){
      std::cout<<Tab<< " - " << '\n';
    }
    else {
      std::cout << Tab;
      printNode(node);
      printIntevalTree(node->left,Tab + '\t');
      printIntevalTree(node->right,Tab + '\t');

    }
  }
bool IntervalTree::search(int ymin, int ymax,int xmin,int xmax, Node* currentNode){
  if(currentNode != NULL){
      if(ymin <= currentNode->intervalY.second && currentNode->intervalY.first >= ymax){
        std::cout << "FOUND: " << '\n';
        printNode(currentNode);
        return true;
      } else if(currentNode->left == NULL){
          search(ymin,ymax,xmin,xmax,currentNode->right);
      } else if(currentNode->left->key <= ymin) {
          search(ymin,ymax,xmin,xmax,currentNode->right);
      } else {
          search(ymin,ymax,xmin,xmax,currentNode->left);
      }
  }
  return false;
}

// PUBLIC FUNCTIONS

IntervalTree::IntervalTree(){
  std::cout << "creando" << '\n';
  *root = NULL;
  std::cout << "aqui tengo problemas" << '\n';
}
IntervalTree::~IntervalTree(){

}

void IntervalTree::insert(int ymin, int ymax, int xmin, int xmax){
  insertWithFather(ymin,ymax,xmin,xmax,NULL,root);
}
void IntervalTree::deleteInterval(int ymin,int ymax,int xmin, int xmax){
  deleteInterval(*root,ymin,ymax,xmin,xmax);
}
void IntervalTree::printIntevalTree(){
  std::cout << "NODE"<<'\t'<<"key"<<'\t'<<"height"<<'\t'<<"node"<<'\t'<<"Dir Father" << '\n';
  printIntevalTree(*root,"");
}
bool IntervalTree::search(int ymin, int ymax, int xmin, int xmax){
  return search(ymin,ymax,xmin,xmax,*root);
}
