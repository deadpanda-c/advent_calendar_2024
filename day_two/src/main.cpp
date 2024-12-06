#include <iostream>
#include <string>
#include <vector>

#include "Parser.hpp"

int main(int ac, char **av)
{
  if (ac < 2) {
    std::cerr << "Usage: " << av[0] << " <filename>" << std::endl;
    return 1;
  }

  std::string filename = av[1];
  Parser parser(filename);
  parser.parse();

  return 0;
}
