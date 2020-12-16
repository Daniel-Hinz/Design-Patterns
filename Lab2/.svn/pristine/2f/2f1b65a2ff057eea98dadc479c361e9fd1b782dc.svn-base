//Daniel Hinz
//CS3 Lab 2
//9/11/2020

#include "WordList.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Please add an argument" << std::endl;
    return 1;
  }

  //open text file
  std::ifstream file1;
  file1.open(argv[1]);

  WordList w;
  std::string word = "";

  //grabs each word in the file
  while (file1 >> word) {
    std::string newWord;
    for (int i = 0; i < word.size(); ++i) {
	if (isalnum(word[i])) 
	  newWord.append(sizeof(word[i]), word[i]);
    }
    w.addWord(newWord);
  }
  w.print();
  file1.close();
}
