/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:28:37 by iltafah           #+#    #+#             */
/*   Updated: 2021/04/02 10:19:26 by iltafah          ###   ########.fr       */
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

void print_cmd_redirection(t_node *node)
{
    t_redirection *curr_redir_node;
    char *input_file = "STDIN";
    char *output_file = "STDOUT";

    curr_redir_node = node->u_infos.redirections;
    while (curr_redir_node)
    {
        //printf("wtf [%s] wtf\n", curr_redir_node->file);
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

void print_preorder(t_node *node, int i)
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
    else if (node->tag == e_word_node)
        printf("%s%s ", YEL, node->u_infos.word);
    else if (node->tag == e_simple_cmd_node)
    {
        printf("%s\n\n>>>simple command<<<    ", CYN);
        print_cmd_redirection(node);
    }
    print_preorder(node->bottom, i);
    print_preorder(node->next, i);
}

void print_postorder(t_node *node) // I will use it to free the ast
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

void print_tokens(t_tokens *tokens)
{
    printf("MAH TOKENS BRO\n");
    int spaces = 50;
    int len;
    int spaces_time;
    char type[7][12] = {"start", "pipe", "semicolon", "word", "redir", "newline"};

    while (tokens)
    {
        if (tokens->data)
        {
            if (tokens->data[0] == '\n')
                tokens->data = "\\n";
            len = strlen(tokens->data);
            spaces_time = spaces - len;
            printf("|%s| %*s type : = %s\n", tokens->data, spaces_time, " ", type[tokens->type]);
        }
        tokens = tokens->next;
    }
}

int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    t_node *cmd_line_node = NULL;
    t_tokens *tokens_list = NULL;

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
            break;
        }
        create_abstract_syntax_tree(&cmd_line_node, tokens_list);

        //line_tokenization2(line, &mother_node);
        print_preorder(cmd_line_node, 1);

        //parse_line(&line, &mother_node);
        //////////////////////////////////print_preorder(mother_node);
    }

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

    return (0);
}
