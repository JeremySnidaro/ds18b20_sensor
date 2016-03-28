#include <vector>
#include <string>

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

class App
{

	const char* config_file ;
	configuration config;

	public :
		App();
		~App();
		vector<string> list_sensor (const char* path);
		configuration load_config (const char* path);

};
