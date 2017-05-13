#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>

// forward declaration needed for friend declaration in StrBlob
class StrBlobPtr;

class StrBlob {
  friend class StrBlobPtr;
 public:
  typedef std::vector<std::string>::size_type size_type;
  
  // constructors
 StrBlob(): data(std::make_shared<std::vector<std::string>>()) { }
  StrBlob(std::initializer_list<std::string> il);
  
  // size operation
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }

  // add and remove elements
  void push_back(const std::string &t) { data->push_back(t); }
  void pop_back();

 private:
  std::shared_ptr<std::vector<std::string>> data;
};

#endif
