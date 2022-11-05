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

static void mkdirRec(const char *path, mode_t mode) {
    char *ptr;
    char path_desired[1024];
    size_t len;

    strncpy(path_desired, path, sizeof(path_desired));
    path_desired[sizeof(path_desired) - 1] = '\0';
    len = strlen(path_desired);
    if (len == 0)
        return;
    else if (path_desired[len - 1] == '/')
        path_desired[len - 1] = '\0';
    for(ptr = path_desired; *ptr; ptr++)
        if (*ptr == '/') {
            *ptr = '\0';
            mkdir(path_desired, mode);
            *ptr = '/';
        }
    if (access(path_desired, F_OK))       
        mkdir(path_desired, mode);
}

int main(int argc, char *argv[]){
    struct stat path;
    if (argc >= 3){
        if (strcmp(argv[1],"-v") == 0){
            int i = 2;
            while (argv[i]!=NULL){
                if (strcmp(argv[i]," ") != 0){
                    if (mkdir(argv[i],0777) != -1){
                        printf("Directory named '%s' created\n", argv[i]);
                    } else {
                        printf("Error: unable to create directory named: '%s'\n", argv[i]);
                    }   
                }
                i++;
            }
            
        } else if (strcmp(argv[1]," ") == 0 && argc == 3){
            int valid;
            valid = mkdir(argv[2],0777);
            if (valid){
                int exists = stat(argv[1], &path);
                if (exists != 1){
                    printf("Error: %s already exists \n", argv[1]);
                }
                else {
                printf("Error: could not create \n");
                }
            }
        }
        
        else if (strcmp(argv[1],"-pv") == 0 && argc == 3){
            mkdirRec(argv[2], S_IRWXU);
        }
        else {
            int i = 1;
            while (argv[i]!=NULL && strcmp(argv[i]," ") != 0){
                int valid;
                valid = mkdir(argv[i],0777);
                if (valid){
                    int exists = stat(argv[i], &path);
                    if (exists != 0){
                        printf("Error: %s already exists \n", argv[1]);
                    }
                    else {
                    printf("Error: could not create \n");
                    }
                }
                i++;
            }
        }
    } 
    else if (argc == 2){
        int valid;
        valid = mkdir(argv[1],0777);
        if (valid){
            int exists = stat(argv[1], &path);
            if (exists != 1){
                printf("Error: %s already exists \n", argv[1]);
            }
            else {
            printf("Error: could not create \n");
            }
        }
    }
    
    return 0;
}