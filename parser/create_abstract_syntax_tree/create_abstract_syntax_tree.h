/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_abstract_syntax_tree.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:38:20 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/15 17:28:07 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_ABSTRACT_SYNTAX_TREE_H
# define CREATE_ABSTRACT_SYNTAX_TREE_H

# include "../parser.h"

typedef struct s_node_state
{
	int		data_node;
	int		pipe_seq_node;
	int		simple_command_node;
}	t_state;

typedef struct s_ast_ptrs
{
	t_ast	**cmd_line;
	t_ast	**curr_data;
	t_ast	**curr_pipe_seq;
	t_ast	**curr_smpl_cmd;
}	t_ast_ptrs;

typedef struct s_ast_vars
{
	t_state		state;
	t_ast_ptrs	ast_ptrs;
}	t_ast_vars;

t_ast	*create_single_node(t_tag tag);
t_ast	**create_data_node(t_ast **curr_node, int dir);
t_ast	**create_pipe_seq_node(t_ast **curr_node, int dir);
t_ast	**create_smpl_cmd_node(t_ast **curr_node, int dir);
void	initialize_ast_vars(t_ast_vars *ast);
void	initialize_node_states(t_state *state);
void	store_word_in_suitable_node(t_ast_vars	*vars, char *word);
void	store_redir_in_suitable_node(t_ast_vars *vars, t_tokens **token);
void	get_suitable_nodes(t_state state, t_ast_ptrs *ast_ptrs);

#endif
