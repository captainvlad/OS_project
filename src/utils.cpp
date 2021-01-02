//
// Created by vlad on 01.11.20.
//
#include "utils.h"

bool contains(std::string* str, std::string* substr) {
    return str->find(*substr) != std::string::npos;
}

void split_string(std::string &txt, std::vector<std::string> &parts, char ch) {
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    parts.clear();

    while(pos != std::string::npos) {
        parts.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    parts.push_back(txt.substr(initialPos, std::min( pos, txt.size()) - initialPos + 1));
}

int findLastIndex(std::string& str, char x)
{
    int index = -1;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == x)
            index = i;
    return index;
}

bool is_process_dir(std::string arg) {
    bool result = true;

    std::string new_string = arg.substr(
            findLastIndex(arg, '/') + 1
            );

    for (auto ch: new_string) {
        result &= isdigit(ch);
    }

    return result;
}

std::vector<double> parseCPUusage(std::string values) {
    std::vector<double> result;

    for (int i = 0; i < values.size(); i++) {
        if (values[i] == '%') {
            result.push_back(std::stod(values.substr(i - 3, 3)));
        }
    }

    return result;
}