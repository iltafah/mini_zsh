/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:28:37 by iltafah           #+#    #+#             */
/*   Updated: 2021/03/28 15:48:54 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void print_current_dir()
{
	char *curr_dir;
	int keep_index;
	int len;
	int i;

	i = 0;
	len = 0;
	keep_index = 0;
	curr_dir = getcwd(NULL, 0);
	while (curr_dir[i] != '\0')
	{
		if (curr_dir[i] == '/')
			keep_index = i + 1;
		i++;
	}
	len = i - keep_index;
	write(1, GRN, ft_strlen(GRN));
	write(1, "➜    ", 5);
	write(1, curr_dir + keep_index, len);
	write(1, " ", 1);
	free(curr_dir);
	write(1, PRP, ft_strlen(PRP));
}

void print_header()
{
	printf(CYN);
	printf("╭━╮╭━┳━━┳━╮╱╭┳━━┳━━━┳╮╱╭┳━━━┳╮╱╱╭╮   \n");
	printf("┃┃╰╯┃┣┫┣┫┃╰╮┃┣┫┣┫╭━╮┃┃╱┃┃╭━━┫┃╱╱┃┃   \n");
	printf("┃╭╮╭╮┃┃┃┃╭╮╰╯┃┃┃┃╰━━┫╰━╯┃╰━━┫┃╱╱┃┃   \n");
	printf("┃┃┃┃┃┃┃┃┃┃╰╮┃┃┃┃╰━━╮┃╭━╮┃╭━━┫┃╱╭┫┃╱╭╮\n");
	printf("┃┃┃┃┃┣┫┣┫┃╱┃┃┣┫┣┫╰━╯┃┃╱┃┃╰━━┫╰━╯┃╰━╯┃\n");
	printf("╰╯╰╯╰┻━━┻╯╱╰━┻━━┻━━━┻╯╱╰┻━━━┻━━━┻━━━╯\n");
}

t_node *create_single_node()
{
	t_node *node = malloc(sizeof(t_node));

	node->bottom = NULL;
	node->next = NULL;

	return (node);
}

t_node *create_cmdline()
{
	t_node	*node = create_single_node();

	node->tag = e_cmdline_node;

	return (node);
}

t_node *create_pipline()
{
	t_node *node = create_single_node();

	node->tag = e_pipeline_node;

	return (node);
}

t_node *create_word(char *cmd_part)
{
	t_node *node = create_single_node();

	node->tag = e_word_node;
	node->u_infos.word = cmd_part;

	return (node);
}

t_node *create_simple_command(char *input_files, char *outputfiles)
{
	t_node *node = create_single_node();

	node->tag = e_simple_cmd_node;
	node->u_infos.redirections.input_files = input_files;
	node->u_infos.redirections.output_files = outputfiles;

	return (node);
}



// t_node *create_list_of_nodes(char *lable)
// {
// 	t_node_list *node_list = malloc(sizeof(t_node_list));
// 	node_list->elem = create_single_node(lable);
// 	node_list->next = NULL;
// 	return (node_list);
// }

void print_preorder(t_node *node)
{
	static int	i = 1;

	if (node == NULL)
	{
		printf("\n");
		return;
	}
	if (node->tag == e_pipeline_node)
		printf("\n\n%s█████████ [%d]pipline █████████\n", RED, i++);
	else if (node->tag == e_word_node)
		printf("%s%s ", YEL, node->u_infos.word);
	else if (node->tag == e_simple_cmd_node)
		printf("%s\n\n>>>simple command<<<\n", CYN);
	print_preorder(node->bottom);
	print_preorder(node->next);
}

void print_postorder(t_node *node)
{
	if (node == NULL)
		return;
	print_postorder(node->bottom);
	print_postorder(node->next);
	printf("%s, ", node->u_infos.word);
}

void print_inorder(t_node *node)
{
	if (node == NULL)
		return;
	print_inorder(node->bottom);
	printf("%s, ", node->u_infos.word);
	print_inorder(node->next);
}

// void	fill_tree(char *line, t_node **mother_node)
// {
// 	t_node	*curr_pipe_node;
// 	t_node	*curr_cmd_node;
// 	t_node	*curr_word_node;

// 	///supouse that the line doesn't have any errors
// 		curr_cmd_node = (*mother_node)->bottom;
// 		curr_cmd_node = create_simple_command(NULL, NULL);

// 		////////
// 		curr_word_node = curr_cmd_node->bottom;

// 		curr_word_node = create_word("ls");
// 		curr_word_node = curr_word_node->next;
// 		curr_word_node = create_word("-l");
// 		curr_word_node = curr_word_node->next;
// 		curr_word_node = create_word("-a");
// 		////////

// 		curr_cmd_node = curr_cmd_node->next;
// 		curr_cmd_node = create_simple_command(NULL, NULL);

// 		////////
// 		curr_word_node = curr_cmd_node->bottom;

// 		curr_word_node = create_word("sleep");
// 		curr_word_node = curr_word_node->next;
// 		curr_word_node = create_word("10");
// 		curr_word_node = curr_word_node->next;
// 		curr_word_node = create_word("20");
// 		////////

// 		curr_cmd_node = curr_cmd_node->next;
// 		curr_cmd_node = create_simple_command(NULL, NULL);

// 		////////
// 		curr_word_node = curr_cmd_node->bottom;

// 		curr_word_node = create_word("sleep");
// 		curr_word_node = curr_word_node->next;
// 		curr_word_node = create_word("10");
// 		curr_word_node = curr_word_node->next;
// 		curr_word_node = create_word("20");
// 		////////
// }

void fill_pipeline(t_node **curr_pipeline_node)
{
	*curr_pipeline_node = create_pipline();
}


void fill_cmd_node(t_node **curr_cmd_node)
{
	*curr_cmd_node = create_simple_command(NULL, NULL);
}

void fill_word_node(t_node **curr_word_node, char *word)
{
	*curr_word_node = create_word(word);
}


//////////////////////////////////////////////
t_node **get_next_node(t_node **curr_node)
{
	return (&((*curr_node)->next));
}

t_node **get_bottom_node(t_node **curr_node)
{
	return (&((*curr_node)->bottom));
}
//////////////////////////////////////////////

t_node **get_node(t_node **curr_node, int dir)
{
	if (dir == BOTTOM)
		return (&((*curr_node)->bottom));
	return (&((*curr_node)->next));
}

char *get_token_dnt_need_this(char **line)
{
	int i;
	int len;
	char *ptr;

	i = 0;
	len = 0;
	ptr = *line;
	while (ptr[i])
	{
		if (ptr[i] == '|')
		{
			*line = *line + i + 1;
			return (ft_substr(ptr, i, 1));
		}
		else if (ptr[i] == '"')
		{
			i++;
			len = 0;
			while (ptr[i + len] != '"' && ptr[i + len] != '\0')
				len++;
			if (ptr[i + len] == '\0')
				printf("syntax error\n");
			*line = *line + i + len;
			return (ft_substr(ptr, i, len));
		}
		else if (ptr[i] != ' ')
		{
			len = 0;
			while (ptr[i + len] != ' ' && ptr[i + len] != '\0' && ptr[i + len] != '|')
				len++;
			*line = *line + i + len;
			return (ft_substr(ptr, i, len));
		}
		i++;
	}
	return (*line);
}

void parse_line(char **line, t_node **mother_node)
{
	t_node **curr_cmd_node;
	t_node **curr_word_node;
	char *token;
	int new_cmd_node;

	*mother_node = create_pipline();
	curr_cmd_node = mother_node;

	curr_cmd_node = get_node(curr_cmd_node, BOTTOM);
	fill_cmd_node(curr_cmd_node);

	token = get_token_dnt_need_this(line);
	curr_word_node = get_node(curr_cmd_node, BOTTOM);
	fill_word_node(curr_word_node, token);

	printf("%s\nTokens given from the cmd line : \n\n|%s|    \n", WHT, token);
	while ((*line)[0] != '\0')
	{
		token = get_token_dnt_need_this(line);
		if (strcmp(token, "|") == 0)
		{
			curr_cmd_node = get_node(curr_cmd_node, NEXT);
			fill_cmd_node(curr_cmd_node);
			new_cmd_node = 1;
		}
		else if (token[0] != '\0')
		{
			if (new_cmd_node)
			{
				curr_word_node = get_node(curr_cmd_node, BOTTOM);
				new_cmd_node = 0;
			}
			else
				curr_word_node = get_node(curr_word_node, NEXT);
			fill_word_node(curr_word_node, token);
		}
		printf("|%s|    \n", token);
	}
}
////////////////////////////////////////////////////////////////////////////////



void print_tokens(t_tokens *tokens)
{
	printf("MAH TOKENS BRO\n");
	int		spaces = 50;
	int		len;
	int		spaces_time;
	char	type[7][12] = {"start", "pipe", "semicolon", "word", "redir", "newline"};
	
	while (tokens)
	{
		if (tokens->data)
		{
			if (tokens->data[0] == '\n')
				tokens->data = "\\n";
			len = strlen(tokens->data);
			spaces_time = spaces - len;
			printf("|%s| %*s type : = %s\n",tokens->data,  spaces_time, " ", type[tokens->type]);
		}
		tokens = tokens->next;
	}
}

/////////////////////////////////////
// int		count_dquotes(char *line)
// {
// 	int		i;
// 	int		count;
// 	int		backslash;
// 	int		single_quotes;

// 	i = 0;
// 	count = 0;
// 	backslash = 0;
// 	single_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\\')
// 			backslash = 1;
// 		else
// 			backslash = 0;
			
// 		if (line[i] == '\'' && backslash == 0)

		
// 		if (line[i] == '"' && backslash == 0)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// int		count_squotes(char *line)
// {
// 	int		i;
// 	int		backslash;
// 	int		double_quotes;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	backslash = 0;
// 	double_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\\')
// 			backslash = 1;
// 		else
// 			backslash = 0;
// 		if (line[i] == '\'')
// 			double_quotes = 1;
// 		else
// 			double_quotes = 0;
// 		if (line[i] == '\'')
// 			count++;
// 		i++;
// 	}
// 	return (0);
// }

////////////////////////////////////////////////////////////////////////////////
// int		check_if_dquotes_closed(char *line, int *index)
// {
// 	int		i;
// 	int		backslash;

// 	i = 1;
// 	backslash = 0;
// 	while (line[i] != '\0' && (line[i] != '"' || backslash == 1))
// 	{
// 		if (line[i] == '\\' && backslash == 0)
// 			backslash = 1;
// 		else
// 			backslash = 0;
// 		i++;
// 	}
// 	*index += i;
// 	if (line[i] == '"')
// 		return (1);
// 	return (0);
// }

// int		check_double_quotes(char *line)
// {
// 	int		i;
// 	int		closed;
// 	int		backslash;

// 	i = 0;
// 	closed = 1;
// 	backslash = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '"' && backslash == 0)
// 		{
// 			closed = check_if_dquotes_closed(line + i, &i);
// 			if (closed == 0)
// 				return (-1);
// 		}
// 		if (line[i] == '\\' && backslash == 0)
// 			backslash = 1;
// 		else
// 			backslash = 0;
// 		i++;
// 	}
// 	return (1);
// }


// int		check_if_squotes_closed(char *line, int *index)
// {
// 	int		i;
// 	int		backslash;

// 	i = 1;
// 	backslash = 0;
// 	while (line[i] != '\0' && line[i] != '\'')
// 		i++;
// 	*index += i;
// 	if (line[i] == '\'')
// 		return (1);
// 	return (0);
// }

// int		check_single_quotes(char *line)
// {
// 	int		i;
// 	int		closed;
// 	int		backslash;

// 	i = 0;
// 	closed = 1;
// 	backslash = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'' && backslash == 0)
// 		{
// 			closed = check_if_squotes_closed(line + i, &i);
// 			if (closed == 0)
// 				return (-1);
// 		}
// 		if (line[i] == '\\' && backslash == 0)
// 			backslash = 1;
// 		else
// 			backslash = 0;
// 		i++;
// 	}
// 	return (1);
// }

// int		check_syntax_error(char *line)
// {
// 	if (check_double_quotes(line) == -1 || check_single_quotes(line) == -1)
// 	{
// 		printf("> Error: multiline commands not allowed\n");
// 		return (-1);
// 	}	
// 	return (0);
// }


////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv, char **env)
{
	char *line;
	t_node *cmd_line_node;
	t_tokens *tokens_list;

	print_header();
	while (1337)
	{
		print_current_dir();
		get_next_line(0, &line);
		printf("\ncmd line given : >%s<\n", line);


		line_tokenization(line, &tokens_list);
		print_tokens(tokens_list);
		if (check_tokens_syntax(tokens_list) == ERROR)
		{
			//free_token_list();
			//free_line();
			continue ;
		}
		create_abstract_syntax_tree(&cmd_line_node, tokens_list);


		//line_tokenization2(line, &mother_node);
		print_preorder(cmd_line_node);

		//parse_line(&line, &mother_node);
		//////////////////////////////////print_preorder(mother_node);
	}

	// ////word///
	// curr_word_node = get_bottom_node(curr_cmd_node);///
	// fill_word_node(curr_word_node, "ls");///
	// curr_word_node = get_next_node(curr_word_node);///
	// fill_word_node(curr_word_node, "-l");///
	// curr_word_node = get_next_node(curr_word_node);///
	// fill_word_node(curr_word_node, "-a");///
	// ///////////

	// curr_cmd_node = get_next_node(curr_cmd_node);
	// fill_cmd_node(curr_cmd_node);

	// ////word///
	// curr_word_node = get_bottom_node(curr_cmd_node);///
	// fill_word_node(curr_word_node, "sleep");///
	// curr_word_node = get_next_node(curr_word_node);///
	// fill_word_node(curr_word_node, "10");///
	// ///////////

	// curr_cmd_node = get_next_node(curr_cmd_node);
	// fill_cmd_node(curr_cmd_node);

	// ///word///
	// curr_word_node = get_bottom_node(curr_cmd_node);///
	// fill_word_node(curr_word_node, "cat");///
	// curr_word_node = get_next_node(curr_word_node);///
	// fill_word_node(curr_word_node, "-e");///
	// curr_word_node = get_next_node(curr_word_node);///
	// fill_word_node(curr_word_node, "file1");///
	// ///////////

	// print_preorder(mother_node);

	// next_cmd_node = NULL;
	// curr_cmd_node = next_cmd_node;
	//fill_cmd_node(curr_cmd_node, next_cmd_node);
	// printf(">%d<\n", mother_node->bottom->next->tag);

	// t_node	**curr_cmd_node;
	// curr_cmd_node = &(mother_node->bottom);
	// *curr_cmd_node = create_simple_command(NULL, NULL);
	// printf(">%d<\n", mother_node->bottom->tag);

	// t_node *mother_node = create_pipline();

	// mother_node->bottom = create_simple_command(NULL, NULL);
	// mother_node->bottom->next = create_simple_command(NULL, NULL);
	// mother_node->bottom->next->next = create_simple_command(NULL, NULL);

	// mother_node->bottom->bottom = create_word("ls");
	// mother_node->bottom->bottom->next = create_word("-l");
	// mother_node->bottom->bottom->next->next = create_word("-a");

	// mother_node->bottom->next->bottom = create_word("sleep 16");

	// mother_node->bottom->next->next->bottom = create_word("cat");
	// mother_node->bottom->next->next->bottom->next = create_word("-e");

	// char	*str = strdup("\n");
	// ///////execute cat command example//////////////
	// char	**newargv = malloc(sizeof(char*) * 4);	//
	// newargv[0] = strdup("/bin/cat");				//
	// newargv[1] = strdup("file");			//
	// newargv[2] = strdup("file1");			//
	// newargv[3] = strdup("minishell.h");
	// newargv[4] = 0;								//
	// execve("/bin/cat", newargv, env);			//
	// ////////////////////////////////////////////////

	return (0);
}
