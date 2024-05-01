
#include "MyMap.h"

// Should accept a text file via std in
// Should build a map of the counts of the characters in that file
// Do not add newlines (\n) to the dictionary (they'll mess up print)
// ./a.out < sample_input.txt should be the form of input
//void get_char_frequency(MyMap<char, int> &in_tree);

int main() {

  MyMap<int, int> map;
  int key[] = {1, 4, 6, 3, 5, 7, 8, 2, 9};
  for (int i=0; i<9;i++){
    map.insert(key[i], 0);
    //std::cout << std::endl;
    //map_obj.inorderTraversal();
  }
 //map.printTree();
 //map.erase(0);
// map.erase(2);
 map.erase(6);
 map.printTree();
  return 0;
}

// void get_char_frequency(MyMap<char, int> &in_tree) {

//   char ch;
//   while (std::cin >> ch) {
//     if (ch != '\n')
//       in_tree[ch] += 1;
//   }
// }
