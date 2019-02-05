#include "logger.h"


std::string info(const char *fname, std::string message) {
	return "[INFO][" + std::string(stripFileName(fname)) + "]\t" + message + "\n";
}
std::string warn(const char *fname, std::string message) {
	return "[WARN][" + std::string(stripFileName(fname)) + "]\t" + message + "\n";
}

std::string stripFileName(const char *fname) {
	return std::string(fname).substr(std::string(fname).find_last_of("\\/") + 1);
}