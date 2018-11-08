//
// Created by Spencer Tuft on 11/5/18.
//

#ifndef RELATIONAL_DATABASE_CS236_BYU_INTERPRETER_H
#define RELATIONAL_DATABASE_CS236_BYU_INTERPRETER_H

#include "./Database.h"
#include "./DatalogParser.h"

class Interpreter {
  std::vector<Scheme> s;
  std::vector<Fact> f;
  std::vector<Query> q;
 public:
  explicit Interpreter(std::string);
  Database build();
  std::vector<Scheme> getSchemes();
  std::vector<Fact> getFacts();
  std::vector<Query> getQueries();
};

#endif //RELATIONAL_DATABASE_CS236_BYU_INTERPRETER_H
