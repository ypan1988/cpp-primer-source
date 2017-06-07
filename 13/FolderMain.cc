#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "Folder.h"

int main()
{
  string s1("contents1");
  string s2("contents2");
  string s3("contents3");
  string s4("contents4");
  string s5("contents5");
  string s6("contents6");

  // all new messages, no copies yet
  Message m1(s1);
  Message m2(s2);
  Message m3(s3);
  Message m4(s4);
  Message m5(s5);
  Message m5(s6);

  return 0;
}
