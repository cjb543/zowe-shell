#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// TODO: Figure out default locations for Zowe. Design search with as little friction as possible.
int update_zowe_config_file(char* id, char* psswd){
    // Check user OS first. This determines where files COULD be located. If
    // unable to automatically check for files, prompt user to search for 
    // zowe.config.js, or to close/abort. Since we're in C with no GUI
    // framework, probably just ask them to type in a path, check if the file
    // is at that path, and execute accordingly.

    pid_t pid = fork();
    if (pid == 0){
        char* decoded_alias[] = {"zowe", "something", "something", NULL};
        execvp(decoded_alias[0], decoded_alias);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("Set Base Profile Executed. Exit Code: %d\n", WEXITSTATUS(status));
    } else {
        perror("Set Base Profile failed to fork. Aborting...");
    }
    return 1;

    // If the user is on any version of Windows (32 is backwards compatible with 64, so
    // any OS works)
    #ifndef _WIN32
    #endif

    // If the user is on Linux...
    #ifndef __gnu_linux__
    #endif

    // If the user is on MacOS...
    
    return 1;
}

int set_base_profile(char** args){
    char id[32], psswd[32];
    char ch;
    int i = 0;

    // Prompt the user to enter their ID
    printf("Enter your team or personal ID:\n");
    while (1){
        ch = getchar();
        id[i] = ch;
        if (ch == '\n')
            break;
        i++;
    }
    // Prompt the user to enter their password
    printf ("Enter your teams or personal password:\n");
    while (1){
        ch = getchar();
        psswd[i] = ch;
        if (ch == '\n')
            break;
        i++;
    }

    pid_t pid = fork();
    if (pid == 0){
        char* decoded_alias[] = {"zowe", "something", "something", NULL};
        execvp(decoded_alias[0], decoded_alias);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("Set Base Profile Executed. Exit Code: %d\n", WEXITSTATUS(status));
    } else {
        perror("Set Base Profile failed to fork. Aborting...");
    }

    // Assign username and password to Zowe config file
    update_zowe_config_file(id, psswd);

    return 1;
}




int submit_latest_job(char** args){
    pid_t pid = fork();
    if (pid == 0){
        char* decoded_alias[] = {"zowe", "something", "something", NULL};
        execvp(decoded_alias[0], decoded_alias);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("Submit Latest Job Executed. Exit Code: %d\n", WEXITSTATUS(status));
    } else {
        perror("Submit Latest Job failed to fork. Aborting...");
    }
    return 1;
}

int fetch_latest_job(char** args){
    pid_t pid = fork();
    if (pid == 0){
        char* decoded_alias[] = {"zowe", "something", "something", NULL};
        execvp(decoded_alias[0], decoded_alias);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("Submit Latest Job Executed. Exit Code: %d\n", WEXITSTATUS(status));
    } else {
        perror("Fetch Latest Job failed to fork. Aborting...");
    }
    return 1;
}

int display_job(char** args){
    pid_t pid = fork();
    if (pid == 0){
        char* decoded_alias[] = {"zowe", "something", "something", NULL};
        execvp(decoded_alias[0], decoded_alias);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("Submit Latest Job Executed. Exit Code: %d\n", WEXITSTATUS(status));
    } else {
        perror("Display Job failed to fork. Aborting...");
    }
    return 1;
}

int show_job_errors(char** args){
    pid_t pid = fork();
    if (pid == 0){
        char* decoded_alias[] = {"zowe", "something", "something", NULL};
        execvp(decoded_alias[0], decoded_alias);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("Submit Latest Job Executed. Exit Code: %d\n", WEXITSTATUS(status));
    } else {
        perror("Show Job Errors failed to fork. Aborting...");
    }
    return 1;
}

