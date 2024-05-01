#include "minishell.h"

int output_file(char *file_name, char *out_file)
{
	int	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int	len;
	int written_size;

	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	if (out_file == NULL)
	{	
		close(fd);
		return (0);
	}
	len = ft_strlen(out_file);
	written_size = write(fd, out_file, len);
	if (written_size == -1)
	{
		perror("write");
		close(fd);
		return(1);
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (1);
	}
	return (0);
}


// TEST

// int main ()
// {
// 	char *file_name = "file.txt";
// 	char *inp_file = "HADI\n";

// 	if (output_file(file_name, inp_file) == -1)
// 	{
// 		//error;
// 		return(1);
// 	}
	
// 	//printf("%s\n", inp_file);
// 	return (0);
// }


