#include <iostream>
#include <dirent.h> // to list dir
#include <glib.h>  // to read config file
#include <stdio.h>

#include "app.h"

using namespace std;


App::App (const char* path_config_file)
{
	config_file = path_config_file;
	vector<string> sensor_list = list_sensor
							   	("/sys/bus/w1/devices/w1_bus_master1/");
	cout << sensor_list[0];
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

	config.port = g_key_file_get_integer(gkf, "Database", "port", NULL);


	// [Sensor]
	//config.time_between_two_value = g_key_file_get_double 
	//											   (gkf,
	//												"Sensor",
	//												"time_between_two_value",
	//												NULL);

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
