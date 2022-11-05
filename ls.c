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
    if(argc == 2){
        if (strcmp(argv[1], "-a") == 0){
            struct dirent *d;
            DIR* dir = opendir(".");
            if (dir == NULL){
                printf("Error: empty directory");
            } 
            else {
                d = readdir(dir);
                while(d!=NULL){
                    printf("%s ", d->d_name);
                    d = readdir(dir);
                }
                printf("\n");
            }
            closedir(dir);
        }
        else if (strcmp("-i", argv[1]) == 0){
            struct dirent *d;
            DIR* dir = opendir(".");
            if (dir == NULL){
                printf("empty directory");
            } else {
                while((d = readdir(dir))!=NULL){
                    if (d->d_name[0] == '.'){
                        continue;
                    }
                    else{
                        char cur_dir[1024];
                        getcwd(cur_dir, 1024);
                        int  fd, inode;  
                        strcat(cur_dir, "/");
                        strcat(cur_dir, d->d_name);
                        fd = open(cur_dir,O_RDONLY);
                        if (fd < 0) {  
                            continue;
                        } else {
                            struct stat file_stat;  
                            int ret;  
                            ret = fstat (fd, &file_stat);  
                            if (ret < 0) {  
                               continue;
                            } 
                            else{
                                inode = file_stat.st_ino; 
                                printf("%lu  %s \n", inode, d->d_name); 
                            }        
                        }
                    }
                    printf("\n");
                } 
                closedir(dir);
            }
        }
        else if (strcmp(argv[1], " ") == 0){
            struct dirent *d;
            DIR* dir = opendir(".");
            if (dir == NULL){
                printf("empty directory");
            }
            else {
                while((d = readdir(dir))!=NULL){
                    if (d->d_name[0] == '.'){
                        continue;
                    }
                    else{
                        printf("%s ", d->d_name);
                    }
                }
                printf("\n");
            }
            closedir(dir);
        }
        else {
            printf("Error: invalid argument \n");
        }
    }
    
    else if (argc ==1){
        struct dirent *d;
        DIR* dir = opendir(".");
        if (dir == NULL){
            printf("empty directory");
        }
        else {
            while((d = readdir(dir))!=NULL){
                if (d->d_name[0] == '.'){
                    continue;
                }
                else{
                    printf("%s ", d->d_name);
                }
            }
            printf("\n");
        }
        closedir(dir);
    }
    else {
        printf("Error: invalid ls call \n");
    }
    return 0;
}