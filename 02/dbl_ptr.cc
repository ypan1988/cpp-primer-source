#include <iostream>

using std::cout;
using std::endl;

int main()
{
  int ival = 1024;
  int *pi = &ival;		// pi points to an int
  int **ppi = &pi;		// ppi points to pointer to an int
  cout << "The value of ival\n"
       << "direct value: " << ival << "\n"
       << "indirect value: " << *pi << "\n"
       << "doubly indirect value: " << **ppi
       << endl;

  int i = 2;
  pi = &i;		        // pi points to an int
  *pi = *pi * *pi;		// equivalent to i = i * i;
  cout << "i = " << i << endl;

  *pi *= *pi;			// equivalent to i *= i;
  cout << "i = " << i << endl;

  return 0;
}
