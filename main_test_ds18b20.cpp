#include <iostream>
#include "ds18b20.h"
#include "unistd.h"
#include <stdlib.h> // for system
#include <glib.h> 
using namespace std;

const char* config_file = "./conf.txt";

int main()
{
	GKeyFile* gkf;
	gkf = g_key_file_new();
	
	// Loads the config file and tests that everything went OK .
    if (!g_key_file_load_from_file(gkf, config_file, G_KEY_FILE_NONE, NULL))
	{
        fprintf (stderr, "Could not read config file %s\n", config_file);
        return -1;
    }	

	// START stuff about the config file ......

	// we will check on the main app if many_sensor if on 0 or 1 for 1
	//just create one ds18b20 instance for more do a for loop and check the directory
	int many_sensor = g_key_file_get_integer(gkf, "Sensor", "many_sensor", NULL);
	cout << many_sensor << endl;

	// END stuff about the config file ......

	// we need to free before leaving
	g_key_file_free(gkf);
/*
	if (many_sensor == 0)
	{
		// this don't work but its the idea
		string file_sensor = system("ls /sys/bus/w1/devices/w1_bus_master1/ | grep '^28'") ;
	}
*/
/*	

	Ds18b20 *sensor = new Ds18b20("test");
	float temp; 
	for (int i=0; i<10; i++)
	{
	    temp = sensor->read_temp();
		cout << temp << endl;
		sleep(1);
	}

*/
	return 0;
}
// how to use glib
// https://github.com/joehakimrahme/Agros/wiki/Parsing-the-conf-file-with-GLib
