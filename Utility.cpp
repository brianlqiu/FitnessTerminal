#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "utility.h"

bool file_exists(std::string filename) {
	std::ifstream ifs(filename);
	return ifs.good();
}

bool string_is_integer(const std::string s) 
{
	return s.find_first_not_of("0123456789") == std::string::npos;
}

bool string_is_double(const std::string s)
{
	double d;
	return ((std::istringstream(s) >> d >> std::ws).eof());
}

std::string space_to_underscore(std::string s) {
	std::string convert;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			convert += '_';
		}
		else {
			convert += s[i];
		}
	}
	return convert;
}