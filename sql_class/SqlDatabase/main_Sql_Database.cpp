#include <sys/time.h>

#include <stdio.h>

#include <mysql.h>
//https://softexpert.wordpress.com/2007/10/18/how-to-connect-to-a-mysql-db-using-c-linux/
//http://www.nitecon.com/tutorials-articles/develop/cpp/c-mysql-beginner-tutorial/

int main(int argc , char* argv[])

{
  MYSQL_RES *result;

  MYSQL_ROW row;

  MYSQL *connection, mysql;

  int state;

  
  mysql_init(&mysql);

  connection = mysql_real_connect(&mysql,"127.0.0.1","jeremy","hello","user_carte",0,0,0);

  if (connection == NULL)

  {

  printf(mysql_error(&mysql));

  return 1;

  }



  state = mysql_query(connection,"SELECT * FROM id_carte");

  if (state !=0)

  {

  printf(mysql_error(connection));

  return 1;

  }
  result = mysql_store_result(connection);
  printf("Rows:%d\n",mysql_num_rows(result));

  //affiche les row de la database
  int i =0;
   while ((row = mysql_fetch_row(result)) != NULL)
   {
        printf("%s\n",row[i] != NULL ?
        row[i] : "NULL"); /* Print the row data */
    }
  //FIN-----affiche les row de la database  
    
  mysql_free_result(result);

  mysql_close(connection);


  return 0;

};