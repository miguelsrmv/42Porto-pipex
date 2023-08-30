/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:31:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/30 11:02:15 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_word(const char *s, size_t *len)
{
	t_split_numbers	num;
	char			*word;

	ft_memset(&num, 0, sizeof(t_split_numbers));
	num.i = 0;
	while (s[num.i] && (num.in_quote || !ft_isspace(s[num.i])))
	{
		if (s[num.i] == '\\' && (num.quote_char != '\'' || !num.in_quote))
		{
			num.i += 2;
			if (!s[num.i])
				break ;
		}
		else if (ft_isquote(s[num.i]) 
			&& (ft_isspace(s[num.i - 1]) || ft_isspace(s[num.i + 1]))
			&& (!num.in_quote || s[num.i] == num.quote_char))
		{
			num.in_quote = !num.in_quote;
			num.quote_char = s[num.i];
		}
		num.i++;
	}
	*len = num.i;
	word = ft_substr(s, 0, num.i);
	return (word);
}

static int	get_word_count(const char *s)
{
	t_split_numbers	num;

	ft_memset(&num, 0, sizeof(t_split_numbers));
	num.i = 0;
	while (s[num.i])
	{
		if (s[num.i] == '\\' && (num.quote_char != '\'' || !num.in_quote))
			num.i += 2;
		else if (ft_isquote(s[num.i])
			&& (ft_isspace(s[num.i - 1]) || ft_isspace(s[num.i + 1]))
			&& (!num.in_quote || s[num.i] == num.quote_char))
		{
			num.in_quote = !num.in_quote;
			num.quote_char = s[num.i];
		}
		else if (!num.in_quote && ft_isspace(s[num.i]))
			num.in_word = 0;
		else if (!num.in_word)
		{
			num.in_word = 1;
			num.word_count++;
		}
		num.i++;
	}
	return (num.word_count);
}

static char	*get_next_word(const char **s, size_t *len)
{
	while (ft_isspace(**s))
		(*s)++;
	return (get_word(*s, len));
}

char	**ft_command_split(const char *s)
{
	char	**words;
	int		word_count;
	int		i;
	size_t	len;

	word_count = get_word_count(s);
	words = malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = -1;
	while (++i < word_count)
	{
		if (!(words[i] = get_next_word(&s, &len)))
		{
			while (i >= 0)
				free(words[i--]);
			free(words);
			return (NULL);
		}
		s += len;
	}
	words[word_count] = NULL;
	return (words);
}


/*
char	**ft_command_split(const char *s)
{
	char	**words;
	int		word_count;
	int		i;
	size_t	len;

	i = 0;
	word_count = get_word_count(s);
	words = malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (i < word_count)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
		{
			words[i] = get_word(s, &len);
			if (!words[i])
			{
				while (i >= 0)
					free(words[i--]);
				free(words);
				return (NULL);
			}
			s += len;
			i++;
		}
	}
	words[word_count] = NULL;
	return (words);
}
*/