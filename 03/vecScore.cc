#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <vector>
using std::vector;

int main()
{
  // hold the grades we read from the standard input
  vector<unsigned> grades;
  
  // count the number of grades by clusters of ten:
  // 0--9, 10--19, ... , 90--99, 100
  vector<unsigned> scores(11, 0);	// 11 buckets, all initially 0
  
  unsigned grade;
  while (cin >> grade) {	// read the grade
    if (grade <= 100) {		// handle only valid grades
      grades.push_back(grade);
      ++scores[grade/10];	// increment the counter for the current cluster
    }
  }
  
  cout << "grades.size = " << grades.size() << endl;
  for (auto it : grades)
    cout << it << " ";
  cout << endl;

  cout << "scores.size = " << scores.size() << endl;
  for (auto it : scores)
    cout << it << " ";
  cout << endl;

  return 0;
}
