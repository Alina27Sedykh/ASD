// Copyright 2024 Marina Usova
//
//#define EASY_EXAMPLE
//#ifdef EASY_EXAMPLE
//
//#include <iostream>
//#include <iomanip>
//#include "../lib_easy_example/easy_example.h"
//
//int main() {
//  int a, b;
//  float result;
//
//  a = 1; b = 4;
//
//  try {
//      result = division(a, b);
//      std::cout << a << " / " << b << " = "
//          << std::setprecision(2) << result << std::endl;
//  } catch (std::exception err) {
//      std::cerr << err.what() << std::endl;
//  }
//
//  a = 1; b = 0;
//
//  try {
//      result = division(a, b);
//      std::cout << a << " / " << b << " = "
//          << std::setprecision(2) << result << std::endl;
//  } catch (std::exception err) {
//      std::cerr << err.what() << std::endl;
//  }
//
//  return 0;
//}
//
//#endif  // EASY_EXAMPLE
#include "skiplist.h"
#include <iostream>
#include <iomanip>
#include <ctime>

int main()
{
    
    srand(static_cast<unsigned>(time(nullptr)));
    SkipList<int, double> skipList(4);
    skipList.insert(10, 12.15);
    skipList.insert(5, 4.0);
    skipList.insert(20, 7.523);
    skipList.insert(15, 87.2);
    skipList.insert(25, 78.5);
    skipList.insert(3, 5.8);
    skipList.insert(30, 58.4238);
    skipList.insert(8, 8.769455);
    skipList.insert(12, 34.5);
    skipList.insert(18, 92.1);

    std::cout << "SkipList:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    skipList.print(std::cout);

    return 0;
}