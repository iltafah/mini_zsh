#include "create_abstract_syntax_tree.h"

void initialize_node_vars(t_vars *vars)
{
    vars->pipe_seq_node = NONE;
    vars->word_node = NONE;
    vars->simple_command_node = NONE;
    //vars->semicolon_token = NONE;
    //vars->pipe_token = NONE;
}

void    initialize_ast_pointers(t_ast_ptrs *ast)
{
    ast->cmd_line_node = NULL;
    ast->curr_pipe_seq_node = NULL;
    ast->curr_simple_cmd_node = NULL;
    ast->curr_word_node = NULL;
}

void remember_last_created_node(t_vars *vars, t_type token)
{
    initialize_node_vars(vars);
    if (token == e_simple_word)
    {
        vars->pipe_seq_node = EXIST;
        vars->simple_command_node = EXIST;
        vars->word_node = EXIST;
    }
    else if (token == e_pipe)
    {
        vars->pipe_seq_node = EXIST;
        vars->simple_command_node = EXIST;
        //vars->pipe_token = EXIST;
    }
    else if (token == e_semicolon)
    {
        vars->pipe_seq_node = EXIST;
        //vars->semicolon_token = EXIST;
    }
}

void get_curr_pipe_seq_node(t_vars vars, t_ast_ptrs *ast)
{
    // else if (/*vars.semicolon_token == EXIST &&*/vars.word_node == NONE)
    // else if (vars.word_node == NONE && vars.simple_command_node == NONE)
    if (vars.pipe_seq_node == NONE)
        ast->curr_pipe_seq_node =
        get_pipe_seq_node(ast->cmd_line_node, BOTTOM);
    else if (vars.simple_command_node == NONE)
        ast->curr_pipe_seq_node =
        get_pipe_seq_node(ast->curr_pipe_seq_node, NEXT);
}

void get_curr_simple_cmd_node(t_vars vars, t_ast_ptrs *ast)
{
    // else if (vars.pipe_token == EXIST)
    // if (vars.simple_command_node == NONE && vars.word_node == NONE)
    if (vars.simple_command_node == NONE)
        ast->curr_simple_cmd_node =
        get_simple_cmd_node(ast->curr_pipe_seq_node, BOTTOM);
    else if (vars.word_node == NONE)
        ast->curr_simple_cmd_node =
        get_simple_cmd_node(ast->curr_simple_cmd_node, NEXT);
}

void get_curr_word_node(t_vars vars, t_ast_ptrs *ast)
{
    if (vars.word_node == NONE)
        ast->curr_word_node = get_word_node(ast->curr_simple_cmd_node, BOTTOM);
    else if (vars.word_node == EXIST)
        ast->curr_word_node = get_word_node(ast->curr_word_node, NEXT);
}


void store_word_in_suitable_node(t_vars vars, t_ast_ptrs *ast, char *word)
{
    get_curr_pipe_seq_node(vars, ast);
    get_curr_simple_cmd_node(vars, ast);
    get_curr_word_node(vars, ast);
    ast->curr_word_node[0]->u_infos.word = ft_strdup(word);
}

t_redirection   *create_single_redirection_node(char *type, char *file)
{
    t_redirection *new_redirection_node;

    new_redirection_node = malloc(sizeof(t_redirection));
    new_redirection_node->type = ft_strdup(type);
    new_redirection_node->file = ft_strdup(file);
    new_redirection_node->next = NULL;
    return (new_redirection_node);
}

void    store_redirection_data(t_ast_ptrs *ast, t_tokens **curr_token)
{
    t_redirection   **curr_redir_node;
    char            *type;
    char            *file;
    
    curr_redir_node = &(ast->curr_simple_cmd_node[0]->u_infos.redirections);
    while (*curr_redir_node != NULL)
        curr_redir_node = &((*curr_redir_node)->next);
    type = (*curr_token)->data;
    (*curr_token) = (*curr_token)->next;
    file = (*curr_token)->data;
    *curr_redir_node = create_single_redirection_node(type, file);
}

void create_abstract_syntax_tree(t_node **cmd_line_node, t_tokens *tokens)
{
    t_tokens *curr_token;
    t_ast_ptrs ast;
    t_vars vars;

    initialize_node_vars(&vars);
    initialize_ast_pointers(&ast);
    *cmd_line_node = create_single_node(e_cmdline_node);
    ast.cmd_line_node = cmd_line_node;
    curr_token = tokens;
    while (curr_token)
    {
        if (curr_token->type == e_simple_word)
        {
            store_word_in_suitable_node(vars, &ast, curr_token->data);
            remember_last_created_node(&vars, e_simple_word);
        }
        else if (curr_token->type == e_pipe)
            remember_last_created_node(&vars, e_pipe);
        else if (curr_token->type == e_semicolon)
            remember_last_created_node(&vars, e_semicolon);
        else if (curr_token->type == e_redir)
            store_redirection_data(&ast, &curr_token);
        curr_token = curr_token->next;
    }
}