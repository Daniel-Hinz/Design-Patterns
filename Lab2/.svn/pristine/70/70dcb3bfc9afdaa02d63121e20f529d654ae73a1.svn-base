#ifndef WORDLIST_HPP
#define WORDLIST_HPP

#include <iostream>
#include <string>

class WordOccurrence {
public:
  WordOccurrence(const std::string &word = "", int num = 0) {
    word_ = word;
    num_ = num;
  }
  bool matchWord(const std::string &str) {
    if (str == word_)
      return true;
    else
      return false;
  }
  void increment() {
    ++num_;
  }

  std::string getWord() const {
    return word_;
  }

  int getNum() const {
    return num_;
  }

private:
  std::string word_;
  int num_;
};

class WordList {
public:
  //default constructor
  WordList() {
    size_ = 0;
    wordArray_ = new WordOccurrence[size_];
  }

  //copy constructor
  WordList(const WordList &rhs) {
    size_ = rhs.size_;

    wordArray_ = new WordOccurrence[size_];
    for (int i = 0; i < size_; ++i)
      wordArray_[i] = rhs.wordArray_[i];
  }

  // destructor
  ~WordList() {
    delete [] wordArray_;
  }
  
  //assignment operator
  WordList &operator=(const WordList &rhs) {
    if (this == &rhs)
      return *this;

    size_ = rhs.size_;
    wordArray_ = new WordOccurrence[size_];
    for (int i = 0; i < size_; ++i)
      wordArray_ = rhs.wordArray_;
    return *this;
  }

  //friend function
  friend bool equal(const WordList &lhs, const WordList &rhs) {
    return lhs.wordArray_ == rhs.wordArray_ && lhs.size_ == rhs.size_;
  }

  //function to add words to list
  void addWord(const std::string &word) {

    //check if word is already in list
    for (int i = 0; i < size_; ++i) {
      if (wordArray_[i].matchWord(word)) {
	wordArray_[i].increment();
	return;
      }
    }

    //increases size of WordArray_
    WordOccurrence *temp = new WordOccurrence[size_+1];
    for (int i = 0; i < size_; ++i)
      temp[i] = wordArray_[i];
    delete[] wordArray_;
    wordArray_ = temp;

    //looks for location to add word
    int add = 0;
    for (int i = 0; i < size_; ++i) {
      if (wordArray_[i].getWord().compare(word) > 0) {
	add = i;
	break;
      }
      else add = i+1;
    }

    for (int i = size_-1; add <= i; --i)
      wordArray_[i+1] = wordArray_[i];
    //add word to list and increase size
    wordArray_[add] = WordOccurrence(word, 1);
    ++size_;
  }

  void print() {
    //output header
    std::cout << "\n Word : Occurences " << std::endl;
    std::cout << "-------------------" << std::endl;

    //sort array in ascending order
    for (int i = 0; i < size_; i++) {
      for (int j = i + 1; j < size_; j++) {
	if (wordArray_[j].getNum() < wordArray_[i].getNum()) {
	  WordOccurrence temp = wordArray_[i];
	  wordArray_[i] = wordArray_[j];
	  wordArray_[j] = temp;
	}
      }
    }

    //output final list
    for (int i = 0; i < size_; ++i)
      std::cout << wordArray_[i].getWord() << " : " << wordArray_[i].getNum() << std::endl;
    std::cout << std::endl;
  }

private:
  WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences may or may not be sorted
  int size_;
};

#endif
