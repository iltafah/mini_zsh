NAME = minishell

FLAGS = #-Wall -Wextra -Werror

SRC = ./environment/convert_env_table_to_array.c \
./environment/create_env_table.c \
./freeing_time/free_abstract_syntax_tree.c \
./freeing_time/free_tokens_list.c \
./get_next_line/get_next_line.c \
./get_next_line/get_next_line_utils.c \
./minishell.c \
./parser/check_tokens_syntax/check_simple_word_syntax.c \
./parser/check_tokens_syntax/check_tokens_order.c \
./parser/check_tokens_syntax/check_tokens_syntax.c \
./parser/create_abstract_syntax_tree/create_abstract_syntax_tree.c \
./parser/create_abstract_syntax_tree/create_ast_nodes.c \
./parser/create_abstract_syntax_tree/get_suitable_nodes.c \
./parser/create_abstract_syntax_tree/initialize_ast_vars.c \
./parser/create_abstract_syntax_tree/store_redirection_in_suitable_node.c \
./parser/create_abstract_syntax_tree/store_word_in_suitable_node.c \
./parser/expanding/expand_dollar_variables.c \
./parser/expanding/expanding.c \
./parser/expanding/give_quotes_special_meaning.c \
./parser/expanding/remove_special_quotes.c \
./parser/expanding/split_element_to_args.c \
./parser/tokenization/cases_treating.c \
./parser/tokenization/tokenization.c \
./parser/usefull_functions/open_and_close_quotes.c \
./vectors/vector_of_chars.c \
./vectors/vector_of_strings.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^

%.o : %.c
	gcc $(FLAGS) -o $@ -c $^

clean :
		rm -f $(OBJ)

fclean : clean
		rm -f $(NAME)

re : fclean all