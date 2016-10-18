#include <iostream>
using std::cin; using std::cout; using std::endl;

// #include <cstddef>
// using std::size_t;

#include <vector>
using std::vector;

int main()
{
  vector<unsigned> grades;

  // count the number of grades by clusters of ten:
  // 0--9, 10--19, ..., 90--99, 100
  unsigned scores[11] = {};	// 11 buckets, all value initialized to 0
  unsigned grade;
  while (cin >> grade) {
    grades.push_back(grade);
    ++scores[grade/10];
  }

  for (auto g : grades)		// for every element in grades
    cout << g << " ";
  cout << endl;

  for (auto i : scores)		// for each counter in scores
    cout << i << " ";		// print the value of that counter
  cout << endl;

  return 0;
}
