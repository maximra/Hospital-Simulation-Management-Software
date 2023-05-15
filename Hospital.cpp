#include "Hospital.h"



using namespace std;
Hospital::Hospital(const std::string& hospital_name) //Constructor
{
	curr_num_of_patients = 0;
	curr_employees = 0;
	m_hospital_name = hospital_name; 
	support construct_s;
    current_date=construct_s.start_simulatiom_time(); //Starting simulation time
	cout << current_date << endl;
}

Hospital::~Hospital() //All dynamic memory that was allocated was already deleted at this point or there was use of containers that took care of it
{
	
}

void Hospital::print_all_doctors() const //Print all doctors in the hospital.
{
	for (int i = 0; i < MAX_DOCTORS; i++)
	{
		cout << "Doctor:" << "  " << i << "  " << list_of_doctors[i]->get_id_num() << "  " << list_of_doctors[i]->get_bday() << "  " << list_of_doctors[i]->get_gender() << "  " << list_of_doctors[i]->get_fname() << "  " << list_of_doctors[i]->get_lname() << endl;
	}
}

void Hospital::print_all_nurses() const //Print all nurses in the hospital.
{
	for (int i = 0; i < MAX_NURSES; i++)
	{
		cout << "Nurse:" << "  " << i << "  " << list_of_nurses[i]->get_id_num() << "  " << list_of_nurses[i]->get_bday() << "  " << list_of_nurses[i]->get_gender() << "  " << list_of_nurses[i]->get_fname() << "  " << list_of_nurses[i]->get_lname() << endl;
	}
}

void Hospital::print_all_patients() const //Print all current patients in the hosptial.
{
	for (auto it = list_of_patients.cbegin(); it != list_of_patients.cend(); ++it)
	{
		cout<<"Patient  ";
		it->second << it->second;
		cout << endl;

	}
	cout << "There are currently " << curr_num_of_patients << " patients in the hospital" << endl;
}

void Hospital::print_all_released_patients() const //Print all patients that were discharged from the hospital.
{
	cout <<"Amount of patiened that were discharged from the hospital:  "<< patients_that_left.size() << endl;
	for (int i = 0; i < patients_that_left.size();i++)
	{
		cout << patients_that_left[i]->get_end_admission_date() << " " << patients_that_left[i]->get_id_num() << "  " << patients_that_left[i]->get_bday() << "  " << patients_that_left[i]->get_fname() << "  " <<
			patients_that_left[i]->get_lname() << endl;
	}
}

void Hospital::print_all_patients_that_passed_away() const //Print all patients that passed away in the hospital.
{
	cout << "Amount of patiened that passed away in the hospital:  " << patients_that_passed_away.size() << endl;
	for (int i = 0; i < patients_that_passed_away.size(); i++)
	{
		cout << patients_that_passed_away[i]->get_end_admission_date() << " " << patients_that_passed_away[i]->get_id_num() << "  " << patients_that_passed_away[i]->get_bday() << "  " << patients_that_passed_away[i]->get_fname() << "  " <<
			patients_that_passed_away[i]->get_lname() << endl;
	}
}



std::string Hospital::get_hostital_name() const //Return the hospital name
{
	return m_hospital_name;
}



int Hospital::check_room() const //looks for the first room that is not full
{
	for (int i = 0; i < NUM_OF_ROOMS; i++)
	{
		if (list_of_rooms[i]->check_if_full() == 0)
			return i;
	}
	return -1;
}

void Hospital::hospital_insert_patient_to_room(const std::string& id, const int& room_number) //this function inserts a patient to a pecific rooom
{
	list_of_rooms[room_number]->insert_patient(id);
	curr_num_of_patients++;
}

void Hospital::launch_simulation() //Launches the main simulation
{
	update_nurse_and_doctor_salaries(1);
	update_nurse_and_doctor_salaries(0);
	cout << "Press any key to continue" << endl;
	cout << _getch();
	system("CLS");
	clear_all_files();
	support construct_s;
     for (int i = 0; i < MAX_DOCTORS; i++)   // Generating array of doctors (via vector)
     {

	   construct_s.generate_gender_and_name();
	   doctor cur_doc(construct_s.insert_random_id(), construct_s.insert_random_bday(), construct_s.insert_random_gender(), construct_s.insert_random_first_name(), construct_s.insert_random_last_name());
	   list_of_doctors.push_back(make_unique<doctor>(cur_doc));

     }

     for (int i = 0; i < MAX_NURSES; i++)  //Generating array of nurses (via vector)
     {
	    construct_s.generate_gender_and_name();
	    nurses cur_nurse(construct_s.insert_random_id(), construct_s.insert_random_bday(), construct_s.insert_random_gender(), construct_s.insert_random_first_name(), construct_s.insert_random_last_name());
	    list_of_nurses.push_back(make_unique<nurses>(cur_nurse));
     }
	 save_all_doctor_and_nurse_data();
	for (int i = 0; i < NUM_OF_ROOMS; i++) //Generating array of room (via vector)
	{

		list_of_rooms.push_back(make_unique<room>(i));
	}
	simulation_limit = -1;
	hospital_profits = 0;
	get_user_input_for_simulation_length(); //Declaring simulation duration
	support time_mover;
	fstream myfile0;    
	myfile0.open("File_patients_accepted_by_day.csv", ios::app);
	myfile0 << "ID," << "bday," << "gender,"<<"fname,"<<"lname,"<<"room,"<<"status,"<<"time,"<<"date," << endl;
	myfile0.close();
	for (int simulations=0; simulations < simulation_limit; simulations++) //Running the simulation itself
	{
		myfile0.open("File_patients_accepted_by_day.csv", ios::app);
		myfile0 << "Day: " << simulations << endl;
		int coin = rand() % 20 + 10;  //Decides the amount of patients that came to the hospital in a specific day.
		for (int i = 0; i < coin; i++) //Generating patients for a specific day.
		{
			if (curr_num_of_patients == MAX_PATIENTS) 
			{
				cout << "Hospital is full" << endl;
				break;
			}
			insert_patient_to_hospital();
		}
		myfile0 << "" << endl;
		myfile0.close();
		cout << simulations << endl;

		insert_employees_to_room();
		save_all_active_rooms(simulations);
		update_all_patient_status();
		perform_action_on_all_patients();
		calc_daily_profits(simulations, current_date);
		remove_employees_from_rooms();
		current_date=time_mover.move_one_day_forward();   //Move one day forward
	}
	save_all_current_patients(); 
	save_all_released_patients();
	save_all_patients_that_passed_away();
	fstream myfile4;
	myfile4.open("File_finances.csv", ios::app);
	myfile4 << endl;
	myfile4 << "Total, Profits, are:," << get_total_profits();
	myfile4.close();
	cout <<"The total profits are:   "<< get_total_profits() << endl;
	myfile4.open("File_patients_accepted_by_day.csv", ios::app);
	myfile4<< "Day: " << simulation_limit<< endl;
	system("CLS");
	main_user_menu();  //Go to main user menu

	
}

void Hospital::remove_patient_from_hospital(const int& num, const std::string& id) //Remove patient from hospital.
{
	list_of_rooms[num]->remove_patient(id);
}

void Hospital::operator<<(const Hospital& a) const  //Prints the hospital name.
{
	cout << get_hostital_name() << endl;
}

void Hospital::update_all_patient_status() //Updates the status of all patients
{
	for (auto it = list_of_patients.cbegin(); it != list_of_patients.cend(); ++it)
	{
		itr = list_of_patients.find(it->first);
		itr->second.update_status();
	}
}

void Hospital::perform_action_on_all_patients()  //Decides whether or not the patient is staying  in the hospital (alternatives that the patient was discharged or the patient passed away)
{
	string a="-1";
	bool key=false;
	for (auto it = list_of_patients.cbegin(); it != list_of_patients.cend(); ++it)
	{
		if (key == true)
		{
			list_of_patients.erase(a);
			key = false;
		}
		if (it->second.get_status() > 90 || it->second.get_status() <= 0) //In case the patient dies or gets gets discharged    
		{
			itr = list_of_patients.find(it->first);
			itr->second.insert_end_admission_date(current_date);
			key = true;
			a = it->first;
			remove_patient_from_hospital(it->second.get_room_num(), it->first); //Removing patient from hospital
			if (it->second.get_status() > 90)
			{
				patients_that_left.push_back(make_unique<patient>(it->second));
			}
			else
			{
				patients_that_passed_away.push_back(make_unique<patient>(it->second));
			}
			curr_num_of_patients--;
		}
	}
	if (key == true)
	{
		list_of_patients.erase(a);
	}
}

void Hospital::insert_patient_to_hospital() //Inserting patient to hospital
{
	support construct_s;
	int emp_room;
	construct_s.generate_gender_and_name();
	patient cur_patient(construct_s.insert_random_id(), construct_s.insert_random_bday(), construct_s.insert_random_gender(), construct_s.insert_random_first_name(),construct_s.insert_random_last_name(),
		construct_s.insert_random_value(), construct_s.insert_random_admission_time(),current_date, "1");
	emp_room = check_room();
	if (emp_room == -1) //In case for some reason we inserted a patient when the hospital was already full.
	{
		cout << "Fatal error" << endl;
		exit(0);
	}
	cur_patient.set_room(emp_room);  //Set a room for the patient
	list_of_patients.insert({ cur_patient.get_id_num(),cur_patient });
	hospital_insert_patient_to_room(cur_patient.get_id_num(), emp_room);
	fstream myfile1; 
	myfile1.open("File_patients_accepted_by_day.csv", ios::app);
	myfile1 <<cur_patient.get_id_num()<<"," << cur_patient.get_bday()<<","<<cur_patient.get_gender()<<"," << cur_patient.get_fname() << "," << cur_patient.get_lname() << "," << cur_patient.get_room_num()<<"," << cur_patient.get_status() << ","
		<<cur_patient.get_admission_time()<<"," <<current_date << endl;
	myfile1.close();
}

void Hospital::move_patient_room() //Moves patient a room
{
	string s_id;
	int input;
	cout << "Insert ID of the patient that you wish to move" << endl;
	map<string, patient>::iterator it;
	cin >> s_id;
	it = list_of_patients.find(s_id);
	if (it == list_of_patients.end())
	{
		cout << "No such patient in the hospital" << endl;
		return;
	}
	
		patient cur_patient(it->second);
		int cur_room=it->second.get_room_num();
		cout << "Insert the room number you wish to move the patient to (0-499)." << endl;
		while (true)
		{
			while (!(cin >> input)) //In case the user inserted a char/string
			{
				clear_buffer();
			}
			if (0 <= input && input <= 499)
			{
				break;
			}
			cout << "Input out of range, Try again" << endl;
		}

		if (list_of_rooms[input]->check_if_full() == true)
		{
			cout << "Specific room is full" << endl;
			return;
		}
		list_of_patients.erase(s_id);
		remove_patient_from_hospital(cur_room,s_id);
		cur_patient.set_room(input);
		list_of_patients.insert({ cur_patient.get_id_num(),cur_patient });
		hospital_insert_patient_to_room(cur_patient.get_id_num(), input);
		curr_num_of_patients--;

		fstream myfile9;
		myfile9.open("File_current_patients.csv", ofstream::out | ofstream::trunc);
		myfile9.close();
		save_all_current_patients();
}

void Hospital::insert_employees_to_room() //Inserts an employee to a room
{
	rooms_data = "";
	int j = 0;
	for (int i = 0; i < NUM_OF_ROOMS; i++)
	{
		if (list_of_rooms[i]->get_current_amount_of_patients() != 0)
		{
			rooms_data.append(to_string(i));
			rooms_data.append(",");
			try {
				array_of_current_employees[curr_employees] = new doctor(*list_of_doctors[j]);
			}
			catch (bad_alloc& exception)  //In case of a memory allocation failure
			{
				cout << "Memory allocation failure" << endl;
				exit(0);
			}
			list_of_rooms[i]->insert_doctor_to_room(j);
			curr_employees++;
			try {
				array_of_current_employees[curr_employees] = new nurses(*list_of_nurses[j]);
			}
			catch (bad_alloc& exeption)  //In case of a memory allocation failure
			{
				cout << "Memory allocation failure" << endl;
				exit(0);
			}
			list_of_rooms[i]->insert_nurse_to_room(j);
			curr_employees++;
			j++;
		}
	}

}

void Hospital::remove_employees_from_rooms() //Removes all employees from all rooms
{
	for (int i = 0; i < curr_employees; i++)
	{
		delete array_of_current_employees[i];
	}
	curr_employees = 0;
}



int Hospital::daily_bill_from_current_employees() const // Get the daily bill from all employees that worked in that specific day, polymorphism  function.
{
	int cost=0;
	for (int i = 0; i < curr_employees; i++)
	{
		cost+=array_of_current_employees[i]->bill();
	}
	return cost;
}

void Hospital::save_all_current_patients() const //this function is responsible to save all current patients in the hospital in an CSV file
{
	fstream myfile2;
	myfile2.open("File_current_patients.csv", ios::app);
	for (auto it = list_of_patients.cbegin(); it != list_of_patients.cend(); ++it)
	{
		myfile2 << it->first << ","<<it->second.get_bday()<<","<<it->second.get_gender() << "," << it->second.get_fname() << "," << it->second.get_lname() << "," << it->second.get_room_num() << "," 
		<< it->second.get_status()<<","<< it->second.get_admission_time() << ","<<it->second.get_admission_date() << endl;
	}
	myfile2.close();
}

void Hospital::pull_up_certain_day_patients(const int& day) const //Pulls up patients that were accepted to the hospital in a certain day using the CSV file
{


	ifstream inFile("File_patients_accepted_by_day.csv");
	vector<unique_ptr<patient>> chosen_day_patients; 
	string converter = to_string(day);
	string line;
	string s_id, s_bday, s_gender, s_fname, s_lname, s_status, s_amin_time, s_room, s_date;
	int value=-1;
	if (inFile.is_open())
	{
		//std::string line;
		while (line != "Day: "+converter)
		{
			getline(inFile, line);
		}
		cout << line << endl;
		cout << endl;
		while (getline(inFile, line))
		{
			if (line == "")
			{
				break;
			}
			stringstream ss(line);

			getline(ss, s_id, ',');
			getline(ss, s_bday, ',');
			getline(ss, s_gender, ','); 
			getline(ss, s_fname, ','); 
			getline(ss, s_lname, ','); 
			getline(ss, s_room, ',');    
			getline(ss, s_status, ','); 
			getline(ss, s_amin_time, ','); 
			getline(ss, s_date, ','); 
			stringstream converter2(s_status);
			converter2 >> value;
			stringstream converter3(s_room);
			patient a(s_id, s_bday, s_gender, s_fname, s_lname, value, s_amin_time,current_date, "-1");
			converter3 >> value;
			a.set_room(value);
			chosen_day_patients.push_back(make_unique<patient>(a));
			cout << endl;
			cout << endl;

		}
		cout << "Day " << converter << "  ," << s_date << endl;
		for (int i = 0; i < chosen_day_patients.size(); i++)
		{
			cout << chosen_day_patients[i]->get_id_num() << "  " << chosen_day_patients[i]->get_bday() <<"  "<<chosen_day_patients[i]->get_gender()<<"  "<<chosen_day_patients[i]->get_fname()<<"  "
				<<chosen_day_patients[i]->get_lname()<<"  "<<chosen_day_patients[i]->get_status()<<"  "<<chosen_day_patients[i]->get_admission_time()<<"  "<< chosen_day_patients[i]->get_room_num() << endl;
		}
	}
	else //In case we failed to open the file
	{
		cout << "Error, cant open file" << endl;
	}
}

void Hospital::save_all_released_patients() const //Saving all patients that were discharged from the hospital->send the data to an CSV file
{
	cout << "Saving all patients that left the hospital" << endl;
	fstream file5;
	file5.open("File_patients_that_left.csv", ios::app);
	for (int i = 0; i < patients_that_left.size(); i++)
	{
		file5 << patients_that_left[i]->get_id_num() << "," << patients_that_left[i]->get_bday() << "," << patients_that_left[i]->get_gender() << "," << patients_that_left[i]->get_fname() << "," << patients_that_left[i]->get_lname()
		<< "," <<patients_that_left[i]->get_status()<<","<<patients_that_left[i]->get_room_num()<<","<< patients_that_left[i]->get_admission_time() << "," << patients_that_left[i]->get_admission_date() << "," << patients_that_left[i]->get_end_admission_date() << endl;
	}
	file5.close();
}

void Hospital::save_all_patients_that_passed_away() const //Saving all patients that passed away in the hospital->send the data to an CSV file
{
	cout << "Saving all patients that passed away" << endl;
	fstream file6;
	file6.open("File_patients_that_passed_away.csv", ios::app);
	for (int i = 0; i < patients_that_passed_away.size(); i++)
	{
		file6 << patients_that_passed_away[i]->get_id_num() << "," << patients_that_passed_away[i]->get_bday() << "," << patients_that_passed_away[i]->get_gender() << "," << patients_that_passed_away[i]->get_fname()
		<< "," << patients_that_passed_away[i]->get_lname()<<"," << 0 << ","<<patients_that_passed_away[i]->get_room_num()<<","<<
		patients_that_passed_away[i]->get_admission_time()<<","<<patients_that_passed_away[i]->get_admission_date() << "," << patients_that_passed_away[i]->get_end_admission_date() << endl;
	}
	file6.close();
}

void Hospital::pull_up_certain_day_finances(int chosen_day) const //Pulls up certain day finances using an CSV file
{
	ifstream inFile2("File_finances.csv");
	string line2;
	string s_day, s_day_num, s_date, s_profits, s_loses, s_sum;
	if (inFile2.is_open())
	{
		for (int i = 0; i < chosen_day + 1; i++)
		{
			getline(inFile2, line2);
		}
		stringstream ss(line2);
		cout << endl;
		getline(ss, s_day, ',');
		cout << s_day;
		getline(ss, s_day_num, ',');
		cout << "  " << s_day_num;
		getline(ss, s_date, ',');
		cout << "  " << s_date;
		getline(ss, s_profits,',');
		cout << "  Profits:  " << s_profits;
		getline(ss, s_loses, ',');
		cout << "  Loses:  " << s_loses;
		getline(ss, s_sum, ',');
		cout << "  " << "  Sum:  " << s_sum;
		return;

	}
	else
	{
		cout << "Error, cant open file";
	}
}

void Hospital::upload_doctor_and_nurse_data() //uploads all doctors and nurses that were generated for the simulation using a CSV file
{
	string s_id, s_bday, s_gender, s_fname, s_lname;
	ifstream inFile3("File_doctors.csv");
	string line3;
	if (inFile3.is_open())
	{

		while (getline(inFile3, line3))
		{
			stringstream ss(line3);
			getline(ss, s_id, ',');
			getline(ss, s_bday, ',');
			getline(ss, s_gender, ',');
			getline(ss, s_fname, ',');
			getline(ss, s_lname, ',');
			doctor cur_doc(s_id, s_bday, s_gender, s_fname, s_lname);
			list_of_doctors.push_back(make_unique<doctor>(cur_doc));

		}
	}
	else
	{
		cout << "Failed to open file , can't upload doctor data" << endl;
		exit(0);
	}
	inFile3.close();
	
	ifstream inFile4("File_nurses.csv");
	string line4;
	if (inFile4.is_open())  //We managed to open the file
	{
		while (getline(inFile4, line4))
		{
			stringstream ss(line4);
			getline(ss, s_id, ',');
			getline(ss, s_bday, ',');
			getline(ss, s_gender, ',');
			getline(ss, s_fname, ',');
			getline(ss, s_lname, ',');
			nurses cur_nurse(s_id, s_bday, s_gender, s_fname, s_lname);
			list_of_nurses.push_back(make_unique<nurses>(cur_nurse));

		}
	}
	else //We failed to open file
	{
		cout << "Failed to open file , can't upload nurse data" << endl;
		exit(0);
	}
	inFile4.close();
}

void Hospital::save_all_active_rooms(const int& day) const //saving all active rooms and uploading the data to a CSV file
{
	fstream file8;
	file8.open("File_active_rooms.csv", ios::app);
	file8 << "day " << day << endl;
	file8 << rooms_data << "/" << endl;
	file8.close();
	
}

void Hospital::pull_up_certain_day_room(const int& day) const //Uploads the data of the rooms that were active for that specific day
{
	ifstream inFile4("File_active_rooms.csv");
	string line4;
	string converter = to_string(day);
	int counter = 0;
	if (inFile4.is_open()) //We managed to open the file
	{
		while (line4 != "day " + converter)
		{
			getline(inFile4, line4);
		}
		getline(inFile4, line4);
		stringstream ss(line4);
		while (true)
		{
			getline(ss, converter, ',');
			if (converter == "/")
			{
				break;
			}
			cout << "Room  " << converter << "  Doctor:  " << list_of_doctors[counter]->get_id_num() << "  Nurse:  " << list_of_nurses[counter]->get_id_num();
			cout << endl;
			counter++;
		}
	}
	else //In case we failed to open the file
	{
		cout << "Failed to open file" << endl;
	}

	
}

void Hospital::pull_up_patients_with_specific_status()  //This function returns patients between two statuses (including edge values too).
{
	cout << "Insert two values, after each value press enter to continue" << endl;
	cout << "The first value you insert is the lower end value, then the higher end value" << endl;
	int low;
	int high;
	int counter = 0;
	while (true)
	{
		while (!(cin >> low))
		{
			clear_buffer(); //In case the user inserts a char/string
		}
		if (1 <= low && low <= 89)
		{
			break;
		}
		cout << "Input out of range" << endl;
	}
	while (true)
	{
		while (!(cin >> high))
		{
			clear_buffer();
		}
		if (1 <= high && high <= 89 && low<=high)
		{
			break;
		}
		cout << "Input out of range" << endl;
	}
	cout << "ID, Bday, Gender, Fname, Lname, Room, Status, Time, Date. " << endl;
	for (auto it = list_of_patients.cbegin(); it != list_of_patients.cend(); ++it)
	{
		if (low <= it->second.get_status() && it->second.get_status() <= high)
		{
			counter++;
			it->second << it->second;   //Uploading the data itself
			cout << endl;
		}
	}
	cout << "There are in total " << counter << "  patients that fit your criteria of status" << endl;
}

void Hospital::get_capacity() const //Returns the amount of free beds in the hospital, occupied beds in hospital, and the capacity in procentage.
{
	cout << "There are currently " << MAX_PATIENTS - curr_num_of_patients << " free beds in the hospital" << endl;
	cout << "There are currently " << curr_num_of_patients << " occupied beds in the hospital" << endl;
	cout << "The hospital is currently at: " << (((double)curr_num_of_patients)/(MAX_PATIENTS))*100 << "%  capacity" << endl;
}

void Hospital::clear_all_files() const //Whenever you choose to launch a new simulation, this functions cleans all the CSV files.
{

	ofstream ofs;
	ofs.open("File_patients_accepted_by_day.csv", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("File_current_patients.csv", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("File_active_rooms.csv", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("File_finances.csv", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("File_patients_that_left.csv", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("File_patients_that_passed_away.csv", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("File_doctors.csv", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("File_nurses.csv", ofstream::out | ofstream::trunc);
	ofs.close();
}

void Hospital::save_all_doctor_and_nurse_data() const //This function saves all the data of the doctors and nurses .
{
	fstream myfile5;
	myfile5.open("File_doctors.csv", ios::app);
	for (int i = 0; i < MAX_DOCTORS; i++)
	{
		myfile5 << list_of_doctors[i]->get_id_num() << "," << list_of_doctors[i]->get_bday() << "," << list_of_doctors[i]->get_gender() << "," << list_of_doctors[i]->get_fname() << ","
			<< list_of_doctors[i]->get_lname() << endl;

	}
	myfile5.close();
	fstream myfile6;
	myfile6.open("File_nurses.csv", ios::app);
	for (int i = 0; i < MAX_NURSES; i++)
	{
		myfile6 << list_of_nurses[i]->get_id_num() << "," << list_of_nurses[i]->get_bday() << "," << list_of_nurses[i]->get_gender() << "," << list_of_nurses[i]->get_fname() << ","
			<< list_of_nurses[i]->get_lname() << endl;

	}
	myfile6.close();
}

void Hospital::get_user_input_for_simulation_length()  //alllows the user to declare  his/her desired simulation length (1-1000 days)
{
	cout << "How many simulation days do you want? (insert an intiger value between 1 and 1000)" << endl;
	while (true)
	{

		while (!(cin >> simulation_limit)) //in case the user inserts a char/string
		{
			clear_buffer();
		}
		if (simulation_limit >= 1 && simulation_limit <= 1000)
		{
			return;
		}
		cout << "Input out of range, try again" << endl;
	}
}

void Hospital::main_user_menu() //Main user menu
{
	system("CLS");
	menu_key = false;
	while (true)
	{
		cout << "Main user menu" << endl;
		cout << endl;
		cout << "Press 1 to see hospital name" << endl;
		cout << endl;
		cout << "Press 2 to see current patients in the hospital " << endl;
		cout << "Press 3 to see which patients were discharged from the hospital" << endl;
		cout << "Press 4 to see which patients died in the hospital" << endl;
		cout << "Press 5 to see what patients were accepted in a specific day " << endl;
		cout << "Press 6 to print list of doctors" << endl;
		cout << "Press 7 to print list of nurses" << endl;
		cout << "Press 8 to see how many doctor and nurses are working in the hospital" << endl;
		cout << "Press 9 to see which rooms were active in a specific day, including the doctors and nurses that worked there" << endl;
		cout << endl;
		cout << "Press 10 to manually insert a patient to the hospital" << endl;
		cout << "Press 11 to move patient a room" << endl;
		cout << endl;
		cout << "Press 12 to get total hospital profits/loses" << endl;
		cout << "press 13 to see profits for a specific day" << endl;
		cout << "Press 14 to see current hospital capacity" << endl;
		cout << "Press 15 to see doctor and nurse salary" << endl;
		cout << endl;
		cout << "Press 16 to search for patient that is currently in the hospital by ID" << endl;
		cout << "Press 17 to search for patient by other criteria (in case you dont know the ID)" << endl;
		cout << "Press 18 to search for patients with a specific status(values between 1 and 89)" << endl;
		cout << endl;
		cout << "Press 19 to exit simulation" << endl;
		get_user_input_for_main_menu();
		cout << endl;
		cout << "Press any key to continue" << endl;
		cout << _getch();
		system("CLS");
		if (menu_key == true) //break statement from main menu
		{
			break;
		}
	}
	save_general_parameters(); //Saving essential simulation parameters
}

void Hospital::get_user_input_for_main_menu()  //User inputs for main menu.
{
	int input;
	while (true)
	{
		while (!(cin >> input)) //in case the user inserts a char/string
		{
			clear_buffer();
		}
		switch (input)
		{
		case 1:
		{
			cout << get_hostital_name() << endl;
			return;
		}
		case 2:
		{
			print_all_patients();
			return;
		}
		case 3:
		{
			print_all_released_patients();
			return;
		}
	
		case 4:
		{
			print_all_patients_that_passed_away();
			return;
		}
		case 5:
		{
			input = get_user_chosen_day(1);
			pull_up_certain_day_patients(input);
			return;
		}
		case 6:
		{
			print_all_doctors();
			cout << endl;
			return;
		}
		case 7:
		{
			print_all_nurses();
			cout << endl;
			return;
		}
		case 8:
		{
			cout << "Amount of doctors in the hospital:  " << list_of_doctors.size() << endl;
			cout << "Amount of nurses in the hospital:  " << list_of_nurses.size() << endl;
			return;
		}
		case 9:
		{
			input = get_user_chosen_day(0);
			pull_up_certain_day_room(input);
			return;
		}
		case 10:
		{
			manual_patient_insert();
			return;
		}
		case 11:
		{
			move_patient_room();
			return;
		}
		case 12:
		{
			cout << "Total hospital profits are:   ";
			cout << get_total_profits() << endl;
			return;
		}
		case 13:
		{
			input = get_user_chosen_day(0);
			pull_up_certain_day_finances(input);
			return;
		}
		case 14:
		{
			get_capacity();
			return;
		}
		case 15:
		{
			doctor a("", "", "", "", "");
			cout <<"The daily salary of a doctor is: "<< a.bill() << endl;
			nurses b("", "", "", "", "");
			cout <<"The daily salary of a nurse is: " << b.bill() << endl;
			return;
		}
		case 16:
		{
			search_for_person_by_id();
			return;
		}
		case 17:
		{
			advanced_patients_search();
			return;
		}
		case 18:
		{
			pull_up_patients_with_specific_status();
			return;
		}
		case 19:
		{
			cout << "left";
			menu_key = true;
			return;
		}
	
		
		default:
		{
			cout << "Out of range" << endl;
		}
		}

	}
}

int Hospital::get_user_chosen_day(int num) //User selected day for specific operation.
{
	int chosen_day;
	cout << "Choose a day between day 0 and day " << simulation_limit - 1 +num<< endl;
	while (true)
	{
		while (!(cin >> chosen_day)) //in case the user inserts a char/string
		{
			clear_buffer();
		}
		if (0 <= chosen_day && chosen_day < simulation_limit+num)
		{
			return chosen_day;
		}
		cout << "Input out of range,try again" << endl;
	}
}

void Hospital::search_for_person_by_id()  //Searches for a patient that is currently in the hospital using by id.
{
	cout << "Enter an ID num to find a patient that is currently in a hospital" << endl;
	string s_id;
	cin >> s_id;
	cout << endl;
	map<string, patient>::iterator it;
	it = list_of_patients.find(s_id);
	if (it == list_of_patients.end())
	{
		cout << "No such patient in the hospital" << endl;
	}
	else
	{
		it->second << it->second;
	}
}

void Hospital::advanced_patients_search()   //searches patients by other criteria in case you dont know the id.
{
	system("CLS");
	bool key_gender = false;
	bool key_fname = false;
	bool key_lname = false;
	bool key_bday = false;
	string s_gender="0";
	string s_fname="0";
	string s_lname="0";
	string s_bday="0";
	cout << "The system will ask you questions about the patient." << endl;
	cout << "If you know the answer to that specific question write the answer " << endl;
	cout << "If you don't know the answer write 0 " << endl;
	
	//Questions here:

	cout << "Do you know the gender of the patient? (male or female)" << endl;
	cin >> s_gender;
	cout << "Do you know the name of the patient?" << endl;
	cin >> s_fname;
	cout << "Do you know the last name of the patient?" << endl;
	cin >> s_lname;
	cout << "Do you know the birthday of the patient?(insert the follwing format D/M/YYYY , don't add zeroes)." << endl;
	cin >>s_bday;
	int counter = 0;
	cout << "ID, Bday, Gender, Fname, Lname, Room, Status, Time, Date. " << endl;
	for (auto it = list_of_patients.cbegin(); it != list_of_patients.cend(); ++it)
	{

		if ((it->second.get_gender() == s_gender) || (s_gender == "0"))
		{
			if ((it->second.get_fname() == s_fname) || (s_fname == "0"))
			{
				if ((it->second.get_lname() == s_lname) || (s_lname == "0"))
				{
					if ((it->second.get_bday() == s_bday) || (s_bday == "0"))
					{
						counter++;
						it->second << it->second;
						cout << endl;
					}
				}
			}
		}
	}
	cout << "The system found  " << counter << "  patients in the hospital that fit your criteria." << endl;
}

void Hospital::manual_patient_insert()  //Manually insert a new patient to the hospital 
{
	system("CLS");
	if (curr_num_of_patients == MAX_PATIENTS)
	{
		cout << "No room left in the hospital" << endl;
		return;
	}
	cout << "The data will be inserted in the following order: ID--> Bday--> Gender--> First name --> Last name--> Patient status--> Patient admission time" << endl;
	string s_id="0";
	string s_bday;
	int  i_gender;
	string s_gender;
	string s_fname;
	string s_lname;
	string s_time;
	int i_status;
	cout << "Insert ID,  number accepted length- 7 digits" << endl;
	while (true)
	{
		cin >> s_id;
		if (7 == s_id.length())
		{
			break;
		}
		cout << "Invalid input, try again" << endl;
	}
	cout << "Insert Birth day , Birthday format D/M/YYYY"<<endl;
	cin >> s_bday;
	cout << "Insert gender, Press 0 for male and 1 for female" << endl;
	while (true)
	{
		while (!(cin >> i_gender))
		{
			clear_buffer();
		}
		if (i_gender == 0)
		{
			s_gender = "male";
			break;
		}
		if (i_gender == 1)
		{
			s_gender = "female";
			break;
		}
		cout << "Out of range" << endl;
	}
	cout << "Insert first name:" << endl;
	cin >> s_fname;
	cout << "Insert last name:" << endl;
	cin >> s_lname;
	cout << "Insert patient status(value between 1 and 89)" << endl;
	while (true)
	{
		while (!(cin >> i_status))
		{
			clear_buffer();
		}
		if (1 <= i_status && i_status <= 89)
		{
			break;
		}
		cout << "Out of range" << endl;
	}
	cout << "Insert arrival time to the hospital, use 00:00 format." << endl;
	cin >> s_time;
	int emp_room;
	patient cur_patient(s_id, s_bday, s_gender, s_fname, s_lname,i_status, s_time, current_date, "1");
	emp_room = check_room();
	if (emp_room == -1)
	{
		cout << "Fatal error" << endl;
		exit(0);
	}
	cur_patient.set_room(emp_room);
	list_of_patients.insert({ cur_patient.get_id_num(),cur_patient });
	hospital_insert_patient_to_room(cur_patient.get_id_num(), emp_room);
	fstream myfile8;
	myfile8.open("File_patients_accepted_by_day.csv", ios::app);
	myfile8 << cur_patient.get_id_num() << "," << cur_patient.get_bday() << "," << cur_patient.get_gender() << "," << cur_patient.get_fname() << "," << cur_patient.get_lname() << "," << cur_patient.get_room_num() << "," << cur_patient.get_status() << ","
		<< cur_patient.get_admission_time() << "," << current_date << endl;
	myfile8.close();
	myfile8.open("File_current_patients.csv", ofstream::out | ofstream::trunc);
	myfile8.close();
	save_all_current_patients();
	
}

void Hospital::update_nurse_and_doctor_salaries(const bool& a) //This function updates the doctor and nurse salaries
{

	int input;
	if (a == 1)
	{
		cout << "The current daily salary for a doctor is 100 NIS, do you wish to update the value?" << endl;
	}
	else
	{
		cout << "The current daily salary for a nurse is 50 NIS, do you wish to update the value?" << endl;
	}
	cout << "Press 1 if yes, press 0 if no" << endl;
	while (true)
	{
		while (!(cin >> input))
		{
			clear_buffer(); //In case the user inserts a char/string
		}
		if (input == 0)
		{
			cout << "You chose to keep the default salary" << endl;
			return;
		}
		else if (input == 1)
		{
			cout << "Enter the new value (between 10 and 200)" << endl;
			while (true)
			{
				while (!(cin >> input))
				{
					clear_buffer();
				}
				if (10 <= input && input <= 200)
				{
					cout << "New value accepted" << endl;
					break;
				}
				else
				{
					cout << "Out of range, Try again" << endl;
				}

			}
			break;
		}
		else
		{
			cout << "Out of range, Try again." << endl;
		}
	}
	if (a == 1)
	{
		doctor cur_doc("1", "1", "1", "1", "1");
		cout << "New doctor salary is : " << input << endl;
		cur_doc.update_doctor_salary(input);  //Updating the doctor's salary
	}
	else
	{
		nurses cur_nurse("1", "1", "1", "1", "1");
		cout << "New Nurse salary is : " << input << endl;
		cur_nurse.update_nurse_salary(input);  //Updating the nurse's salary
	}

}

void Hospital::calc_daily_profits(const int& day,const std::string& date)  //Calculating daily profits
{
	int loses=daily_bill_from_current_employees();
	int profits=curr_num_of_patients*50;
	int sum = profits - loses;
	hospital_profits += sum;
	fstream myfile3; 
	myfile3.open("File_finances.csv", ios::app);
	myfile3 <<"Day," <<day<<"," <<date<<","<<profits << "," << loses << "," << sum << endl;
	myfile3.close();
}

int Hospital::get_total_profits() const //Returns total hospital profits
{
	return hospital_profits;
}

int Hospital::ask_for_previous_data() //Checks whether or not the user wants to upload the data from the previous simulation
{
	cout << endl;
	cout << "If you wish to see the data from the previous simulation press 1" << endl;
	cout<<"If you wish to launch a new simulation press 0 " << endl;
	int input;
	while (true)
	{
		while (!(cin >> input))
		{
			clear_buffer();
		}
		if (input == 1)
		{
			cout << "You chose to upload the previous data" << endl;
			
			return 1;
		}
		else if(input==0)
		{
			cout << "Continuing to simulation" << endl;
			
			return 0;
		}
		cout << "Input out of range,Try again" << endl;
	}
}

void Hospital::save_general_parameters() const //Saving all general data in a doc file
{
	doctor cur_doc("", "", "", "", "");
	nurses cur_nur("", "", "", "", "");
	fstream myfile_recovery;
	myfile_recovery.open("File_parameters.doc",ios::out);
	myfile_recovery << simulation_limit << endl;
	myfile_recovery << hospital_profits << endl;
	myfile_recovery << curr_num_of_patients << endl;
	myfile_recovery << cur_doc.bill() << endl;
	myfile_recovery << cur_nur.bill() << endl;
	myfile_recovery.close();
}

void Hospital::get_general_parameters()  //Uploading all general data from the doc file
{
	doctor a("", "", "", "", "");
	nurses b("", "", "", "", "");
	ifstream myfile_recovery2("File_parameters.doc");
	string s_simulation_limit;
	string s_hospital_profits;
	string s_curr_number_of_patients;
	string s_doctor_bill;
	string s_nurse_bill;
	string line;
	int value = 1;
	if (myfile_recovery2.is_open())
	{
		getline(myfile_recovery2, line);
		s_simulation_limit = line;
		getline(myfile_recovery2, line);
		s_hospital_profits = line;
		getline(myfile_recovery2, line);
		s_curr_number_of_patients = line;
		getline(myfile_recovery2, line);
		s_doctor_bill = line;
		getline(myfile_recovery2, line);
		s_nurse_bill = line;
		myfile_recovery2.close();
	}
	else
	{
		cout << "Failed to open file" << endl;
		exit(0);
	}
	stringstream converter2(s_simulation_limit);
	converter2 >> value;
	simulation_limit = value;
	stringstream converter3(s_hospital_profits);
	converter3 >> value;
	hospital_profits = value;
	stringstream converter4(s_curr_number_of_patients);
     converter4 >> value;
	curr_num_of_patients = value;
	stringstream converter5(s_doctor_bill);
	converter5 >> value;
	a.update_doctor_salary(value);
	stringstream converter6(s_nurse_bill);
	converter6 >> value;
	b.update_nurse_salary(value);
}

void Hospital::recover_data()  // This function is responsible to recover all data from the previous simulation
{
	for (int i = 0; i < NUM_OF_ROOMS; i++)
	{
		list_of_rooms.push_back(make_unique<room>(i));
	}
	upload_doctor_and_nurse_data();
	upload_all_patient_data();
	get_general_parameters();
	main_user_menu();
}

void Hospital::upload_all_patient_data() //This functions uploads all patient data from previous launch.
{
	string s_id, s_bday, s_gender, s_fname, s_lname, s_time, s_admission_date, s_end_date, s_room, s_status;
	ifstream inFile3("File_patients_that_left.csv");
	string line3;
	int value=-1;
	if (inFile3.is_open())
	{

		while (getline(inFile3, line3))
		{
			stringstream ss(line3);
			getline(ss, s_id, ',');
			getline(ss, s_bday, ',');
			getline(ss, s_gender, ',');
			getline(ss, s_fname, ',');
			getline(ss, s_lname, ',');
			getline(ss, s_status, ',');
			getline(ss, s_room, ',');
			getline(ss, s_time, ',');
			getline(ss, s_admission_date, ',');
			getline(ss, s_end_date, ',');
			stringstream converter2(s_status);
			converter2 >> value;
			stringstream converter3(s_room);
			patient a(s_id, s_bday, s_gender, s_fname, s_lname, value, s_time, s_admission_date, s_end_date);
			converter3 >> value;
			a.set_room(value);
			patients_that_left.push_back(make_unique<patient>(a));
		}
	}
	else
	{
		cout << "Failed to open file" << endl;
		exit(0);
	}
	inFile3.close();

	ifstream inFile4("File_patients_that_passed_away.csv");
	string line4;
	if (inFile4.is_open())
	{
		while (getline(inFile4, line4))
		{
			stringstream ss2(line4);
			getline(ss2, s_id, ',');
			getline(ss2, s_bday, ',');
			getline(ss2, s_gender, ',');
			getline(ss2, s_fname, ',');
			getline(ss2, s_lname, ',');
			getline(ss2, s_status, ',');
			getline(ss2, s_room, ',');
			getline(ss2, s_time, ',');
			getline(ss2, s_admission_date, ',');
			getline(ss2, s_end_date, ',');
			stringstream converter4(s_status);
			converter4 >> value;
			stringstream converter5(s_room);
			patient b(s_id, s_bday, s_gender, s_fname, s_lname, value, s_time, s_admission_date,s_end_date);
			converter5 >> value;
			b.set_room(value);
			patients_that_passed_away.push_back(make_unique<patient>(b));
		}
	}
	else
	{
		cout << "Failed to open file" << endl;
		exit(0);
	}
	inFile4.close();
	ifstream inFile5("File_current_patients.csv");
	string line5;
	if (inFile5.is_open())
	{

		while (getline(inFile5, line5))
		{
			stringstream ss3(line5);
			getline(ss3, s_id, ',');
			getline(ss3, s_bday, ',');
			getline(ss3, s_gender, ',');
			getline(ss3, s_fname, ',');
			getline(ss3, s_lname, ',');
			getline(ss3, s_room, ',');
			getline(ss3, s_status, ',');
			getline(ss3, s_time, ',');
			getline(ss3, s_admission_date, ',');
			stringstream converter6(s_status);
			converter6 >> value;
			patient c(s_id, s_bday, s_gender, s_fname, s_lname, value, s_time, s_admission_date, "-1");
			stringstream converter7(s_room);
			converter7 >> value;
			c.set_room(value);
			list_of_patients.insert({ c.get_id_num(),c });
			hospital_insert_patient_to_room(c.get_id_num(), c.get_room_num());

		}
	}
	else
	{
		cout << "Failed to open file" << endl;
		exit(0);
	}
	inFile5.close();
}



void Hospital:: clear_buffer() //in case the user inserts a string or char
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Invalid input .Try again" << endl;
}

