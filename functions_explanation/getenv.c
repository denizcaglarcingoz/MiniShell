// NAME
//        getenv, secure_getenv - get an environment variable

// SYNOPSIS
//        #include <stdlib.h>

//        char *getenv(const char *name);


//  it is to get environment variable

#include <stdio.h>
#include <stdlib.h>

int main() {
    char *home_directory = getenv("DESKTOP_SESSION"); // write here the environment variable name such as HOME / DESKTOP_SESSION
    if (home_directory != NULL) {
        printf("Home directory: %s\n", home_directory);
    } else {
        printf("HOME environment variable not set.\n");
    }
    return 0;
}