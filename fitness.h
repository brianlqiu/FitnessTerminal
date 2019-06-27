#ifndef FITNESS_H
#define FITNESS_H

#include <vector>
#include <string>
#include <ctime>

/*
@file fitness.h

@brief Contains the definitions for the Exercise and Workout classes

@author Brian Qiu
Contact: brianlqiu5@gmail.com
*/


/*
Stores the rep range and rest time for a set
*/
class Set {
public:

	/*
	Returns the number of reps for the set

	@return the number of reps for the set
	*/
	int getReps() { return reps; }

	/*
	Returns the rest time for the set

	@return the rest time in seconds for the set
	*/
	int getRestTime() { return restTime; }

	/*
	Changes the number of reps for the set

	@param the desired number of reps
	*/
	void setReps(int numReps) { reps = numReps; }

	/*
	Changes the rest time for the set

	@param the desired rest time in seconds
	*/
	void setRestTime(int newRestTime) { restTime = newRestTime; }

private:

	int reps;
	int restTime;
};

/*
Stores data about an exercise
*/
class Exercise {
public:
	
	/*
	Initializes the name, number of sets, number of reps per set, and rest times per
	set; If a text file for tracking progress for the exercise has not been created, 
	one is created

	@param name name of the exercise
	@param sets number of sets for the exercise
	*/
	Exercise(string name, int sets);
	
	/*
	Adds a set of the specified number of reps at the given index

	@param setIndex the index at which the set should be inserted
	@param repNum the number of reps for the set
	*/
	void addSet(int setIndex, int repNum);

	/*
	Removes the set at the given index

	@param setIndex the index of the set to be removed
	*/
	void removeSet(int setIndex);

	/*
	Changes the number of reps for the set at the given index

	@param setIndex the index of the set to be changed
	@param repNum the desired number of reps
	*/
	void changeSetReps(int setIndex, int repNum);
	
	/*
	Changes the name of the exercise

	@param name the name to change the exercise name to
	*/
	void setExerciseName(string name) { exerciseName = name; }

	/*
	Displays a data table of the progress of this exercise
	*/
	void displayStatsTable();

	/*
	Displays a graph of the progress of this exercise
	*/
	void displayStatsGraph();

	/*
	Returns a reference to the sets of this exercise

	@return a reference to the sets of this exercise
	*/
	&vector<Set> getSets(); { return sets; }

	/*
	Returns the name of this exercise

	@return the name of this exercise
	*/
	string getName() { return exerciseName; }

	/*
	Overloaded equals comparative operator, returns true if the exercises have the same 
	name, false if not

	@return true if the names are the same, false if the names are different
	*/
	friend bool operator==(const& Exercise e1, const& Exercise e2) 
	{ return e1.exerciseName == e2.exerciseName; }
private:
	/*
	Used in the construcctor to update the setsRepsRest vector, prompts the user for
	number of reps and rest times per set
	*/
	void addRepsAndRestTimes();

	string exerciseName;
	vector<Set> sets;
};

/*
Stores information about the exercises for a workout day
*/
class WorkoutDay {
public:

	/*
	Creates a workout day with the given name; If the workout day already exists
	the data is loaded

	@param the name of the workout day
	*/
	WorkoutDay(string name);

	/*
	Adds the exercise to the end of the vector of exercises

	@param newExercise the exercise to be added
	*/
	void addExercise(Exercise newExercise) { exercises.push_back(newExercise); }

	/*
	Inserts the exercise at the given index

	@param newExercise the exercise to be inserted
	@param index the index at which the exercise is inserted
	*/
	void insertExercise(Exercise newExercise, int index);

	/*
	Removes the exercise at the given index

	@param index the index of the exercise to be removed
	*/
	void removeExercise(int index);

	/*
	Moves the exercise from its old index to the new index

	@param oldIndex the current index of the exercise
	@param newIndex the new index of the exercise
	*/
	void moveExercise(int oldIndex, int newIndex);

	/*
	Sets the name of the day to the desired name

	@param name the new name for the day
	*/
	void setDayName(string name) { dayName = name; }

	/*
	Returns a reference to the exercise list for the day

	@return a vector containing the exercises for the day
	*/
	&vector<Exercise> getExercises() { return exercises; }

private:
	string dayName;
	vector<Exercise> exercises;
};

/*
Contains a vector of workout days comprising a workout plan
*/
class WorkoutPlan {
public:
	/*
	If a text file containing the workout plan name does not exist,
	a workout plan is created; Otherwise the existing workout plan
	is loaded

	@param name the name of the workout plan
	*/
	WorkoutPlan(string name);

	/*
	Adds a workout day to the list of days

	@param newDay the day to be added
	*/
	void addWorkoutDay(WorkoutDay newDay) { plan.push_back(newDay); }

	/*
	Inserts a workout day to the given index

	@param newDay the day to be added
	@return index the index the day is added to
	*/
	void insertWorkoutDay(WorkoutDay newDay, int index);

	/*
	Moves the workout day to a new index

	@param oldIndex the workout day's old index
	@return newIndex the workout day's new index
	*/
	void moveWorkoutDay(int oldIndex, int newIndex);

	/*
	Removes the workout day at the index

	@param index the index to be removed
	*/
	void removeWorkoutDay(int index);

	/*
	Updates the workout plan text file
	*/
	void updateWorkoutPlan();

	/*
	Returns the plan name

	@return the plan name
	*/
	string getPlanName() { return planName; }

	/*
	Returns the vector of WorkoutDays

	@return a reference to the vector of WorkoutDays
	*/
	&vector<WorkoutDay> getPlan() { return plan; }
private:
	string planName;
	vector<WorkoutDay> plan;
};

/*
Contains functions that allow for a workout
*/
class Workout{
public:
	/*
	Initializes the date, the workout timer, and the exercise list
	*/
	Workout();

	/*
	Performs the exercise at the given index

	@param exerciseIndex the index of the exercise to be performed
	*/
	void performExercise(int exerciseIndex);

	/*
	Counts down the seconds for the rest timer

	@param secs the time to rest in seconds
	*/
	void restTimer(int secs);

private:
	time_t date;
	clock_t timer;
	vector<Exercise> exercises;

};
#endif