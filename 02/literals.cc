#include <iostream>
int main()
{
  std::cout << 'a';		// character literal
  std::cout << "Hello World!"; 	// string literal
  // literal using newlines and tabs

  // multiline string literal
  std::cout << "a really, really long string literal "
    "that spans two lines" << std::endl;

  // three ways to print a capital M
  std::cout << 'M' << " " << '\115' << " " << '\x4d' << std::endl;

  unsigned long long bigVal = -1ULL;
  std::cout << bigVal << std::endl;
}
