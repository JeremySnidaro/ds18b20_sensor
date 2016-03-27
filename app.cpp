#include <iostream>
#include <dirent.h> // to list dir
#include <glib.h>  // to read config file
#include <stdio.h>

#include "app.h"

using namespace std;


App::App()
{
	config_file = " ./conf.txt ";
	vector<string> sensor_list = list_sensor( "/sys/bus/w1/devices/w1_bus_master1/" );

}

App::~App()
{
}

configuration App::load_config( const char* path )
{
	configuration config;
	GKeyFile* gkf;
	gkf = g_key_file_new();
	
	// Loads the config file and tests that everything went OK .
    if (!g_key_file_load_from_file(gkf, config_file, G_KEY_FILE_NONE, NULL))
	{
        fprintf (stderr, "Could not read config file %s\n", config_file);
    }	

	// START stuff about the config file ......

	// we will check on the main app if many_sensor if on 0 or 1 for 1
	config.numero_raspberry =
	config.ip_server = 
	config.user =
	config.pwd =
	config.table =
	config.port = g_key_file_get_integer(gkf, "Database", "port", NULL);


	// [Sensor]
	config.time_between_two_value = 
	config.many_sensor = g_key_file_get_integer(gkf, "Sensor", "many_sensor", NULL);


	// free before leaving
	g_key_file_free(gkf);

	return config;
}

vector<string> App::list_sensor( const char* path )
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
			sensors.push_back(entry->d_name);
		}
		else
		{
			continue;
		}

    }

	closedir(dir);
	return sensors;
}
