/*
* DISCLAIMER; THIS SHELL IS BASED ON THE LAB 6 ADRBOOK SHELL
* FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW (University of Chicago)
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "shell.h"
#include "cli.h"
#include "cmd.h"

#define BUFFER_SIZE 256

/* trim_newline: duplicate the string and replace the newline
 * at the end with '\0' if it exists.
 */
char *trim_newline(char *s)
{
  int n = strlen(s);
  char *t = strdup(s);
  if (s[n-1]=='\n')
    t[n-1] = '\0';
  return t;
}

/*Char array that stores valid commands to complete*/
char *commandnames[] =
  {
    "LOOK",
    "HELP",
    "FIND",
    "QUIT",
    NULL
  };

/*Helper function that compares to see if given command matches with a valid command*/
/*
 * Parameters:
 * text: written in by user, and a yes or no state
 *
 * Returns:
 *  The pointer to the command in the stored array
 */
char* command_name(const char *text, int state)
{
  static int index, len;
  char *name;
  if(!state)
    {
      index = 0;
      len = strlen(text);
    }
  while((name = commandnames[index++])){
    if (strncmp(name, text, len)==0) {
      return strdup(name);
    }
  }
  return NULL;
}

  /* Function that allows for autocompletion of commands written by user */
/* 
 *
 * Parameters:
 * text output from command_name, and a start and end for future implementation 
 *
 * returns 
 *  a pointer to the char pointer to the char array
 */
char** command_complete(const char *text, int start, int end)
{
  rl_attempted_completion_over = 1;
  return rl_completion_matches(text, command_name);
}
 



/* ===================================== */
/* ==== run the chiventure  shell  ===== */
/* ===================================== */

int main()
{
    int quit = 1;
    char *cmd_string;
    greet();
    //rl_bind_key('\t', rl_complete); // Configure readline to auto-complete paths when the tab key is hit.
    using_history();
    while (quit) {
      rl_attempted_completion_function = command_complete;
      // Display prompt and read input
      char* input = readline("chiventure (enter HELP for help)> ");

	cmd_string = trim_newline(input);
        putchar('\n');
        //check whether user input is empty
        if (!strcmp(cmd_string,""))
            continue;

        cmd *c = cmd_from_string(cmd_string);
        if (!c) {
            shell_error_arg("unrecognized or malformed command: \"%s\"", input);
            putchar('\n');
        }
	else {
	    do_cmd(c,&quit);
            // Add valid input to readline history.
            add_history(input);
	}

        if (cmd_string)
            free(cmd_string);
        //cmd_free(c);
        free(input);
        }


    return 0;
}