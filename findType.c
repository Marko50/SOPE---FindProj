#include "findName.h"


int findType(char type, char action[] , char* actualPath)
{
  DIR* directory = opendir(actualPath);
  if(directory == NULL)
  {
    printf("Error on opening current path!\n");
    return 1;
  }
  struct dirent* file = readdir(directory);
  while(file != NULL)
  {
    struct stat buf;
    char* filePath = concat(actualPath, "/");
    filePath = concat(filePath, file->d_name);
    if(strcmp(file->d_name, "..") == 0 ||  strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "sfind") == 0)
    {
      file = readdir(directory);
      continue;
    }
    if(stat(filePath, &buf) == -1)
    {
      printf("Error filling stat struct for file : %s\n", filePath);
    }
    else{
      if(S_ISDIR(buf.st_mode) && type == 'd')
      {
        if(strcmp(action, "print") == 0)
        {
          printf ("Found a new directory at : %s\n", filePath);
        }
        else if(strcmp(action, "delete") == 0)
        {
          if(remove(filePath) == -1)
          {
              printf("Error deleting a directory at : %s\n", filePath);
          }
          else
            printf ("Deleted a directory with at : %s\n", filePath);

            file = readdir(directory);
            continue;
        }
        else if(strcmp(action, "exec") == 0)
        {
          execlp(action, action, NULL);
        }

        pid_t pid;
        pid = fork();
        if(pid < 0)
        {
          fprintf(stderr, "fork error\n");
        }
        else if(pid == 0) //Son
        {
          if(closedir(directory) == -1)
          {
            printf("Failed to close directory\n");
          }
          findType(type, action, filePath);
          return 0;
        }
      }

      else if(S_ISREG(buf.st_mode) && type == 'f' )
      {
        if(strcmp(action, "print") == 0)
        {
          printf ("Found a new regular file at : %s\n", filePath);
        }
        else if(strcmp(action, "delete") == 0)
        {
          if(remove(filePath) == -1)
          {
              printf("Error deleting a regular file at : %s\n", filePath);
          }
          else
            printf ("Deleted a regular file at : %s\n", filePath);
            file = readdir(directory);
            continue;
        }
        else if(strcmp(action, "exec") == 0)
        {
          execlp(action,action,NULL);
        }
      }

      else if(S_ISLNK(buf.st_mode) && type == 'l' )
      {
        if(strcmp(action, "print") == 0)
        {
          printf ("Found a symbolic link at : %s\n", filePath);
        }
        else if(strcmp(action, "delete") == 0)
        {
          if(remove(filePath) == -1)
          {
              printf("Error deleting a symbolic link at : %s\n", filePath);
          }
          else
            printf ("Deleted a symbolic link with at : %s\n", filePath);

            file = readdir(directory);
            continue;
        }
        else
        {
          execlp(action, action, NULL);
        }
      }

    }
    file = readdir(directory);
  }
  return 0;
}
