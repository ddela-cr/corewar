/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_vm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 13:20:03 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/09/02 13:20:05 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <time.h>

static void		ft_get_pc(t_process *process)
{
	process->pc += process->op_size;
	process->op_size = 1;
}

void	ft_execute(t_vm *vm, t_process *process)
{
	t_op	*op;
	t_args	*args;

	op = ft_get_op_data(process->waiting_op);
	args = ft_get_args(vm, process, op);
	ft_doing_op(args, vm, process);
	process->is_waiting = FALSE;
	if (process->waiting_op != ZJMP)
		ft_get_pc(process);
	process->waiting_op = 0;
}

void	ft_do_process(t_vm *vm)
{
	t_process	*process;

	process = vm->process;
	while (process)
	{
		if (!process->waiting_op)
		{
			if (vm->memory[process->pc] > 0 && vm->memory[process->pc] < 17)
			{
			// ft_printf("waiting_op = %d || Pc = %d\n", vm->memory[process->pc], process->pc);
			process->waiting_op = vm->memory[process->pc];
			//ft_debug_memory(vm->memory, 0, 50);
			process->cycle_to_wait = ft_get_op_data(process->waiting_op)->cycle;
			process->is_waiting = TRUE;
			}
			else
				process->pc++;
		}
		else if (process->cycle_to_wait == 1)
			ft_execute(vm, process);
		else
			--process->cycle_to_wait;
		process = process->next;
	}
}

void	ft_launch_vm(t_vm *vm)
{
	int		cycles;

	cycles = 1;
	while (1)
	{
		if (vm->dump > 0 && cycles == vm->dump)
			ft_dump_memory(vm->memory, 0, MEM_SIZE);
		if (vm->cycle_in_current_period == vm->cycle_to_die)
			ft_check_alive(vm);
		if (vm->cycle_to_die < 0)
			break ;
		ft_do_process(vm);
		vm->cycle_in_current_period++;
		cycles++;
	}
}