#include <sys/time.h>
#include <stdio.h>

#include "SqlDatabase.h"


SqlDatabase::SqlDatabase (const char* ipServer,
                          const char* user,
                          const char* password,
                          const char* database)
{
  mysql_init (&mysql);
  connection = mysql_real_connect (&mysql,ipServer,
                                   user,password,database,0,0,0);
  if (connection == NULL)
  {
    printf (mysql_error (&mysql));
  }
  
}


SqlDatabase::~SqlDatabase()
{
  mysql_close (connection);
}

void SqlDatabase::sendQuery (const char* query)
{
  //only return the last element and when it's empty
  //it cause a segmentation fault 
  int state;
  state = mysql_query (connection,query);
  if (state !=0)
  {
    printf (mysql_error (connection));
  }
}
