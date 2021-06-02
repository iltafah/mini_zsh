NAME = minishell
LIB = libft

FLAGS = -Wall -Wextra -Werror

SRC = ./environment/convert_env_table_to_array.c \
./environment/create_env_table.c \
./environment/get_value_of_env_name.c \
./freeing_time/free_abstract_syntax_tree.c \
./freeing_time/free_array_of_pointers.c \
./freeing_time/free_tokens_list.c \
./ft_strlen_utf8.c \
./get_curr_dir_name.c \
./get_next_line/get_next_line.c \
./get_prompt_name.c \
./libft/ft_atoi.c \
./libft/ft_bzero.c \
./libft/ft_calloc.c \
./libft/ft_isalnum.c \
./libft/ft_isalpha.c \
./libft/ft_isascii.c \
./libft/ft_isdigit.c \
./libft/ft_isprint.c \
./libft/ft_itoa.c \
./libft/ft_lstadd_back_bonus.c \
./libft/ft_lstadd_front_bonus.c \
./libft/ft_lstclear_bonus.c \
./libft/ft_lstdelone_bonus.c \
./libft/ft_lstiter_bonus.c \
./libft/ft_lstlast_bonus.c \
./libft/ft_lstmap_bonus.c \
./libft/ft_lstnew_bonus.c \
./libft/ft_lstsize_bonus.c \
./libft/ft_memccpy.c \
./libft/ft_memchr.c \
./libft/ft_memcmp.c \
./libft/ft_memcpy.c \
./libft/ft_memmove.c \
./libft/ft_memset.c \
./libft/ft_putchar_fd.c \
./libft/ft_putendl_fd.c \
./libft/ft_putnbr_fd.c \
./libft/ft_putstr_fd.c \
./libft/ft_split.c \
./libft/ft_strchr.c \
./libft/ft_strdup.c \
./libft/ft_strjoin.c \
./libft/ft_strlcat.c \
./libft/ft_strlcpy.c \
./libft/ft_strlen.c \
./libft/ft_strmapi.c \
./libft/ft_strncmp.c \
./libft/ft_strnstr.c \
./libft/ft_strrchr.c \
./libft/ft_strtrim.c \
./libft/ft_substr.c \
./libft/ft_tolower.c \
./libft/ft_toupper.c \
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
./readline/clear_lines.c \
./readline/create_key_seq_trie.c \
./readline/detect_screen_resizing.c \
./readline/erase_and_remove_char.c \
./readline/get_screen_width.c \
./readline/initializing.c \
./readline/insert_curr_line_to_history.c \
./readline/load_history_file_to_vec.c \
./readline/move_cursor_to_funcs/move_cursor_end_of_prec_line.c \
./readline/move_cursor_to_funcs/move_cursor_left_right.c \
./readline/move_cursor_to_funcs/move_cursor_start_of_next_line.c \
./readline/move_cursor_to_funcs/move_cursor_to_colum.c \
./readline/move_cursor_to_funcs/move_cursor_to_colum_and_row.c \
./readline/move_cursor_to_funcs/move_cursor_to_end_of_printed_line.c \
./readline/move_cursor_to_funcs/move_cursor_to_row.c \
./readline/move_cursor_to_funcs/move_cursor_up_down_vertically.c \
./readline/move_cursor_to_funcs/move_left.c \
./readline/move_cursor_to_funcs/move_right.c \
./readline/move_cursor_to_funcs/move_to_beginning_of_line.c \
./readline/move_cursor_to_funcs/move_to_end_of_line.c \
./readline/move_cursor_to_funcs/move_to_next_word.c \
./readline/move_cursor_to_funcs/move_to_prec_word.c \
./readline/move_cursor_to_funcs/move_up_down_vertically.c \
./readline/open_history_file.c \
./readline/overwrite_history_file.c \
./readline/printing_funcs/print_after_cursor.c \
./readline/printing_funcs/print_curr_char.c \
./readline/printing_funcs/print_line_with_chosen_method.c \
./readline/printing_funcs/print_prompt.c \
./readline/printing_funcs/print_suggestions.c \
./readline/printing_funcs/put_char.c \
./readline/printing_funcs/put_colorful_char.c \
./readline/printing_funcs/rdl_print_char.c \
./readline/process_input.c \
./readline/readline.c \
./readline/restore_cursor_position.c \
./readline/show_history.c \
./readline/signals_handler.c \
./readline/syntax_highlighting_funcs/check_if_cmd_exist.c \
./readline/syntax_highlighting_funcs/check_if_file_exist.c \
./readline/syntax_highlighting_funcs/print_with_syntax_highlighting.c \
./readline/text_highlighting_funcs/copy_highlighted_text.c \
./readline/text_highlighting_funcs/cut_highlighted_text.c \
./readline/text_highlighting_funcs/determine_beg_last_highlighted_text_index.c \
./readline/text_highlighting_funcs/left_highlight.c \
./readline/text_highlighting_funcs/past_highlighted_text.c \
./readline/text_highlighting_funcs/quit_highlighting_mode.c \
./readline/text_highlighting_funcs/right_highlight.c \
./readline/text_highlighting_funcs/start_highlighting_mode.c \
./readline/update_cursor_data.c \
./readline/usefull_history_vec_func.c \
./vectors/vector_of_char_vectors.c \
./vectors/vector_of_chars.c \
./vectors/vector_of_int.c \
./vectors/vector_of_strings.c

OBJ = $(SRC:.c=.o)

all: $(NAME) 
	
$(NAME): $(OBJ)
	make -sC ./libft
	gcc -o $@ $^ -ltermcap ./libft/libft.a

%.o : %.c
	gcc $(FLAGS) -o $@ -c $^

clean :
		rm -f $(OBJ)
		make fclean -sC ./libft

fclean : clean
		rm -f $(NAME)

re : fclean all