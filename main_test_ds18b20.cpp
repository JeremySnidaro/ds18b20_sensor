#include <iostream>
#include <glib.h>  // to read config file
#include <dirent.h> // to see file on directory
#include <vector>

#include <unistd.h> // to use sleep delete this after test

#include "ds18b20.h"

using namespace std;

const char* config_file = "./conf.txt";

vector<string> list_dir (const char *path)
{
	vector<string> files;

    struct dirent *entry;
    DIR *dir;
    dir = opendir (path);

    while ((entry = readdir (dir)) != NULL)
	{

		string file_name;
		file_name = entry->d_name;
		if ( file_name.find ("28-") != string::npos )
		{
			files.push_back(entry->d_name);
		}
		else
		{
			continue;
		}

    }

	closedir(dir);
	return files;

}

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
	int many_sensor = g_key_file_get_integer(gkf,
											 "Sensor",
											 "many_sensor",
											 NULL);
	cout << many_sensor << endl;
	// we need to free before leaving
	g_key_file_free(gkf);

	// END stuff about the config file ......


	string base_dir = "/sys/bus/w1/devices/";	
	vector<string> sensor_list;
	if (many_sensor == 0)
	{
		sensor_list = list_dir( "/sys/bus/w1/devices/w1_bus_master1/" );
		cout << sensor_list[0] << endl;
		// just create one ds18b20 instance
		// for more use for loop and check the directory
	    Ds18b20 *sensor = new Ds18b20( base_dir +
									   sensor_list[0] +
									   "/w1_slave" );
		float temp; 
		for (int i=0; i<10; i++)
		{
			temp = sensor->read_temp();
			cout << temp << endl;
			sleep(1);
		}
	}

	else if(many_sensor == 1)
	{
		
	}
	else
	{
		cerr << "Error please make sure many_sensor \
		variable on conf.txt is on 1 or 0" << endl;
	}
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
