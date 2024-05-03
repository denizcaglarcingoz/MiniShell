#include "minishell.h"

bool is_white_space(char is)
{
    if (is == '\t' || is == '\n' || is == '\v'
            || is == '\f' || is == '\r' || is == ' ')
        return (true);
    return (false);
}

bool is_meta_char(char is)
{
    if (is == '|' || is == '<' || is == '>')
        return (true);
    return (false);
}