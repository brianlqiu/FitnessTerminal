#ifndef FITNESS_H
#define FITNESS_H	

#include <vector>
#include <string>

/*
Super setting
*/
class Exercise {
public:
	Exercise();
	Exercise(std::string name);

	void add_set(int index, double exercise_weight, int num_reps, int exercise_time, int rest_time, bool yAMRAP, bool yALAP);
	void remove_set(int index);
	void clear();
	void change_all_weight(double exercise_weight);
	void change_all_reps(int num_reps, bool yAMRAP);
	void change_all_time(int exercise_time, bool yALAP);
	void change_all_rest(int rest_time);
	void change_weight(int index, double exercise_weight);
	void change_reps(int index, int num_reps, bool yAMRAP);
	void change_time(int index, int exercise_time, bool yALAP);
	void change_rest(int index, int rest_time);
	void change_name(std::string new_name);
	void fast_add(int num_sets, double exercise_weight, int num_reps, int exercise_time, int rest_time, bool yAMRAP, bool yALAP);

	int size();
	std::string get_exercise_name();

	bool skip();
	bool return_to();
	void display_exercise();
	double calculate_volume();
	void remove();

private:
	struct Set {
		Set(double set_weight, int num_reps, int exercise_time, int rest_time, bool yAMRAP, bool yALAP);
		double weight;
		int reps;
		int time;
		int rest;
		bool AMRAP; //As many reps as possible, can't be AMRAP & ALAP
		bool ALAP; //As long as possible

	};

	bool valid_index(int index);

	double weight;
	bool skipped;
	std::string exercise_name;
	std::string file_name;
	std::vector<Set> sets;
};

class Menu {
public:
	void create_exercise();

	void prompt_create_set(Exercise& e, int sets, int index);
	void prompt_fast_add(Exercise& e);
	void prompt_add(Exercise& e);
	void prompt_all_weight(Exercise& e);
	void prompt_all_reps(Exercise& e);
	void prompt_all_time(Exercise& e);
	void prompt_all_rest(Exercise& e);
	void prompt_specific_weight(Exercise& e);
	void prompt_specific_reps(Exercise& e);
	void prompt_specific_time(Exercise& e);
	void prompt_specific_rest(Exercise& e);
	void prompt_change_name(Exercise& e);
	void prompt_remove(Exercise& e);
	

private:
	bool exit(std::string response);
	int prompt_sets();
	double prompt_weight();
	int prompt_reps();
	int prompt_AMRAP();
	int prompt_rest();
	int prompt_reps_or_time();
	int prompt_time();
	int prompt_ALAP();
	int prompt_index(int size, bool add);
	std::string prompt_name();
};



#endif