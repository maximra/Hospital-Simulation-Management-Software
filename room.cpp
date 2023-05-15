#include"room.h"

using namespace std;





room::room(const int& room_num) //Constructor
{
	m_room_num = room_num;
	curr_amount_of_patients = 0;
	for (int i = 0; i < num_of_patients; i++) //Allocate memory.
	{
		try {
			m_array_of_patients[i] = new std::string("0");
		}
		catch (bad_alloc& exception) //In case the memory allocation failed.
		{
			cout << "Memory allocation failure" << endl;
			exit(0);
		}
	}
	m_room_doctor_index =-1;
	m_room_nurse_index = -1;

}

room::~room() //Activating destructor
{
	for (int i = 0; i < num_of_patients; i++)  //Freeing memory.
	{
		delete m_array_of_patients[i];
	}

}

void room::insert_patient(const std::string& patient_id)
{
	if (curr_amount_of_patients >= num_of_patients) //In case we ran out of space.
	{
		cout << "Out of space " << endl;
		return;
	}
	*m_array_of_patients[curr_amount_of_patients] = patient_id;  
	curr_amount_of_patients++;                                   //Amount of patients in the room grew.
}

void room::remove_patient(const std::string& patient_id)
{
	for (int i = 0; i < curr_amount_of_patients; i++)
	{
		if (patient_id == *m_array_of_patients[i])
		{
			curr_amount_of_patients--;              //Amount of patients decreased in the room.
			while (true)
			{
				if (i == num_of_patients - 1)
				{
					break;
				}
				*m_array_of_patients[i] = *m_array_of_patients[i + 1];
				i++;
			}

			//cout << "Patient was removed" << endl;
			return;
		}
	}
	cout << "No such patient in the room" << endl;  //In case the patient does not exist in this room
	return;
}

bool room::check_if_full() const //Checks whether or not the room is full (1-full) ,(0-not full).
{
	if (curr_amount_of_patients >= num_of_patients)
		return true;
	else
		return false;
}

int room::get_current_amount_of_patients() const //Returns the amount of patients in the room.
{
	return curr_amount_of_patients;
}

void room::insert_doctor_to_room(const int& a)  //Insert the index of a doctor to the room.
{
	m_room_doctor_index = a;
}

void room::insert_nurse_to_room(const int& a) //Insert the index of a nurse to the room.
{
	m_room_nurse_index = a;
}

int room::get_doctor_in_room() const  //Returns the doctor index.
{
	return m_room_doctor_index;
}

int room::get_nurse_in_room() const //Returns the nurse index.
{
	return m_room_nurse_index;
}

void room::operator<<(const room& a) const //prints the ID's of the  patients in the room.
{
	cout << "ID of patients in room are:"<<endl;
	for (int i = 0; i < curr_amount_of_patients; i++)
	{
		cout <<"  " << *m_array_of_patients[i];
	}

}





