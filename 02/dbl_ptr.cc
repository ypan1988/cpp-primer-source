#include <iostream>

using std::cout;
using std::endl;

int main()
{
  int ival = 1024;
  int *pi = &ival;		// pi points to an int
  int **ppi = &pi;		// ppi points to pointer to an int
}
