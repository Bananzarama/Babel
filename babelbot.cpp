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

const int ascii_start = 97;
const int ascii_end = 122;
const int pageLength = 3200;
const int bookLength = 410;
const int lineBreak = 80;

/**
int msleep(unsigned long milisec)
{
    struct timespec req={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    while(nanosleep(&req,&req)==-1)
        continue;
    return 1;
}
**/

void createPage(int page) {
  int count = 0, spaces = 0, periods = 0, commas = 0;
  std::ofstream nfile("Page" + std::to_string(page) + ".txt");
  for (int i = 0; i < pageLength; i++) {
    count++;
    spaces++;
    periods++;
    commas++;

    nfile << (char)(rand()
                    % ((ascii_end - ascii_start) + 1) + ascii_start);

    if (spaces >= (rand() % 5) + rand() % 12) {
      if (commas >= 15 + rand() % 50) {
        if (rand()%2 == 0) {
          nfile << ",";
          commas = 0;
          periods = 0;
          count++;
        } else {
          commas = 0;
        }
      }
      if (periods >= 15 + rand() % 50) {
        if (rand()%4 != 0) {
          nfile << ".";
          periods = 0;
          commas = 0;
          count++;
        } else {
          periods = 0;
        }
      }
      nfile << " ";
      spaces = 0;
      count++;
    }
    if (count >= lineBreak) {
      nfile << "\n";
      count = 0;
    }
  }
}

void createBook() {
  int pageCount = 0;
  for (int i = 0; i < bookLength; i++) {
    pageCount++;
    createPage(pageCount);
  }
}

void electriceito() {
  std::cout << "\nDon't waste electriceito\n";
  std::cin.clear();
  std::cin.ignore(1000, '\n');
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  if (argc == 1) {
    electriceito();
  } else {
    std::string input = argv[1];
    if (input == "book") {
      createBook();
    }
    if (input == "page") {
      int pageNum = atoi(argv[2]);
      createPage(pageNum);
    }
    if (input != "book" and input != "page") {
      electriceito();
    }
  }
  return 0;
}
