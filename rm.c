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

int main(int argc, char *argv[]){ 
    if (strcmp(argv[1]," ") == 0 && argc == 3){
        printf("%s ", argv[1]);
        struct stat path;
        int exists = stat(argv[2], &path);
        int is_dir = S_ISREG(path.st_mode);
        if (exists == 0){
            if (is_dir == 1){
            int check = remove(argv[2]); 
            } 
            else if (is_dir == 0){
                printf("Error: cannot remove %s, it is a directory \n", argv[2]);
            }
            else {
                printf("Error: \n");
            }
        } else {
            printf("Error: cannot remove %s, no such file or directory exists \n", argv[2]);
        }
    } 
    else if (strcmp(argv[1],"-v") == 0 && argc >= 3){
        int i = 2;
        while(argv[i] != NULL){
            struct stat path;
            int exists = stat(argv[i], &path);
            int is_dir = S_ISREG(path.st_mode);
            if (exists == 0){
                if (is_dir == 1){
                int check = remove(argv[i]);
                    if (check == 0){
                        printf("%s file deleted successfully \n", argv[i]);
                    }  
                } 
                else if (is_dir == 0){
                    printf("Error: cannot remove %s, it is a directory \n", argv[i]);
                }
                else {
                    printf("Error: \n");
                }
            } else {
                printf("Error: cannot remove %s, no such file or directory exists \n", argv[i]);
            }
            i++;
        }
    } 
    else if (strcmp(argv[1],"-d") == 0 && argc >= 3){
        int i = 2;
        while(argv[i] != NULL){
            struct stat path;
            int exists = stat(argv[i], &path);
            int is_dir = S_ISREG(path.st_mode);
            if (exists == 0){
                int check = remove(argv[i]);
                if (check != 0){
                    printf("Error: cannot remove %s\n", argv[i]);
                }
            } else {
                printf("Error: cannot remove %s, no such file or directory exists \n", argv[i]);
            }
            i++;
        }        
    } else if (argc>=2){
        int i = 1;
        while(argv[i] != NULL){
            struct stat path;
            int exists = stat(argv[i], &path);
            int is_dir = S_ISREG(path.st_mode);
            if (exists == 0){
                int check = remove(argv[i]);
                if (check != 0){
                    printf("Error: cannot remove %s\n", argv[i]);
                }
            } else {
                printf("Error: cannot remove %s, no such file or directory exists \n", argv[i]);
            }
            i++;
        }  
    }
}