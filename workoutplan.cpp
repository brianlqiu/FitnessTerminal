#include "fitness.h"
#include "utility.h"
#include <string>

WorkoutPlan::WorkoutPlan(std::string plan_name)
{
	//Create directory if one does not exist, otherwise loads and creates workoutdays

}

void WorkoutPlan::add_day(int index, WorkoutDay& w)
{
	workoutdays.insert(workoutdays.begin() + index, w);
}

int WorkoutPlan::size()
{
	return workoutdays.size();
}

void WorkoutPlan::remove_day(int index)
{
	workoutdays.erase(workoutdays.begin() + index);
}

void WorkoutPlan::display_plan()
{
	for (int i = 0; i < workoutdays.size(); i++) {
		workoutdays[i].display_day();
		std::cout << std::endl;
	}
}