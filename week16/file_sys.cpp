#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

int main() {
    char path[PATH_MAX + 1];
    DIR * dp;
    dirent * dirp;

    cout << "Please choose the directory you want to traverse: " << endl;
    cin >> path;
    if((dp = opendir(path)) == NULL)
    /* fail to open the directory */
    {
        printf("Cannot read path: %s\n", path);
        return 0;
    }

    while((dirp = readdir(dp)) != NULL)
    /* continue to traverse the directory */
    {
        printf("File Name: %s \n", dirp -> d_name);
    }
    return 0;
}