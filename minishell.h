#ifndef MINISHELL_H

# define MINISHELL_H
# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
# define RED "\e[1;91m"
# define GRN "\e[1;92m"
# define PRP "\e[1;95m"
# define WHT "\e[1;97m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "./get_next_line/get_next_line.h"


# define BOTTOM 0
# define NEXT 1

typedef enum {e_pipeline_node, e_simple_cmd_node, e_word_node}   t_tag;
typedef enum {e_pipe, e_semicolon, e_word}        t_type;

typedef struct                  s_redirection
{
    char                        *input_files;
    char                        *output_files;
}                               t_redirection;


typedef struct          s_node
{
    t_tag               tag;
    struct s_node       *bottom;
    struct s_node       *next;

    union               infos
    {
        char            *word;
        t_redirection   redirections;
    }                   u_infos;
    
}                       t_node;

typedef struct          s_tokens
{
    t_type              type;
    char                *data;
    struct s_tokens     *next;
}                       t_tokens;


// typedef struct  s_node_list
// {
//     t_node               *elem;
//     struct s_node_list   *next;
// }               t_node_list;


#endif