/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:01:14 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/01 17:20:09 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void    print_list(t_tokens *head)
// {
//     t_tokens *tmp;
    
//     tmp = head;
//     while(tmp != NULL)
// 	{
//         if(tmp->next == NULL)
//         {
//             printf("%s   ", tmp->cmd[0]);
//             printf("%s\n", tmp->cmd[1]);
//         }
//         else
//         {
//             printf("%s   ", tmp->value[0]);
//             printf("%s\n", tmp->value[1]);
//         }
//         tmp = tmp->next;
//     }
// }

// void	free_stack(t_tokens *head)
// {
// 	t_tokens	*tmp;

// 	while (head != NULL)
// 	{
// 		tmp = head;
// 		free(tmp);
// 		if (head->next != NULL)
// 			head = head->next;
// 		else
// 			break ;
// 	}
// }

int	count_list(t_tokens *head)
{
	t_tokens	*current;
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}