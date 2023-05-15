#include "people.h"
#include<stdlib.h>
using namespace std;

int doctor::doctor_salary = 100;
int nurses::nurse_salary = 50;
person::person(const std::string& id,const std::string& bday,const std::string& gender,const std::string& fname,const std::string& lname)
{
	m_id = id;
	m_bday = bday;
	m_gender = gender;
	m_fname = fname;
	m_lname = lname;
}
person::~person() //no dynamic memory was allocated
{
}

std::string person::get_id_num() const
{
	return m_id;
}

std::string person::get_gender() const
{
	return m_gender;
}

std::string person::get_fname() const
{
	return m_fname;
}

std::string person::get_lname() const
{
	return m_lname;
}

std::string person::get_bday() const
{
	return m_bday;
}

void person::operator<<(const person& a) const
{
	cout << a.get_id_num() << "  " << a.get_bday() << "  " << a.get_gender() << "  " << a.get_fname() << "  " << a.get_lname() << endl;
}


void patient::set_room(const int& r) //sets the patient's current room number.
{
	m_room_number = r;
}

int patient::get_room_num() const
{
	return m_room_number;
}

void patient::update_status()
{
	m_status += rand() % 8 - 3; //updates the health status
}

int patient::get_status() const //This funciton is reponsible to return the current health status of the patient
{
	return m_status;
}


std::string patient::get_admission_time() const
{
	return m_admission_time;
}

std::string patient::get_admission_date() const
{
	return m_admission_date;
}

void patient::insert_end_admission_date(const std::string& a)
{
	m_end_admission_date = a;
}

std::string patient::get_end_admission_date() const
{
	return m_end_admission_date;
}

void patient::operator<<(const patient& a) const
{
	std::string b = "                             ";
	b.insert(0, a.get_id_num());
	b.insert(9, a.get_bday());
	b.insert(21, a.get_gender());
	b.insert(29, a.get_fname());
	b.insert(37, a.get_lname());
	b.insert(45, to_string(a.get_room_num()));
	b.insert(50, to_string(a.get_status()));
	b.insert(55, a.get_admission_time());
	b.insert(62, a.get_admission_date());
	cout << b;
}


int doctor::bill() const
{
	return doctor_salary;
}

int nurses::bill() const
{
	return nurse_salary;
}

