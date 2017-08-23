#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <set>

class Folder;

class Message {
  friend void swap(Message&, Message&);
  friend class Folder;
 public:
  // folders is implicitly initialized to the empty set
  explicit Message(const std::string &str = ""): contents(str) { }

  // copy control to manage pointers to this Message
  Message(const Message&);             // copy constructor
  Message& operator=(const Message&);  // copy assignment
  Message(Message&&);                  // move constructor
  Message& operator=(Message&&);       // move assignment
  ~Message();                          // destructor

  // add/remove this Message from the specified Folder's set of messages
  void save(Folder&);
  void remove(Folder&);
  void debug_print();           // print contents and it's list of Folders,
                                // printing each Folder as well
 private:
  std::string contents;         // actual message text
  std::set<Folder*> folders;    // Folders that have this Message

  // utility functions used by copy constructor, assignment, and destructor
  // add this Message to the Folders that point to the parameter
  void add_to_Folders(const Message&);
  // remove this Message from every Folder in folders
  void remove_from_Folders();
};

// declaration for swap should be in the same header as Message itself
void swap(Message&, Message&);

class Folder {

};

#endif
