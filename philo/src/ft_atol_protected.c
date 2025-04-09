/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_protected.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:39 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/09 11:24:33 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int	clean(char **str)
{
	int	is_negative;

	is_negative = 0;
	if (*str[0] == '-' || *str[0] == '+')
	{
		if (*str[0] == '-')
			is_negative = 1;
		*str += 1;
	}
	return (is_negative);
}

static int	do_calcul(int is_negative, char *str, int *i, long *long_ptr)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (is_negative)
		{
			if (*long_ptr * 10 - (str[*i] - '0') > *long_ptr)
				return (0);
			*long_ptr = *long_ptr * 10 - (str[*i] - '0');
		}
		else
		{
			if (*long_ptr * 10 + (str[*i] - '0') < *long_ptr)
				return (0);
			*long_ptr = *long_ptr * 10 + (str[*i] - '0');
		}
		(*i)++;
	}
	return (1);
}

long	ft_atol_protected(const char *str, long *long_pt)
{
	int	i;
	int	is_negative;

	if (str == NULL)
		return (0);
	i = 0;
	*long_pt = 0;
	is_negative = clean((char **)&str);
	if (do_calcul(is_negative, (char *)str, &i, long_pt) == 0
		|| str[i] != '\0' || i == 0)
		return (0);
	return (1);
}
