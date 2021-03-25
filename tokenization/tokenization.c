#include "tokenization.h"

t_tokens *create_single_token(char *data, t_type type)
{
	t_tokens *token_node;

	token_node = malloc(sizeof(t_tokens));
	token_node->data = data;
	token_node->type = type;
	token_node->next = NULL;
	return (token_node);
}

char *get_token(char **line, t_type *type)
{
	char *token;

	token = NULL;
	if (**line == '|')
		token = get_pipe(line, type);
	else if (**line == ';')
		token = get_semicolon(line, type);
	else if (**line == '>' || **line == '<')
		token = get_redirection(line, type);
	else if (**line != ' ' && **line != '\0')
		token = get_simple_word(line, type);
	return (token);
}

void line_tokenization(char *line, t_tokens **tokens_list)
{
	char *token;
	t_type type;
	t_tokens *curr_token;

	*tokens_list = create_single_token(NULL, e_start);
	curr_token = *tokens_list;

	while (*line)
	{
		if (*line == ' ')
			line++;
		else
		{
			token = get_token(&line, &type);
			curr_token->next = create_single_token(token, type);
			curr_token = curr_token->next;
		}
	}
}

// void	line_tokenization2(char *line, t_node **cmdline_node)
// {
// 	char	*token;
// 	t_type	type;
// 	t_node	**curr_cmd_node;
// 	t_node	**curr_word_node;
// 	t_node	**curr_pipeline;
// 	int		first_word_node;
// 	int		first_cmd_node;

// 	first_word_node = 1;
// 	first_cmd_node = 1;
// 	*cmdline_node = create_single_node();
	
// 	curr_pipeline = get_node(cmdline_node, BOTTOM);
// 	fill_pipeline(curr_pipeline);

// 	//curr_cmd_node = get_node(curr_pipeline, BOTTOM);
// 	//fill_cmd_node(curr_cmd_node);

	
// 	while (*line)
// 	{
// 		if (*line == ' ')
// 			line++;
// 		else
// 		{
// 			token = get_token(&line, &type);
// 			if (type == e_simple_word)
// 			{	if (first_word_node)
// 					curr_word_node = get_node(curr_cmd_node, BOTTOM);
// 				else
// 					curr_word_node = get_node(curr_word_node, NEXT);
				
// 				fill_word_node(curr_word_node, token);
// 				first_word_node = 0;
// 			}
// 			else if (type == e_semicolon)
// 			{
// 				curr_pipeline = get_node(curr_pipeline, NEXT);
// 				fill_pipeline(curr_pipeline);
// 			}
// 		}
// 	}
// }