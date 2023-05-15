#ifndef _SUPPORT_H_ 
#define _SUPPORT_H_

#include<time.h>
#include<iostream>
#include<string>
#define num_of_names 20
#define num_of_last_names 20
#define DAY 86400 // in seconds 
class support {
public:
	std::string  insert_random_gender() const; //This function returns a random gender that was generated in the "generate_gender_and_name" function.
	std::string insert_random_first_name() const;  //This function returns a random first name that was generated in the "generate_gender_and_name" function.
	void generate_gender_and_name() ; //This function generates a random first name and gender. They are generated together because there is a dependance betweem the first name and gender.
	std::string insert_random_last_name()const; //This function returns a random last name.
	std::string insert_random_id() const; //This function gives an id.
	int insert_random_value() const; //This function gives a random value(for patient status).
	std::string insert_random_bday() const; //This function returns a random birthday.

	std::string get_current_time()const; //This function returns the current time .
	std::string insert_random_admission_time() const; //Inserts random admission time of the patient(hour and minute).
	std::string start_simulatiom_time(); //Begins the time simulation of the function.
	std::string move_one_day_forward(); //Moves the simulation on day forward.
	void operator<<(const support& a)const; //Operator, prints the curent time.
private:
	std::string temp_gender; //This variable is responsible to remember the gender.
	std::string temp_name; //This variable is responsible to remember the name.  
	std::string list_of_first_names[num_of_names] = { "Diana","Shai","Roni","Noy","Lilah","Shani","Koral","Adi","Sivan","Sarah",  //List of names.
	"Haim","Moshe","Ofer","Eduard","Evgeni","Rami","Nisim","Arie","Dani","Abraham"};
	std::string list_of_last_names[num_of_last_names] = { "Cohen","Levi","Biton","Mizrahi","Freeman","Barak","Azulai","Rabbin", //List of last names.
	"Hadad","Gabai","Klein","Smith","katz","Dahan","Edri","Biden","Shapira","Hazzan","Assaf","Jackson" };
	static int curr_id; //This static variable is responsible to remember the current ID number.
	static long long m_sim_time; // This static variable is responsible to move the dates forward(in 24 hour jumps),it basically remembers the current simulation time.
	
	

};

#endif