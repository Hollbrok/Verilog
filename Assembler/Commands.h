#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

constexpr int MAX_SIZE_COMMAND  = 20;
constexpr int MAX_SIZE_LABLE    = 15;
constexpr int DEBUG_STATE       = 0;

constexpr int S_NUMBER_SPEC     = 1;   // push 2       S -- working with a Stack
constexpr int S_REGIST_SPEC     = 0;   // push rbx     S -- working with a Stack
constexpr int OP_DOUBLE_NUMBER  = 3;   // push [2]     OP -- working with Operative memory
constexpr int OP_DOUBLE_REGIST  = 2;   // push [rbx]   OP -- working with Operative memory
constexpr int OP_CHAR_NUM       = 5;   // push (2)
constexpr int OP_CHAR_REG       = 4;   // push (rbx)

class Stack;

            /* ! 13417 -> 11010001101001 -> hi */
#define print_assem_id(file_name)		\
    fprintf(file_name, "13417 ");

#define check_assem_id					\
	if(data_[0] != 13417)	\
		error_state_ += ERROR_ID;

#define stk_size_check(size, message, object, function)\
	if(object.function < size)	        \
    {									    \
    	printf(#message);				    \
        error_state_ += ERROR_STACK_SIZE;	\
    }                                       \


//? ERROR_MESSAGE



namespace my_commands
{
	enum Errors_code
	{
		ERROR_ID 			= 1,
		ERROR_STACK_SIZE	= 2,
		ERROR_UNKNOWN_COM	= 4,
		ERROR_CMD_PUSH		= 8,
		ERROR_CMD_POP		= 16,
		ERROR_COMPAIR		= 32,
		ERROR_STK_CALL_SIZE = 64,
		ERROR_FIND_LABEL	= 128,
		ERROR_PROC_BRACKET	= 256,
		ERROR_UNK_BRACKET	= 512,
		NUMBER_OF_ERRORS	= 10,
	};

	enum Errors_bytes
	{
		ID_ID				= 1,
		ID_STACK_SIZE		= 2,
		ID_UNKNOWN_COM		= 3,
		ID_CMD_PUSH			= 4,
		ID_CMD_POP			= 5,
		ID_COMPAIR			= 6,
		ID_STK_CALL_SIZE    = 7,
		ID_FIND_LABEL		= 8,
		ID_PROC_BRACKET 	= 9,
		ID_UNK_BRACKET		= 10,
	};

	enum Bit_positions
	{
		BIT_NUMBER 	= 1,
		BIT_D_OP	= 2,
		BIT_C_OP	= 3,
		BIT_PUSH	= 4,
		BIT_POP		= 8,

		BIT_RAX		= 1, // 1 0010 000(1)
		BIT_RBX		= 2, // 1 0010 00(1)0
		BIT_RCX		= 3, // 1 0010 0(1)00
		BIT_RDX		= 4, // 1 0010 (1)000

		BIT_EQUAL 	= 1,
		BIT_JUMP    = 2,
		BIT_ABOVE 	= 3,
		BIT_BELOW 	= 6,
	};

//                 Bits, which are used when primary defining a command:
//                      ��������� ���������� � 1
//         (*)   4 bit (push)
//         (*)   8 bit (pop)
//         (*)   2
//        (**)   9 bit (all teams, except this: HLT, PUSH, POP)
//       (***)   If 9'th bit is 0, then this is a kind of special com-
//               mands like: HLT, PUSH, POP and ERROR_ASSEM
//
    enum Commands
    {
        CMD_HLT         = 0,	// 0 (0)000 (0)000
        CMD_PUSH        = 8,	// 0 (0)000 (1)000
		CMD_POP         = 128,	// 0 (1)000 (0)000
		//CMD_ASSEM_ERROR = 23,   // 0 (0)001 (0)111

        CMD_ADD         = 256,	// 1 (0)000 (0)000
        CMD_MUL         = 257,  // 1 (0)000 (0)001
        CMD_DIV         = 258,  // 1 (0)000 (0)010
        CMD_SUB         = 259,  // 1 (0)000 (0)011
        CMD_DUMP         = 260,  // 1 (0)000 (0)100
        CMD_CMP			= 261,  // 1 (0)000 (0)101
        //CMD_POW         = 262,  // 1 (0)000 (0)110
        //CMD_SQRT        = 263,	// 1 (0)000 (0)111

        CMD_IN          = 272,	// 1 (0)001 (0)000
        CMD_OUT         = 273,  // 1 (0)001 (0)001
        CMD_DEL         = 274,  // 1 (0)001 (0)010

        //CMD_LN          = 275,  // 1 (0)001 (0)011
        //CMD_LOG10       = 276,  // 1 (0)001 (0)100
        //CMD_LABEL   	  = 277,  // 1 (0)001 (0)101
        //CMD_LOG2        = 278,  // 1 (0)001 (0)110

////////////////////////// �his is not PRIMARY commands
////////////////////////// Therefore, the reserved bits
////////////////////////// do not apply to them.

		CMD_RAX         = 289,	// 1 (0)010 (0)001
        CMD_RBX         = 290,	// 1 (0)010 (0)010
        CMD_RCX         = 292,	// 1 (0)010 (0)100
        CMD_RDX         = 296,	// 1 (0)010  1 000

//////////////////////////
//////////////////////////
//////////////////////////

        CMD_RET         = 308,  // 1 (0)011 (0)100
        CMD_CALL        = 309,	// 1 (0)011 (0)101

        //CMD_DRAW        = 310,  // 1 (0)011 (0)110
        //CMD_FILL        = 311,	// 1 (0)011 (0)111
        //CMD_ABS         = 320,	// 1 (0)100 (0)000
        //CMD_CIRC        = 321,
        //CMD_CAT         = 322,
        //CMD_KOPM        = 323,
        //CMD_MEM         = 324,	// 1 (0)100 (0)100

		CMD_JMP      	= 338,  // 1 (0)101 (0)010 ->

        CMD_JE         	= 337, 	// 1 (0)101 (0)001 ==
        CMD_JAB         = 373,	// 1 (0)111 (0)101 !=
        CMD_JAE        	= 341,	// 1 (0)101 (0)101 >=
        CMD_JBE         = 369,	// 1 (0)111 (0)001 <=
        CMD_JA         	= 340,	// 1 (0)101 (0)100 >
        CMD_JB          = 368,	// 1 (0)111 (0)000 <
	};
}


#endif // COMMANDS_H_INCLUDED
