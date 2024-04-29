
#include "minishell.h"

void	pipe_free_d_str(char **str)
{
	int	i;

	i = 0;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;	
	}
	free(str);
}

char	**pipe_append_path(char **str, char *path_add)
{
	char	**new;
	int		i;

	i = 0;
	while(str[i])
		i++;
	new = (char **)malloc((i + 1) * sizeof(char*));	
	if (new == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while(str[i])
	{
		new[i] = ft_strjoin(str[i], path_add);
		i++;
	}
	new[i] = NULL;
	free(path_add);
	pipe_free_d_str(str);
	return (new);
}

char	*pipe_path_run(char **all_paths, char **argv, char **environ, int is_out)
{
	int		i;
	i = 0;
	
	if (is_out == 2)
	{return (NULL);}
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0)
		{	

			if (execve(all_paths[i], argv, environ) == -1)
			pipe_free_d_str(all_paths);
			printf("execve failed\n");
			exit(0);
		}
		i++;
	}

	return (NULL);
}

char	*pipe_exter_cmd_run(char *path, char **argv, int is_out)
{
	char	**environ;
	char	**all_paths;

	environ = get_full_env(0);
	if (argv[0] == NULL)
		return (NULL);
	if (access(path, X_OK) == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			return (NULL);
		}
		exit(0);
	}
	all_paths = pipe_append_path(ft_split(getenv("PATH"), ':'), ft_strjoin("/", path));
	if (all_paths == NULL)
		return (NULL);
	return (pipe_path_run(all_paths, argv, environ, is_out));
}

// TEST

// int main(int argc, char **argv)
// {
// 	if (argc < 3)
// 	{
// 		printf("Not enough arg\n");
// 		return (1);
// 	}
// 	int x = 0;
// 	while (argv[x] != NULL)
// 	{
// 		write(1, argv[x], ft_strlen(argv[x]));
// 		write(1, "\n", 1);
// 		x++;
// 	}
// 	exter_cmd_run(argv[1], argv);
// 	return (0);
// }


