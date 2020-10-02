#include <iostream>
#include <fstream>
#include <vector>

unsigned long adler32_file(std::string str, std::string salt)
{
    unsigned char c;
    unsigned long s1 = 1;
    unsigned long s2 = 0;
    int i = 0;

    while(true) {
        c = str[i] + std::stoi(salt);

        if (i == str.size()) break;

        if (i < str.size())
            ++i;

        s1 = (s1 + c) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return (s2 << 16) + s1;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string filename, salt;
    int numbilets = -1;
    for (std::vector<std::string>::iterator i = args.begin(); i != args.end(); ++i) {
        if (*i == "--h" || *i == "--help") {
            std::cout << "Syntax: ./program --file <filename> --numbilets <number> --parameter <number>" << std::endl;
            return 0;
        } else if (*i == "--file") {
            filename = *++i;
        } else if (*i == "--numbilets") {
            numbilets = std::stoi(*++i);
        } else if (*i == "--parameter") {
            salt = *++i;
        }
    }
    if (numbilets == -1) {
        std::cout << "Please enter file name, number of tickets and parameter.\n"
                     "Syntax: ./program --file <filename> --numbilets <number> --parameter <number>" << std::endl;
        return 0;
}
    std::string s;
    std::ifstream file(filename);
    while(getline(file, s)) {
        std::cout << s << ": " << (adler32_file(s, salt) % numbilets + 1) << std::endl;
    }
    file.close();
    return 0;
}
