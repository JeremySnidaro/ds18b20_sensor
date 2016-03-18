#include <fstream>

using namespace std;

class Ds18b20
{
	ifstream sensor;
	string frame;
	const char* sensor_file;

	public:
		Ds18b20(const char* path_to_sensor);
		~Ds18b20();
		void read_temp_raw();
		float read_temp();
		void open_sensor();
		void close_sensor();
	
};
