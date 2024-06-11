#include "lib.h"
#include "shell.h"
#include "terminal.h"
#include "tokenizer.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <format>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

void shell_loop(Terminal&);
void exec(const std::vector<char*>&);

int main() {
  Shell shell{};
  Terminal terminal{shell};

  shell_loop(terminal);

  return EXIT_SUCCESS;
}

void shell_loop(Terminal& terminal) {
  while (true) {
    terminal.print_output(terminal.shell().prompt());

    std::string command{};

    std::getline(std::cin >> std::ws, command);

    if (command == "exit") {
      std::cout << "chepp: Goodbye 👋\n";
      break;
    }

    const std::vector<char*> argv{command_tokenizer(command)};

    if (strcmp(argv[0], "cd") == 0) {
      try {
        std::string new_path = (argv.size() >= 2) ? std::string(argv[1]) : "/";
        if (new_path.starts_with('"')) {
          new_path = new_path.substr(1, new_path.length() - 1);
        }
        terminal.update_directory(new_path.c_str());
      } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
      }
      continue;
    }

    exec(argv);
  }
}

void exec(const std::vector<char*>& argv) {
  std::vector<char*> cargv{};
  for (auto arg : argv) {
    cargv.push_back(const_cast<char*>(arg));
  }
  cargv.push_back(nullptr);

  pid_t pid = fork();
  if (pid == -1) {
    std::cerr << "Fork failed!\n";

    return;
  } else if (pid == 0) {
    execvp(cargv[0], cargv.data());

    std::cerr << "chepp: \"" << cargv[0] << "\" command not found."
              << std::endl;

    exit(EXIT_FAILURE);
  } else {
    int status;
    waitpid(pid, &status, 0);

    if (!WIFEXITED(status)) {
      std::cerr << "Command execution failed" << std::endl;
    }
  }
}
