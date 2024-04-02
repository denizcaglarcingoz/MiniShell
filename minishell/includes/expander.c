#include "minishell.h"


int	get_exit_status_len()//get from shellstruct in case of calling added var...
{
	int	len;

}

size_t	get_var_len(char *str)
{

}

size_t	get_expanded_len(char *str)//pass in shell struct for exit size and env...make get env for ours
{
	bool	in_s_quote;
	bool	in_d_quote;
	size_t	total_len;

	
	//perform quote count check and return error... init and check function?
	in_s_quote = 0;
	in_d_quote = 0;
	total_len = 0;
	while (*str)
	{
		if (*str == '\"' && !in_s_quote)
			in_d_quote = !in_d_quote;
		if (*str == '\'' && !in_d_quote)
			in_s_quote = !in_s_quote;
		if (*str == '$' && *(str + 1) == '?' && !in_s_quote)
		{
			total_len += get_exit_status_len();//todo
			str += 2;
		}
		else if (*str == '$' && !in_s_quote)
		{
			total_len += get_var_len(str + 1);//todo
			//str+ length, consider uses indice and adjust pointer...
		}
		else
			str++;
		total_len++;

	
	}
	return (total_len);//then malloc and build...
}