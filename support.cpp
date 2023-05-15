#include "support.h"
#include<stdlib.h>
using namespace std;
struct tm newtime; //neccessary for dates and time
__time32_t aclock; //neccessary for dates and time
char buffer[32];  //neccessary for dates and time
errno_t errNum;  //neccessary for dates and time

int support::curr_id = 1000000;  //Static int, remembers the current ID num
long long support::m_sim_time = 0; //Static long long, reponsible to remember the current date(in seconds starting from jan 1st 1970)
std::string support::insert_random_gender() const //Return a random gender
{
	return temp_gender;
}

std::string support::insert_random_first_name() const //Return a random first name
{
	return temp_name;
}

void support::generate_gender_and_name() //Generating a random name and gender 
{
	
	int coin=rand() % 2;
	if (coin == 0)
	{
		coin = rand() % 10 + 10; 
		temp_gender = "male";
	}
	else
	{
		coin = rand() % 10;
		temp_gender = "female";
	}
	temp_name = list_of_first_names[coin];
}

std::string support::insert_random_last_name() const //return a random last name
{
	return list_of_last_names[rand()%20];
}

std::string support::insert_random_id() const //return an ID
{
	string temp_string = to_string(curr_id);
	curr_id++;
	return temp_string;
}

int support::insert_random_value() const //return a randum status (for the patient)
{
	return rand()%81+10;
}

std::string support::insert_random_bday() const  //return a random bday
{
	int year = 1995 - rand() % 45;
	int month = 1+rand() % 12;
	int day =1+ rand() % 30;
	string s_year=to_string(year);
	string s_month=to_string(month);
	string s_day=to_string(day);

		return s_day +"/"+s_month+"/" + s_year; 
}

std::string support::get_current_time() const //returns the current time
{
	_time32(&aclock);
	_localtime32_s(&newtime, &aclock);
	errNum = asctime_s(buffer, 32, &newtime);
	string s_admission = buffer;
	return s_admission.substr(4,12)+  s_admission.substr(19, 5);
}


std::string support::insert_random_admission_time() const //returns a random time(for the patient admission)
{
	int hour = rand() % 24;
	int minute = rand() % 60;
	string s_hour = to_string(hour);
	string s_minute = to_string(minute);
	if (hour < 10)
	{
		s_hour = "0" + s_hour;
	}
	if (minute < 10)
	{
		s_minute = "0" + s_minute;
	}
	return s_hour + ":"+s_minute;
}

std::string support::start_simulatiom_time() //This function is reponsible to start the simulation time
{
	_time32(&aclock);
	_localtime32_s(&newtime, &aclock);
	errNum = asctime_s(buffer, 32, &newtime);
	string s_admission = buffer;
	cout << "The exact launch time is : " << endl;
	cout << s_admission << endl;
	cout << "The simulation will begin simulating from the following date :" << endl;
	m_sim_time = aclock;
	return s_admission.substr(4, 6) + s_admission.substr(19, 5);
}

std::string support::move_one_day_forward() //move the date one day forward
{
	m_sim_time += DAY;
	aclock = m_sim_time;
	_localtime32_s(&newtime, &aclock);
	errNum = asctime_s(buffer, 32, &newtime);
	string s_admission = buffer;
	return s_admission.substr(4, 6) + s_admission.substr(19, 5);
}

void support::operator<<(const support& a) const //prints the current time
{
	cout << get_current_time() << endl;
}

