#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

class Parser {
  public:
    enum class State {
      NEUTRAL,
      ASCENDING,
      DESCENDING,
      NOR_INCREASING_NOR_DECREASING,
      INCREASING_AND_DECREASING,
    };
    Parser(const std::string &filename);
    ~Parser();

    void parse();
  private:
    std::ifstream _file;
    std::string _filename;
    std::string _line;
    int _line_number;
    int _safe_count;
    bool _is_open;

    bool isSafe(const std::vector<int> &v);
    Parser::State isNorIncreasingNorDecreasing(const std::vector<int> &v);
    Parser::State isIncreasingAndDecreasing(const std::vector<int> &v);
    Parser::State isAscending(const std::vector<int> &v);
    int countGaps(const std::vector<int> &v);
    std::vector<int> split(const std::string &s, char delim);

};

std::ostream& operator<<(std::ostream &os, const Parser::State &state);
