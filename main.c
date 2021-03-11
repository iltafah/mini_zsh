/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:28:37 by iltafah           #+#    #+#             */
/*   Updated: 2021/03/11 18:59:35 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	print_current_dir()
{
	char	*curr_dir;
	int		keep_index;
	int		len;
	int		i;

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
	write(1, YEL, ft_strlen(YEL));
	write(1, "➜    ", 5);
	write(1, curr_dir + keep_index, len);
	write(1, " ", 1);
	free(curr_dir);
	write(1, RED, ft_strlen(RED));
}

void	print_header()
{
	printf("\e[1;96m");
	printf("╭━╮╭━┳━━┳━╮╱╭┳━━┳━━━┳╮╱╭┳━━━┳╮╱╱╭╮   \n");
	printf("┃┃╰╯┃┣┫┣┫┃╰╮┃┣┫┣┫╭━╮┃┃╱┃┃╭━━┫┃╱╱┃┃   \n"); 
	printf("┃╭╮╭╮┃┃┃┃╭╮╰╯┃┃┃┃╰━━┫╰━╯┃╰━━┫┃╱╱┃┃   \n"); 
	printf("┃┃┃┃┃┃┃┃┃┃╰╮┃┃┃┃╰━━╮┃╭━╮┃╭━━┫┃╱╭┫┃╱╭╮\n"); 
	printf("┃┃┃┃┃┣┫┣┫┃╱┃┃┣┫┣┫╰━╯┃┃╱┃┃╰━━┫╰━╯┃╰━╯┃\n"); 
	printf("╰╯╰╯╰┻━━┻╯╱╰━┻━━┻━━━┻╯╱╰┻━━━┻━━━┻━━━╯\n");
}

t_node	*create_single_node()
{
	t_node *node = malloc(sizeof(t_node));
	
	node->bottom = NULL;
	node->next = NULL;
	
	return (node);
}

t_node	*create_pipline()
{
	t_node *node = create_single_node();

	node->e_tag = pipeline;
	

	return (node);
}

t_node	*create_word(char *cmd_part)
{
	t_node *node = create_single_node();
	
	node->e_tag = word;
	node->u_infos.word = cmd_part;

	return (node);
}

t_node	*create_simple_command(char *input_files, char *outputfiles)
{
	t_node *node = create_single_node();
	
	node->e_tag = simple_cmd;
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

void	print_preorder(t_node *node)
{
	if (node == NULL)
	{
		printf("\n");
		return ;
	}
	if (node->e_tag == pipeline)
		printf(">>>>>> pipline <<<<<<\n");
	else if (node->e_tag == word)
		printf("%s ", node->u_infos.word);
	else if (node->e_tag == simple_cmd)
		printf("\n\n>>>simple command<<<\n");
	print_preorder(node->bottom);
	print_preorder(node->next);
}

void	print_postorder(t_node *node)
{
	if (node == NULL)
		return ;
	print_postorder(node->bottom);
	print_postorder(node->next);
	printf("%s, ", node->u_infos.word);
}

void	print_inorder(t_node *node)
{
	if (node == NULL)
		return ;
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

void	fill_cmd_node(t_node **curr_cmd_node)
{
	*curr_cmd_node = create_simple_command(NULL, NULL);
}

void	fill_word_node(t_node **curr_word_node, char *word)
{
	*curr_word_node = create_word(word);
}



//////////////////////////////////////////////
t_node	**get_next_node(t_node **curr_node)
{
	return (&((*curr_node)->next));
}

t_node	**get_bottom_node(t_node **curr_node)
{
	return (&((*curr_node)->bottom));
}
//////////////////////////////////////////////



t_node	**get_node(t_node **curr_node, int dir)
{
	if (dir == BOTTOM)
		return (&((*curr_node)->bottom));
	return (&((*curr_node)->next));
}

char	*get_token(char **line)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	len = 0;
	ptr = *line;
	while (ptr[i])
	{
		if (ptr[i] != ' ' && ptr[i] != '|')
		{
			len = 0;
			while (ptr[i + len] != ' ' && ptr[i + len] != '\0' && ptr[i + len] != '|')
				len++;
			*line = *line + i + len;
			return (ft_substr(ptr, i, len));
		}
		else if (ptr[i] == '|')
		{
			*line = *line + i + 1;
			return (ft_substr(ptr, i, 1));
		}
		i++;
	}
	return (*line);
}

void	fill_ast(char **line)
{
	t_node	*mother_node;
	t_node	**curr_cmd_node;
	t_node	**curr_word_node;
	char	*token;
	int		dir;
	
	mother_node = create_pipline();
	curr_cmd_node = &mother_node;

	curr_cmd_node = get_node(curr_cmd_node, BOTTOM);
	fill_cmd_node(curr_cmd_node);
	
	token = get_token(line);
	curr_word_node = get_node(curr_cmd_node, BOTTOM);
	fill_word_node(curr_word_node, token);


	//printf("%s    \n",token);
	while ((*line)[0] != '\0')
	{
		token = get_token(line);
		if (strcmp(token, "|") == 0)
		{
			curr_cmd_node = get_node(curr_cmd_node, NEXT);
			fill_cmd_node(curr_cmd_node);

			curr_word_node = get_node(curr_cmd_node, BOTTOM);
			fill_word_node(curr_word_node, token);
		}
		else if (token != NULL)
		{
			curr_word_node = get_node(curr_word_node, NEXT);
			fill_word_node(curr_word_node, token);
		}
		printf("|%s|    \n", token);
		sleep(1);
	}



	print_preorder(mother_node);

}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	

	

	print_header();
	while (1337)
	{
		print_current_dir();
		get_next_line(0, &line);
		printf(">%s<\n", line);
		

		fill_ast(&line);

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
	// printf(">%d<\n", mother_node->bottom->next->e_tag);

	
	// t_node	**curr_cmd_node;
	// curr_cmd_node = &(mother_node->bottom);
	// *curr_cmd_node = create_simple_command(NULL, NULL);
	// printf(">%d<\n", mother_node->bottom->e_tag);
		
	

	
	
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

	

	/////////execute cat command example//////////////	
	// char	**newargv = malloc(sizeof(char*) * 4);	//
	// newargv[0] = strdup("/bin/cat");				//
	// newargv[1] = strdup("main.c");				//
	// newargv[2] = strdup("minishell.h");			//
	// newargv[3] = 0;								//
	// execve("/bin/cat", newargv, env);			//
	//////////////////////////////////////////////////

	



	

	return (0);
}
