#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "/home/dcingoz/CC/minishell/minishell_j/minishell.h"

int main ()
{

	extern char	**environ;
	execve("/usr/bin/cat", {"file.txt", NULL}, environ);
}

