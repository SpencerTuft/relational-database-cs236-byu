//
// Created by Spencer Tuft on 10/27/18.
//

#include <sstream>
#include "Relation.h"
Relation::Relation() = default;
Relation::Relation(std::string relation_name) {
  n = std::move(relation_name);
};
Relation::Relation(std::string relation_name, List header) {
  n = std::move(relation_name);
  h = std::move(header);
}
Relation::Relation(std::string relation_name, List header, Tuples tuples) {
  n = std::move(relation_name);
  h = std::move(header);
  t = std::move(tuples);
}
void Relation::add(Tuples tuples) {
  for (auto &tuple : tuples) {
    add(tuple);
  }
}
void Relation::add(Tuple tuple) {
  if (!exists(tuple)) t.emplace_back(tuple);
  std::sort(t.begin(), t.end());
}
void Relation::add(List list) {
  add(Tuple(list));
}
void Relation::clear() {
  t.clear();
}
bool Relation::empty() {
  return t.empty();
}
bool Relation::vacant() {
  return h.empty();
}
int Relation::size() {
  return t.size();
}
bool Relation::exists(Tuple tuple) {
  for (auto &existing_tuple : t) {
    if (tuple == existing_tuple) return true;
  }
  return false;
}
int Relation::resolve_column(std::string value) {
  for (auto i = 0; i < h.size(); i++) {
    if (h[i] == value) return i;
  }
  return -1;
}
std::string Relation::resolve_column(int position) {
  if (position >= 0 && position < h.size()) return h[position];
  return "";
}
Relation Relation::select(int column, std::string value) {
  Relation temp(n, h);
  for (auto &tuple : t) {
    Tuple selected = tuple.select(column, value);
    if (!selected.empty()) temp.add(selected);
  }
  return temp;
}
Relation Relation::select(int column1, int column2) {
  Relation temp(n, h);
  for (auto &tuple : t) {
    Tuple selected = tuple.select(column1, column2);
    if (!selected.empty()) temp.add(selected);
  }
  return temp;
}
Relation Relation::select(std::vector<int> columns) {
  Relation temp(n, h);
  for (auto &tuple : t) {
    Tuple selected = tuple.select(columns);
    if (!selected.empty()) temp.add(selected);
  }
  return temp;
}
Relation Relation::project(List column_names) {
  std::vector<int> column_numbers;
  std::vector<std::string> new_header;

  for (const auto &column_name : column_names) {
    auto num = resolve_column(column_name);
    if (num != -1) {
      column_numbers.emplace_back(num);
      new_header.emplace_back(column_name);
    }
  }

  Relation temp(n, new_header);
  for (auto &tuple : t) {
    Tuple projected = tuple.project(column_numbers);
    temp.add(projected);
  }
  return temp;
}
Relation Relation::project(std::vector<int> column_positions) {
  std::vector<std::string> new_header;
  for (auto &position : column_positions) {
    if (position >= 0 && position < h.size()) {
      new_header.emplace_back(h[position]);
    }
  }
  Relation temp(n, new_header);

  for (auto &tuple : t) {
    Tuple projected = tuple.project(column_positions);
    temp.add(projected);
  }
  return temp;
}
Relation Relation::rename(int column, std::string value) {
  List new_header = h;
  new_header[column] = value;
  return Relation(n, new_header, t);
}
Relation Relation::rename(std::string from, std::string to) {
  List new_header = h;
  new_header[resolve_column(from)] = to;
  return Relation(n, new_header, t);
}
std::string Relation::str() {
  std::stringstream ss;
  for (auto & tuple : t) {
    if (&tuple != &t[0]) ss << std::endl;
    ss << "  " << tuple.str(h);
  }
  return ss.str();
}
