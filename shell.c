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
#include <pthread.h>

#define clear() printf("\033[H\033[J");

void ThreadFunc(char *command)
{
    int ret = 0;
    ret = system(command);
}

char** array_of_inputs(char* string){
    char *element;
    char **arr = (char**)malloc(sizeof(string) * sizeof(char*));
    element = strtok (string, " \n");
    int i = 0;
    while(element != NULL){
        arr[i++] = element;
        element = strtok(NULL, " \n");
    }
    return arr;
}

int get_len(char* string){
    char *element;
    char **arr = (char**)malloc(sizeof(string) * sizeof(char*));
    element = strtok (string, " \n");
    int i = 0;
    int count = 0;
    while(element != NULL){
        arr[i++];
        count+=1;
        element = strtok(NULL, " \n");
    }
    return i;
}

void getpwd(){
    char cur_dir[1024];
        if (getcwd(cur_dir, sizeof(cur_dir)) != NULL){
            printf("Current working directory: %s\n", cur_dir);
            fflush(stdout);
        } else{
            printf("Error encountered in current working directory");
            fflush(stdout);
        }
}

void fork_mkdir(char* dir, char *option, char *arr){
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
   	    printf("Fork Failed \n");
        return ;
    } else if (pid == 0) {
        //printf("hi \n");
        execl(dir, "mkdir", option , arr, NULL);
    } else { 
   	    wait(NULL);
    } 
}
void fork_ls(char* dir, char **arr, int count){
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
   	    printf("Fork Failed \n");
        return ;
    } else if (pid == 0) {
        if (count == 1){
            execl(dir, "ls", NULL, NULL);
        } 
        else if (count == 2){
            if (strcmp(arr[1], "-i") == 0){
                execl(dir, "ls", "-i", NULL);
            } 
            else if (strcmp(arr[1], "-a") == 0){
                execl(dir, "ls", "-a", NULL);
            } 
            else {
                execl(dir, "ls", arr[1], NULL);
            }
        }
        else {
            execl(dir, "ls", "err", NULL);
        }
    } else { 
   	    wait(NULL);
    } 
}
void fork_rm(char* dir, char *option, char *arr){
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
   	    printf("Fork Failed \n");
        return ;
    } else if (pid == 0) {
        execl(dir, "rm", option, arr, NULL);
    } else { 
   	    wait(NULL);
    } 
}
void fork_cat(char* dir, char *option, char *file_name){
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
   	    printf("Fork Failed \n");
        return ;
    } else if (pid == 0) {
        //when no file name is given
        
        if (strcmp(file_name, "cat") == 0){
            //cat
            if (strcmp(option, " ") == 0){
                execl(dir, "cat", " ", "cat", NULL);
            }
            //cat -n
            else if (strcmp(option, "-n") == 0){
                execl(dir, "cat", "-n", "cat", NULL);
            }
            else if (strcmp(option, "-b") == 0){
                execl(dir, "cat", "-b", "cat", NULL);
            }
        }
        else {
            if (strcmp(option, "-n") == 0){
                execl(dir, "cat","-n", file_name, NULL);
            }
            else if (strcmp(option, "-b") == 0){
                execl(dir, "cat","-b", file_name, NULL);
            } 
            else if (strcmp(option, " ") == 0){
                execl(dir, "cat"," ", file_name, NULL);
            }
        }
    } else { 
   	    wait(NULL);
    } 
}
void fork_date(char* dir, char *option, char *file){
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
   	    printf("Fork Failed \n");
        return ;
    } else if (pid == 0) {
        execl(dir, "date", option, file, NULL);
    } else { 
   	    wait(NULL);
    } 
}

int main(int argc, char **argv) {
    char cwd_curr[4096];
    char cwd_store[4096];
    //getcwd(cwd, 4096);
    getcwd(cwd_curr, 4096);
    getcwd(cwd_store, 4096);
    bool flag = true;
    char* user = getenv("USER");
    clear();
    printf("SHELL\n");
    printf("USER: %s \n", user);
    while(flag){
        char cur_dir[1024];
        getcwd(cur_dir, 1024);
        int n; 
        printf("%s@Custom-Device shell %% ", user);
        char string[1024];
        fgets(string, 1024, stdin);
        char *element;
        char **arr = (char**)malloc(sizeof(string) * sizeof(char*));
        element = strtok (string, " \n");
        int i = 0;
        while(element != NULL){
            arr[i++] = element;
            element = strtok(NULL, " \n");
        }
        strcat(cwd_curr, "/");
        int count = i;
        if (count == 0){
            printf("0 \n");
        }
        else if (strcmp(arr[count-1], "&t") == 0){
            arr[count-1] = NULL;
            //char pthread_arg[1024] = cur_dir;
            //printf("%s \n", cwd_curr);
            //char* arg;
            int i = 0;
            while (arr[i] != NULL){  
                strcat(cwd_curr, arr[i]);
                strcat(cwd_curr, " ");
                //printf("%s \n", cwd_curr);
                i++;
            }

            pthread_t t1;
            int ret = pthread_create(&t1, NULL, (void *(*)(void *))ThreadFunc, (void *)cwd_curr);
            pthread_join(t1, NULL);
            strcpy(cwd_curr, cwd_store);
        }

        else if (strcmp("exit", arr[0]) == 0){
            flag = false;
            printf("Exiting session... \n");
            printf("[Process completed]\n");
        } 
        else if (strcmp("mkdir", arr[0]) == 0){
            strcat(cwd_curr, "mkdir");
            if (count == 1){
                printf("Error: insufficient arguments \n");
            }
            else if (count ==2){
                if (strcmp("-v", arr[1]) == 0 || strcmp("-pv", arr[1]) == 0){
                    printf("Error: insufficient arguments \n");
                }
            }
            else if (strcmp("-v", arr[1]) == 0 && count >= 3){
                int k = 2;
                while (arr[k]!=NULL){
                    fork_mkdir(cwd_curr, "-v", arr[k]);
                    k++;
                }
            } 
            else if (strcmp("-pv", arr[1]) == 0){
                fork_mkdir(cwd_curr, "-pv", arr[2]);
            }
            else if (count != 1){
                int k = 1;
                while (arr[k]!=NULL){
                    fork_mkdir(cwd_curr, " ", arr[k]);
                    k++;
                }
            }
            else {
                printf("Error: insufficient arguments \n");
            }
            strcpy(cwd_curr, cwd_store);
        } 
        else if (strcmp("date", arr[0]) == 0){
            strcat(cwd_curr, "date");
            if (count == 1){
                fork_date(cwd_curr," ", " ");
            }
            else if (strcmp("-r", arr[1]) == 0){
                if (count == 3){
                    fork_date(cwd_curr, "-r", arr[2]);
                } else {
                    printf("Error: missing file argument \n");
                }
            }
            else if (strcmp("-u", arr[1]) == 0){
                fork_date(cwd_curr, "-u", " ");
            }
            else {
                printf("Error \n");
            }
            strcpy(cwd_curr, cwd_store);
        }
        else if (strcmp("pwd", arr[0]) == 0){
            if (count == 2){
                if (strcmp("-l", arr[1]) == 0 ||strcmp("-p", arr[1]) == 0){
                    getpwd();
                }
                else {
                    printf("Error : %s is an invalid argument for pwd \n", arr[1]);
                }
            }
            else if (count ==1){
                getpwd();
            }
            else {
                printf("Error : invalid command for pwd \n");
            }
        } else if (strcmp("echo", arr[0]) == 0){
            if (strcmp("-n", arr[1]) == 0){
                int k = 2;
                while(arr[k]!=NULL){
                    printf("%s ", arr[k]);
                    k++;
                }
            } else if (strcmp("--help", arr[1]) == 0) {
                printf("Usage: echo [SHORT-OPTION]... [STRING]... \n");
                printf("or: echo [LONG-OPTION] \n");
                printf("Echo the string(s) to standard output \n");
                printf("-n      do not output the trailing newline \n");
                printf("--help  display this help page and exit \n");
                printf("Thankyou for calling help function \n");
            } else {
                int k = 1;
                while(arr[k] != NULL){
                    printf("%s ", arr[k]);
                    k++;
                }
                printf("\n");
                //--help
            }
        } else if (strcmp("cd", arr[0]) == 0){
            if (count == 1){
                chdir(getenv("HOME"));
            }
            else if (strcmp("..", arr[1])==0 && count == 2){
                getpwd();
                chdir("..");
                getpwd();
            } else if(count == 2){
                char* to = arr[1];
                if (chdir(to) == -1){
                    printf("Error: cd, no such file or directory : %s \n", to);
                } else {
                    chdir(to);
                }
            } 
            else {
                printf("Error \n");
            }
        } else if (strcmp("ls", arr[0]) == 0){
            strcat(cwd_curr, "ls");
            fork_ls(cwd_curr, arr, count);
            strcpy(cwd_curr, cwd_store);
        } 
        else if (strcmp("rm", arr[0]) == 0){
            strcat(cwd_curr, "rm");
            if (count == 1){
                printf("Error, no arguments given");
            }
            
            else if (strcmp("-v", arr[1]) == 0){
                int k = 2;
                while (arr[k]!=NULL){
                    fork_rm(cwd_curr, "-v", arr[k]);
                    k++;
                }   
            }
            else if (strcmp("-d", arr[1]) == 0){
                int k = 2;
                while (arr[k]!=NULL){
                    fork_rm(cwd_curr, "-d", arr[k]);
                    k++;
                }
            } else {
                int k = 1;
                while (arr[k]!=NULL){
                    fork_rm(cwd_curr, " ", arr[k]);
                    k++;
                }
            }
            strcpy(cwd_curr, cwd_store);
        }
        else if (strcmp("cat", arr[0]) == 0){
            strcat(cwd_curr, "cat");
            if (count == 1){
                fork_cat(cwd_curr, " ", "cat");
            }
            else if (count == 2){
                if (strcmp( "-n", arr[1]) == 0){
                    fork_cat(cwd_curr, "-n", "cat");
                } 
                else if (strcmp("-b", arr[1]) == 0){
                    fork_cat(cwd_curr, "-b", "cat");
                }
                else {
                    fork_cat(cwd_curr, " ", arr[1]);
                }
            }
            else if (count == 3){
                if (strcmp("-n", arr[1]) == 0){
                    fork_cat(cwd_curr, "-n", arr[2]);
                }
                else if (strcmp("-b", arr[1]) == 0){
                    fork_cat(cwd_curr, "-b", arr[2]);
                }
                else {
                    printf("Error: cat, illegal option %s \n", arr[1]);
                }
            }
            else {
                printf("Error \n");
            } 
            strcpy(cwd_curr, cwd_store);
        }
        else {
            printf("Error: invalid command \n");
        }
        free(arr);
    }
    return 0;
}