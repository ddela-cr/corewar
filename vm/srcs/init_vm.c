/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 11:44:50 by vbaudin           #+#    #+#             */
/*   Updated: 2016/08/30 11:54:40 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		init_champ(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->champions[i].name = NULL;
		vm->champions[i].comment = NULL;
		vm->champions[i].data = NULL;
		vm->champions[i].champ_nb = -1;
		vm->champions[i].live = 0;
		i++;
	}
}

void		init_vm(t_vm *vm)
{
	int		i;

	i = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->nb_executed_live = 0;
	while (i < MEM_SIZE)
		vm->memory[i++] = 0;
	init_champ(vm);
}