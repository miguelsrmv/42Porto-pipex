/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:31:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/30 09:25:01 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pipex.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static char	*get_word(const char *s, size_t *len)
{
	int		in_quote;
	char	quote_char;
	char	*word;
	size_t	i;

	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (s[i] && (in_quote || !ft_isspace(s[i])))
	{
		if (s[i] == '\\' && (quote_char != '\'' || !in_quote))
		{
			i += 2;
			if (!s[i])
				break;
		}
		else if (is_quote(s[i]) && (!in_quote || s[i] == quote_char))
		{
			in_quote = !in_quote;
			quote_char = s[i];
		}
		i++;
	}
	*len = i;
	word = ft_substr(s, 0, i);
	return (word);
}

static int	get_word_count(const char *s)
{
	int		word_count;
	int		in_word;
	int		in_quote;
	char	quote_char;
	size_t	i;

	i = 0;
	word_count = 0;
	in_word = 0;
	in_quote = 0;
	quote_char = 0;
	while (s[i])
	{
		if (s[i] == '\\' && (quote_char != '\'' || !in_quote))
			i += 2;
		else if (is_quote(s[i]) && (!in_quote || s[i] == quote_char))
		{
			in_quote = !in_quote;
			quote_char = s[i];
		}
		else if (!in_quote && ft_isspace(s[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

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
