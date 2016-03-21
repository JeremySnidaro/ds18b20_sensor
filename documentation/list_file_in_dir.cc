// directory.cc - M. Heck - 21 mars 2016
// Liste des dossiers/fichiers d'un répertoire.


#include <sys/types.h>
#include <dirent.h> 
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
if (argc<2) { cout<<"usage : directory repertoire\n"; exit (-1); }
DIR * rep;
rep=opendir(argv[1]);
struct dirent *entree;
struct dirent *result;
while (entree=readdir(rep)) cout <<entree->d_name<<endl;
closedir(rep);
}

