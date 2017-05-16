#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include "QueryResult.h"

class QueryResult;              // declaration needed for return type in the query function
class TextQuery {
 public:
  using line_no = std::vector<std::string>::size_type;
  TextQuery(std::ifstream&);
  QueryResult query(const std::string&) const;
  void display_map();		// debugging aid: print the map
 private:
  std::shared_ptr<std::vector<std::string>> file; // input file
  // map each word to the set of the lines in which that word appears
  std::map<std::string,
    std::shared_ptr<std::set<line_no>>> wn;

  // canonicalizes text: removes punctuation and makes everything lower case
  static std::string cleanup_str(const std::string&);
};

#endif
