/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:49:28 by cogata            #+#    #+#             */
/*   Updated: 2024/01/15 16:49:32 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_words(char const *s, char c)
{
	t_flags	flag;
	int		i;

	i = 0;
	flag.count_word = 0;
	flag.count_flag = 1;
	flag.quote_flag = 0;
	flag.quote_aux = 0;
	flag.quote = '\'';
	while (s[i] != '\0')
	{
		if (s[i] == c && flag.quote_flag == 0)
			flag.count_flag = 1;
		else if (s[i] == flag.quote)
			ft_update_quote_flag(&flag.quote_flag, &flag.quote_aux);
		else if ((s[i] != c && flag.count_flag == 1 && flag.quote_aux == 0)
			|| (flag.quote_flag == 1 && flag.quote_aux == 1))
		{
			flag.count_word = flag.count_word + 1;
			flag.count_flag = 0;
			flag.quote_flag = 0;
		}
		i++;
	}
	return (flag.count_word);
}

static char	**ft_init_words(char const *s, char **words, int k,
		int count_letters)
{
	int	l;

	l = 0;
	while (l < count_letters)
	{
		words[0][l] = s[k];
		k++;
		l++;
	}
	words[0][l] = '\0';
	return (words);
}

static void	ft_free(char **words, int i)
{
	while (i - 1 >= 0)
	{
		free(words[i]);
		i--;
	}
	free(words);
}

static char	**ft_logic(char *s, char **words, char c, int count_word)
{
	int		i;
	int		j;
	int		count_letters;
	char	quote;

	i = 0;
	j = 0;
	quote = '\'';
	while (i < count_word)
	{
		count_letters = ft_count_leters(s, c, quote, &j);
		words[i] = malloc((count_letters + 1) * sizeof(char));
		if (words[i] == NULL)
			ft_free(words, i);
		else
			ft_init_words(s, &words[i], j - count_letters, count_letters);
		i++;
		if (s[j] == quote)
			j++;
	}
	words[count_word] = NULL;
	return (words);
}

char	**ft_split_modified(char *s, char c)
{
	char	**words;
	int		count_word;

	if (s == NULL)
		return (NULL);
	count_word = ft_count_words(s, c);
	words = malloc((count_word + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	ft_logic(s, words, c, count_word);
	return (words);
}
