#include <fstream>

using namespace std;

class Ds18b20
{
	ifstream sensor;
	const char* sensor_file;

	public:
		Ds18b20(string path_to_sensor);
		~Ds18b20();
		string read_temp_raw();
		float read_temp();
		int open_sensor();
		void close_sensor();
		int crc_check(string raw_frame);
	
};
