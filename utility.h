#ifndef UTILITY_H
#define UTILITY_H

bool file_exists(std::string filename);

bool string_is_integer(const std::string s);

bool string_is_double(const std::string s);

std::string space_to_underscore(std::string s);

#endif