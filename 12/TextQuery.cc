#include "TextQuery.h"

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
  string text;
  while (getline(is, text)) {   // for each line in the file
    file->push_back(text);      // remember this line of text
    int n = file->size() - 1;   // the current line number
    istringstream line(text);   // separate the line into words
    string word;
    while (line >> word) {      // for each word in that line
      // if word isn't already in wm, subscripting adds a new entry
      auto &lines = wm[word];   // lines is a shared_ptr
      if (!lines)               // that pointer is null the first time we see word
        lines.reset(new set<line_no>); // allocate a new set
      lines->intert(n);                // insert this line number
    }
  }
}
