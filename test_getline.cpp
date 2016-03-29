#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

int main()
{
        const char* name_file = "/sys/bus/w1/devices/28-0000075fe0d5/w1_slave" ;
        ifstream in;
        in.open(name_file);
        string line;
        string temp_line;
        while( getline(in, temp_line) )
        {
                line += temp_line;      
        }
        cout << line << endl;
        cout << name_file << endl;


        in.close();
        sleep(2);
        in.open(name_file);
        line = "";
        temp_line = "";

        while( getline(in, temp_line) )
        {
                line += temp_line;      
        }
        cout << line << endl;
        cout << name_file << endl;
        
        return 0;
}

