#include "../minishell.h"

int input_file(char *file_name, char **inp_file)
{
	int	inp_len; 
	int	fd = open(file_name, O_RDONLY);
	int BUFFER_SIZE;
	char buffer[BUFFER_SIZE];
	int bytes_read;
	if (fd == -1)
	{
		perror("open");
		return 1;
	}
	inp_len = 1;
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
	    if(bytes_read == -1)
		{
			perror("read");
			close(fd);
			return (1);
		}
		*inp_file = (char *)malloc(inp_len + bytes_read);
		//protect
		inp_len = ft_strlen(*inp_file) + 1;
		ft_strlcat(*inp_file, buffer, bytes_read);


	}
	if (close(fd) == -1)
	{
		perror("close");
		return 1;
	}
	return (0);
}


// TEST


int main ()
{
	char *file_name = "file.txt";
	char *inp_file = NULL;

	if (input_file(file_name, &inp_file) == -1)
	{
		//error;
		return(1);
	}
	
	printf("%s\n", inp_file);
	return (0);
}


