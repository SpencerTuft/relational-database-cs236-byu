#include <iostream>
//#include <string>
//#include <map>
//#include <vector>
#include "./Interpreter.h"
/**
 * Main process
 * @param argc = argument count
 * @param argv = argument vector
 * @return
 */
int main(int argc, const char *argv[]) {
  std::string fileName = argv[1];

  if (argc < 1) {
    std::cout << "Missing input file argument" << std::endl;
    return 0;
  }
  std::string inputFileName = std::string(fileName);
  Interpreter interpreter(inputFileName);

  auto db = interpreter.build();
//  std::cout << "Database:" << std::endl << db.str();

  auto queries = interpreter.getQueries();
  auto results = db.eval(queries);
  for (int i = 0, max = static_cast<int>(results.size()); i < max; i++) {
    if (i != 0) std::cout << std::endl;
    std::cout << queries[i].str() << " ";
    int size = results[i].size();
    if (size == 0) {
      std::cout << "No";
    } else {
      std::cout << "Yes(" << size << ")";
    }
    if (!results[i].vacant() && !results[i].empty()) {
      std::cout << std::endl << results[i].str();
    }
  }

  return 0;
}