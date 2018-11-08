//
// Created by Spencer Tuft on 10/29/18.
//

#ifndef RELATIONAL_DATABASE_CS236_BYU_DATABASE_H
#define RELATIONAL_DATABASE_CS236_BYU_DATABASE_H

#include <map>
#include <sstream>
#include "./DatalogParser.h"
#include "./Relation.h"

class Database {
 private:
  std::map<std::string, Relation> r;
  Relation stg_select(Relation&, Query);
  Relation stg_project(Relation&, Query);
  Relation stg_rename(Relation&, Query);
 public:
  Database(std::vector<Scheme>);
  Database(std::vector<Scheme>, std::vector<Fact>);
  void add(Scheme);
  void add(std::vector<Scheme>);
  void add(Fact);
  void add(std::vector<Fact>);
  Relation eval(Query);
  std::vector<Relation> eval(std::vector<Query>);
  bool exists(std::string);
  Relation look_up(std::string);
  std::string str();
};

#endif //RELATIONAL_DATABASE_CS236_BYU_DATABASE_H
