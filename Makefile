NAME = minishell
LIB = libft

FLAGS = #-Wall -Wextra -Werror

SRC = ./environment/convert_env_table_to_array.c \
./environment/create_env_table.c \
./freeing_time/free_abstract_syntax_tree.c \
./freeing_time/free_tokens_list.c \
./freeing_time/free_array_of_pointers.c \
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
./readline/erase_and_remove_char.c \
./readline/ft_strlen_utf8.c \
./readline/get_curr_dir_name.c \
./readline/get_prompt_name.c \
./readline/get_screen_width.c \
./readline/initializing.c \
./readline/insert_curr_line_to_history.c \
./readline/left_highlight.c \
./readline/move_cursor_to_funcs/move_cursor_end_of_prec_line.c \
./readline/move_cursor_to_funcs/move_cursor_left_right.c \
./readline/move_cursor_to_funcs/move_cursor_start_of_next_line.c \
./readline/move_cursor_to_funcs/move_cursor_to_colum.c \
./readline/move_cursor_to_funcs/move_cursor_to_colum_and_row.c \
./readline/move_cursor_to_funcs/move_cursor_to_row.c \
./readline/move_cursor_to_funcs/move_cursor_up_down_vertically.c \
./readline/move_cursor_to_funcs/move_left.c \
./readline/move_cursor_to_funcs/move_right.c \
./readline/move_cursor_to_funcs/move_to_beginning_of_line.c \
./readline/move_cursor_to_funcs/move_to_end_of_line.c \
./readline/move_cursor_to_funcs/move_to_next_word.c \
./readline/move_cursor_to_funcs/move_to_prec_word.c \
./readline/move_cursor_to_funcs/move_up_down_vertically.c \
./readline/printing_funcs/print_after_cursor.c \
./readline/printing_funcs/print_curr_char.c \
./readline/printing_funcs/print_prompt.c \
./readline/printing_funcs/put_char.c \
./readline/printing_funcs/put_colorful_char.c \
./readline/printing_funcs/rdl_print_char.c \
./readline/printing_funcs/print_suggestions.c \
./readline/process_input.c \
./readline/readline.c \
./readline/restore_cursor_position.c \
./readline/right_highlight.c \
./readline/show_history.c \
./readline/sigwinch_handler.c \
./readline/text_highlighting_funcs/copy_highlighted_text.c \
./readline/text_highlighting_funcs/cut_highlighted_text.c \
./readline/text_highlighting_funcs/determine_beg_last_highlighted_text_index.c \
./readline/text_highlighting_funcs/past_highlighted_text.c \
./readline/turn_on_off_reverse_video_mode.c \
./readline/update_cursor_data.c \
./readline/usefull_history_vec_func.c \
./vectors/vector_of_char_vectors.c \
./vectors/vector_of_chars.c \
./vectors/vector_of_strings.c \
./vectors/vector_of_chars.c \
./vectors/vector_of_char_vectors.c \
./vectors/vector_of_strings.c \
./get_next_line/get_next_line.c \
./get_next_line/get_next_line_utils.c

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