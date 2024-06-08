#include "colors.h"
#include "prompt.h"
#include <cstring>
#include <iostream>
#include <istream>
#include <string>

int main() {
    const std::string username{RED + "username" + RESET};
    const std::string hostname{GREEN + "hostname" + RESET};

    const std::string prompt{std::string(username) + "@" +
                             std::string(hostname) + " > "};

    Prompt terminal_prompt{prompt, std::string(""), std::string("/")};

    std::cout << prompt;

    std::string command{};

    std::getline(std::cin >> std::ws, command);

    std::cout << "{ " << command << " } is the command you entered\n";

    return 0;
}
