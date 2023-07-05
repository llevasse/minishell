/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsep_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:42:23 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/05 17:50:07 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char str[] = "cc hello hi";
	char *p = str;
	printf("%s\n", p); 
	strsep(&p, " ");
	printf("%s\n", p);
	strsep(&p, " ");
	printf("%s\n", p);
}
