#include <iostream>
#include <dirent.h> // to list dir
#include <glib.h>  // to read config file
#include <stdio.h>
#include <unistd.h> // to use sleep for test
#include <sstream>

#include "app.h"

using namespace std;


App::App (string path_config_file)
{
    config_file = path_config_file;
    config = load_config();
    

    if (config.many_sensor == 0)
    {
        float temp; 
        for (int i=0; i<10; i++)
        {
            vector<Ds18b20*> sensors = open_sensor();
            temp = sensors[0]->read_temp();
            cout << temp << endl;
            open_db();
            send_temp(temp);
            delete db;
            sleep(1);
        }
    }
    else
    {
        cout << " Code to use multiple sensor not ready " << endl;
    }

}

App::~App()
{
}

void App::open_db()
{
    db = new SqlDatabase (config.ip_server, config.user,
                          config.pwd ,config.database);
}

void App::send_temp (float temp)
{
// send the temperature to the database
/*
sql request to insert data look like this :

mysql> INSERT INTO tutorials_tbl 
     ->(tutorial_title, tutorial_author, submission_date)
     ->VALUES
     ->("Learn PHP", "John Poul", NOW());
*/
    ostringstream buf;
    buf << temp;
    string temp_str (buf.str());
   
    string query = "INSERT INTO " + string (config.table)
                                 + " (" 
                                    + string (config.column1) 
                                    + ","
                                    + string (config.column2) 
                                 + ") "
                                 + "VALUES " 
                                 + "(\"" 
                                    + string (config.numero_raspberry) 
                                 + "\","
                                    + temp_str
                                 + ")";

// the request look like this
// INSERT INTO salle (numero_raspberry,temp) VALUES ("42",23.32)

    db->sendQuery (query.c_str());

    db_check_entry();
}

void App::db_check_entry()
{
// delete the entry oldest than 3 years
// DELETE FROM config.table
// WHERE config.column_date < (NOW() - INTERVAL (365*3) DAY)
    string query = "DELETE FROM " + string (config.table)
                 + " WHERE " + string (config.column_date)
                 + " < (NOW() - INTERVAL 1 MINUTE)";

    db->sendQuery (query.c_str());
}

configuration App::load_config()
{
    configuration config;
    GKeyFile* gkf;
    gkf = g_key_file_new();
    
    // Loads the config file and tests that everything went OK .
    if (!g_key_file_load_from_file (gkf, config_file.c_str(), G_KEY_FILE_NONE, NULL))
    {
        fprintf (stderr, "Could not read config file %s\n",
                 config_file.c_str());
    }   

    // [Raspberry]
    config.numero_raspberry = g_key_file_get_string (gkf,
                                                     "Raspberry",
                                                     "numero_raspberry",
                                                     NULL);
    // [Database]
    config.ip_server = g_key_file_get_string (gkf,
                                              "Database",
                                              "ip_server",
                                              NULL);

    config.database = g_key_file_get_string (gkf,
                                             "Database",
                                             "database",
                                             NULL);

    config.user = g_key_file_get_string (gkf, "Database", "user", NULL);

    config.pwd = g_key_file_get_string (gkf, "Database", "pwd", NULL);

    config.table = g_key_file_get_string (gkf, "Database", "table", NULL);

    config.column1 = g_key_file_get_string (gkf, "Database", "column1", NULL);

    config.column2 = g_key_file_get_string (gkf, "Database", "column2", NULL);

    config.column_date = g_key_file_get_string (gkf,
                                                "Database",
                                                "column_date",
                                                NULL);
    // [Sensor]
    config.time_between_two_value = g_key_file_get_double 
                                                   (gkf,
                                                    "Sensor",
                                                    "time_between_two_value",
                                                    NULL);

    config.many_sensor = g_key_file_get_integer (gkf,
                                                 "Sensor", 
                                                 "many_sensor", 
                                                 NULL);


    // free before leaving
    g_key_file_free (gkf);

    return config;
}

vector<string> App::list_sensor (const char* path)
{
    vector<string> sensors;

    struct dirent *entry;
    DIR *dir;
    dir = opendir (path);

    while ((entry = readdir (dir)) != NULL)
    {

        string file_name;
        file_name = entry->d_name;
        if ( file_name.find ("28-") != string::npos )
        {
            sensors.push_back (entry->d_name);
        }
        else
        {
            continue;
        }

    }

    closedir (dir);
    return sensors;
}

vector<Ds18b20*> App::open_sensor()
{
    vector<Ds18b20*> sensors;
    string base_dir_sensor = "/sys/bus/w1/devices/";
    vector<string> sensor_name;
    sensor_name = list_sensor ("/sys/bus/w1/devices/w1_bus_master1/");
    for (int i=0; i < sensor_name.size(); i++)
    {
        sensors.push_back(new Ds18b20 (base_dir_sensor
                                       + sensor_name[i]
                                       + "/w1_slave") );
    }

    return sensors;
}





