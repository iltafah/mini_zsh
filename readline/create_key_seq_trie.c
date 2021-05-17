#include "./readline.h"

t_trie_node *get_trie_node(void)
{
	t_trie_node *new_node;
	int		index;

	index = 0;
	new_node = malloc(sizeof(t_trie_node));
	new_node->key = none;
	new_node->children = malloc(sizeof(t_trie_node) * 128);
	while (index < 128)
		new_node->children[index++] = NULL;
	return (new_node);
}

void	insert_key(t_trie_node *trie_root, char *key_seq, int key_type)
{
	int	i;
	int	node_index;
	t_trie_node *curr_node;

	i = 0;
	curr_node = trie_root;
	while (key_seq[i] != '\0')
	{
		node_index = (int)key_seq[i];
		if (curr_node->children[node_index] == NULL)
		{
			curr_node->children[node_index] = get_trie_node();
		}
		curr_node = curr_node->children[node_index];
		i++;
	}
	curr_node->key = key_type;
}

int	get_key(t_trie_node *trie_root, char c)
{
	int	key;
	static t_trie_node *curr_node = NULL;

	key = none;
	if (curr_node == NULL)
	{
		curr_node = trie_root;
	}
	curr_node = curr_node->children[(int)c];
	if (curr_node != NULL)
	{
		key = curr_node->key;
		if (key == none)
			key = waiting;
		else
			curr_node = NULL;
	}
	return (key);
}

void	insert_printable_characters(t_trie_node *trie_root)
{
	static char	printable_char[] = "\0";
	int			curr_printable_char = 32;
	int			last_printable_char = 127;

	while (curr_printable_char < last_printable_char)
	{
		printable_char[0] = curr_printable_char;
		insert_key(trie_root, printable_char, printable);
		curr_printable_char++;
	}
}

t_trie_node	*initialize_key_seq_trie()
{
	t_trie_node *trie_root;
	trie_root = get_trie_node();
	
	insert_printable_characters(trie_root);
	insert_key(trie_root, "\e[A", up_arrow);
	insert_key(trie_root, "\e[B", down_arrow);
	insert_key(trie_root, "\e[C", right_arrow);
	insert_key(trie_root, "\e[D", left_arrow);
	insert_key(trie_root, "\177", backspace);
	insert_key(trie_root, "\n", enter);
	return (trie_root);
}