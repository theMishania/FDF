/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:19:53 by chorange          #+#    #+#             */
/*   Updated: 2019/02/27 14:49:05 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int		main(int ac, char **av)
{
	argc_count_errors(ac);
	provider(4, av[1]);
	return (0);
}
