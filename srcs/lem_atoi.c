/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:58:01 by ppiirone          #+#    #+#             */
/*   Updated: 2022/08/21 15:58:03 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	lem_atoi(const char *str)
{
	unsigned long int	res;
	int					sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (unsigned long int)*str - '0';
		if (res > 9223372036854775807 && sign < 0)
			return (0);
		if (res > 9223372036854775807 && sign > 0)
			return (-1);
		str++;
	}
	if (*str != ' ' && *str != '\n' && *str != '\0')
		exit(0);			// Add error message here !
	return (sign * (int)res);
}
