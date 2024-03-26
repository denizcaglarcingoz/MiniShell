#include "minishell.h"

/// get it at the start of the program

char **get_env()
{
    extern char **environ;
    char **env;

    int i = 0;
    if (environ == NULL || environ[i] == NULL)
        return (NULL);

    while(environ[i] != NULL)
        i++;

    env = (char **)malloc(i * sizeof(char*));
        //protect
    env[i-1] = NULL;
    
    i = 0;
    while(environ[i] != NULL)
    {
        env[i] =ft_strdup(environ[i]);
        //protect
        i++;
    }

    return (env);
}

// print when command env runs

void print_env(char **env)
{
    while (env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
    if (env == NULL)
        printf("Empty Environmental Variable List\n");
}

/// remember to add/delete variabes if they run the commands

char **add_env(char **env, char *variable)
{

    // assume getting  like this variable = "DENIZ=deniz/home/cd asdasdadasdasdDasdasd"

    char **new_env;


    if (variable == NULL)
        return (env);
    
    int i = 0;
    while(env[i] != NULL)
        i++;
    new_env = (char **)malloc((i + 1) * sizeof(char **));
    //protect

    i = 0;
    while(env[i] != NULL)
    {
        new_env[i] =ft_strdup(env[i]);
        //protect
        i++;
    }
    new_env[i] = ft_strdup(variable);
    //protect

    //free original env
    //might be free variable
    return new_env;
}


char **del_env(char **env, char *variable)
{

    // assume getting  like this variable = "DENIZ=deniz/home/cd asdasdadasdasdDasdasd"

    char **new_env;


    if (variable == NULL)
        return (env);
    
    int i = 0;
    while(env[i] != NULL)
        i++;
    new_env = (char **)malloc((i - 1) * sizeof(char **));
    //protect

    i = 0;
    while(env[i] != NULL)
    {
        if(ft_strncmp(env[i], variable, ft_strlen(variable) + 1) == 0)
            new_env[i] =ft_strdup(env[i]);
        i++;
    }
    new_env[i] = ft_strdup(variable);
    //protect

    //free original env
    //might be free variable
    return new_env;
}