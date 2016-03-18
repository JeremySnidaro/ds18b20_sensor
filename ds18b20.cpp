#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> //to use atoi
#include "ds18b20.h"


Ds18b20::Ds18b20(const char* path_to_sensor)
{
	sensor_file = path_to_sensor;
}

Ds18b20::~Ds18b20()
{
	sensor.close();	
}

void Ds18b20::open_sensor()
{
	sensor.open(sensor_file);
	//	sensor.open("/sys/bus/w1/devices/28-0000075fe0d5/w1_slave");

	if(!sensor.is_open())
	{
		perror("Error unable to open sensor : ");	
	}
}

void Ds18b20::close_sensor()
{
	sensor.close();
}

string Ds18b20::read_temp_raw()
{
	open_sensor();
	string line;
	string frame;
    while( getline(sensor,line) )
	{
      frame += line;
	}
	frame = frame.substr( frame.find_last_of("=")+1 );
	close_sensor();
	return frame;
}

float Ds18b20::read_temp()
{
	float temperature = atoi( read_temp_raw().c_str() ); 
	temperature = temperature / 1000;
	return temperature;
}


