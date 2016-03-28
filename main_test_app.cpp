#include <iostream>

#include "app.h"

using namespace std;

int main()
{ 
	configuration config;
	App *app = new App ("./conf.txt");
	config = app->load_config();
	cout << config.port;
	return 0;
}
