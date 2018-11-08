//
// Created by Spencer Tuft on 10/29/18.
//

#include <algorithm>
#include "Database.h"
Database::Database(std::vector<Scheme> schemes) {
  add(std::move(schemes));
};
Database::Database(std::vector<Scheme> schemes, std::vector<Fact> facts) {
  add(std::move(schemes));
  add(std::move(facts));
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

  relation = stg_select(relation, query);
  relation = stg_project(relation, query);
  relation = stg_rename(relation, query);

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
Relation Database::stg_select(Relation &relation, Query query) {
  std::map<int, std::string> constants;
  std::map<std::string, std::vector<int>> variables;
  Predicate predicate = query.get_predicate();
  std::vector<Parameter> params = predicate.get_param_list();
  for (int i = 0, max = static_cast<int>(params.size()); i < max; i++) {
    if (params[i].getType() == "STRING") {
      constants.emplace(i, params[i].getValue());
    }
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

  // Select Constants
  for (auto &constant : constants) {
    relation = relation.select(constant.first, constant.second);
  }

  // Select Variables
  for (auto &variable : variables) {
    std::vector<int> positions = variable.second;
    if (positions.size() > 1) {
      relation = relation.select(positions);
    }
  }
  return relation;
}
Relation Database::stg_project(Relation &relation, Query query) {
  Predicate predicate = query.get_predicate();
  std::vector<Parameter> params = predicate.get_param_list();

  // Find position of first-encounter, unique variables
  std::vector<int> positions;
  std::vector<std::string> variable_names;
  for (size_t i = 0, max = params.size(); i < max; i++) {
    if (params[i].getType() == "ID") {
      std::string value = params[i].getValue();
      bool found = std::find(variable_names.begin(), variable_names.end(), value) != variable_names.end();
      if (!found) {
        variable_names.emplace_back(value);
        positions.emplace_back(i);
      }
    }
  }

  relation = relation.project(positions);
  return relation;
}
Relation Database::stg_rename(Relation &relation, Query query) {
  Predicate predicate = query.get_predicate();
  std::vector<Parameter> params = predicate.get_param_list();

  // Find unique variable ordering
  std::vector<std::string> variable_names;
  for (auto &param : params) {
    if (param.getType() == "ID") {
      std::string value = param.getValue();
      bool found = std::find(variable_names.begin(), variable_names.end(), value) != variable_names.end();
      if (!found) variable_names.emplace_back(value);
    }
  }

  for (size_t i = 0, max = variable_names.size(); i < max; i++) {
    relation = relation.rename(static_cast<int>(i), variable_names[i]);
  }

  return relation;
}
