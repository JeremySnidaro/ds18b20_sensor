#include <iostream>
#include "ds18b20.h"
#include "unistd.h"
#include <glib.h> 
using namespace std;

int main()
{
	

	Ds18b20 *sensor = new Ds18b20("test");
	float temp; 
	for (int i=0; i<10; i++)
	{
	    temp = sensor->read_temp();
		cout << temp << endl;
		sleep(1);
	}
	return 0;
}
