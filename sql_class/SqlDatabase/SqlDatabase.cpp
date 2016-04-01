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
  mysql_free_result (result);
  mysql_close (connection);
}

const char** SqlDatabase::sendQuery (const char* query)
{
  //only return the last element and when it's empty
  //it cause a segmentation fault 
  int state;
  state = mysql_query (connection,query);
  if (state !=0)
  {
    printf (mysql_error (connection));
  }
  else
  {
    result = mysql_store_result (connection);
    int num_column = mysql_num_fields (result);
    const char* resultQuery[num_column];
    while ((row = mysql_fetch_row (result)))
      {
       for(int i = 0; i < num_column; i++)
	{
           // Make sure row[i] is valid!
           if(row[i] != NULL)
	   {
                resultQuery[i] = row[i];
	   }
           else
                resultQuery[i]= "NULL";
	}
      }
    return resultQuery;   
  }
}
bool SqlDatabase::isPresent (const char* query)
{ 
  
  sendQuery (query);
  if(mysql_num_rows (result))
  {
    return true;
  }
  else
  {
    return false;
  }
}
