#include "colors.h"
#include "shell.h"
#include "tokenizer.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

void shell_loop(Shell&);
void exec(const std::vector<char*>&);

int main() {
  const std::string username{RED + "username" + RESET};
  const std::string hostname{GREEN + "hostname" + RESET};

  const std::string prompt{std::string(username) + "@" + std::string(hostname) +
                           " > "};

  Shell shell{prompt, std::string("/")};

  shell_loop(shell);

  return EXIT_SUCCESS;
}

void shell_loop(Shell& shell) {
  while (true) {
    std::cout << shell.prompt();

    std::string command{};

    std::getline(std::cin >> std::ws, command);

    if (command == "exit") {
      break;
    }

    const std::vector<char*> argv{string_tokenizer(command, ' ')};

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
      /*  std::cout << "Command executed with exit status: " <<
       * WEXITSTATUS(status)*/
      /*            << std::endl;*/
      /*} else {*/
      std::cerr << "Command execution failed" << std::endl;
    }
  }
}
