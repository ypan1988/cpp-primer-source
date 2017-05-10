#include <iostream>
using std::cout; using std::endl;

#include <fstream>
using std::ifstream;

#include <sstream>
using std::istringstream;

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string;

#include <map>
using std::map;

map<string, string> buildMap(ifstream &map_file) {
  map<string, string> trans_map; // holds the transformations
  string key;			 // a word to transform
  string value;			 // phrase to use instead
  // read the first word into key and the rest of the line into value
  while (map_file >> key && getline(map_file, value))
    if (value.size() > 1) 	// check that there is a transformation
      trans_map[key] = value.substr(1); // skip leading space
    else
      throw runtime_error("no rule for " + key);
  
  return trans_map;
}

const string& transform(const string &s, const map<string, string> &m) {
  // the actual map work; this part is the heart of the program
  auto map_it = m.find(s);
  // if this word is in the transformation map
  if (map_it != m.cend()) 
    return map_it->second;	// use the replacement word
  else 
    return s;			// otherwise return the original unchanged
}

void word_transform(ifstream &map_file, ifstream &input) {
  auto trans_map = buildMap(map_file); // store the transformations
  string text;			       // hold each line from the input
  while (getline(input, text)) {       // read a line of input
    istringstream stream(text);	       // read each word
    string word;
    bool firstword = true;	// controls whether a space is printed
    while (stream >> word) {
      if (firstword)
	firstword = false;
      else 
	cout << " ";		// print a space between words
      // transform returns its first argument or its transformation
      cout << transform(word, trans_map); // print the output
    }
    cout << endl;		// done with this line of input
  }
}

int main(int argc, char **argv)
{
  // open and check both files
  if (argc != 3)
    throw runtime_error("wrong number of arguments");
  
  ifstream map_file(argv[1]);	// open transformation file
  if (!map_file)
    throw runtime_error("no transformation file");

  ifstream input(argv[2]);	// open file of text to transform
  if (!input)
    throw runtime_error("no input file");

  word_transform(map_file, input);

  return 0;
}
