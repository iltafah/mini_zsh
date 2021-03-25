#include "check_tokens_syntax.h"



int     check_tokens_syntax(t_tokens *tokens_list)
{
    t_tokens    *curr_token_node;
    int         command_exist;

    curr_token_node = tokens_list;
    command_exist = 0;
    while (curr_token_node)
    {
        if (curr_token_node->type == e_simple_word)
        {
            if (check_simple_word_syntax(curr_token_node->data) == ERROR)
            {
                printf("%s> Error: multiline commands not allowed\n", RED);
                return (ERROR);
            }
            command_exist = 1;
        }
        else if (curr_token_node->type == e_pipe)
        {
            if (command_exist == FALSE)
            {
                printf("%sbash: syntax error near unexpected token `|'\n", RED);
                return (ERROR);
            }
            command_exist = 0;
        }
        else if (curr_token_node->type == e_semicolon)
        {
            if (command_exist == FALSE)
            {
                printf("%sbash: syntax error near unexpected token `;'\n", RED);
                return (ERROR);
            }
            command_exist = 0;
        }
        // else if (curr_token_node->type == e_redir)
        // {

        // }
        curr_token_node = curr_token_node->next;
    }
    return (TRUE);
}