#include "moutarde.h"

int main() {
 
  std::string instruct_file = "teste.instruct";
  std::string moutarde_file = "teste.moutarde";
  std::string html_file = "teste.html";
  unsigned int end_head = 6;

  moutardify(moutarde_file, instruct_file, html_file, end_head);

  return 0;
};


