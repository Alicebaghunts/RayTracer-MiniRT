/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:51:59 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/21 19:10:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/validation.h"

static int	parse_int_checked(const char *s, int *ok)
{
	int	i;
	int	sign;
	int	acc;

	if (!s || !*s)
		return (*ok = 0, 0);
	i = 0;
	sign = get_sign(s, &i);
	if (!s[i])
		return (*ok = 0, 0);
	acc = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i])
			|| (sign == 1 && acc > (INT_MAX - (s[i] - '0')) / 10)
			|| (sign == -1 && acc > (-(INT_MIN + (s[i] - '0'))) / 10))
			return (*ok = 0, 0);
		acc = acc * 10 + (s[i] - '0');
		i++;
	}
	*ok = 1;
	return (sign * acc);
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
	int	dot;

	if (!str || !*str)
		return (0);
	i = 0;
	dot = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (dot)
				return (0);
			dot = 1;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 0 && (ft_isdigit(str[i - 1]) || (dot && i > 1)))
		return (1);
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
