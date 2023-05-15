#ifndef _PEOPLE_H_
#define _PEOPLE_H_
#include<string>
#include<iostream>



 class person {
public:
	person(const std::string& id,const std::string& bday,const std::string& gender,const std::string& fname,const std::string& lname);
	~person();
	  std::string get_id_num() const; //Prints id number.
	  std::string get_gender() const; //Prints the gender.
	  std::string get_fname() const; //Prints the first name.
	  std::string get_lname() const; //Prints the last name.
	  std::string get_bday() const; //Print the bday.
	 virtual void operator<<(const person& a)const;
protected:
	std::string m_id; //  ID.
	std::string m_bday; //Birthday.
	std::string  m_gender; //Gender. 
	std::string m_fname; //First name.
	std::string m_lname; //Last name.
};

class patient : public person
{
public:
	patient(const std::string& id, const std::string& bday, const std::string& gender, const std::string& fname, const std::string& lname,const int& status,const std::string& admission_time,const std::string& admission_date ,const std::string& end_admission_date) : 
		person(id, bday, gender, fname, lname), m_status(status),m_admission_time(admission_time),m_admission_date(admission_date), m_end_admission_date(end_admission_date)
	{
		m_id = id;
		m_bday = bday;
		m_gender = gender;
		m_fname = fname;
		m_lname = lname;
		m_status = status;
		m_room_number = -1; //currently doesnt have a room
	}
	void set_room(const int& r); //sets the current room for the patient.
	int get_room_num() const; //Returns the room number of the patient.
	void update_status(); //Updates the health status of the patient.
	int get_status() const; //Returns the current status of the patient.
	std::string get_admission_time() const; //Returns admission time.
	std::string get_admission_date() const; //Returns admission date.
	void insert_end_admission_date(const std::string& a);//Insert time in which patient was released from hosptial.
	std::string get_end_admission_date() const; //Returns end admission date.
	void operator<<(const patient& a) const; //Prints the full patient data.
private:
	int m_status; //current medical condition from (0-100).
	std::string m_admission_time; //when the patient was admitted to the hospital.(time)
	std::string m_admission_date; //When the patient was admitted to the hospital. (date)
	std::string m_end_admission_date; //when the patient was discharged/passed away.
	int m_room_number; // In what room is the patient located in.
};

class employee : public person
{
public:
	employee(const std::string& id, const std::string& bday, const std::string& gender, const std::string& fname, const std::string& lname) :
		person(id, bday, gender, fname, lname) 
	{
		m_id = id;
		m_bday = bday;
		m_gender = gender;
		m_fname = fname;
		m_lname = lname;
		
	}
	virtual int bill() const = 0; //Returns the daily bill for using the employee.
protected:
};

class doctor : public employee
{
public:
	doctor(const std::string& id, const std::string& bday, const std::string& gender, const std::string& fname, const std::string& lname) :
		employee(id, bday, gender, fname, lname)
	{
		m_id = id;
		m_bday = bday;
		m_gender = gender;
		m_fname = fname;
		m_lname = lname;
	}
	int bill() const; //daily bill of a doctor
	static void update_doctor_salary(const int& doc_salary) //Update the salary to all doctors.
	{
		doctor_salary = doc_salary;
	}
private:
	static int doctor_salary; //Static int, it contains the doctor's salary.
};

class nurses : public employee
{
public:
	nurses(const std::string& id, const std::string& bday, const std::string& gender, const std::string& fname, const std::string& lname) :
		employee(id, bday, gender, fname, lname)
	{
		m_id = id;
		m_bday = bday;
		m_gender = gender;
		m_fname = fname;
		m_lname = lname;
	}
	int bill() const; //daily bill of a nurse
	static void update_nurse_salary(const int& nur_salary) //Update the salary to all nurses.
	{
		nurse_salary = nur_salary;
	}
private:
	static int nurse_salary; //Static int , it contains the nurse's salary.
};

#endif