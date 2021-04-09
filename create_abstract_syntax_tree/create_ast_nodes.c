#include "create_abstract_syntax_tree.h"

t_ast *create_single_node(t_tag tag)
{
	t_ast *node = malloc(sizeof(t_ast));

	node->tag = tag;
	if (tag == e_word_node)
	{
		node->node.data.args = NULL;
		node->node.data.redirections = NULL;
	}
		// node->u_infos.word = NULL;
	else
	{
		node->node.dir.bottom = NULL;
		node->node.dir.next = NULL;
	}
		// node->u_infos.redirections = NULL;
	return (node);
}

t_ast **create_word_node(t_ast **simple_cmd, int dir)
{
	t_ast **new_word_node;

	if (dir == BOTTOM)
		new_word_node = &((*simple_cmd)->node.dir.bottom);
	else
		new_word_node = &((*simple_cmd)->node.dir.next);
	*new_word_node = create_single_node(e_word_node);
	return (new_word_node);
}

t_ast **create_pipe_seq_node(t_ast **cmd_line, int dir)
{
	t_ast **new_pipe_seq_node;

	if (dir == BOTTOM)
		new_pipe_seq_node = &((*cmd_line)->node.dir.bottom);
	else
		new_pipe_seq_node = &((*cmd_line)->node.dir.next);
	*new_pipe_seq_node = create_single_node(e_pipeline_node);
	return (new_pipe_seq_node);
}

t_ast **create_simple_cmd_node(t_ast **pipe_line_seq, int dir)
{
	t_ast **new_cmd_node;

	if (dir == BOTTOM)
		new_cmd_node = &((*pipe_line_seq)->node.dir.bottom);
	else
		new_cmd_node = &((*pipe_line_seq)->node.dir.next);
	*new_cmd_node = create_single_node(e_simple_cmd_node);
	return (new_cmd_node);
}