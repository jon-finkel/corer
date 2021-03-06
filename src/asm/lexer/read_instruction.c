/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/31 17:04:03 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** read content (except header) of the .s files
*/

#include "asm_lexer.h"

/*
** arg tokenizer
*/

static t_progress		read_arg(char *arg, size_t len, \
								t_instruct_read *instruct)
{
	char	*arg_swap;
	char	*arg_start;

	if (instruct->argc || !(arg_swap = arg))
		return (P_ARG);
	while (!IS_EOL(*arg_swap) && instruct->argc < MAX_ARGS_NUMBER)
	{
		while (!IS_EOL(*arg_swap) && ft_isspace(*arg_swap))
			arg_swap++;
		arg_start = arg_swap;
		while (!IS_EOL(*arg_swap) && *arg_swap != SEPARATOR_CHAR)
			arg_swap++;
		while (arg_swap != arg_start && (ft_isspace(*arg_swap) \
				|| *arg_swap == SEPARATOR_CHAR || IS_EOL(*arg_swap)))
			arg_swap--;
		len = check_arg_len((size_t)(arg_swap - arg_start) + 1, instruct);
		ft_memcpy(instruct->argv + instruct->argc, arg_start, len);
		*(*(instruct->argv + instruct->argc) + len) = 0;
		instruct->argc++;
		while (!IS_EOL(*arg_swap) && *arg_swap != SEPARATOR_CHAR)
			arg_swap++;
		if (*arg_swap == SEPARATOR_CHAR)
			arg_swap++;
	}
	return (P_ARG);
}

/*
** op tokenizer
*/

static t_progress		read_op(char *op, size_t len, t_instruct_read *instruct)
{
	if (len > MAX_OP_CODE_LENGTH)
		error(E_INVALID, "Invalid op (too long).");
	ft_memcpy(&instruct->op, op, len);
	*(instruct->op + len) = 0;
	return (P_OP);
}

/*
** label tokenizer
*/

static t_progress		read_label(char *label, size_t len, \
								t_instruct_read *instruct)
{
	char	*label_swap;

	label_swap = label;
	while ((size_t)(label_swap - label) < len)
		if (!ft_strchr(LABEL_CHARS, *label_swap++))
			error(E_INVALID, "Invalid label (forbidden character).");
	if (len > MAX_LABEL_LENGTH)
		error(E_INVALID, "Invalid label (too long).");
	ft_memcpy(&instruct->label, label, len);
	*(instruct->label + len) = 0;
	return (P_LABEL);
}

/*
** tokenize the current asm line
*/

static t_progress		read_instruction(char *line, \
											t_progress progress, \
											t_instruct_read *instruct)
{
	char		*word_start;

	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	if (IS_EOL(*line))
		return (progress);
	word_start = line;
	while (!IS_EOL(*line) && !ft_isspace(*line))
		line++;
	if (*word_start == '.' && progress == P_NOPROGRESS)
		return (error(E_WARNING, ".CMD not found (ignoring).") || P_NOPROGRESS);
	if (*(line - 1) == LABEL_CHAR)
	{
		if (progress & P_LABEL || progress & P_OP)
			error(E_INVALID, "Invalid label (label/op already found).");
		progress |= read_label(word_start, \
							(size_t)(line - word_start - 1), instruct);
	}
	else if (!(progress & P_OP))
		progress |= read_op(word_start, (size_t)(line - word_start), instruct);
	else
		progress |= read_arg(word_start, (size_t)(line - word_start), instruct);
	return (read_instruction(line, progress, instruct));
}

/*
** read instruction lines from asm file
*/

void					read_loop(void)
{
	int				ret;
	t_progress		progress;
	t_instruct_read	instruct;

	ft_bzero(&instruct, sizeof(t_instruct_read));
	ft_memdel((void **)&(g_err.line));
	if (!(ret = get_next_line(g_err.fd, &(g_err.line))))
		return ;
	else if (ret == -1)
		error(E_READ, NULL);
	g_err.line_pos += 1;
	progress = read_instruction(g_err.line, P_NOPROGRESS, &instruct);
	if (!(!progress
		|| (progress & P_LABEL && !(progress & P_OP))
		|| (progress & P_OP && progress & P_ARG)))
		error(E_INVALID, "Something's wrong with that instruction.");
	if (progress)
		parse_instruct(&instruct);
	read_loop();
}
