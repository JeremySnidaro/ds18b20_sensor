#include <iostream>
#include "SqlDatabase.h"


using namespace std;

int main(int argc , char* argv[])
{
  SqlDatabase* bdd= new SqlDatabase("127.0.0.1","jeremy","hello","user_carte");
  /*if(bdd->isPresent("SELECT *FROM `id_carte` WHERE `10` = 42"))
  {
    cout << "La carte est valide" << endl;
  }
  */
  const char** buffer;
  buffer = bdd->sendQuery("SELECT * FROM id_carte ");
  cout << buffer[0] << endl;
  
  cout << bdd->isPresent("SELECT * FROM id_carte")<<endl;
  /*if(bdd->isPresent("SELECT * FROM id_carte "))
  {
    cout << "is present << endl;
  }*/
  delete bdd;
  return 0;
}