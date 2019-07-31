#include "fitness.h"
#include "utility.h"
#include <string>
#include <vector>	
#include <fstream>
#include <algorithm>
#include <iostream>

WorkoutDay::WorkoutDay(std::string planname, std::string dayname, int index)
{
	std::string day_path = "./" + space_to_underscore(planname) + "/" + space_to_underscore(dayname) + ".txt";
	plan_name = planname;
	day_name = dayname;
	day_index = index;
	if (file_exists(day_path)) {
		std::fstream fs(day_path);
		std::string line;
		std::getline(fs, line);	
		while (std::getline(fs, line)) {
			std::string exercise_name = line;
			Exercise e(exercise_name);
			
			int set_index = 0;
			while (std::getline(fs, line, '\n')) {
				if (line.find('~') != std::string::npos) {
					break;
				}
				int reps = std::stoi(line.substr(0, line.find(' ')));
				line = line.substr(line.find(' ') + 1);
				int time = std::stoi(line.substr(0, line.find(' ')));
				line = line.substr(line.find(' ') + 1);
				int rest = std::stoi(line.substr(0, line.find(' ')));
				line = line.substr(line.find(' ') + 1);
				bool yAMRAP = string_to_bool(line.substr(0, line.find(' ')));
				line = line.substr(line.find(' ') + 1);
				bool yALAP = string_to_bool(line.substr(0, line.find('\n')));
				e.add_set(set_index, -1, reps, time, rest, yAMRAP, yALAP);
				set_index++;
			}
			exercises.push_back(e);
		}
	}
	else {
		std::ofstream ofs(day_path);
	}
}

void WorkoutDay::display_day()
{
	std::cout << day_name << std::endl << std::endl;
	for (int i = 0; i < static_cast<int>(exercises.size()); i++) {
		std::cout << i + 1 << " - ";
		exercises[i].display_exercise();
		std::cout << std::endl;
	}
}

void WorkoutDay::add_exercise(int index, Exercise e)
{
	exercises.insert(exercises.begin() + index, e);
}

std::vector<Exercise>& WorkoutDay::get_exercises()
{
	return exercises;
}

void WorkoutDay::remove_exercise(int index)
{
	exercises.erase(exercises.begin() + index);
}

std::size_t WorkoutDay::size()
{
	return exercises.size();
}

void WorkoutDay::clear()
{
	exercises.clear();
}

void WorkoutDay::update()
{
	std::string day_path = "./" + space_to_underscore(plan_name) + "/" + space_to_underscore(day_name) + ".txt";
	std::ofstream ofs(day_path);
	ofs << day_index << "\n";
	for (int i = 0; i < static_cast<int>(exercises.size()); i++) {
		ofs << exercises[i].get_info() << "~\n";	
	}
}

void WorkoutDay::swap_exercise(int ind1, int ind2)
{
	std::iter_swap(exercises.begin() + ind1, exercises.begin() + ind2);
}

std::string WorkoutDay::get_path()
{
	std::string day_path = "./" + space_to_underscore(plan_name) + "/" + space_to_underscore(day_name) + ".txt";
	return day_path;
}

void WorkoutDay::change_day_index(int index)
{
	day_index = index;
}

int WorkoutDay::get_index()
{
	return day_index;
}