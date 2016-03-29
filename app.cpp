#include <iostream>
#include <dirent.h> // to list dir
#include <glib.h>  // to read config file
#include <stdio.h>
#include <unistd.h> // to use sleep for test

#include "app.h"

using namespace std;


App::App (const char* path_config_file)
{
	config_file = path_config_file;
	vector<string> sensor_list = list_sensor
							   	("/sys/bus/w1/devices/w1_bus_master1/");
	config = load_config();
	vector<Ds18b20*> sensors = open_sensor();
	
	if (config.many_sensor == 0)
	{
		float temp; 
		for (int i=0; i<10; i++)
		{
			temp = sensors[0]->read_temp();
			cout << temp << endl;
			sleep(1);
		}
	}
	else
	{
		cout << " Code to use multiple sensor not ready " << endl;
	}

}

App::~App()
{
}

configuration App::load_config()
{
	configuration config;
	GKeyFile* gkf;
	gkf = g_key_file_new();
	
	// Loads the config file and tests that everything went OK .
    if (!g_key_file_load_from_file (gkf, config_file, G_KEY_FILE_NONE, NULL))
	{
        fprintf (stderr, "Could not read config file %s\n", config_file);
    }	

	// [Raspberry]
	config.numero_raspberry = g_key_file_get_string (gkf,
												 	 "Raspberry",
													 "numero_raspberry",
													 NULL);
	// [Database]
	config.ip_server = g_key_file_get_string (gkf,
											  "Database",
										      "ip_server",
										      NULL);
	config.user = g_key_file_get_string (gkf, "Database", "user", NULL);

	config.pwd = g_key_file_get_string (gkf, "Database", "pwd", NULL);

	config.table = g_key_file_get_string (gkf, "Database", "table", NULL);

	config.port = g_key_file_get_integer (gkf, "Database", "port", NULL);


	// [Sensor]
	config.time_between_two_value = g_key_file_get_double 
												   (gkf,
													"Sensor",
													"time_between_two_value",
													NULL);

	config.many_sensor = g_key_file_get_integer (gkf,
											 	 "Sensor", 
												 "many_sensor", 
												 NULL);


	// free before leaving
	g_key_file_free (gkf);

	return config;
}

vector<string> App::list_sensor (const char* path)
{
	vector<string> sensors;

    struct dirent *entry;
    DIR *dir;
    dir = opendir (path);

	while ((entry = readdir (dir)) != NULL)
	{

		string file_name;
		file_name = entry->d_name;
		if ( file_name.find ("28-") != string::npos )
		{
			sensors.push_back (entry->d_name);
		}
		else
		{
			continue;
		}

    }

	closedir (dir);
	return sensors;
}

vector<Ds18b20*> App::open_sensor()
{
	vector<Ds18b20*> sensors;
	string base_dir_sensor = "/sys/bus/w1/devices/";
	vector<string> sensor_name;
	sensor_name = list_sensor( "/sys/bus/w1/devices/w1_bus_master1/" );
	for (int i=0; i < sensor_name.size(); i++)
	{
		sensors.push_back(new Ds18b20 ( base_dir_sensor
										+ sensor_name[i]
										+"/w1_slave") );
	}

	return sensors;
}





