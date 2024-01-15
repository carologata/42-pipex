/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:58:09 by cogata            #+#    #+#             */
/*   Updated: 2024/01/15 16:58:11 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_update_quote_flag(int *quote_flag, int *quote_aux)
{
	if (*quote_flag == 0 && *quote_aux == 0)
	{
		*quote_flag = 1;
		*quote_aux = 1;
	}
	else if (*quote_flag == 0 && *quote_aux == 1)
		*quote_aux = 0;
}

int	ft_count_leters(char *s, char c, char quote, int *j)
{
	int	count_letters;

	count_letters = 0;
	while (s[*j] == c)
		*j = *j + 1;
	if (s[*j] == quote)
	{
		*j = *j + 1;
		while (s[*j] != quote && s[*j] != '\0')
		{
			count_letters = count_letters + 1;
			*j = *j + 1;
		}
	}
	else
	{
		while (s[*j] != c && s[*j] != '\0')
		{
			count_letters = count_letters + 1;
			*j = *j + 1;
		}
	}
	return (count_letters);
}
