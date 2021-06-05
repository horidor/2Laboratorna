#pragma once
#include <string>
#include <vector>

std::vector<std::string> get_info_into_files(std::string, std::string);
std::string* read_files(std::vector<std::string> files, int*);
std::string* get_results(std::string*, int*);
int match_result(int, int);
void output_results(std::string*, int*, std::string);