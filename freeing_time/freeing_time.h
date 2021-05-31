#ifndef FREEING_TIME_H
# define FREEING_TIME_H

// # include "../minishell.h"
# include "../parser/parser.h"

void	free_array(char ***array_addr);
void	free_tokens_list(t_tokens **tokens_list);
void	free_abstract_syntax_tree(t_ast *ast);

#endif