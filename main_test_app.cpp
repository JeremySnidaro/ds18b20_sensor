#include <iostream>

#include "app.h"

using namespace std;

int main()
{ 
	configuration config;
	App *app = new App ("./conf.txt");
	config = app->load_config();
	cout << config.port;
	cout << config.user;
	cout << config.pwd;
	cout << config.table;
	cout << config.time_between_two_value;
	return 0;
}
