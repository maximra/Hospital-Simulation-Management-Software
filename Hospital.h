#ifndef _HOSPITAL_H_ 
#define _HOSPITAL_H_

#include"people.h"
#include"room.h"
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<array>
#include"support.h"
#include<fstream>
#include<sstream> //for std::stringstream
#include <stdlib.h> 
#include<conio.h>
#define MAX_PATIENTS 2000
#define MAX_NURSES 500
#define MAX_DOCTORS 500
#define NUM_OF_ROOMS 500
class Hospital {


public:
	Hospital(const std::string& hospital_name); //consturctor
	~Hospital(); //destructor

	//Printing functions :
	void print_all_doctors() const; //Prints array of doctors.
	void print_all_nurses() const;  //Prints the array of nurses.
	void print_all_patients() const; //Prints the array of all patients that are currently in the hospital.
	void print_all_released_patients() const; //Prints the vector array of patients that were discharged from the hospital.
	void print_all_patients_that_passed_away() const; //Prints the vetor array of patients that passed away.
	std::string get_hostital_name() const; //Returns the hosptial name .
	void operator<<(const Hospital& a)const; //Prints the hospital name.

	void launch_simulation(); //This function launches the main simulation

	//Room functions:
	int check_room() const; //Returns room that is not full.
	void hospital_insert_patient_to_room(const std::string& id, const int& room_number); //This function is responsible to insert a patient to a room.
	void remove_patient_from_hospital(const int& num, const std::string& id); //This function removes a patient from the hospital.
	

	//Patient functions:
	void update_all_patient_status(); //Updates the status of all patients in the hopsital. 
	void perform_action_on_all_patients(); //Checks the status of all patients->if above a certain threshold, release from hospital. If below a certain threshold, patient passed away.
	void insert_patient_to_hospital(); //Inserts a random new patient to the hospital.
	void move_patient_room(); //This functions moves patient a room.
	//Employee functions:
	void insert_employees_to_room(); //Inserts employees to the rooms that aren't empty .
	void remove_employees_from_rooms(); //Removes employees from a room.
	int daily_bill_from_current_employees() const; //This function returns the bill from the employees for that specific day..

	//Fstream functions:
	void save_all_current_patients() const; //Saves all current patients in the hospital in an CSV file.
	void pull_up_certain_day_patients(const int& day) const; // This functions uploads the data of all the patients that were accepted in a specific day.
	void save_all_released_patients() const; //This funciton saves all the patients that were discharged from the hospital in an CSV file.
	void save_all_patients_that_passed_away() const; //This funcion saves all the patients that passed away in an CSV file.
	void pull_up_certain_day_finances(int chosen_day) const;  //This function pulls up certrain day profits and loses from an CSV file.
	void save_all_active_rooms(const int& day) const; //Saves all active rooms for that specific day.
	void pull_up_certain_day_room(const int& day) const; //Uploads the data of the rooms that were active for that specific day
	void pull_up_patients_with_specific_status() ; //This function returns patients between two statuses (including edge values too).
	void get_capacity()const; //Returns the amount of free beds in the hospital, occupied beds in hospital, and the capacity in procentage.
	void clear_all_files()const; //Whenever you choose to launch a new simulation, this functions cleans all the CSV files.
	void save_all_doctor_and_nurse_data() const; //This function saves all the data of the doctors and nurses .

	//User input functions:
	void clear_buffer(); //In case the user inserts a char/string.
	void get_user_input_for_simulation_length(); //This function is reponsible to insert how many simulation days the user wants.
	void main_user_menu(); // This function opens the main user menu.
	void get_user_input_for_main_menu(); //User inputs for main menu.
	int get_user_chosen_day(int num); //User selected day for specific operation.
	void search_for_person_by_id(); //Opens a sub menu that searches for a person that is currently in the hospital.
	void advanced_patients_search(); //searches patients by other criteria in case you dont know the id.
	void manual_patient_insert(); //Manually insert a patient to the hospital.
	void update_nurse_and_doctor_salaries(const bool& a); //This function allows the user to update the salaries for doctors and nurses.
	//Finance functions:
	void calc_daily_profits(const int& day,const std::string& date); // Calculates the daily profits/loses of the hospital.
	int get_total_profits() const; //Returns total hospital profits/loses.
	
	//Recovery functions
	int ask_for_previous_data();  //This function asks the user whether or not the he/she wishes to use the previous data instead of launching a new simulation.
	void save_general_parameters()const; //saves general data that is essential for recovery.
	void get_general_parameters(); //uploads the general data from the previous launch.
	void recover_data(); //This functions allows us to recover the data from the previous launch.
	void upload_doctor_and_nurse_data(); //This function uploads all doctor and nurse data from the previous launch.
	void upload_all_patient_data(); //This functions uploads all patient data from previous launch.

private:
	 int curr_num_of_patients; //Current numbers of patients in the hospital.
	 int curr_employees; //Shows the current amount of doctors and nurses working.
	std::map<std::string, patient> list_of_patients{}; //Container type-map, It's responsible to hold the array of patients in the hospital.
	std::vector<std::unique_ptr <doctor>>list_of_doctors; //Container type-vector it's responsible to hold the array of doctors in the hospital.
	std::vector <std::unique_ptr <nurses>>list_of_nurses; //Container type-vector, it's responsible to hold the array of nurses in the hospital.
	std::vector<std::unique_ptr<room>>list_of_rooms; //Container type-vector, it's repsonsible to hold the array of rooms in the hospital.
	std::vector<std::unique_ptr<patient>> patients_that_left; //container type-vector, it's responsible to hold the array of patients that were discharged 
	std::vector<std::unique_ptr<patient>> patients_that_passed_away; //container type-vector, it's responsible to hold the array of patients that passed away in the hospital
	std::string m_hospital_name; //Hospital name.
	std::map<std::string, patient>::iterator itr; //It's used to update the values of the list_of_patients. 
	std::string current_date; //Holds the current date.
	employee* array_of_current_employees[MAX_DOCTORS + MAX_NURSES]; // Pointer, shows the employees that are working today. 
	int simulation_limit; // This variable is responsible to remember how many simulations days were declared.
	int hospital_profits; //This variable is responsible to remember the total profits/loses of the hospital.
	std::string rooms_data; //Responsible to remember which rooms were used for a specific day.
	bool menu_key; //This variable is responsible to quit the  main menu(ends the programs).
	
};

#endif