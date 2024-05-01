
#include "MyMap.h"

int main() {

  MyMap<int, int> map;
  for (int i=0; i<12;i++){
    map.insert(i, 0);
  }
map.erase(1);
map.erase(10);
map.printTree();
std::cout<<map.getHeight(map.begin())<<std::endl;
  return 0;
}