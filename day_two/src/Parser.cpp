#include "Parser.hpp"

Parser::Parser(const std::string &filename) : _filename(filename), _safe_count(0), _line("")
{
  std::cout << "Parser constructor" << std::endl;
}

Parser::~Parser()
{
  std::cout << "Parser destructor" << std::endl;
}

Parser::State Parser::isAscending(const std::vector<int> &v)
{
  for (size_t i = 0; i < v.size() - 1; ++i) {
    if (v[i] < v[i + 1])
      return State::ASCENDING;
  }
  return State::DESCENDING;
}

int Parser::countGaps(const std::vector<int> &v)
{
  // count gaps between numbers and return the highest gap
  int gap = 0;
  int max_gap = 0;

  for (size_t i = 0; i < v.size() - 1; ++i) {
    gap = (v[i + 1] > v[i]) ? v[i + 1] - v[i] : v[i] - v[i + 1];
    if (gap > max_gap)
      max_gap = gap;
  }
  return max_gap;
}

std::vector<int> Parser::split(const std::string &s, char delim)
{
  std::vector<int> result;
  std::stringstream ss(s);
  std::string item;

  while (std::getline(ss, item, delim)) {
    result.push_back(std::stoi(item));
  }
  return result;
}

Parser::State Parser::isIncreasingAndDecreasing(const std::vector<int> &v)
{
  bool increasing = false;
  bool decreasing = false;


  for (size_t i = 0; i < v.size() - 1; i++) {
    if (v[i] < v[i + 1]) {
      increasing = true;
    } else if (v[i] > v[i + 1]) {
      decreasing = true;
    }
  }
  if (increasing && decreasing)
    return State::INCREASING_AND_DECREASING;
  return State::NEUTRAL;
}

Parser::State Parser::isNorIncreasingNorDecreasing(const std::vector<int> &v)
{
  for (size_t i = 0; i < v.size() - 1; ++i)
    if (v[i] == v[i + 1])
      return State::NOR_INCREASING_NOR_DECREASING;
  return State::NEUTRAL;
}

bool Parser::isSafe(const std::vector<int> &v)
{
  int gap = 0;
  State state = this->isIncreasingAndDecreasing(v);

  if (state == State::INCREASING_AND_DECREASING)
    return false;

  state = this->isNorIncreasingNorDecreasing(v);
  if (state == State::NOR_INCREASING_NOR_DECREASING)
    return false;


  gap = this->countGaps(v);
  state = this->isAscending(v);
  if (state == Parser::State::ASCENDING || state == Parser::State::DESCENDING)
    if (gap > 3)
      return false;

  std::cout << "[";
  for (size_t i = 0; i < v.size() - 1; ++i)
    std::cout << v[i] << ",";
  std::cout << v[v.size() - 1] << "]: " << gap << " => " << state << std::endl;
  return true;
}

void Parser::parse()
{
  std::vector<int> copy;
  std::vector<int> col;
  std::cout << "Parsing file: " << _filename << std::endl;

  _file.open(_filename);
  if (!_file.is_open()) {
    std::cerr << "Error opening file: " << _filename << std::endl;
    return;
  }


  while (std::getline(_file, _line)) {
    col = split(_line, ' ');

    if (this->isSafe(col)) {
      _safe_count++;
    } else {
      for (size_t i = 0; i < col.size(); ++i) {
        copy = col;
        copy.erase(copy.begin() + i);
        if (this->isSafe(copy)) {
          _safe_count++;
          break;
        }
      }
    }
  }

  std::cout << "Safe count: " << _safe_count << std::endl;
}



std::ostream& operator<<(std::ostream &os, const Parser::State &state)
{
  switch (state) {
    case Parser::State::NEUTRAL:
      os << "NEUTRAL";
      break;
    case Parser::State::ASCENDING:
      os << "ASCENDING";
      break;
    case Parser::State::DESCENDING:
      os << "DESCENDING";
      break;
    case Parser::State::NOR_INCREASING_NOR_DECREASING:
      os << "NOR_INCREASING_NOR_DECREASING";
      break;
    case Parser::State::INCREASING_AND_DECREASING:
      os << "INCREASING_AND_DECREASING";
      break;
  }
  return os;
}
