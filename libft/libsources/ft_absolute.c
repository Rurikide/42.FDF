/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absolute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:33:40 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/02 09:34:22 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_absolute(int nb)
{
	if (nb < 0)
		nb += -1;
	return (nb);
}
