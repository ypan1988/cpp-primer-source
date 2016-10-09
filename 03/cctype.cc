#include <string>
using std::string;

#include <cctype>
using std::ispunct; using std::toupper; using std::isspace;

#include <iostream>
using std::cout; using std::endl;

int main()
{
  string s("Hello World!!!");
  // punct_cnt has the same type that s.size returns; see § 2.5.3 (p. 70)
  decltype(s.size()) punct_cnt = 0;

  // count the number of punctuation characters in s
  for (auto c : s)		// for every char in s
    if (ispunct(c))		// if the character is punctuation
      ++punct_cnt;		// increment the punctuation counter
  
  cout << punct_cnt
       << " punctuation characters in " << s << endl;

  // convert s to uppercase
  string orig = s;
  for (auto &c : s)		// for every char in s (note: c is a reference)
    c = toupper(c);		// c is a reference, so the assignment changes
				// the char in s
  cout << s << endl;

  // convert first word in s to uppercase
  s = orig;

  // process characters in s until we run out of characters or we hit a
  // whitespace
  for (decltype(s.size()) index = 0;
       index != s.size() && !isspace(s[index]); ++index)
    s[index] = toupper(s[index]); // capitalize the current character

  cout << s << endl;
  
  return 0;
}
