/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 22:38:52 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/08/25 22:38:57 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


void			ft_print_value(int value, int size)
{
	int		print;
	int		initial_size;

	print = 0;
	initial_size = size;
	while (size)
	{
		print = (value >> (size * 8 - 8)) & 0xff;
		ft_printf("%-4d", print);
		size--;
	}
	while (++initial_size <= 4)
		ft_putstr("    ");
	ft_putstr("  ");
}

static void		ft_print_values_bis(t_inst *inst, t_op *infos, t_list *instructions)
{
	int		i = 0;
	int		arg_type = 0;

	ft_printf("                          %-5d", infos->code);
	if (infos->has_encoding)
		ft_printf("{yellow}%-7d{eoc}", ft_get_prefix(infos->nb_args, inst->args));
	else
		ft_putstr("       ");
	while (i < infos->nb_args)
	{
		arg_type = ft_get_arg_type(inst->args[i]);
		if (arg_type == IS_REG)
			ft_printf("%-18d", ft_atoi(&(inst->args[i][1])), 1);
		else if (arg_type == IS_DIR_VALUE)
			ft_printf("%-18d", ft_atoi(&(inst->args[i][1])), infos->label_size);
		else if (arg_type == IS_DIR_LABEL)
			ft_printf("%-18d", ft_get_label_value(instructions, inst, &(inst->args[i][2])),
							infos->label_size);
		else if (arg_type == IS_IND_VALUE)
			ft_printf("%-18d", ft_atoi(&(inst->args[i][0])), 2);
		else if (arg_type == IS_IND_LABEL)
			ft_printf("%-18d", ft_get_label_value(instructions, inst, &(inst->args[i][1])),
							4);
		i++;
	}
	ft_putstr("\n\n");
}

static void		ft_print_values(t_inst *inst, t_op *infos, t_list *instructions)
{
	int		i = 0;
	int		arg_type = 0;

	ft_printf("                          %-5d", infos->code);
	if (infos->has_encoding)
		ft_printf("{yellow}%-7d{eoc}", ft_get_prefix(infos->nb_args, inst->args));
	else
		ft_putstr("       ");
	while (i < infos->nb_args)
	{
		arg_type = ft_get_arg_type(inst->args[i]);
		if (arg_type == IS_REG)
			ft_print_value(ft_atoi(&(inst->args[i][1])), 1);
		else if (arg_type == IS_DIR_VALUE)
			ft_print_value(ft_atoi(&(inst->args[i][1])), infos->label_size);
		else if (arg_type == IS_DIR_LABEL)
			ft_print_value(ft_get_label_value(instructions, inst, &(inst->args[i][2])),
							infos->label_size);
		else if (arg_type == IS_IND_VALUE)
			ft_print_value(ft_atoi(&(inst->args[i][0])), 2);
		else if (arg_type == IS_IND_LABEL)
			ft_print_value(ft_get_label_value(instructions, inst, &(inst->args[i][1])),
							2);
		i++;
	}
	ft_putstr("\n");
}

static void		ft_print_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		ft_printf("%-18s", args[i]);
		i++;
	}
	ft_putchar('\n');
}

void	ft_print_instruction(t_inst *instruction, t_op *infos, int total_size, t_list *head)
{
	if (instruction->label)
	{
		ft_printf("%-15d:", total_size);
		ft_printf("     {red}%s:{eoc}\n", instruction->label);
	}
	ft_printf("%-6d", total_size);
	ft_printf("(%-5d)  :", instruction->size);
	ft_printf("          {green}%-12s{eoc}", instruction->opcode);
	ft_print_args(instruction->args);
	ft_print_values(instruction, infos, head);
	ft_print_values_bis(instruction, infos, head);


}
