#include "LocalMath.h"

// factorial of val is val * (val - 1) *  (val - 2) . . . * ((val -  (val - 1)) * 1)
int fact(int val)
{
  int ret = 1;			// local variable to hold the result as we calculate it
  while (val > 1)
    ret *= val--;		// assign ret * val to ret and decrement val

  return ret;			// return the result
}

// calculate val!, which is 1*2*3...*val
int factorial(int val)
{
  if (val > 1)
    return factorial(val-1) * val;
  return 1;
}
