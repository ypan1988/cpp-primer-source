#include "StrVec.h"

#include <iostream>
using std::cout;
using std::endl;
using std::istream;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

void print(const StrVec &svec)
{
    for (auto it : svec) cout << it << " ";
    cout << endl;
}

StrVec getVec(istream &is)
{
    StrVec svec;
    string s;
    while (is >> s) svec.push_back(s);
    return svec;
}

int main()
{
    // we'll call getVec a couple of times
    // and will read the same file each time
    ifstream in("../data/storyDataFile");
    StrVec svec = getVec(in);
    print(svec);
    in.close();

    return 0;
}
