//
// Created by Spencer Tuft on 10/29/18.
//

#include "Database.h"
Database::Database(std::vector<Scheme> schemes) {
  add(std::move(schemes));
};
Database::Database(std::vector<Scheme> schemes, std::vector<Fact> facts) {
  add(std::move(schemes));
  add(std::move(facts));
}
Database::Database(std::vector<Scheme> schemes, std::vector<Fact> facts, std::vector<Query> queries) {
  add(std::move(schemes));
  add(std::move(facts));
  eval(std::move(queries));
}
void Database::add(Scheme scheme) {
  std::string relation_name = scheme.get_name();
  List headers = scheme.get_list();
  if (!exists(relation_name)) {
    Relation new_relation(relation_name, headers);
    r.emplace(relation_name, new_relation);
  }
}
void Database::add(std::vector<Scheme> schemes) {
  for (auto &scheme : schemes) {
    add(scheme);
  }
}
void Database::add(Fact fact) {
  auto relation_name = fact.get_name();
  if (exists(relation_name)) {
    r.at(relation_name).add(fact.get_list());
  }
}
void Database::add(std::vector<Fact> facts) {
  for (auto &fact : facts) {
    add(fact);
  }
}
Relation Database::eval(Query query) {
  std::string relation_name = query.get_predicate().get_id();
  Relation relation = look_up(relation_name);

  auto constant_map = findConstants(query);
  auto variable_map = findVariables(query);

  // Select Constants
  for (auto &constant : constant_map) {
    relation = relation.select(constant.first, constant.second);
  }

  // Select Variables
  for (auto &variable : variable_map) {
    std::vector<int> positions = variable.second;
    if (positions.size() > 1) {
      relation = relation.select(positions);
    }
  }

  // Project Variable Positions
  relation = relation.project(variable_map);

  // Rename Relation Schema
  for (auto &variable : variable_map) {
    relation = relation.rename(variable.second[0], variable.first);
  }

  return relation;
}
std::vector<Relation> Database::eval(std::vector<Query> queries) {
  std::vector<Relation> relations;
  for (auto &query : queries) {
    relations.emplace_back(eval(query));
  }
  return relations;
}
bool Database::exists(std::string relation_name) {
  auto iter = r.find(relation_name);
  return iter != r.end();
}
Relation Database::look_up(std::string relation_name) {
  if (exists(relation_name)) return r.at(relation_name);
  return Relation();
}
std::string Database::str() {
  std::stringstream ss;
  for (auto &relation : r) {
    ss << relation.first << std::endl << relation.second.str() << std::endl;
  }
  return ss.str();
}
Constants Database::findConstants(Query query) {
  Constants constants;
  Predicate predicate = query.get_predicate();
  std::vector<Parameter> params = predicate.get_param_list();
  for (auto i = 0; i < params.size(); i++) {
    if (params[i].getType() == "STRING") {
      constants.emplace(i, params[i].getValue());
    }
  }
  return constants;
}
Variables Database::findVariables(Query query) {
  Variables variables;
  Predicate predicate = query.get_predicate();
  std::vector<Parameter> params = predicate.get_param_list();
  for (auto i = 0; i < params.size(); i++) {
    if (params[i].getType() == "ID") {
      std::string value = params[i].getValue();
      auto iter = variables.find(value);
      if (iter != variables.end()) {
        variables.at(value).emplace_back(i);
      } else {
        variables.emplace(params[i].getValue(), std::vector<int>{i});
      }
    }
  }
  return variables;
}
