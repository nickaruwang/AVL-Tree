#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "utils.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc < 3) {
    throw invalid_argument("USAGE: ./wordrange <INPUTFILE> <OUTPUTFILE>");
  }

  ifstream input;
  input.open(argv[1]);
  ofstream output;
  output.open(argv[2]);

  string line;
	AVL *tree = new AVL();
  while (getline(input, line)) {
    stringstream sline(line);
    string command;
    sline >> command;
    if (command == "i") {
      string word;
      sline >> word;

      // insert word
			tree->insert(word); 
    }
    else if (command == "r") {
      string left_word, right_word;
      sline >> left_word >> right_word;
      // output range of words
			int r = tree->range(left_word, right_word);
			output << r << endl; // wrong a s
    }
  }
	
	
	
  input.close();
  output.close();

  return 0;
}
