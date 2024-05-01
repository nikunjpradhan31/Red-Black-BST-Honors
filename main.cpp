#include "RBMyMap.h"

int main() {

  RBMyMap<int, int> map;
  //int key[] = {7,5,3,4};
  for (int i=0; i<4;i++){
    map.insert(i, 0);
    //std::cout << std::endl;
    //map_obj.inorderTraversal();
  }
 map.printTree();
 std::cout<<"\n\n\n\n"<<std::endl;
map.erase(1);
map.printTree();


  return 0;
}