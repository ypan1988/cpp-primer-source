#include <string>
using std::string;

#include <iostream>
using std::cin; using std::cout; using std::endl;

int main()
{
  const string hexdigits = "0123456789ABCDEF"; // possible hex digits
  cout << "Enter a series of numbers between 0 and 15"
       << " separated by spaces. Hit ENTER when finished: "
       << endl;
  string result;		// will hold the resulting hexify'd
				// string
  string::size_type n;		// hold number from the input
  while (cin >> n)
    if (n < hexdigits.size())	// ignore invalid input
      result += hexdigits[n];	// fetch the indicated hex digit
  cout << "Your hex number is: " << result << endl;

  return 0;
}
