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
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include "./get_next_line/get_next_line.h"


# define BOTTOM 0
# define NEXT 1

# define TRUE 1
# define FALSE 0

# define CLOSED 0
# define OPEND 1

# define NONE 0
# define EXIST 1

# define VALID 1
# define ERROR -1

# define DOUBLE_QUOTES '"'
# define SINGLE_QUOTES '\''
# define BACKSLASH '\\'
# define PIPE '|'
# define SEMICOLON ';'

typedef enum e_tag {e_cmdline_node, e_pipeline_node, e_simple_cmd_node, e_word_node}            t_tag;
typedef enum e_type {e_start, e_pipe, e_semicolon, e_simple_word, e_redir, newline}             t_type;


// typedef enum e_special_characters
// {single_quotes = '\'', double_quotes = '"',
// backslash = '\\', semicolon = ';', pipe = '|'}
// t_special_characters;

typedef struct                  s_redirection
{
    char                        *type;
    char                        *file;
    struct s_redirection        *next;
}                               t_redirection;


// typedef struct          s_node
// {
//     t_tag               tag;
//     struct s_node       *bottom;
//     struct s_node       *next;

//     union               infos
//     {
//         char            *word;
//         t_redirection   *redirections;
//     }                   u_infos;
    
// }                       t_node;

// typedef struct			s_pipe_seq
// {
// 	char				**simple_cmd;
// 	t_redirection		*redirections;
// 	struct s_pipe_seq	*next;
// }						t_pipe_seq;

// typedef struct			s_simple_cmd
// {
// 	char				**content;
// 	int					content_size;
// 	t_redirection		*redirections;
// }						t_simple_cmd;

typedef struct          s_tokens
{
    t_type              type;
    char                *data;
    struct s_tokens     *next;
}                       t_tokens;
////////////////////////////////////////////////////

typedef struct			s_data
{
	char				**args;
	t_redirection		*redirections;
}						t_data;

typedef struct			s_dir
{
	struct s_ast		*bottom;
    struct s_ast		*next;
}						t_dir;

typedef struct          s_ast
{
    t_tag               tag;
    union               u_node
    {
		t_dir			dir;
		t_data			data;
    }                   node;
}                       t_ast;

//////////////////////////////////////////////////////




// typedef struct  s_node_list
// {
//     t_node               *elem;
//     struct s_node_list   *next;
// }               t_node_list;


void    line_tokenization(char *line, t_tokens **tokens_list);
int     check_tokens_syntax(t_tokens *tokens_list);
void    create_abstract_syntax_tree(t_ast **ast, t_tokens *tokens);
// void    line_tokenization2(char *line, t_node **mother_node);

#endif