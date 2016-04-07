#include <vector>

#include "ds18b20.h"
#include "sql_class/SqlDatabase/SqlDatabase.h"


using namespace std;

struct configuration
{
    // [Raspberry]
    const char* numero_raspberry;    
    
    // [Database]
    const char* ip_server;
    const char* database;
    const char* user;
    const char* pwd;
    const char* table;
    const char* column1;
    const char* column2;
    const char* column_date;

    // [Sensor]
    float time_between_two_value;
    int many_sensor;
    const char* sensor_file;
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

