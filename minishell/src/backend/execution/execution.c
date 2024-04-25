#include "minishell.h"
char **check_hdoc(t_table exp_table)
{
	int i;
	char *hdoc;
	char **hdocs;

	if (exp_table.heredoc[0] == NULL)
		return (NULL);
	i = 0;
	hdoc = NULL;
	while (exp_table.heredoc[i] != NULL)
	{
		if (hdoc != NULL)
			free(hdoc);
		hdoc = hdoc_inp((exp_table.heredoc)[i]); // hdoc_inp is a function that is inside of redirections heredoc
		i++;
	}
	hdocs = (char **)malloc(sizeof(char *) * 2);
	hdocs[0] = hdoc;
	hdocs[1] = NULL;
	return (hdocs);
}

char *check_in(t_table exp_table)
{
	int i;
	
	if (exp_table.in[0] == NULL)
		return (NULL);
	i = 0;
	while (exp_table.in[i] != NULL)
		i++;
	return (exp_table.in[i - 1]);
}

void run_builtin(){}

void	run_command(t_table exp_table, int table_id, int pipefd1, int out_fd)
{
	char *return_out;
	char **hdoc;
	char *in;
	t_token_type t_type;

	hdoc = check_hdoc(exp_table);
	in = check_in(exp_table);
	// if (is_builtin(exp_table.args[0]) == 1) // run_builtin is a function that is inside of builtins
	// 	run_builtin(); 
	// else
	{
		if (exp_table.args == NULL)
			return ;
		printf("\n---dasdd-----\n");//test
		if (exp_table.args[1] == NULL && exp_table.in[0] == NULL && exp_table.heredoc[0] == NULL &&
				exp_table.my_stdin[0] != NULL)
		{
			return_out = exter_cmd_run(exp_table.args[0], exp_table.args);
		}
		else if (exp_table.args[1] != NULL || (exp_table.in[0] == NULL && exp_table.heredoc[0] == NULL))
		{
			printf("\n---wes-----\n");//test

			return_out = exter_cmd_run(exp_table.args[0], exp_table.args);
		}
		else
		{
			printf("\n---ads-----\n");//test
			t_type = in_o_hdoc(exp_table, table_id); 
			if (t_type == D_LESS)
				return_out = exter_cmd_run(exp_table.args[0], hdoc);
			else if (t_type == LESS)
				return_out = exter_cmd_run(exp_table.args[0], &in);
		}
	}

	if (exp_table.out[0] != NULL || exp_table.append[0] != NULL)
	{
		t_type = out_o_app(exp_table, table_id);
		if (t_type == GREATER)
			output_file(last_str(exp_table.out), return_out);
		else if (t_type == D_GREATER)
			append_file(last_str(exp_table.append), return_out);
		
	}
	else
	{	
		if (table_id + 1 == exp_table.table_len)
		{
			if (pipefd1 != 0 && out_fd != 0)
			{
				close(pipefd1);
				dup2(out_fd, STDOUT_FILENO);
				// printf("table_id %d, exp_table.table_len %d\n", table_id, exp_table.table_len);
			}
		}
		if (return_out != NULL)
		{	
			ft_putstr_fd(return_out, 1);
			// int j = 0;
			// while (exp_table.args[j] != NULL)
			// {
			// 	printf("args[%d]: %s\n", j, exp_table.args[j]);
			// 	j++;
			// }
			// printf("inside close pipefd1\n");
		}// printf("return_out: %s\n", return_out);
	}
}

void execution(t_table *exp_table)
{
	if (exp_table == NULL)
		return ;
	if (exp_table->table_len < 2)
	{	
		single_exec(exp_table[0], 0);
	}
	else
	{
		pipe_execution(exp_table);
	}
}
