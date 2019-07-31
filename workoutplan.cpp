#ifndef WORKOUTPLAN_CPP
#define WORKOUTPLAN_CPP


#include "fitness.h"
#include "utility.h"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

WorkoutPlan::WorkoutPlan(std::string plan_name)
{
	std::string pathname = "./" + space_to_underscore(plan_name);
	fs::path p = pathname;
	fs::create_directory(p);

	for (const auto& entry : fs::directory_iterator(p)) {
		std::ifstream ifs(entry.path());
		char index[256];
		ifs.getline(index, 256);
		int ind = std::atoi(index);
		std::string convert = underscore_to_space(entry.path().filename());
		WorkoutDay w(plan_name, convert.substr(0, convert.find(".txt")), ind);
		workoutdays.push_back(w);
	}
	sort_days();
	this->plan_name = plan_name;
	path = pathname;
	
}

void WorkoutPlan::add_day(int index, WorkoutDay& w)
{
	for (int i = index + 1; i < workoutdays.size(); i++) {
		workoutdays[i].change_day_index(i + 1);
	}
	workoutdays.insert(workoutdays.begin() + index, w);
}

std::size_t WorkoutPlan::size()
{
	return workoutdays.size();
}

void WorkoutPlan::remove_day(int index)
{
	workoutdays.erase(workoutdays.begin() + index);
	std::string path = workoutdays[index].get_path();
	std::remove(path.c_str());
	
}

std::vector<WorkoutDay>& WorkoutPlan::get_days()
{
	return workoutdays;
}

void WorkoutPlan::display_plan()
{
	std::cout << plan_name << std::endl;
	for (int i = 0; i < static_cast<int>(workoutdays.size()); i++) {
		workoutdays[i].display_day();
		std::cout << std::endl;
	}
}

void WorkoutPlan::swap_day(int ind1, int ind2)
{
	workoutdays[ind1].change_day_index(ind2);
	workoutdays[ind2].change_day_index(ind1);
	std::iter_swap(workoutdays.begin() + ind1, workoutdays.begin() + ind2);

}

void WorkoutPlan::clear()
{
	for (int i = 0; i < static_cast<int>(workoutdays.size()); i++) {
		remove_day(i);
	}
	workoutdays.clear();
}

void WorkoutPlan::update()
{
	for (int i = 0; i < static_cast<int>(workoutdays.size()); i++) {
		workoutdays[i].update();
	}
}

std::string WorkoutPlan::get_name()
{
	return plan_name;
}

void WorkoutPlan::sort_days()
{
	for (int i = 0; i < workoutdays.size(); i++) {
		if (workoutdays[i].get_index() - 1 != i) {
			for (int j = i; j < workoutdays.size(); j++) {
				if (workoutdays[j].get_index() - 1 == i) {
					std::iter_swap(workoutdays.begin() + i, workoutdays.begin() + j);
				}
			}
		}
	}
}

#endif