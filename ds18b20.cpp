#include <iostream>
#include <fstream> // to open file ( the sensor here)
#include <string> // to use find function
#include <stdlib.h> //to use atoi

#include "ds18b20.h"

static int count_crc_error;

Ds18b20::Ds18b20(const char* path_to_sensor)
{
	sensor_file = path_to_sensor;
}

Ds18b20::~Ds18b20()
{
	sensor.close();	
}

int Ds18b20::open_sensor()
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

int Ds18b20::crc_check(string raw_frame)
{
	if( raw_frame.find("YES") != string::npos )
	{
		// find return npos if he not found the string
		return 1;
	}
	else
	{
		return -1;
	}
}

string Ds18b20::read_temp_raw()
{
	open_sensor();
	string temp_line;
	string raw_frame;
    while( getline(sensor,temp_line) )
	{
      raw_frame += temp_line;
	}

	if( crc_check(raw_frame) )
	{
		close_sensor();
		return raw_frame;
	}
	else
	{
		cerr << "Error CRC check" << endl;
		close_sensor();
		read_temp_raw();
		// put a if here when we have 5 following crc check error
		// exit the program and print error
	}

}



float Ds18b20::read_temp()
{
	string raw_frame = read_temp_raw(); // check if raw_frame don't get the cerr error
	string str_temperature = raw_frame.substr( raw_frame.find_last_of("t=")+1 );//check if the t don't broke this

	float temperature = atoi( raw_frame.c_str() ); 
	temperature = temperature / 1000;

	return temperature;
}


