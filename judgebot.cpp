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

int popback(int num);
int suffixCheck(int rank, int suffix, std::string extension);
const int rankGoal = 400;

int main() {
  int rank = 0;
  int suffix = 1;
  std::string extension = ".rnk";
  std::string passName = "Pass";
  std::string failName = "Fail";

  rank = (suffixCheck(1, suffix, extension) - 1)
         + ((suffixCheck(2, suffix, extension) - 1) * 2);

  if (rank >= rankGoal) {
    //std::ofstream nfile(passName + "("
    //                    + std::to_string(rank) + ")" + extension);
    std::ofstream nfile(passName + extension);
  } else {
    //std::ofstream nfile(failName + "("
    //                    + std::to_string(rank) + ")" + extension);
    std::ofstream nfile(failName + extension);
  }
  return 0;
}



int suffixCheck(int rank, int suffix, std::string extension) {
  std::ifstream fin(std::to_string(rank)
                    + "." + std::to_string(suffix) + extension);
  if (fin.fail()) {
    return suffix;
  } else {
    suffix++;
    return suffixCheck(rank, suffix, extension);
  }
}
