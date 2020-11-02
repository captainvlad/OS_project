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