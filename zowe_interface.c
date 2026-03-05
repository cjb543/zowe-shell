/**
 * @file zowe_interface.c
 * @brief Wrappers for invoking Zowe CLI commands and managing Zowe configuration.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/**
 * @brief Writes credentials to the Zowe config file.
 *
 * @todo Determine default config file locations per OS. If not found
 *       automatically, prompt the user to supply a path.
 *
 * @param id     User or team identifier.
 * @param psswd  Corresponding password.
 * @return 1.
 */
int update_zowe_config_file(char* id, char* psswd){
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
}

/**
 * @brief Prompts for credentials interactively, then calls update_zowe_config_file.
 *
 * @param args Unused.
 * @return 1.
 */
int set_base_profile(char** args){
    char id[32], psswd[32];
    char ch;
    int i = 0;

    printf("Enter your team or personal ID:\n");
    while (1){
        ch = getchar();
        id[i] = ch;
        if (ch == '\n')
            break;
        i++;
    }
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

    update_zowe_config_file(id, psswd);

    return 1;
}

/**
 * @brief Submits the most recent job via Zowe CLI.
 *
 * @param args Unused.
 * @return 1.
 */
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

/**
 * @brief Fetches output for the most recent job via Zowe CLI.
 *
 * @param args Unused.
 * @return 1.
 */
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

/**
 * @brief Displays job details via Zowe CLI.
 *
 * @param args Unused.
 * @return 1.
 */
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

/**
 * @brief Retrieves job error output via Zowe CLI.
 *
 * @param args Unused.
 * @return 1.
 */
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
