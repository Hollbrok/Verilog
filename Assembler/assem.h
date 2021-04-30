#ifndef ASSEM_H_INCLUDED
#define ASSEM_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <stdio.h>
#include <limits>
#include <fstream>

#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
#include <string>
#include <assert.h>
#include "assem_info.h"

#include "Commands.h"

using number_of_labels = int;

#define cmd_check(name, command)   \
	else if (!strcmp(temp, #name)) \
		data_[i] = command;

#define rix_check(name, command)                  \
	else if (!strcmp(temp, #name))                \
	{                                             \
		data_[i] = command;           \
		specifiers[flags_size++] = S_REGIST_SPEC; \
		IS_LAST_COMMAND_PUSH = false;             \
	}

#define transition_check(name, command) \
	else if (!strcmp(temp, #name))      \
	{                                   \
		data_[i] = command; \
		IS_LAST_COMMAND_JMP = true;     \
	}

#define bracket_check(bracket)   \
	else if (temp[0] == bracket) \
		bracket_exe(bracket, temp, this, &flags_size, specifiers, i);

#define CHECK_ALL_REGISTERS()\
rix_check(r1, 401)			\
rix_check(r2, 402)			\
rix_check(r3, 403)			\
rix_check(r4, 404)			\
rix_check(r5, 405)			\
rix_check(r6, 406)			\
rix_check(r7, 407)			\
rix_check(r8, 408)			\
rix_check(r9, 409)			\
rix_check(r10, 410)			\
rix_check(r11, 411)			\
rix_check(r12, 412)			\
rix_check(r13, 413)			\
rix_check(r14, 414)			\
rix_check(r15, 415)			\
rix_check(r16, 416)			\
rix_check(r17, 417)			\
rix_check(r18, 418)			\
rix_check(r19, 419)			\
rix_check(r20, 420)			\
rix_check(r21, 421)			\
rix_check(r22, 422)			\
rix_check(r23, 423)			\
rix_check(r24, 424)			\
rix_check(r25, 425)			\
rix_check(r26, 426)			\
rix_check(r27, 427)			\
rix_check(r28, 428)			\
rix_check(r29, 429)			\
rix_check(r30, 430)			\
rix_check(r31, 431)			\
rix_check(r32, 432)


auto set_time(struct tm *time) -> char *;

auto define_date(void) -> char *;

auto error_process(int i, char *temp) -> int;

//auto get_byte(int digit, int number_of_bit) -> bool;

auto get_labels(Label *labels, Code *code_class) -> number_of_labels;

inline void get_lexeme(int *j, Code *code_class, char *temp);

inline void bracket_exe(char spec, char *temp, Bytecode *byte_class, int *flags_size, double *specifiers, int i);

auto define_specs(int *SPEC_NUMBER, int *SPEC_REGIST, char spec) -> int;

auto get_byte(int digit, int number_of_bit) -> bool;

#endif // ASSEM_H_INCLUDED
