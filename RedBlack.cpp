#include "RBMyMap.h"

int main() {

  RBMyMap<int, int> map_obj;
  int key[] = {1, 4, 6, 3, 5, 7, 8, 2, 9};
  for (int i=0; i<9;i++){
    map_obj.insert(key[i], 0);
    //std::cout << std::endl;
    //map_obj.inorderTraversal();
  }
  map_obj.printTree();



  return 0;
}


