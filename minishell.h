#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

# include "./vectors/vectors.h"
# include "./parser/parser.h"
# include "./libft/libft.h"
# include "./freeing_time/freeing_time.h"
# include "./get_next_line/get_next_line.h"
# include "./readline/readline.h"

typedef struct s_gvars
{
	t_rdline		rdl_vars;
	t_env_table		env_table;
}				t_gvars;

extern t_gvars		g_vars;

t_gvars	g_vars;

void	expand_curr_cmd(t_ast *curr_simple_cmd, t_env_table env_table);
int		check_tokens_syntax(t_tokens *tokens_list);
void	line_tokenization(char *line, t_tokens **tokens_list);
void	create_abstract_syntax_tree(t_ast **ast, t_tokens *tokens);
void	free_tokens_list(t_tokens **tokens_list);
void	free_abstract_syntax_tree(t_ast *ast);

char	*get_prompt_name(void);
char	*get_curr_dir_name(void);
int		ft_strlen_utf8(char *str);


#endif















// typedef enum e_special_characters
// {single_quotes = '\'', double_quotes = '"',
// backslash = '\\', semicolon = ';', pipe = '|'}
// t_special_characters;

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