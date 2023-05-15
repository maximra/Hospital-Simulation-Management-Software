#ifndef _ROOM_H_ 
#define _ROOM_H_
#include"people.h"
#include<iostream>
#include<string>
#define num_of_patients 4

class room
{
public:
	room(const int& room_num);
	~room();
	void insert_patient(const std::string& patient_id); //This function inserts a patient to the room.
	void remove_patient(const std::string& patient_id); //This function removes a patient from the room.
	bool check_if_full() const; //Checks whether or not the room is full (1-full) ,(0-not full).
	int get_current_amount_of_patients() const; //Returns the amount of patients in the room.
	void insert_doctor_to_room(const int& a); //Insert the index of a doctor to the room.
	void insert_nurse_to_room(const int& a); //Insert the index of a nurse to the room.
	int get_doctor_in_room() const; //Returns the doctor index.
	int get_nurse_in_room() const; //Returns the nurse index.
	void operator<<(const room& a)const; //prints the ID's of the  patients in the room.
private:
	std::string* m_array_of_patients[num_of_patients]; // The array of patients in that specific room
	int m_room_nurse_index;  //Index of the nurse in the list of nurses.
	int m_room_doctor_index;// Index of the doctor in the list of doctor.
	int curr_amount_of_patients; //Shows the current amount of patients in the room.
	int m_room_num;  //Room number.

};

#endif
