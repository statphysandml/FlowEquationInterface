#include "flowequations/flowequations.hpp"
#include <iostream>

int main(){
  int result = flowequations::add_one(1);
  std::cout << "1 + 1 = " << result << std::endl;
}