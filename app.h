#include <vector>

#include "ds18b20.h"
#include "sql_class/SqlDatabase/SqlDatabase.h"


using namespace std;

struct configuration
{
    // [Raspberry]
    string numero_raspberry;    
    
    // [Database]
    string ip_server;
    string database;
    string user;
    string pwd;
    string table;
    string column1;
    string column2;
    string column_date;

    // [Sensor]
    float time_between_two_value;
    int many_sensor;
    string sensor_file;
};

#ifndef APP_H_
#define APP_H_

class App
{

    string config_file;
    configuration config;
    

    SqlDatabase* db; 


    configuration load_config();

    public :
        App (string path_config_file);
        ~App();
        vector<string> list_sensor (string path);
        vector<Ds18b20*> open_sensor();

        void open_db();
        void send_temp (float temp);
        void db_check_entry();


};

#endif // APP_H_

