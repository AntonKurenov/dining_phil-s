/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 11:36:21 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/06 20:13:52 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "unistd.h"

void ft_print_comb(void)
{
	// write(1, " ", 1);
    char x;
	x = 55;
    write(1, &x, 1);
	// printf("\nx = %c\n", x);

    char x1 = 0, x2 = 1, x3 = 2;

    while (x1 != 7 && x2 != 8 && x3 != 9)
    {
        if (x3 > 9) {
            x2++;
            x3 = x2 + 1;
        }
        if (x2 > 8) {
            x1++;
            x2 = x1 + 1;
            x3 = x2 + 1;
        }
        
        write(1, &x1, sizeof(x1));
        write(1, &x2, sizeof(x2));
        write(1, &x3, sizeof(x3));
        x3++;
    }
}

int main(void)
{
	char x = 55;
    write(1, &x, 1);

	ft_print_comb();



}
