/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:28:37 by iltafah           #+#    #+#             */
/*   Updated: 2021/04/15 13:43:44 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

////////////////////////////////////////////////////////////////////////////////

// void	fill_table(char **table, int size)
// {

// }

// char	*get_the_first_command(t_node *node, int first, char **table, int size)
// {
// 	if (node->tag == e_pipeline_node && first)
// 		first = 0;
// 	else if (node->tag == e_pipeline_node && !first)
// 		return ;
// 	else if (node->tag == e_simple_cmd_node)
// 	{
// 		size++;
// 		fill_table(table, size);
// 	}
// 	get_the_first_command(node->bottom, first, table, size);
// 	get_the_first_command(node->next, first, table, size);
// }
////////////////////////////////////////////////////////////////////////////////
// t_node *get_first_pipe_seq(t_node *cmd_line_node)
// {
// 	return (cmd_line_node->bottom);
// }

// t_node *get_first_simple_cmd(t_node *pipe_seq_node)
// {
// 	return (pipe_seq_node->bottom);
// }

// t_node *get_first_word(t_node *simple_cmd_node)
// {
// 	return (simple_cmd_node->bottom);
// }

// void print_words(t_node *node)
// {
//     if (node == NULL)
//     {
//         printf("\n");
//         return ;
//     }
//     printf("%s%s ", YEL, node->u_infos.word);
//     print_words(node->next);
// }

// void	fill_content_with_curr_word(char *word, t_simple_cmd *simple_cmd)
// {
// 	int		i;
// 	char	**new_content;

// 	i = 0;
// 	new_content = malloc(sizeof(char*) * (simple_cmd->content_size + 1 + 1));
// 	while (i < simple_cmd->content_size)
// 	{
// 		new_content[i] = ft_strdup(simple_cmd->content[i]);
// 		printf("%s\n",new_content[i]);
// 		i++;
// 	}
// 	new_content[i] = ft_strdup(word);
// 	printf("%s\n",new_content[i]);
// 	new_content[++i] = NULL;

// 	while (i < simple_cmd->content_size)
// 	{
// 		free(simple_cmd->content[i]);
// 		i++;
// 	}
// 	free(simple_cmd->content);

// 	simple_cmd->content = new_content;

// 	// printf("%s%d\n",WHT,simple_cmd->content_size);
// 	// for (int i = 0; i < simple_cmd->content_size; i++)
// 	// {
// 	// 	printf("%s\n", simple_cmd->content[i]);
// 	// 	i++;
// 	// }
// 	 printf("---------\n");
// }

// void	store_words(t_node *words, t_simple_cmd *simple_cmd)
// {
// 	if (words == NULL)
// 		return ;

// 	fill_content_with_curr_word(words->u_infos.word, simple_cmd);
// 	simple_cmd->content_size += 1;
// 	store_words(words->next, simple_cmd);
// }

// char	**array_of_pointers_to_string_join(char **array, int size, char *string)
// {
// 	int		i;
// 	char	**new_array;

// 	i = 0;
// 	new_array = malloc(sizeof(char*) * (size + 1 + 1));
// 	while (i < size)
// 		new_array[i++] = ft_strdup(string);

// 	new_array[i] = ft_strdup(string);
// 	new_array[++i] = NULL;
// 	return (new_array);
// }

/*
** ************************************************************************** **
*/

// void	store_words(t_node *words, t_pipe_seq *curr_pipe_seq, int size)
// {
// 	t_node		*curr_word;
// 	int			i;

// 	i = 0;
// 	curr_pipe_seq = malloc(sizeof(t_pipe_seq));
// 	curr_pipe_seq->simple_cmd = malloc(sizeof(char*) * (size + 1));
// 	curr_word = words;
// 	while (curr_word)
// 	{
// 		curr_pipe_seq->simple_cmd[i++] = curr_word->u_infos.word;
// 		curr_word = curr_word->next;
// 	}
// 	curr_pipe_seq->simple_cmd[i] = NULL;
// }

// int		count_words_num(t_node *curr_word)
// {
// 	int		size;

// 	size = 0;
// 	while (curr_word)
// 	{
// 		size++;
// 		curr_word = curr_word->next;
// 	}
// 	return (size);
// }

// t_pipe_seq	**get_next_pipe_seq_node(t_pipe_seq *node)
// {
// 	return (&(node->next));
// }

// t_pipe_seq	*get_curr_pipe_line_seq(t_node *cmd_line_node)
// {
// 	t_node			*curr_ast_pipe_seq = cmd_line_node->bottom;
// 	t_node			*curr_ast_simple_cmd = curr_ast_pipe_seq->bottom;
// 	t_node			*curr_ast_word;

// 	t_pipe_seq		*pipe_seq_list = NULL;
// 	t_pipe_seq		**curr_pipe_seq = &pipe_seq_list;

// 	int				size;

// 	while (curr_ast_simple_cmd)
// 	{
// 		curr_ast_word = curr_ast_simple_cmd->bottom;

// 		size = count_words_num(curr_ast_word);
// 		store_words(curr_ast_word, *curr_pipe_seq, size);

// 		curr_ast_simple_cmd = curr_ast_simple_cmd->next;
// 		curr_pipe_seq = get_next_pipe_seq_node(*curr_pipe_seq);
// 	}
// 	(*curr_pipe_seq) = NULL;
// 	return (pipe_seq_list);
// }

/*
** ************************************************************************** **
*/

// t_node *get_first_simple_cmd(t_node *node)
// {
// 	if (node->bottom == NULL)
// 		return (NULL);
// 	return (node->bottom->bottom->bottom);
// }

// t_node *get_first_simple_cmd(t_node *node, t_simple_cmd *simple_cmd)
// {
// 	if (node->tag == e_simple_cmd_node)
// 	{
// 		simple_cmd->redirections = node->u_infos.redirections;
// 		get_first_simple_cmd(node->bottom, simple_cmd);
// 	}
// 	else if (node->tag == e_word_node)
// 		fill_simple_cmd_table(simple_cmd->simple_cmd_table);
// 	get_first_simple_cmd(node->next, simple_cmd);
// }

// /*
// ** ************************************************************************** **
// */

// void	free_first_command_form_ast(t_node *cmd_line_node)
// {

// }

/*
** ************************************************************************** **
*/

// void print_preorder(t_node *node, int i)
// {
//     if (node == NULL)
//     {
//         printf("\n");
//         return ;
//     }
//     if (node->tag == e_cmdline_node)
//         printf("\n\n%s   »»»»» Command line «««««\n", GRN);
//     else if (node->tag == e_pipeline_node)
//         printf("\n\n%s█████████ [%d] pipline █████████\n", RED, i++);
//     else if (node->tag == e_word_node)
//         printf("%s%s ", YEL, node->u_infos.word);
//     else if (node->tag == e_simple_cmd_node)
//     {
//         printf("%s\n\n>>>simple command<<<    ", CYN);
//         print_cmd_redirection(node);
//     }
//     print_preorder(node->bottom, i);
//     print_preorder(node->next, i);
// }

// void print_postorder(t_node *node) // I will use it to free the ast
// {
//     if (node == NULL)
//         return;
//     print_postorder(node->bottom);
//     print_postorder(node->next);
//     printf("%s, ", node->u_infos.word);
// }

// void print_inorder(t_node *node)
// {
//     if (node == NULL)
//         return;
//     print_inorder(node->bottom);
//     printf("%s, ", node->u_infos.word);
//     print_inorder(node->next);
// }

/*
** ************************************************************************** **
							printing functions
** ************************************************************************** **
*/

void print_cmd_redirection(t_ast *data_node)
{
	t_redirection *curr_redir_node;
	char *input_file = "STDIN";
	char *output_file = "STDOUT";

	curr_redir_node = data_node->node.data.redirections;
	while (curr_redir_node)
	{
		if (strcmp(curr_redir_node->type, ">") == 0 || strcmp(curr_redir_node->type, ">>") == 0)
			output_file = curr_redir_node->file;
		else if (strcmp(curr_redir_node->type, "<") == 0)
			input_file = curr_redir_node->file;
		curr_redir_node = curr_redir_node->next;
	}
	printf("%sredirections:  Input file = [%s%s%s]  , Output file = [%s%s%s]\n",
		   WHT,
		   YEL, input_file, WHT,
		   YEL, output_file, WHT);
}

void print_tokens(t_tokens *tokens)
{
	int spaces = 50;
	int len;
	int spaces_time;
	char type[7][12] = {"start", "pipe", "semicolon", "word", "redir", "newline"};

	while (tokens)
	{
		printf("%s", WHT);
		if (tokens->data)
		{
			if (tokens->data[0] == '\n')
				tokens->data = "\\n";
			len = strlen(tokens->data);
			spaces_time = spaces - len;
			printf("|%s%s%s| %*s type : = %s%s\n", CYN, tokens->data, WHT,
				   spaces_time, " ", YEL, type[tokens->type]);
		}
		tokens = tokens->next;
	}
}

void print_preorder(t_ast *node, int i)
{
	if (node == NULL)
	{
		printf("\n");
		return;
	}
	if (node->tag == e_cmdline_node)
		printf("\n\n%s   »»»»» Command line «««««\n", GRN);
	else if (node->tag == e_pipeline_node)
		printf("\n\n%s█████████ [%d] pipline █████████\n", RED, i++);
	else if (node->tag == e_data_node)
	{
		int i;

		print_cmd_redirection(node);
		i = 0;
		if (node->node.data.args != NULL)
			while (node->node.data.args[i])
				printf("%s%s \n", YEL, node->node.data.args[i++]);
		printf("\n");
		return;
	}
	else if (node->tag == e_simple_cmd_node)
	{
		printf("%s\n\n>>>simple command<<<    ", CYN);
	}
	print_preorder(node->node.dir.bottom, i);
	print_preorder(node->node.dir.next, i);
}

/*
** ************************************************************************** **
*/

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
	write(1, WHT, ft_strlen(WHT));
}

void print_header()
{
	printf(CYN);
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}



/*
** ************************************************************************** **
** ************************************************************************** **
*/
t_ast *get_curr_pipeline_seq_node(t_ast *ast)
{
	static t_ast	*curr_pipeline_seq = NULL;
	static int		first = 1;

	if (ast)
	{
		if (first == 1)
			curr_pipeline_seq = ast->node.dir.bottom;
		else if (curr_pipeline_seq != NULL)
			curr_pipeline_seq = curr_pipeline_seq->node.dir.next;
		first++;
	}
	return (curr_pipeline_seq);
}

t_ast *get_curr_smpl_cmd_node(t_ast *pipeline_seq)
{
	static t_ast	*curr_smpl_cmd = NULL;
	static int		first = 1;

	if (pipeline_seq)
	{
		if (first == 1)
			curr_smpl_cmd = pipeline_seq->node.dir.bottom;
		else if (curr_smpl_cmd != NULL)
			curr_smpl_cmd = curr_smpl_cmd->node.dir.next;
		first++;
	}
	if (curr_smpl_cmd == NULL)
		first = 1;
	return (curr_smpl_cmd);
}

void	print_args(t_ast *data_node)
{
	int		i;
	int		len;
	int		max_len;
	char	**args;

	i = 0;
	len = 0;
	max_len = 0;
	args = data_node->node.data.args;
	printf("%s[\n%s", PRP,WHT);
	while (args[i])
	{
		len = printf("  %s\n", args[i++]);
		if (max_len < len)
			max_len = len;
	}
	printf("%*s",max_len, "");
	printf("%s]\n", PRP);
	printf("---------------------------------------------------------------\n\n");
}

void	execute_test(t_ast *ast)
{
	t_ast *curr_pipeline_seq;
	t_ast *curr_simple_cmd;
	t_ast *curr_data_node;

	curr_pipeline_seq = get_curr_pipeline_seq_node(ast);
	while (curr_pipeline_seq)
	{	
		curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
		printf("%s ╔███████████████████████ Pipeline ███████████████████████╗\n\n",RED);
		while (curr_simple_cmd)
		{
			curr_data_node = curr_simple_cmd->node.dir.bottom;
			print_cmd_redirection(curr_data_node);
			print_args(curr_data_node);
			curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
		}
		curr_pipeline_seq = get_curr_pipeline_seq_node(ast);
	}
}
/*
** ************************************************************************** **
** ************************************************************************** **
*/


int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	t_tokens *tokens_list = NULL;
	t_ast *ast = NULL;

	print_header();
	while (1337)
	{
		print_current_dir();
		get_next_line(0, &line);

		line_tokenization(line, &tokens_list);
		print_tokens(tokens_list);
		if (check_tokens_syntax(tokens_list) == ERROR)
		{
			free_tokens_list(&tokens_list);
			free(line);
			continue;
		}
		create_abstract_syntax_tree(&ast, tokens_list);
		print_preorder(ast, 1);
		//execute_test(ast);
		/////////////////////////////////
		/**		  freeing time		**///
		/////////////////////////////////
		free_tokens_list(&tokens_list);//
		free_abstract_syntax_tree(ast);//
		free(line);					   //
		/////////////////////////////////
	}
	return (0);
}

/*
** ************************************************************************** **
*/
// data fiha (char **args  && t_redirection *redirections)
// data = get_the_first_cmd();
// then the executer will execute the first cmd using data
// free data and free it also from ast
// then let the cmd_line_node->pipe_seq_node point to the next cmd if it exist
// but what will happend if it doesn't exist ??!! Hmmmm
// if (cmd_line->pipe_seq_node->bottom == NULL) => then simply there is no pipe |
// if (cmd->line->pipe_seq_node->NEXT == NULL) => then simply there is no semicolon ;
// but if (cmd_line->pipe_seq_node->bottom != NULL) => then there is a pipe xd
// how silly me, but if there is a pipe what will you do
// of course get the next focking simple cmd

/*
** ************************************************************************** **
*/
//char	*str = strdup("\n");
// ///////execute cat command example//////////////
// char	**newargv = malloc(sizeof(char*) * 4);	//
// newargv[0] = strdup("cat");				//
// newargv[1] = strdup("file");			//
// newargv[2] = strdup("file1");			//
// newargv[3] = strdup("file2");
// newargv[4] = 0;								//

// execve("/bin/cat", newargv, env);			//
// ////////////////////////////////////////////////