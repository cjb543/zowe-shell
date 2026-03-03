#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SHELL_READLINE_BUFFER_SIZE 1024
#define SHELL_TOKEN_BUFFER_SIZE 64
#define SHELL_TOKEN_DELIMITER " \t\r\n\a"

void shell_loop();
char* shell_read_line();
char** shell_split_line(char*);
int shell_execute(char**);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_num_builtins();
int shell_launch(char** args);
// Zowe args
int set_base_profile(char** args);
int submit_latest_job(char** args);
int fetch_latest_job(char** args);
int display_job(char** args);
int show_job_errors(char** args);
int update_zowe_config_file(char*, char*);

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

int main(int argc, char* argv[]){
    // Load config files if any
    // Run command loop
    shell_loop();
    // Shutdown/Cleanup
    return EXIT_SUCCESS;
}


/*
 * Shell functions
 */
void shell_loop(){
    char *line;  // <---- Line to be read
    char **args; // <---- Arguments to be executed
    int status;  // <---- Determines when to terminate

    do {
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);
        free(line);
        free(args);
    } while (status);
}

char* shell_read_line(){
    int bufsize = SHELL_READLINE_BUFFER_SIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char)* bufsize);
    int c;

    if (!buffer){
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1){ // <----- More verbose way to write?
        // Read a character
        c = getchar();

        // If EOF, add null terminator and return
        if (c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
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

int shell_execute(char** args){
    int i;
    if (args[0] == NULL){
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < shell_num_builtins(); i++){
        if (strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    return shell_launch(args);
}

int shell_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1){
            perror("Child process error\n");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        // Error forking
        perror("Forking error\n");
    }
    else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int shell_num_builtins(){
    return sizeof(builtin_str) / sizeof(char*);
}

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

int shell_exit(char **args){
    return 0;
}


/*
 * Zowe Functions
 */
int set_base_profile(char** args){
    char id[32], psswd[32];
    char ch;
    int i = 0;

    // Prompt the user for their username and password
    printf("Enter your team or personal ID:\n");
    while (1){
        ch = getchar();
        id[i] = ch;
        if (ch == '\n')
            break;
        i++;
    }

    printf ("Enter your teasm or personal password:\n");
    while (1){
        ch = getchar();
        psswd[i] = ch;
        if (ch == '\n')
            break;
        i++;
    }

    // Assign username and password to Zowe config file
    update_zowe_config_file(id, psswd);

    return 1;
}


int update_zowe_config_file(char* id, char* psswd){

}

int submit_latest_job(char** args){
    return 1;
}

int fetch_latest_job(char** args){
    return 1;
}

int display_job(char** args){
    return 1;
}

int show_job_errors(char** args){
    return 1;
}

