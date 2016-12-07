// g++ -std=c++11 wdebug.cc
// g++ -std=c++11 -D NDEBUG wdebug.cc

#include <iostream>
using std::cout; using std::cerr; using std::endl;

#include <string>
using std::string;

#include <cstddef>
using std::size_t;

#include <cassert>
// assert is a preprocessor macro and therefore not in std
// hence we need to include cassert header, 
// but no using declaration for assert 

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

  string word = "foo";
  const string::size_type threshold = 5;
  if (word.size() < threshold) {
    cerr << "Error: " << __FILE__
	 << " : in function " << __func__
	 << " at line " << __LINE__ << endl
	 << "       Compiled on " << __DATE__
	 << " at " << __TIME__ << endl
	 << "       Word read was \"" << word
	 << "\":  Length too short" << endl;
  }

  word = "something longer than five chars";
  assert(word.size() > threshold);
  
  return 0;
}
