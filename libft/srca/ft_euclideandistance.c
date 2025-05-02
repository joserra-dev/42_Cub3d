/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_euclideandistance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscastr <joscastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:22:20 by joscastr          #+#    #+#             */
/*   Updated: 2025/03/14 19:22:23 by joscastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_euclideandistance(t_vector src, t_vector dest)
{
	return (ft_sqrt(ft_recursive_power(dest.x - src.x, 2) + \
							ft_recursive_power(dest.y - src.y, 2)));
}
