/**
 * @file shell.c
 * @brief A simple shell with built-in command dispatch.
 */

#include "zowe_interface.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SHELL_READLINE_BUFFER_SIZE 1024  /**< Initial buffer size for line input. */
#define SHELL_TOKEN_BUFFER_SIZE 64       /**< Initial buffer size for token array. */
#define SHELL_TOKEN_DELIMITER " \t\r\n\a" /**< Delimiters used during tokenization. */

void shell_loop();
char* shell_read_line();
char** shell_split_line(char*);
int shell_execute(char**);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_num_builtins();
int shell_launch(char** args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "set_base_profile",
    "submit_latest_job",
    "fetch_latest_job",
    "display_job",
    "show_job_errors"
};
int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &set_base_profile,
    &submit_latest_job,
    &fetch_latest_job,
    &display_job,
    &show_job_errors
};

/**
 * @brief Runs the main read-execute loop until a command returns 0.
 */
void shell_loop(){
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);
        free(line);
        free(args);
    } while (status);
}

/**
 * @brief Reads a line of input from stdin into a heap-allocated buffer.
 *
 * @return Null-terminated string. Caller is responsible for freeing.
 */
char* shell_read_line(){
    int bufsize = SHELL_READLINE_BUFFER_SIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char)* bufsize);
    int c;

    if (!buffer){
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1){
        c = getchar();

        if (c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize){
            bufsize += SHELL_READLINE_BUFFER_SIZE;
            buffer = realloc(buffer,bufsize);
            if (!buffer) {
                fprintf(stderr,"shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * @brief Splits a line into a null-terminated array of tokens.
 *
 * @param line Input string. Modified in place by strtok.
 * @return Null-terminated array of token pointers. Caller is responsible for freeing.
 */
char** shell_split_line(char* line){
    int bufsize = SHELL_TOKEN_BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        fprintf(stderr, "shell: token allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_TOKEN_DELIMITER);
    while (token != NULL){
        tokens[position] = token;
        position++;

        if (position >= bufsize){
            bufsize += SHELL_TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens){
                fprintf(stderr,"shell: token allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SHELL_TOKEN_DELIMITER);
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * @brief Matches args[0] against built-ins and dispatches accordingly,
 *        falling back to shell_launch.
 *
 * @param args Null-terminated argument array.
 * @return Status code; 0 exits the shell loop.
 */
int shell_execute(char** args){
    int i;
    if (args[0] == NULL){
        return 1;
    }

    for (i = 0; i < shell_num_builtins(); i++){
        if (strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    return shell_launch(args);
}

/**
 * @brief Forks a child process and execs the given command.
 *
 * @param args Null-terminated argument array; args[0] is the executable.
 * @return 1 when the child process exits or is signaled.
 */
int shell_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1){
            perror("Child process error\n");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("Forking error\n");
    }
    else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

/**
 * @brief Returns the number of registered built-in commands.
 *
 * @return Length of builtin_str[].
 */
int shell_num_builtins(){
    return sizeof(builtin_str) / sizeof(char*);
}

/**
 * @brief Changes the current working directory.
 *
 * @param args args[1] is the target directory.
 * @return 1.
 */
int shell_cd(char **args){
    if (args[1] == NULL){
        fprintf(stderr, "shell: expected argument to  \"cd\"\n");
    }
    else {
        if (chdir(args[1]) != 0){
            perror("shell error...\n");
        }
    }
    return 1;
}

/**
 * @brief Prints a list of available built-in commands to stdout.
 *
 * @param args Unused.
 * @return 1.
 */
int shell_help(char **args){
    int i;
    printf("Benson's Zowe Shell\n");
    printf("Type program names and arguments. Zowe-compatible commands are listed here.\n");
    printf("The following are built in:\n");
    for (i = 0; i < shell_num_builtins(); i++){
        printf("  %s\n", builtin_str[i]);
    }
    return 1;
}

/**
 * @brief Signals the shell loop to terminate.
 *
 * @param args Unused.
 * @return 0.
 */
int shell_exit(char **args){
    return 0;
}
