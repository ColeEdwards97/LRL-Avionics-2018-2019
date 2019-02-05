#pragma once
#include <string>

std::string info(const char *fname, std::string message);
std::string warn(const char *fname, std::string message);
std::string stripFileName(const char *fname);
