/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:17 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 19:04:38 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char c, int *s_quote, int *d_quote)
{
	if (c == '\"' && !*s_quote && !*d_quote)
		*d_quote = 1;
	else if (c == '\"' && !*s_quote)
		*d_quote = 0;
	if (c == '\'' && !*d_quote && !*s_quote)
		*s_quote = 1;
	else if (c == '\'' && !*d_quote)
		*s_quote = 0;
}

void	expansion_empty(t_token **token)
{
	if ((*token)->type == empty_expansion && ft_strcmp((*token)->token, "\0"))
		(*token)->type = cmd;
}

int	its_space(char c)
{
	if (c == ' ' || (c >= 9 && c < 13))
		return (1);
	return (0);
}

int	its_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

t_token	**parse(char *line, t_list *lst, t_ints *t_int)
{
	t_token	**tokens;
	char	*temp;
	int		i;

	tokens = start_tokens(line);
	if (!tokens)
		return (NULL);
	if (!tokens[0])
		return (tokens);
	if (token_lab(&tokens))
	{
		free_tokens(&tokens);
		return (NULL);
	}
	i = 0;
	while (tokens[i])
	{
		temp = tokens[i]->token;
		tokens[i]->token = expand(&tokens[i], lst, t_int);
		expansion_empty(&tokens[i]);
		free(temp);
		i++;
	}
	return (tokens);
}
