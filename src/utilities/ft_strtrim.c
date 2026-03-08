/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaltine  <akaltine@student.42kocael>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:38:22 by akaltine          #+#    #+#             */
/*   Updated: 2024/07/22 17:37:51 by akaltine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "stdlib.h"

char	*ft_strtrim(char *s1, char *set)
{
	int	size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	size = ft_strlen(s1);
	while (ft_strchr(set, s1[size]) && size != 0)
		size--;
	return (ft_substr(s1, 0, size + 1));
}
