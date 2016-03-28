#include <iostream>

#include "app.h"

using namespace std;

int main()
{ 
	configuration config;
	App *app = new App ("./conf.txt");
	return 0;
}
