#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <signal.h>

int findName(char name[], char action[], char* actualPath);
char* concat(const char *s1, const char *s2);
int findPerm(int perm, char action[] , char* actualPath);
int findType(char type, char action[] , char* actualPath);
