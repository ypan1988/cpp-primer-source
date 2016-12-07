// g++ -std=c++11 wdebug.cc
// g++ -std=c++11 -D NDEBUG wdebug.cc

#include <iostream>
using std::cout; using std::cerr; using std::endl;

void print(const int ia[], size_t size)
{
  #ifndef NDEBUG
  // __func__ is a local static defined by the compiler that holds the
  // function's name
  cerr << __func__ << ": array size is " << size << endl;
  #endif
  // ...
}

int main()
{
  constexpr size_t sz = 5;
  int arr[sz] = {1, 2, 3, 4, 5};
  print(arr, sz);

  return 0;
}
