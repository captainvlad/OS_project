//
// Created by vlad on 01.11.20.
//

#ifndef SOLO_UTILS_H
#define SOLO_UTILS_H

#include <string>
#include <vector>

bool contains(std::string* str, std::string* substr);
void split_string(std::string &txt, std::vector<std::string> &parts, char ch);

int findLastIndex(std::string& str, char x);
bool is_process_dir(std::string arg);

#endif //SOLO_UTILS_H