#include<iostream>
#include"people.h"
#include"room.h"
#include<string>
#include<map>
#include<time.h>
#include <stdlib.h> 
#include <crtdbg.h>
#include"support.h"
#include"Hospital.h"
#include<fstream>


#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

using namespace std;


int main()
{
	{
		int coin;
		srand(time(NULL));
		Hospital h("Ramm");
		coin=h.ask_for_previous_data();
		if (coin == 1)
		{
			h.recover_data();
		}
		else 
		{
			h.launch_simulation();
		}
		support b;
		cout << b.get_current_time();
		cout << endl;
	}
	cout << " Leaks : " << _CrtDumpMemoryLeaks() << endl; //checking memory leaks 
	cout << "Done" << endl;
}