#ifndef MINISHELL_H

# define MINISHELL_H
# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
# define RED "\e[1;91m"



# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "./get_next_line/get_next_line.h"


# define BOTTOM 0
# define NEXT 1

typedef enum {pipeline, simple_cmd, word} t_tag;

typedef struct                  s_redirection
{
    char                        *input_files;
    char                        *output_files;
}                               t_redirection;


typedef struct          s_node
{
    t_tag               e_tag;
    struct s_node       *bottom;
    struct s_node       *next;

    union               infos
    {
        char            *word;
        t_redirection   redirections;
    }                   u_infos;
    
}                       t_node;

// typedef struct  s_node_list
// {
//     t_node               *elem;
//     struct s_node_list   *next;
// }               t_node_list;


#endif