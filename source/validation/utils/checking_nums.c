/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:51:59 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/24 20:11:28 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include <limits.h>

/*
 * Parse integer from string with overflow detection for 32-bit int.
 * If parsing succeeds and value fits in int, *ok is set to 1 and the value
 * is returned. Otherwise *ok is set to 0.
 */
static int	parse_int_checked(const char *s, int *ok)
{
	int		i;
	int		sign;
	unsigned long long	acc;

	if (!s || !*s)
	{
		*ok = 0;
		return (0);
	}
	i = 0;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
	{
		*ok = 0;
		return (0);
	}
	acc = 0ULL;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (*ok = 0, 0);
		acc = acc * 10ULL + (unsigned long long)(s[i] - '0');
		if (sign == 1)
		{
			if (acc > (unsigned long long)INT_MAX)
				return (*ok = 0, 0);
		}
		else
		{
			if (acc > (unsigned long long)INT_MAX + 1ULL)
				return (*ok = 0, 0);
		}
		i++;
	}
	*ok = 1;
	if (sign == 1)
		return ((int)acc);
	return (-(int)acc);
}

int	is_in_range_float(const char *str, float min, float max)
{
	float	val;

	if (!str)
		return (0);
	val = ft_atof(str);
	if (val < min || val > max)
		return (0);
	return (1);
}

int	is_in_range_int(const char *str, float min, float max)
{
	int	val;
	int	ok;

	if (!str)
		return (0);
	val = parse_int_checked(str, &ok);
	if (!ok)
		return (0);
	if (val < (int)min || val > (int)max)
		return (0);
	return (1);
}

int	is_valid_float(const char *str)
{
	int	i;
	int	has_dot;

	if (!str || !*str)
		return (0);
	i = 0;
	has_dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 0 && (ft_isdigit(str[i - 1]) || (has_dot && i > 1)))
		return (1);
	else
		return (0);
}

int	is_valid_number(char *num_str)
{
	int	ok;

	if (!num_str)
		return (0);
	parse_int_checked(num_str, &ok);
	return (ok);
}
