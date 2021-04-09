#include "create_abstract_syntax_tree.h"

t_redirection   *create_single_redirection_node(char *type, char *file)
{
    t_redirection *new_redirection_node;

    new_redirection_node = malloc(sizeof(t_redirection));
    new_redirection_node->type = ft_strdup(type);
    new_redirection_node->file = ft_strdup(file);
    new_redirection_node->next = NULL;
    return (new_redirection_node);
}

void            store_redirection_data(t_ast_ptrs *ast, t_tokens **curr_token)
{
    // t_redirection **curr_redir_node;
    // char *type;
    // char *file;

    // curr_redir_node = &(ast->curr_simple_cmd_node[0]->u_infos.redirections);
    // while (*curr_redir_node != NULL)
    //     curr_redir_node = &((*curr_redir_node)->next);
    // type = (*curr_token)->data;
    // (*curr_token) = (*curr_token)->next;
    // file = (*curr_token)->data;
    // *curr_redir_node = create_single_redirection_node(type, file);
}