#include "findName.h"


static void sig_handler(int signo){
    if(signo == SIGINT)
    {
      char opc;
      printf("Are you sure you want to terminate (Y/N)? :");
      scanf(" %c", &opc);
      if(opc == 'y' || opc == 'Y')
        exit(1);
    }
}

void printUsage()
{
  printf("Usage: ./sfind name/type/perm string/char/octal print/delete/exec\n");
  exit(1);
}

int main(int argc , char* argv[])
{
  //argv[0]->sfind argv[1]->nome/type/perm argv[2]->NOME/TYPE/PERM  argv[3]->print/delete/exec
  signal(SIGINT, sig_handler);
  char* buffActualPath = malloc(PATH_MAX);
  char* actualPath = getcwd(buffActualPath, PATH_MAX);

if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
  printUsage();

 else if(strcmp(argv[1], "name") == 0)
 {
   if(strcmp(argv[3],"print") == 0 || strcmp(argv[3],"delete") == 0 ||  strcmp(argv[3],"exec") == 0)
   {
     findName(argv[2], argv[3], actualPath);
   }
   else{
     printUsage();
   }
 }

 else if(strcmp(argv[1], "type") == 0)
 {
   if(strcmp(argv[3],"print") == 0 || strcmp(argv[3],"delete") == 0 ||  strcmp(argv[3],"exec") == 0)
   {
     findType(*argv[2], argv[3], actualPath);
   }
   else{
     printUsage();
   }
 }

 else if(strcmp(argv[1], "perm") == 0)
 {
   if(strcmp(argv[3],"print") == 0 || strcmp(argv[3],"delete") == 0 ||  strcmp(argv[3],"exec") == 0)
   {
     int permission = atoi(argv[2]);
     findPerm(permission, argv[3], actualPath);
   }
   else{
     printUsage();
   }
 }

  //findName("lixo", "delete", actualPath);
  //findPerm(775,"delete", actualPath);
  //findType('d', "delete", actualPath);
  free(buffActualPath);
  return 0;
}
