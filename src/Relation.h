//
// Created by Spencer Tuft on 10/27/18.
//

#ifndef RELATIONAL_DATABASE_CS236_BYU_RELATION_H
#define RELATIONAL_DATABASE_CS236_BYU_RELATION_H

#include <string>
#include <vector>
#include <map>
#include "./Tuple.h"

typedef std::vector<Tuple> Tuples;

class Relation {
 private:
  std::string n;
  List h;
  std::vector<Tuple> t;
 public:
  Relation();
  explicit Relation(std::string);
  Relation(std::string, List);
  Relation(std::string, List, Tuples);
  void add(Tuples);
  void add(Tuple);
  void add(List);
  void clear();
  bool empty();
  bool vacant();
  int size();
  bool exists(Tuple);
  int resolve_column(std::string);
  std::string resolve_column(int);
  Relation select(int, std::string);
  Relation select(int, int);
  Relation select(std::vector<int>);
  Relation project(List);
  Relation project(std::map<std::string, std::vector<int>>&);
  Relation project(std::vector<int>);
  Relation rename(int, std::string);
  Relation rename(std::string, std::string);
  std::string str();
};

#endif //RELATIONAL_DATABASE_CS236_BYU_RELATION_H
