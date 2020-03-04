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
#include <cstdlib>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>

const std::string wordList = "en_US.txt";
const int ascii_start = 97;
const int ascii_end = 122;
const int pageLength = 3200;
const int bookLength = 410;
const int randTotal = 40000;
const int nanoConv = 1000000000;

void createPage(std::vector<std::string>& words, int method);
void loadWordList(std::vector<std::string>& words, std::string fileName);
bool checkWord(std::vector<std::string>& words, std::string wurd);
void checkPage(std::vector<std::string>& listedWords, std::vector<std::string>& words, double& realWords, double pageSize);
std::string newToken(std::string oldToken);
double runPage(std::vector<std::string>& listedWords, int method);
double vecAvg(std::vector<double>& avgVec);
char letterFreq(int number);

int main() {
    srand(time(NULL));
    std::vector<std::string> listedWords(0);
    std::vector<double> pageRank(1);
    std::cout << std::setprecision(3) << std::fixed;
    auto before_all = std::chrono::high_resolution_clock::now();
    auto before_list = std::chrono::high_resolution_clock::now();
    loadWordList(listedWords, wordList);
    auto after_list = std::chrono::high_resolution_clock::now();
    double time_list = std::chrono::duration_cast<std::chrono::nanoseconds>(after_list - before_list).count();
    time_list /= nanoConv;
    std::cout << "Wordlist : \""<< wordList
              << "\" loaded! - " << time_list << "s" << std::endl;
    int searchMethod = 1;
    auto before_one = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= bookLength; i++) {
        pageRank.push_back(runPage(listedWords, searchMethod));
    }
    auto after_one = std::chrono::high_resolution_clock::now();
    double time_one = std::chrono::duration_cast<std::chrono::nanoseconds>(after_one - before_one).count();
    time_one /= nanoConv;
    std::cout << "Method "<< searchMethod << " - Pages : " << bookLength
              << " - Total Avg : " << vecAvg(pageRank) << "% - Time : "
              << time_one << "s" << std::endl;
    searchMethod = 2;
    auto before_two = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= bookLength; i++) {
        pageRank.push_back(runPage(listedWords, searchMethod));
    }
    auto after_two = std::chrono::high_resolution_clock::now();
    double time_two = std::chrono::duration_cast<std::chrono::nanoseconds>(after_two - before_two).count();
    time_two /= nanoConv;
    std::cout << "Method "<< searchMethod << " - Pages : " << bookLength
              << " - Total Avg : " << vecAvg(pageRank) << "% - Time : "
              << time_one << "s" << std::endl;
    auto after_all = std::chrono::high_resolution_clock::now();
    double time_all = std::chrono::duration_cast<std::chrono::nanoseconds>(after_all - before_all).count();
    time_all /= nanoConv;
    std::cout << "Total time : "<< time_all << " s" << std::endl;
}


double runPage(std::vector<std::string>& listedWords, int method) {
    std::vector<std::string> vPage(0);
    double realWords = 0;
    createPage(vPage, method);
    double pageSize = vPage.size();
    checkPage(listedWords, vPage, realWords, pageSize);
    double avgReal = pageSize / realWords;
    return avgReal;
}

void createPage(std::vector<std::string>& words, int method) {
    int count = 0, spaces = 0, periods = 0, commas = 0;
    std::string wordString = "";
    for (int i = 0; i < pageLength; i++) {
        count++;
        spaces++;
        periods++;
        commas++;
        if (method == 1) {
            wordString += letterFreq(rand() % randTotal);
        }
        if (method == 2) {
            wordString += (char)(rand()
                                 % ((ascii_end - ascii_start) + 1) + ascii_start);
        } if (method != 1 and method != 2) {
			std::cout << "Invalid Method!" << std::endl;
			exit(-1);
		}

        if (spaces >= (rand() % 5) + rand() % 12) {
            if (commas >= 15 + rand() % 50) {
                if (rand()%2 == 0) {
                    words.push_back(wordString);
                    wordString = "";
                    commas = 0;
                    periods = 0;
                    count++;
                } else {
                    commas = 0;
                }
            }
            if (periods >= 15 + rand() % 50) {
                if (rand()%4 != 0) {
                    words.push_back(wordString);
                    wordString = "";
                    periods = 0;
                    commas = 0;
                    count++;
                } else {
                    periods = 0;
                }
            }
            words.push_back(wordString);
            wordString = "";
            spaces = 0;
            count++;
        }
    }
}

void loadWordList(std::vector<std::string>& listedWords, std::string fileName) {
    std::ifstream fin(fileName.c_str());
    if (fin.fail()) {
        exit(-1);
    } else {
        for (std::string word; std::getline(fin, word);) {
            listedWords.push_back(word);
        }
        fin.close();
    }
}

bool checkWord(std::vector<std::string>& listedWords, std::string wurd) {
    int wordfind = 0;
    for (unsigned int i = 0; i < listedWords.size(); i++) {
        std::string allWords = listedWords[i];
        if (wurd == allWords) {
            wordfind++;
        }
    }
    if (wordfind == 0) {
        return false;
    } else {
        return true;
    }
}

void checkPage(std::vector<std::string>& listedWords, std::vector<std::string>& words, double& realWords, double pageSize) {
    std::string wordInput;
    for (unsigned int i = 0; i <= pageSize; i++) {
        std::string newWord = newToken(words[i]);
        if (checkWord(listedWords, newWord) == true) {
            realWords++;
        }
    }
}

std::string newToken(std::string oldToken) {
    std::string tokenNew = oldToken;
    if (tokenNew[tokenNew.size() - 1] == 46
            or tokenNew[tokenNew.size() - 1] == 44)
        tokenNew.pop_back();
    return tokenNew;
}

double vecAvg(std::vector<double>& avgVec) {
    double rankTotal = 0.0;
    for (unsigned int i = 0; i <= avgVec.size(); i++ ) {
        rankTotal += avgVec[i];
    }
    double bookAvg = rankTotal / static_cast<double>(avgVec.size());
    return bookAvg;
}

char letterFreq(int number) {
    int feqe = randTotal * 0.1202;
    int feqt = feqe + (randTotal * 0.0910);
    int feqa = feqt + (randTotal * 0.0812);
    int feqo = feqa + (randTotal * 0.0768);
    int feqi = feqo + (randTotal * 0.0731);
    int feqn = feqi + (randTotal * 0.0695);
    int feqs = feqn + (randTotal * 0.0628);
    int feqr = feqs + (randTotal * 0.0602);
    int feqh = feqr + (randTotal * 0.0592);
    int feqd = feqh + (randTotal * 0.0432);
    int feql = feqd + (randTotal * 0.0398);
    int fequ = feql + (randTotal * 0.0288);
    int feqc = fequ + (randTotal * 0.0271);
    int feqm = feqc + (randTotal * 0.0261);
    int feqf = feqm + (randTotal * 0.0230);
    int feqy = feqf + (randTotal * 0.0211);
    int feqw = feqy + (randTotal * 0.0209);
    int feqg = feqw + (randTotal * 0.0203);
    int feqp = feqg + (randTotal * 0.0182);
    int feqb = feqp + (randTotal * 0.0149);
    int feqv = feqb + (randTotal * 0.0111);
    int feqk = feqv + (randTotal * 0.0069);
    int feqx = feqk + (randTotal * 0.0017);
    int feqq = feqx + (randTotal * 0.0011);
    int feqj = feqq + (randTotal * 0.0010);
    int feqz = feqj + (randTotal * 0.0007);

    if (number >= 0 && number <= feqe)
        return 'e';
    if (number > feqe && number <= feqt)
        return 't';
    if (number > feqt && number <= feqa)
        return 'a';
    if (number > feqa && number <= feqo)
        return 'o';
    if (number > feqo && number <= feqi)
        return 'i';
    if (number > feqi && number <= feqn)
        return 'n';
    if (number > feqn && number <= feqs)
        return 's';
    if (number > feqs && number <= feqr)
        return 'r';
    if (number > feqr && number <= feqh)
        return 'h';
    if (number > feqh && number <= feqd)
        return 'd';
    if (number > feqd && number <= feql)
        return 'l';
    if (number > feql && number <= fequ)
        return 'u';
    if (number > fequ && number <= feqc)
        return 'c';
    if (number > feqc && number <= feqm)
        return 'm';
    if (number > feqm && number <= feqf)
        return 'f';
    if (number > feqf && number <= feqy)
        return 'y';
    if (number > feqy && number <= feqw)
        return 'w';
    if (number > feqw && number <= feqg)
        return 'g';
    if (number > feqg && number <= feqp)
        return 'p';
    if (number > feqp && number <= feqb)
        return 'b';
    if (number > feqb && number <= feqv)
        return 'v';
    if (number > feqv && number <= feqk)
        return 'k';
    if (number > feqk && number <= feqx)
        return 'x';
    if (number > feqx && number <= feqq)
        return 'q';
    if (number > feqq && number <= feqj)
        return 'j';
    if (number > feqj && number <= feqz)
        return 'z';
    else
        return '6';
}
