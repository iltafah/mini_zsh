#include "tokenization.h"

int		treat_quotes(char *line, char sd_quote)
{
	int		i;
	int		closed;
	int		backslash;

	i = 1;
	closed = 0;
	backslash = 0;
	while (line[i] != '\0' && (backslash == 1 || line[i] != sd_quote))
	{
		if ((line)[i] == '\\')
			backslash = 1;
		else
			backslash = 0;
		i++;
	}
	return (i);
}

char	*get_redirection(char **line, t_type *type)
{
	char	*token;
	char	redir;
	int		i;

	i = 0;
	redir = **line;
	while ((*line)[i] == redir && (*line)[i] != '\0' && i < 2)
		i++;
	token = ft_substr(*line, 0, i);
	*line = *line + i;
	*type = e_redir;
	return (token);

}

char *get_pipe(char **line, t_type *type)
{
	char *token;
	int i;

	i = 0;
	while ((*line)[i] == '|' && (*line)[i] != '\0')
		i++;
	token = ft_substr(*line, 0, i);
	*line = *line + i;
	*type = e_pipe;
	return (token);
}

char *get_semicolon(char **line, t_type *type)
{
	char *token;
	int i;

	i = 0;
	while ((*line)[i] == ';' && (*line)[i] != '\0')
		i++;
	token = ft_substr(*line, 0, i);
	*line = *line + i;
	*type = e_semicolon;
	return (token);
}

char *get_simple_word(char **line, t_type *type)
{
	char	*token;
	int		i;
	int		backslash;

	i = 0;
	backslash = 0;
	while (((*line)[i] != ' ' && (*line)[i] != '|' && (*line)[i] != ';' && (*line)[i] != '\0') ||
	backslash == 1)
	{
		if ((*line)[i] == '"' && backslash == 0)
			i += treat_quotes(*line + i, '"');
		else if ((*line)[i] == '\'' && backslash == 0)
			i += treat_quotes(*line + i, '\'');
		if ((*line)[i] == '\\' && backslash == 0)
			backslash = 1;
		else
			backslash = 0;
		if ((*line)[i] != '\0')
			i++;
	}
	token = ft_substr(*line, 0, i);
	*line = *line + i;
	*type = e_simple_word;
	return (token);
}


////don't forget to treat this case =>>   echo \\"hello world" this is not an error
////and this one too                =>>   echo '\'
////and this one too				=>>   echo "`"