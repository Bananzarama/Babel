/** //\
*   V  \
*    \  \_
*     \,'.`-.
*     |\ `. `.
*     ( \  `. `-.                        _,.-:\
*      \ \   `.  `-._             __..--' ,-';/
*       \ `.   `-.   `-..___..---'   _.--' ,'/
*        `. `.    `-._        __..--'    ,' /
*          `. `-_     ``--..''       _.-' ,'
*            `-_ `-.___        __,--'   ,'
*               `-.__  `----"""    __.-'
*                    `--..____..--'
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

const std::string wordList = "en_US.txt";
void loadWordList(std::vector<std::string>& words, std::string fileName);
bool checkWord(std::vector<std::string>& words, std::string wurd);
void checkPage(std::vector<std::string>& words, int& realWords, std::vector<std::string>& maybeWords);
std::string newToken(std::string oldToken);
int suffixCheck(int rank, int suffix, std::string extension);
const int low = 10;
const int high = 30;

int main() {
  srand(time(NULL));
  std::vector<std::string> words(0);
  std::vector<std::string> maybeWords(0);
  loadWordList(words, wordList);
  int realWords = 0;
  int fileRank = 0;
  int suffix = 1;
  std::string extension = ".rnk";
  std::string wordInput;
  std::ifstream curPage;
  std::string word;
  checkPage(words, realWords, maybeWords);

  if (realWords >= 0 && realWords <= low) {
    fileRank = 0;
    std::ofstream nfile(std::to_string(fileRank)
                        + "." + std::to_string(suffixCheck(fileRank, suffix, extension))
                        + extension);

	for (unsigned int i = 0; i < maybeWords.size() - 1; i++) {
		nfile << maybeWords[i] << std::endl;
	}
	
  } else if (realWords > low && realWords < high) {
    fileRank = 1;
    std::ofstream nfile(std::to_string(fileRank)
                        + "." + std::to_string(suffixCheck(fileRank, suffix, extension))
                        + extension);

	for (unsigned int i = 0; i < maybeWords.size() - 1; i++) {
		nfile << maybeWords[i] << std::endl;
	}

  } else if (realWords >= high) {
    fileRank = 2;
    std::ofstream nfile(std::to_string(fileRank)
                        + "." + std::to_string(suffixCheck(fileRank, suffix, extension))
                        + extension);
                        
         for (unsigned int i = 0; i < maybeWords.size(); i++) {
		nfile << maybeWords[i] << std::endl;
	}
  }
  return 0;
}


void loadWordList(std::vector<std::string>& words, std::string fileName) {
  int wordCount = 0;
  std::ifstream fin(fileName.c_str());
  if (fin.fail()) {
    exit(-1);
  } else {
    for (std::string word; std::getline(fin, word);) {
      words.push_back(word);
      wordCount++;
    }
    fin.close();
  }
}

void checkPage(std::vector<std::string>& words, int& realWords, std::vector<std::string>& maybeWords) {
  std::string wordInput;
  while (std::cin >> wordInput) {
    std::string newWord = newToken(wordInput);
    if (checkWord(words, newWord) == true) {
      realWords++;
      maybeWords.push_back(newWord);
    }
  }
}

bool checkWord(std::vector<std::string>& words, std::string wurd) {
  int wordfind = 0;
  for (unsigned int i = 0; i < words.size(); i++) {
    std::string newWord = words[i];
    if (wurd == newWord) {
      wordfind++;
    }
  }
  if (wordfind == 0) {
    return false;
  } else {
    return true;
  }
}

std::string newToken(std::string oldToken) {
  std::string tokenNew = oldToken;
  if (tokenNew[tokenNew.size() - 1] == 46
      or tokenNew[tokenNew.size() - 1] == 44)
    tokenNew.pop_back();
  return tokenNew;
}

int suffixCheck(int rank, int suffix, std::string extension) {
  std::ifstream fin(std::to_string(rank) + "." + std::to_string(suffix) + extension);
  if (fin.fail()) {
    return suffix;
  } else {
    suffix++;
    return suffixCheck(rank, suffix, extension);
  }
}
