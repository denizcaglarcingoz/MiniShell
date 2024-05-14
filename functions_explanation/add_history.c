
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



// 	Add history helps you when you run the program. 
//	The readline gives you a place to write you input so it can take it as line into program.
//	add_history adds to history for you. On the next readline of same program running,
//  you press up or down arrows on the keyboard, it brings the last inputs back up
 
int main()
{
	char *input = readline("DemonShell: ");
	add_history(input);

	input = readline("DemonShell: ");
	add_history(input);

	input = readline("DemonShell: ");
	add_history(input);

	input = readline("DemonShell: ");
	add_history(input);

	printf("Your last input is: %s\n", input);

	return (0);
}
