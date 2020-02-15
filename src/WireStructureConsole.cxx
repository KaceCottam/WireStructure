#include "Gates.h"

#include <unordered_set>
#include <memory>
#include <string>
#include <iostream>
#include <utility>
#include <optional>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

template<class T>
using IO = T;

using std::string;
using std::pair;
using std::getline;
using std::unordered_set;
using std::unique_ptr;
using std::cin;
using std::optional;
using std::vector;
using std::transform;

enum GATE_TYPE {
 WIRE,
 NOT,
 AND,
 OR,
 NOR,
 NAND,
 XOR,
 XNOR,
 INPUT,
 OUTPUT
};

enum COMMAND_TYPE {
  CREATE_COMMAND,
  DISPLAY_COMMAND,
  CONNECT_COMMAND,
  SHOWME_COMMAND,
  HELP_COMMAND,
  QUIT_COMMAND,
  INVALID_COMMAND
};

auto parse(const IO<string>& in) noexcept {
  vector<string> args;
  {
    std::stringstream inputStream(static_cast<string>(in));
    string line;
    transform(line.begin(), line.end(), line.begin(),
              [](auto c){return tolower(c);});
    while(inputStream >> line) args.push_back(line);
  }
  switch(args.size()) {
    case 1:
      if(args[0] == "display") return DISPLAY_COMMAND;
      if(args[0] == "help") return HELP_COMMAND;
      if(args[0] == "quit") return QUIT_COMMAND;
      return INVALID_COMMAND;
    case 2:
      if(args[0] == "create") { 
      }
      return INVALID_COMMAND;
    case 3:
      if(args[0] == "create") {
      }
      if(args[0] == "connect") {
      }
      return INVALID_COMMAND;
    default:
      return INVALID_COMMAND;
  }
}

int main() {
  bool wantsToQuit = false;

  // Commands:
  //   let <POSITION> = (<x>,<y>) in
  //     create <GATE> <POSITION>
  //     display
  //     connect <POSITION> <POSITION>
  //     showme <POSITION>
  //     help
  //     quit

  unordered_set<unique_ptr<Node>> board;

  while(!wantsToQuit) {
    IO<string> userInput;
    getline(cin, userInput);
    auto result = parse(userInput);
  }

}
