#include <string>
using std::string;

#include <iostream>
using std::cout; using std::endl;

int main()
{
  string str = "Hello";
  string phrase = "Hello World";
  string slang = "Hiya";

  cout << "str: " << str << endl
       << "phrase: " << phrase << endl
       << "slang: " << slang << endl;
  
  if (str < phrase) cout << "str is smaller than phrase" << endl;
  if (slang > str) cout << "slang is greater than str" << endl;
  if (slang > phrase) cout << "slang is greater than phrase" << endl;
}
