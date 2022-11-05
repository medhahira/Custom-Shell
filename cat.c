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

void cat(){
    char printing[1024];
    bool flag = true;
    while(fgets(printing, 1024, stdin) && flag){
        char *element;
        char **arr = (char**)malloc(sizeof(printing) * sizeof(char*));
        element = strtok (printing, " \n");
        int i = 0;
        while(element != NULL){
            arr[i++] = element;
            element = strtok(NULL, " \n");
        } 
        if (i == 1 && strcmp(arr[0], "exit") == 0){
            flag = false;
            break;
        } 
        else{
            printf("%s \n\n", printing);
        }
    } 
}

void cat_n(){
    char printing[1024];
    bool flag = true;
    int cnt = 1;
    while(fgets(printing, 1024, stdin) && flag){
        char *element;
        char **arr = (char**)malloc(sizeof(printing) * sizeof(char*));
        element = strtok (printing, " \n");
        int i = 0;
        while(element != NULL){
            arr[i++] = element;
            element = strtok(NULL, " \n");
        } 
        if (i == 1 && strcmp(arr[0], "exit") == 0){
            flag = false;
            break;
        } 
        else{
            printf("%d %s \n\n", cnt, printing);
            cnt++;
        }
    }
}

void cat_b(){
    char printing[1024];
    bool flag = true;
    int cnt = 1;
    while(fgets(printing, 1024, stdin) && flag){
        char *element;
        char **arr = (char**)malloc(sizeof(printing) * sizeof(char*));
        element = strtok (printing, " \n");
        int i = 0;
        while(element != NULL){
            arr[i++] = element;
            element = strtok(NULL, " \n");
        } 
        if (i == 1 && strcmp(arr[0], "exit") == 0){
            flag = false;
            break;
        } 
        else {
            if (arr[0] == NULL){
                cnt+=0;
            }
            else {
                printf("%d %s \n\n", cnt, printing);
                cnt++;
            }
        }
    } 
}
void cat_n_file(char *file_name){
    FILE *fpt;
    fpt = fopen(file_name, "rb");
    if (fpt == NULL){
        printf("Error: %s no such file or directory exist \n", file_name);
    } 
    else {
        char printing[1024];
        int cnt = 1;
        while (fgets(printing, 1024, fpt)){
            char *element;
            char **arr = (char**)malloc(sizeof(printing) * sizeof(char*));
            element = strtok (printing, " \n");
            int i = 0;
            while(element != NULL){
                arr[i++] = element;
                element = strtok(NULL, " \n");
            } 
            printf("%d %s \n", cnt, printing);
            cnt++;
        }
    }
    printf("\n");
    fclose(fpt); 
}
void cat_b_file(char *file_name){
    FILE *fpt;
    fpt = fopen(file_name, "rb");
    if (fpt == NULL){
        printf("Error: %s no such file or directory exist \n", file_name);
    } 
    else {
        char printing[1024];
        int cnt =1;
        
        while (fgets(printing, 1024, fpt)){
            char *element;
            char **arr = (char**)malloc(sizeof(printing) * sizeof(char*));
            element = strtok (printing, " \n");
            int i = 0;
            while(element != NULL){
                arr[i++] = element;
                element = strtok(NULL, " \n");
            } 
            if (arr[0] == NULL){
                cnt+=0;
                printf("\n \n");
            }
            else {
                printf("%d %s \n", cnt, printing);
                cnt++;
            }   
        }
        printf("\n");
        fclose(fpt); 
    }
}
void cat_file(char *file_name){
    FILE *fpt;
    fpt = fopen(file_name, "rb");
    if (fpt == NULL){
        printf("Error: %s no such file or directory exist \n", file_name);
    } 
    else {
        char printing[1024];
        while (fgets(printing, 1024, fpt)){
            char *element;
            char **arr = (char**)malloc(sizeof(printing) * sizeof(char*));
            element = strtok (printing, " \n");
            int i = 0;
            while(element != NULL){
                arr[i++] = element;
                element = strtok(NULL, " \n");
            }         
            printf("%s \n",printing);
        }
        printf("\n");
        fclose(fpt); 
    }
}
void forking(char *file_name, char *option){

    if (strcmp(file_name, "cat") == 0){
        if (strcmp(option, " ") == 0){
            cat();
        }
        else if (strcmp(option, "-n") == 0){
            cat_n();
        }
        else if (strcmp(option, "-b") == 0){
            cat_b();
        }
    }
    else {
        if (strcmp(option, "-n") == 0){
            cat_n_file(file_name);
            
        }       
        else if (strcmp(option, "-b") == 0){
            cat_b_file(file_name);
        } 
        else if(strcmp(option, " ") == 0){
            cat_file(file_name);
        }
    }
}
int main(int argc, char *argv[]){
    if (argc == 3){
        char *file_name = argv[2];
        char *option = argv[1];
        forking(file_name, option);
    } 
    
    //cat -n
    //cat -b
    else if (argc == 2) {
        if (strcmp(argv[1], "-n") == 0){
            cat_n();
        } 
        else if (strcmp(argv[1],"-b") == 0){
            cat_b();
        }
        else {
            cat_file(argv[1]);
        }
    }
    else if (argc == 1){
        cat();
    } 
    if (argc > 3){
        printf("Error: too many arguments encountered \n");
    }
}
