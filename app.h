#include <vector>
#include <string>

#include "ds18b20.h"

using namespace std;

struct configuration
{
	// [Raspberry]
	string numero_raspberry;	
	
	// [Database]
	string ip_server;
	string user;
	string pwd;
	string table;
	int port;

	// [Sensor]
	float time_between_two_value;
	int many_sensor;
	string sensor_file;
};

#ifndef App_H_
#define App_H_

class App
{

	const char* config_file;
	configuration config;

	configuration load_config();

	public :
		App (const char* path_config_file);
		~App();
		vector<string> list_sensor (const char* path);
		vector<Ds18b20*> open_sensor();

};

#endif
