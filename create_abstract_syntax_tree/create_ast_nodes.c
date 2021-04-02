#include "create_abstract_syntax_tree.h"

t_node *create_single_node(t_tag tag)
{
	t_node *node = malloc(sizeof(t_node));

	node->tag = tag;
	node->bottom = NULL;
	node->next = NULL;
	if (tag == e_word_node)
		node->u_infos.word = NULL;
	else if (tag == e_simple_cmd_node)
		node->u_infos.redirections = NULL;
	return (node);
}

t_node **create_word_node(t_node **curr_node, int dir)
{
	t_node **new_word_node;

	if (dir == BOTTOM)
		new_word_node = &((*curr_node)->bottom);
	else
		new_word_node = &((*curr_node)->next);
	*new_word_node = create_single_node(e_word_node);
	return (new_word_node);
}

t_node **create_pipe_seq_node(t_node **curr_node, int dir)
{
	t_node **new_pipe_seq_node;

	if (dir == BOTTOM)
		new_pipe_seq_node = &((*curr_node)->bottom);
	else
		new_pipe_seq_node = &((*curr_node)->next);
	*new_pipe_seq_node = create_single_node(e_pipeline_node);
	return (new_pipe_seq_node);
}

t_node **create_simple_cmd_node(t_node **curr_node, int dir)
{
	t_node **new_cmd_node;

	if (dir == BOTTOM)
		new_cmd_node = &((*curr_node)->bottom);
	else
		new_cmd_node = &((*curr_node)->next);
	*new_cmd_node = create_single_node(e_simple_cmd_node);
	return (new_cmd_node);
}