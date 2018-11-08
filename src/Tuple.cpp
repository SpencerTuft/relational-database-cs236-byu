//
// Created by Spencer Tuft on 10/29/18.
//

#include <iostream>
#include <sstream>
#include "Tuple.h"

Tuple::Tuple() = default;
Tuple::Tuple(List list) {
  l = std::move(list);
}
bool Tuple::empty() const {
  return l.empty();
}
bool Tuple::operator==(const Tuple &l2) const {
  if (l2.size() != this->size()) return false;
  for (auto i = 0; i < l.size(); i++) {
    if (l2.at(i) != this->at(i)) return false;
  }
  return true;
}
bool Tuple::operator<(const Tuple & l2) const {
  for (auto i = 0; i < this->size(); i++) {
    if (this->at(i) == l2.at(i)) continue;
    else return this->at(i) < l2.at(i);
  }
  return false;
}
bool Tuple::operator>(const Tuple & l2) const {
  for (auto i = 0; i < this->size(); i++) {
    if (this->at(i) == l2.at(i)) continue;
    else return this->at(i) > l2.at(i);
  }
  return false;
}
int Tuple::size() const {
  return static_cast<int>(l.size());
}
std::string Tuple::at(int position) const {
  return l[position];
}
Tuple Tuple::select(int column, std::string value) const {
  if (l[column] == value) return Tuple(l);
  return Tuple();
}
Tuple Tuple::select(int column1, int column2) const {
  if (l[column1] == l[column2]) return Tuple(l);
  return Tuple();
}
Tuple Tuple::select(std::vector<int> columns) const {
  // Find all column values
  std::vector<std::string> values;
  for (auto &column : columns) {
    if (column >= 0 && column < l.size()) {
      values.emplace_back(l[column]);
    }
  }
  // If all column values are equal
  if (std::adjacent_find(values.begin(), values.end(), std::not_equal_to<std::string>()) == values.end()) {
    return Tuple(l);
  }
  return Tuple();
}
Tuple Tuple::project(std::vector<int> columns) const {
  List temp;
  for (auto &column : columns) {
    temp.emplace_back(l[column]);
  }
  return Tuple(temp);
}
std::string Tuple::str(List headers) const {
  std::stringstream ss;
  for (auto i = 0; i < headers.size(); i++) {
    if (i != 0) ss << ", ";
    ss << headers[i] << "=" << l[i];
  }
  return ss.str();
}
