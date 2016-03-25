#include <iostream>
#include <fstream> // to open file ( the sensor here)
#include <string> // to use find function
#include <stdlib.h> //to use atoi

#include "ds18b20.h"

static int count_crc_error = 0;

Ds18b20::Ds18b20(string path_to_sensor)
{
	sensor_file =  path_to_sensor.c_str();
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
		count_crc_error += 1;
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
		if( count_crc_error > 4 )
		{ 
			cerr << "Too much CRC check error check the sensor" << endl;		
			exit(-1);
		}
		cerr << "Error CRC check count_crc_error = " << count_crc_error << endl;
		close_sensor();
		read_temp_raw();
	}

}



float Ds18b20::read_temp()
{
	string raw_frame = read_temp_raw(); // check if raw_frame don't get the cerr error
	string str_temperature = raw_frame.substr( raw_frame.find_last_of("t=")+1 );//check if the t don't broke this

	float temperature = atoi( str_temperature.c_str() ); 
	temperature = temperature / 1000;
	float temperature_round = temperature * 10;
	temperature_round = int(temperature_round);
	temperature_round /= 10;

	return temperature_round;
	// we get temperature like this 21.3 but if we have 21.39 we will get 21.3 not 21.4
}


