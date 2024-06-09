#include "colors.h"
#include "prompt.h"
#include <array>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

bool shell_loop(Prompt&);
std::string exec(const std::string&);

int main() {
    const std::string username{RED + "username" + RESET};
    const std::string hostname{GREEN + "hostname" + RESET};

    const std::string prompt{std::string(username) + "@" +
                             std::string(hostname) + " > "};

    Prompt terminal_prompt{prompt, std::string("/")};

    if (!shell_loop(terminal_prompt)) {
        return 0;
    }

    return 0;
}

bool shell_loop(Prompt& prompt) {
    while (true) {
        std::cout << prompt.prompt();

        std::string command{};

        std::getline(std::cin >> std::ws, command);

        if (command == "exit") {
            return false;
        }

        std::cout << exec(command) << std::endl;
    }

    return true;
}

std::string exec(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result{};
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                  pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
