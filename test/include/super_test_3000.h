/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_test_3000.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 00:30:12 by mc                #+#    #+#             */
/*   Updated: 2018/03/14 14:38:03 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPER_TEST_3000
# define SUPER_TEST_3000

# include "minunit.h"
# include "asm.h"
# include "corewar.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>

/*
** asm
*/
void test_asm(void);
void test_asm_parser(void);
void test_asm_lexer(void);
void test_asm_encoder(void);

#endif