#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <limits.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
    struct stat fstat;
    
    if (argc > 3){  
        printf("Error: date, invalid input \n");
    }
    else if(argc == 2){
        if(strcmp("-r", argv[1]) == 0){
            printf("Error: missing file argument \n");
        }
        else if(strcmp("-u", argv[1]) == 0){
            time_t utc_now = time(&utc_now);
            struct tm *pass = gmtime(&utc_now);
            printf("UTC %s \n", asctime(pass));
        }
        else{
            printf("Error: invalid option for date \n");
        } 
    }
    else if (argc == 3){
        if(strcmp("-r", argv[1]) == 0){
            if(stat(argv[2],&fstat) < 0){
                printf("Error: does not exist\n");
            }
            else{
                printf("IST : %s \n", ctime(&fstat.st_mtime));
            }  
        }
        else if (strcmp("-u", argv[1]) == 0 && strcmp(" ", argv[2]) == 0){
            time_t utc_now = time(&utc_now);
            struct tm *pass = gmtime(&utc_now);
            printf("UTC %s \n", asctime(pass));
        }
        else if (strcmp("-u", argv[1]) == 0){
            printf("Error: invalid \n");
        }
        else if (strcmp(" ", argv[1]) == 0 && strcmp(" ", argv[2]) == 0){
            time_t IST_time = time(NULL);
            printf("IST %s \n", ctime(&IST_time));
        }
        else{
            printf("Error \n");
        }
    }
    else if(argc == 1){
        time_t IST_time = time(NULL);
        printf("IST %s \n", ctime(&IST_time));
    }
}