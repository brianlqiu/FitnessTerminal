#include "fitness.h"
#include "utility.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>


Exercise::Set::Set(double set_weight = -1, int num_reps = -1, int exercise_time = -1, int rest_time = -1, bool yAMRAP = false, bool yALAP = false) {
	weight = set_weight;
	reps = num_reps;
	time = exercise_time;
	rest = rest_time;
	AMRAP = yAMRAP;
	ALAP = yALAP;
}

bool Exercise::valid_index(int index) 
{
	if (index < 0 || index >= static_cast<int>(sets.size())) {
		std::cout << "Invalid index" << std::endl;
		return false;
	}
	return true;
}


Exercise::Exercise(std::string name) 
{
	exercise_name = name;
	file_name = "./Exercises/" + space_to_underscore(name) + ".txt";
	if (!file_exists(name)) {
		std::ofstream outfile(file_name);
	}
}

void Exercise::add_set(int index, double exercise_weight, int num_reps, int exercise_time, int rest_time, bool yAMRAP, bool yALAP)
{
	Set new_set(exercise_weight, num_reps, exercise_time, rest_time, yAMRAP, yALAP);
	sets.insert(sets.begin() + index, new_set);
	
}

void Exercise::remove_set(int index)
{
	if (valid_index(index)) {
		sets.erase(sets.begin() + index);
	}
}

void Exercise::change_all_weight(double exercise_weight)
{
	if (exercise_weight > 0) {
		for (int i = 0; i < static_cast<int>(sets.size()); i++) {
			sets[i].weight = exercise_weight;
		}
	}
	else {
		std::cout << "Invalid weight" << std::endl;
	}
}

void Exercise::change_all_reps(int num_reps, bool yAMRAP)
{
	if (num_reps > 0) {
		for (int i = 0; i < static_cast<int>(sets.size()); i++) {
			sets[i].reps = num_reps;
			sets[i].time = -1;
			sets[i].AMRAP = yAMRAP;
			sets[i].ALAP = false;
		}
	}
	else {
		std::cout << "Invalid rep range" << std::endl;
	}
}

void Exercise::change_all_time(int exercise_time, bool yALAP)
{
	if (exercise_time > 0) {
		for (int i = 0; i < static_cast<int>(sets.size()); i++) {
			sets[i].time = exercise_time;
			sets[i].reps = -1;
			sets[i].ALAP = yALAP;
			sets[i].AMRAP = false;
		}
	}
	else {
		std::cout << "Invalid time" << std::endl;
	}
}

void Exercise::change_all_rest(int rest_time)
{
	if (rest_time > 0) {
		for (int i = 0; i < static_cast<int>(sets.size()); i++) {
			sets[i].rest = rest_time;
		}
	}
	else {
		std::cout << "Invalid time" << std::endl;
	}
}

void Exercise::change_weight(int index, double exercise_weight)
{
	if (valid_index(index) && exercise_weight > 0) {
		sets[index].weight = exercise_weight;
	}
	else {
		std::cout << "Invalid weight" << std::endl;
	}
}

void Exercise::change_reps(int index, int num_reps, bool yAMRAP) 
{
	if (valid_index(index) && num_reps > 0) {
		sets[index].reps = num_reps;
		sets[index].time = -1;
		sets[index].AMRAP = yAMRAP;
		sets[index].ALAP = false;
	}
	else {
		std::cout << "Invalid rep range" << std::endl;
	}
}

void Exercise::change_time(int index, int exercise_time, bool yALAP)
{
	if (valid_index(index) && exercise_time > 0) {
		sets[index].time = exercise_time;
		sets[index].reps = -1;
		sets[index].ALAP = yALAP;
		sets[index].AMRAP = false;
	}
	else {
		std::cout << "Invalid time" << std::endl;
	}
}

void Exercise::change_rest(int index, int rest_time)
{
	if (valid_index(index) && rest_time > 0) {
		sets[index].rest = rest_time;
	}
	else {
		std::cout << "Invalid rest time" << std::endl;
	}
}

void Exercise::change_name(std::string new_name)
{
	if (new_name != "" && !file_exists(new_name)) {
		exercise_name = new_name;
		std::string tmp = space_to_underscore(exercise_name) + ".txt";
		(void)std::rename(file_name.c_str(), tmp.c_str());
		file_name = tmp;
	}
	else {
		std::cout << "Name is invalid (already exists or empty string)" << std::endl;
	}
}

void Exercise::fast_add(int num_sets, double exercise_weight, int num_reps, int exercise_time, int rest_time, bool yAMRAP, bool yALAP)
{
	for (int i = 0; i < num_sets; i++) {
		add_set(i, exercise_weight, num_reps, exercise_time, rest_time, yAMRAP, yALAP);
	}
}

bool Exercise::skip() {
	skipped = true;
	return true;
}

bool Exercise::return_to() {
	skipped = false;
	return false;
}

void Exercise::display_exercise() {
	std::cout << exercise_name << std::endl;
	for (int i = 0; i < static_cast<int>(sets.size()); i++) {
		std::cout << "Set " << i + 1;
		if (sets[i].weight != -1) {
			std::cout << " (" << sets[i].weight << " lbs): ";
		}
		else {
			std::cout << ": ";
		}
		if (sets[i].reps != -1) {
			std::cout << sets[i].reps;
			if (sets[i].AMRAP) {
				std::cout << "+";
			}
			std::cout << " reps | ";
		}
		if (sets[i].time != -1) {
			std::cout << sets[i].time;
			if (sets[i].ALAP) {
				std::cout << "+";
			}
			std::cout << " seconds | ";
		}
		
		std::cout << sets[i].rest << " seconds of rest |" << std::endl;
	}
}

double Exercise::calculate_volume() {
	double ans = 0;
	for (int i = 0; i < static_cast<int>(sets.size()); i++) {
		ans += sets[i].weight * sets[i].reps;
	}
	return ans;
}

void Exercise::clear() {
	sets.clear();
}

std::size_t Exercise::size() {
	return sets.size();
}

std::string Exercise::get_exercise_name()
{
	return exercise_name;
}

void Exercise::remove() 
{
	std::remove(file_name.c_str());
}

std::string Exercise::get_info()
{
	std::string info = exercise_name + "\n";
	for (int i = 0; i < static_cast<int>(sets.size()); i++) {
		info += std::to_string(sets[i].reps) + " " + std::to_string(sets[i].time) + " " + std::to_string(sets[i].rest) + " " + bool_to_string(sets[i].AMRAP) + " " + bool_to_string(sets[i].ALAP);
		info += "\n";
	}
	return info;
}

void Exercise::swap_sets(int ind1, int ind2)
{
	if (valid_index(ind1) && valid_index(ind2)) {
		Set tmp = sets[ind1];
		sets[ind1] = sets[ind2];
		sets[ind2] = tmp;
	}
}