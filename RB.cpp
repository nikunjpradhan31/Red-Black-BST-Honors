#include "RBMyMap.h"

int main() {

  RBMyMap<int, int> map;
  for (int i=0; i<13;i++){
    map.insert(i, 0);
  }
map.printTree();
std::cout<<"\n\n\n\n"<<std::endl;
map.erase(1);
//map.erase(10);
//map.erase(5);
//map.erase(40);
map.printTree();
std::cout<<map.getHeight(map.begin())<<std::endl;
  return 0;
}