#include "findName.h"

char* concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1+len2+1);
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);
    return result;
}

int findName(char name[], char action[] , char* actualPath)
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
    if(strcmp(name, file->d_name) == 0)
    {
      if(strcmp(action, "print") == 0)
      {
        printf ("Found a file with that name at : %s\n", filePath);
      }
      else if(strcmp(action, "delete") == 0)
      {
        if(remove(filePath) == -1)
        {
            printf("Error deleting a file with that name at : %s\n", filePath);
        }
        else
          printf ("Deleted a file with that name at : %s\n", filePath);

          file = readdir(directory);
          continue;
      }
      else if(strcmp(action, "exec") == 0)
      {
        execlp(action,action,NULL);
      }
    }

    if(strcmp(file->d_name, "..") == 0 ||  strcmp(file->d_name, ".") == 0)
    {
      file = readdir(directory);
      continue;
    }

    if(stat(filePath, &buf) == -1)
    {
      printf("Error filling stat struct for file : %s\n", filePath);
    }
    else{

      if(S_ISDIR(buf.st_mode))
      {
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
          findName(name, action, filePath);
          return 0;
        }
      }
    }
    file = readdir(directory);
  }
  return 0;
}
