#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    
	while (1)
	{
        char* input = readline("MINISHELL> ");
		if (errno != 0 )
		{
			perror("Malloc Error");
			clear_history();
			break;
		}
		if (input == 0)
		{
			clear_history();
			break;
		}
        add_history(input);
        if (strcmp(input, "exit") == 0) {
            printf("Exiting MINISHELL!\n");
            free(input);
            break;
        }

        printf("You entered: %s\n", input);
    }

    return 0;
}