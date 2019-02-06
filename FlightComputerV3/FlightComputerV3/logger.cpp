#include "logger.h"

namespace logger {
	
	void info(const char *fname, std::string message) {

		std::lock_guard<std::mutex> lock(mtx);
		std::cout.width(28); std::cout << std::left << "[INFO][" + stripFilename(fname) + "]";
		std::cout.width(20); std::cout << std::left << message + "\n";
		lock.~lock_guard();

	}
	void warn(const char *fname, std::string message) {

		std::lock_guard<std::mutex> lock(mtx);
		std::cout.width(28); std::cout << std::left << "[WARN][" + stripFilename(fname) + "]";
		std::cout.width(20); std::cout << std::left << message + "\n";
		lock.~lock_guard();

	}

	std::string stripFilename(const char *fname) {
		return std::string(fname).substr(std::string(fname).find_last_of("\\/") + 1);
	}

}