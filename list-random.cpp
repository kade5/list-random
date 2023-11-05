#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct State {
  std::vector<std::string> input;
  bool is_file = false;
  bool use_seed = false;
  int seed = 0;
  int count = 1;
};

std::vector<std::string> getRandom(State state) {
  std::vector<std::string> output;
  std::mt19937 generator;
  if (!state.use_seed) {
    generator = std::mt19937{std::random_device{}()};
  } else {
    generator.seed(state.seed);
  }
  std::sample(state.input.begin(), state.input.end(), std::back_inserter(output),
              state.count, generator);

  return output;
}

int convertIntString(std::string value, std::string int_type) {
  int int_value;
  try {
    int_value = std::stoi(value);
  } catch (const std::invalid_argument &e) {
    std::cerr << int_type << " must be an integer\n";
    exit(EXIT_FAILURE);
  } catch (const std::out_of_range &e) {
    std::cerr << int_type << " out of range\n";
    exit(EXIT_FAILURE);
  }
  return int_value;
}

std::vector<std::string> parseFile(std::string filename) {
  std::vector<std::string> input;
  std::ifstream infile(filename);

  if (!infile.is_open()) {
    std::cerr << "Failed to open the file.\n";
    exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(infile, line)) {
    input.push_back(line);
  }

  infile.close();
  return input;
}

std::vector<std::string> parseInput() {
  std::vector<std::string> input;
  std::string line;

  while (std::getline(std::cin, line)) {
    input.push_back(line);
  }

  return input;
}

void parseArguments(State *state, int argc, char *argv[]) {
  std::vector<std::string> args;

  for (int i = 0; i < argc; i++) {
    args.push_back(std::string(argv[i]));
  }

  for (int i = 1; i < argc; i++) {

    if (args[i] == "-h" || args[i] == "-help") {
      std::cout << "Use -f to set file, -s to set a random seed and -c to set "
                   "number of items returned\n";
      exit(EXIT_SUCCESS);

    } else if (args[i] == "-f" || args[i] == "-file") {
      state->is_file = true;
      i++;
      if (i >= argc or args[i].front() == '-') {
        std::cerr << "No file passed in\n";
      } else {
        state->input = parseFile(args[i]);
      }

    } else if (args[i] == "-s" || args[i] == "-seed") {
      state->use_seed = true;
      i++;
      if (i >= argc or args[i].front() == '-') {
        std::cerr << "No seed value passed\n";
        exit(EXIT_FAILURE);
      } else {
        state->seed = convertIntString(args[i], "seed");
      }

    } else if (args[i] == "-c" || args[i] == "-count") {
      i++;
      if (i >= argc or args[i].front() == '-') {
        std::cerr << "No count value passed in\n";
        exit(EXIT_FAILURE);
      } else {
        state->count = convertIntString(args[i], "count");
      }

    } else {
      std::cerr << "Invalid argument: " << args[i] << "\nUse -h for help\n";
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char *argv[]) {

  std::vector<std::string> output;

  State state;

  parseArguments(&state, argc, argv);

  if (!state.is_file) {
    state.input = parseInput();
  }

  output = getRandom(state);

  for (auto o : output) {
    std::cout << o << "\n";
  }

  return EXIT_SUCCESS;
}
