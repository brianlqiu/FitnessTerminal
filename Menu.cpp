#include "fitness.h"
#include "utility.h"
#include <iostream>
#include <string>

bool Menu::exit(std::string response) 
{
	if (response == "x") {
		std::cout << "Exited" << std::endl;
		return true;
	} 
	return false;
}

std::string Menu::prompt_name()
{
	std::string response;
	while (true) {
		std::cout << "Input a name: ";
		std::getline(std::cin, response);
		if (exit(response)) {
			return "-1";
		}
		std::string filename = space_to_underscore(response);
		if (response != "") {
			return response;
		}
		else {
			std::cout << "Name is invalid (already exists or empty string)" << std::endl;
		}
	}
}

int Menu::prompt_sets()
{
	std::string response;
	int num_sets = -1;
	while (true) {
		std::cout << "Input number of sets: ";
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (!string_is_integer(response)) {
			std::cout << "Response is not a number" << std::endl;
		}
		else {
			num_sets = std::stoi(response);
			if (num_sets > 0) {
				return num_sets;
			}
			else {
				std::cout << "Cannot have 0 or negative sets" << std::endl;
			}
		}
	}
}

double Menu::prompt_weight()
{
	std::string response;
	double weight;
	while (true) {
		std::cout << "Input weight (in pounds): ";
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (!string_is_double(response)) {
			std::cout << "Response is not a number" << std::endl;
		}
		else {
			weight = std::stod(response);
			if (weight >= 0) {
				return weight;
			}
			else {
				std::cout << "Cannot input negative weight" << std::endl;
			}
		}
	}

}

int Menu::prompt_reps()
{
	std::string response;
	int num_reps = -1;
	while (true) {
		std::cout << "Input number of reps for the set(s): ";
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (!string_is_integer(response)) {
			std::cout << "Response is not a number" << std::endl;
		}
		else {
			num_reps = std::stoi(response);
			if (num_reps > 0) {
				return num_reps;
			}
			else {
				std::cout << "Number of reps cannot be 0 or negative" << std::endl;
			}
		}
	}
}

int Menu::prompt_AMRAP() 
{
	while (true) {
		std::cout << "Input y for AMRAP set, n if not: ";
		std::string response;
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (response == "y") {
			return 1;
		}
		if (response == "n") {
			return 0;
		}
		std::cout << "Invalid response" << std::endl;
	}
}

int Menu::prompt_rest() 
{
	std::string response;
	int rest_time = -1;
	while (true) {
		std::cout << "Input rest time in seconds: ";
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (!string_is_integer(response)) {
			std::cout << "Response is not a number" << std::endl;
		}
		else {
			rest_time = std::stoi(response);
			if (rest_time >= 0) {
				return rest_time;
			}
			else {
				std::cout << "Cannot have negative rest time" << std::endl;
			}
		}
	}
}

int Menu::prompt_reps_or_time() 
{
	std::string response;
	while (true) {
		std::cout << "Input r for reps or t for timed: ";
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (response != "r" && response != "t") {
			std::cout << "Invalid response" << std::endl;
		}
		else {
			if (response == "r") {
				return 0;
			}
			else {
				return 1;
			}
		}
	}
}

int Menu::prompt_time() 
{
	std::string response;
	int exercise_time = -1;
	while (true) {
		std::cout << "Input exercise time for the set(s): ";
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (!string_is_integer(response)) {
			std::cout << "Response is not a number" << std::endl;
		}
		else {
			exercise_time = std::stoi(response);
			if (exercise_time > 0) {
				return exercise_time;
			}
			else {
				std::cout << "Number of reps cannot be 0 or negative" << std::endl;
			}
		}
	}
}

int Menu::prompt_ALAP()
{
	while (true) {
		std::cout << "Input y for ALAP set, n if not: ";
		std::string response;
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (response == "y") {
			return 1;
		}
		if (response == "n") {
			return 0;
		}
		std::cout << "Invalid response" << std::endl;
	}
}

int Menu::prompt_index(int size, bool add)
{
	while (true) {
		std::cout << "Input the index: ";
		std::string response;
		int index;
		std::getline(std::cin, response);
		if (exit(response)) {
			return -1;
		}
		if (!string_is_integer(response)) {
			std::cout << "Response is not a number" << std::endl;
		}
		else {
			index = std::stoi(response);
			if (add && index >= 1 && index <= size + 1) {
				return index;
			}
			else if (!add && index >= 1 && index <= size) {
				return index;
			}
			else {
				std::cout << "Invalid index" << std::endl;
			}
		}
	}

}

void Menu::prompt_create_set(Exercise& e, int sets, int index)
{
	int r_or_t_response = prompt_reps_or_time();
	if (r_or_t_response != -1) {
		if (r_or_t_response == 0) {
			int num_reps = prompt_reps();
			if (num_reps != -1) {
				int yAMRAP = prompt_AMRAP();
				if (yAMRAP != -1) {
					int rest_time = prompt_rest();
					if (rest_time != -1) {
						if (index == -1) {
							e.fast_add(sets, -1, num_reps, -1, rest_time, yAMRAP, false);
						}
						else {
							e.add_set(index - 1, -1, num_reps, -1, rest_time, yAMRAP, false);
						}
					}
				}
			}
		}
		else {
			int exercise_time = prompt_time();
			if (exercise_time != -1) {
				int yALAP = prompt_ALAP();
				if (yALAP != -1) {
					int rest_time = prompt_rest();
					if (rest_time != -1) {
						if (index == -1) {
							e.fast_add(sets, -1, -1, exercise_time, rest_time, false, yALAP);
						}
						else {
							e.add_set(index - 1, -1, -1, exercise_time, rest_time, false, yALAP);
						}
					}
				}
			}
		}
	}
	
}

void Menu::prompt_fast_add(Exercise& e)
{
	int num_sets = prompt_sets();
	if (num_sets != -1) {
		prompt_create_set(e, num_sets, -1);
	}
}

void Menu::prompt_add(Exercise& e)
{
	int index = prompt_index(e.size(), true);
	if (index != -1) {
		prompt_create_set(e, -1, index - 1);
	}
}

void Menu::prompt_all_weight(Exercise& e)
{
	double exercise_weight = prompt_weight();
	if (exercise_weight != -1) {
		e.change_all_weight(exercise_weight);
	}
}

void Menu::prompt_all_reps(Exercise& e)
{
	int num_reps = prompt_reps();
	if (num_reps != -1) {
		int yAMRAP = prompt_AMRAP();
		if (yAMRAP != -1) {
			e.change_all_reps(num_reps, yAMRAP);
		}
	}
}

void Menu::prompt_all_time(Exercise& e)
{
	int exercise_time = prompt_time();
	if (exercise_time != -1) {
		int yALAP = prompt_ALAP();
		if (yALAP != -1) {
			e.change_all_time(exercise_time, yALAP);
		}
	}
}

void Menu::prompt_all_rest(Exercise& e)
{
	int rest_time = prompt_rest();
	if (rest_time != -1) {
		e.change_all_rest(rest_time);
	}
}

void Menu::prompt_specific_weight(Exercise& e)
{
	int index = prompt_index(e.size(), false);
	if (index != -1) {
		double exercise_weight = prompt_weight();
		if (exercise_weight != -1) {
			e.change_weight(index - 1, exercise_weight);
		}
	}
}

void Menu::prompt_specific_reps(Exercise& e)
{
	int index = prompt_index(e.size(), false);
	if (index != -1) {
		int num_reps = prompt_reps();
		if (num_reps != -1) {
			int yAMRAP = prompt_AMRAP();
			if (yAMRAP != -1) {
				e.change_reps(index - 1, num_reps, yAMRAP);
			}
		}
	}
}

void Menu::prompt_specific_time(Exercise& e)
{
	int index = prompt_index(e.size(), false);
	if (index != -1) {
		int exercise_time = prompt_time();
		if (exercise_time != -1) {
			int yALAP = prompt_ALAP();
			if (yALAP != -1) {
				e.change_reps(index - 1, exercise_time, yALAP);
			}
		}
	}
}

void Menu::prompt_specific_rest(Exercise& e)
{
	int index = prompt_index(e.size(), false);
	if (index != -1) {
		int rest_time = prompt_rest();
		if (rest_time != -1) {
			e.change_rest(index - 1, rest_time);
		}
	}
}

void Menu::prompt_change_name(Exercise& e)
{
	std::string name = prompt_name();
	if (name != "-1") {
		e.change_name(name);
	}
}

void Menu::prompt_remove(Exercise& e)
{
	int index = prompt_index(e.size(), false);
	if (index != -1) {
		e.remove_set(index - 1);
	}
}

void Menu::prompt_swap_sets(Exercise& e)
{
	int ind1 = prompt_index(e.size(), false);
	if (ind1 != -1) {
		int ind2 = prompt_index(e.size(), false);
		if (ind2 != -1) {
			e.swap_sets(ind1 - 1, ind2 - 1);
		}
	}
}

Exercise Menu::create_exercise() 
{
	std::string name;
	name = prompt_name();
	if (name != "-1") {
		Exercise new_exercise(name);
		edit_exercise(new_exercise);
		return new_exercise;
	}
	Exercise blank;
	return blank;
}


void Menu::edit_exercise(Exercise& ex) {
	Exercise& e = ex;
	std::string response;
	do {
		std::cout << "-----------------------------------" << std::endl;
		e.display_exercise();
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Options: " << std::endl;
		std::cout << "1 - Fast add" << std::endl;
		std::cout << "2 - Add set" << std::endl;
		std::cout << "3 - Change all set reps/AMRAP" << std::endl;
		std::cout << "4 - Change all set times/ALAP" << std::endl;
		std::cout << "5 - Change all set rest times" << std::endl;
		std::cout << "6 - Change specific set reps/AMRAP" << std::endl;
		std::cout << "7 - Change specific set time/ALAP" << std::endl;
		std::cout << "8 - Change specific set rest time" << std::endl;
		std::cout << "9 - Rearrange set order" << std::endl;
		std::cout << "10 - Change exercise name" << std::endl;
		std::cout << "11 - Remove a set" << std::endl;
		std::cout << "12 - Clear all sets" << std::endl;
		std::cout << "13 - Remove the exercise" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl << "Enter your input: ";
		std::getline(std::cin, response);

		if (response == "1") {
			prompt_fast_add(e);
		}
		else if (response == "2") {
			prompt_add(e);
		}
		else if (response == "3") {
			prompt_all_reps(e);
		}
		else if (response == "4") {
			prompt_all_time(e);
		}
		else if (response == "5") {
			prompt_all_rest(e);
		}
		else if (response == "6") {
			prompt_specific_reps(e);
		}
		else if (response == "7") {
			prompt_specific_time(e);
		}
		else if (response == "8") {
			prompt_specific_rest(e);
		}
		else if (response == "9") {
			prompt_swap_sets(e);
		}
		else if (response == "10") {
			prompt_change_name(e);
		}
		else if (response == "11") {
			prompt_remove(e);
		}
		else if (response == "12") {
			std::cout << "Are you sure you want to clear all sets? (y/n): ";
			std::getline(std::cin, response);
			if (response == "y") {
				e.clear();
			}
			else {
				std::cout << "Exited" << std::endl;
			}
		}
		else if (response == "13") {
			std::cout << "Are you sure you want to delete this exercise? (y/n): ";
			std::getline(std::cin, response);
			if (response == "y") {
				e.remove();
				response = "x";
			}
			else {
				std::cout << "Exited" << std::endl;
			}
		}
		else if (response != "x") {
			std::cout << "Invalid response";
		}
	} while (!exit(response));
}

void Menu::prompt_add_exercise(WorkoutDay& w)
{
	int index = 1;
	if (w.size() > 0) {
		index = prompt_index(w.size(), true);
	}
	if (index != -1) {
		Exercise e = create_exercise();
		w.add_exercise(index - 1, e);
	}
}

void Menu::prompt_edit_exercise(WorkoutDay& w)
{
	int index = prompt_index(w.size(), false);
	if (index != -1) {
		edit_exercise(w.get_exercises()[index - 1]);
	}
}

void Menu::prompt_remove_exercise(WorkoutDay& w)
{
	int index = prompt_index(w.size(), false);
	if (index != -1) {
		w.remove_exercise(index - 1);
	}
}

void Menu::prompt_clear_exercise(WorkoutDay& w)
{
	std::string response;
	std::cout << "Are you sure you want to clear all exercises? (y/n): ";
	std::getline(std::cin, response);
	if (response != "n") {
		w.clear();
	}
}

void Menu::prompt_swap_exercises(WorkoutDay& w)
{
	int ind1 = prompt_index(w.size(), false);
	if (ind1 != -1) {
		int ind2 = prompt_index(w.size(), false);
		if (ind2 != -1) {
			w.swap_exercise(ind1 - 1, ind2 - 1);
		}
	}
}

void Menu::edit_day(WorkoutDay& d)
{
	std::string response;
	do {
		std::cout << "-----------------------------------" << std::endl;
		d.display_day();
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Options: " << std::endl;
		std::cout << "1 - Add an exercise" << std::endl;
		std::cout << "2 - Edit an exercise" << std::endl;
		std::cout << "3 - Rearrange order of exercises" << std::endl;
		std::cout << "4 - Remove an exercise" << std::endl;
		std::cout << "5 - Clear all exercises" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl << "Enter your input: ";
		std::getline(std::cin, response);

		if (response == "1") {
			prompt_add_exercise(d);
			d.update();
		}
		else if (response == "2") {
			prompt_edit_exercise(d);
			d.update();
		}
		else if (response == "3") {
			prompt_swap_exercises(d);
			d.update();
		}
		else if (response == "4") {
			prompt_remove_exercise(d);
			d.update();
		}
		else if (response == "5") {
			prompt_clear_exercise(d);
			d.update();
		}
		else {
			std::cout << "Invalid response" << std::endl;
		}

	} while (!exit(response));
	
}

WorkoutDay Menu::create_day(std::string planname, int index)
{
	std::string name = prompt_name();
	if (name != "-1") {
		WorkoutDay d(planname, name, index);
		edit_day(d);
		return d;
	}
	WorkoutDay blank;
	return blank;
}

void Menu::prompt_add_day(WorkoutPlan& p)
{
	int index = 0;
	if (p.size() != 0) {
		index = prompt_index(p.size(), true);
	}
	if (index != -1) {
		WorkoutDay w = create_day(p.get_name(), index);
		p.add_day(index - 1, w);

	}
}

void Menu::prompt_edit_day(WorkoutPlan& p)
{
	int index = prompt_index(p.size(), false);
	if (index != -1) {
		edit_day(p.get_days()[index - 1]);
	}
}

void Menu::prompt_swap_days(WorkoutPlan& p)
{
	int ind1 = prompt_index(p.size(), false);
	if (ind1 != -1) {
		int ind2 = prompt_index(p.size(), false);
		if (ind2 != -1) {
			p.swap_day(ind1 - 1, ind2 - 2);
		}
	}
}

void Menu::prompt_remove_day(WorkoutPlan& p)
{
	int index = prompt_index(p.size(), false);
	if (index != -1) {
		std::string response;
		std::cout << "Are you sure you want to remove this day? (y/n): ";
		std::getline(std::cin, response);
		if (response == "y") {
			p.remove_day(index - 1);
		}
	}
}

void Menu::prompt_clear_days(WorkoutPlan& p)
{
	std::string response;
	std::cout << "Are you sure you want to clear all days? (y/n): ";
	std::getline(std::cin, response);
	if (response == "y") {
		p.clear();
	}
}

void Menu::edit_plan(WorkoutPlan& p)
{
	std::string response;
	do {
		std::cout << "-----------------------------------" << std::endl;
		p.display_plan();
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Options: " << std::endl;
		std::cout << "1 - Add an day" << std::endl;
		std::cout << "2 - Edit a day" << std::endl;
		std::cout << "3 - Rearrange days" << std::endl;
		std::cout << "4 - Remove a day" << std::endl;
		std::cout << "5 - Clear all days" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl << "Enter your input: ";
		std::getline(std::cin, response);

		if (response == "1") {
			prompt_add_day(p);
			p.update();
		}
		else if (response == "2") {
			prompt_edit_day(p);
			p.update();
		}
		else if (response == "3") {
			prompt_swap_days(p);
			p.update();
		}
		else if (response == "4") {
			prompt_remove_day(p);
			p.update();
		}
		else if (response == "5") {
			prompt_clear_days(p);
			p.update();
		}
		else {
			std::cout << "Invalid response" << std::endl;
		}

	} while (!exit(response));
}

WorkoutPlan Menu::create_plan()
{
	std::string name = prompt_name();
	if (name != "-1") {
		WorkoutPlan p(name);
		edit_plan(p);
		return p;
	}
	WorkoutPlan blank;
	return blank;
}
