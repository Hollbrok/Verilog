#include "assem.h"

//static int NEW_COMMAND_ERROR = 0; // If unknown command -- leave from assembling
static int IS_LAST_COMMAND_PUSH = 0;
static int IS_LAST_COMMAND_JMP = 0;


Text::Text(FILE *user_code, bool need_dump) :
	data_(nullptr),
	lines_(nullptr),
	num_of_lines_(0),
	length_file_(0),
	user_code_(user_code)
{
	assert(this && "You passed nullptr to Text construct\n");
	assert(user_code && "You must pass file* to text construct");

	// get_length(user_code);
	get_num_of_lines_buffer_length_of_file();

	lines_ = (Line*) calloc(num_of_lines_ + 1, sizeof(Line));
	assert(lines_ && "Can't calloc memory for lines_");

	Line *lines = (Line *)calloc(num_of_lines_ + 1, sizeof(Line));
	assert(lines && "Can't calloc memory for lines");

	get_lines_pointer(lines);

	free(lines);
	lines = nullptr;

	if(need_dump)
		dump();
}

int Text::get_length_file()
{
	assert(this && "You passed nullptr to get_length\n");
	return length_file_;
}

int Text::get_num_of_lines()
{
	assert(this && "You passed nullptr to get_num_of_line\n");
	return num_of_lines_;
}

int Text::get_length(size_t number_of_line)
{
	assert(this && "You passed nullptr to get_length\n");
	return lines_[number_of_line].length;
}

char Text::get_char(size_t number_of_line, size_t number_of_char)
{
	assert(this && "You passed nullptr to get_char\n");
	return lines_[number_of_line].line[number_of_char];
}

void Text::get_num_of_lines_buffer_length_of_file()
{
	// assert(user_code && "You must pass file* to get_num_of_lines");

	fseek(user_code_, 0, SEEK_END);
	long file_length = ftell(user_code_);
	fseek(user_code_, 0, SEEK_SET);

	file_length++;

	data_ = (char*) calloc(file_length, sizeof(char));
	assert(data_ && "Can't calloc memory for data_\n");

	while ((data_[length_file_] = fgetc(user_code_)) && (!feof(user_code_)))
	{
		if (data_[length_file_] == '\n')
			num_of_lines_++;
		length_file_++;
	}

	return;
}

void Text::get_lines_pointer(Line *lines)
{
	long length = 0;
	long n_structs = 0;

	while (true)
	{
		int iter_length = 0;

		while (isspace(data_[length]))
			length++;

		if (length >= length_file_)
			break;

		lines[n_structs].line = &(data_)[length];

		while ((data_[length] != '\n') && (length < length_file_))
		{
			if ((data_[length] == ';'))
			{
				while (data_[length] != '\n')
					length++;
				break;
			}
			length++;
			iter_length++;
		}

		lines[n_structs].length = iter_length;
		while (isspace(lines[n_structs].line[lines[n_structs].length - 1]))
			(lines[n_structs].length)--;

		n_structs++;
	}

	for (int j = 0; j < n_structs; j++)
	{
		lines_[j].line = lines[j].line;
		lines_[j].length = lines[j].length;
	}

	num_of_lines_ = n_structs;

	return;
}

void Text::dump()
{
	FILE *info = fopen("[!]info.txt", "w");
	assert(info);

	fprintf(info, "Number of lines      = %d\n", num_of_lines_);
	fprintf(info, "Length of the file   = %d\n", length_file_);

	for (int x = 0; x < num_of_lines_; x++)
	{
		fprintf(info, "lines[%d]. [", x + 1);

		for (int y = 0; y < lines_[x].length; y++)
			fprintf(info, "%c", lines_[x].line[y]);

		fprintf(info, "]\n");
		fprintf(info, "\tlength = %ld\n\n", lines_[x].length);
	}

	fclose(info);
}

Text::~Text()
{
	assert(this && "Ypu passed nullptr to destructor\n");
	free(data_);
	data_ = nullptr;

	free(lines_);
	lines_ = nullptr;

	num_of_lines_ = -1;
	length_file_  = -1;

}

//!

Code::Code(Text* text_class, bool need_dump) :
	data_(nullptr),
	length_(0),
	terms_(0),
	cur_size_(0)
{
	assert(text_class && "You passed nullptr(text_class) to Code construct\n");
	assert(this && "You passed nullptr to Code construct\n");

	length_ = text_class->get_length_file() + 3; // may be without + 3

	data_ = (char *)calloc(length_, sizeof(char));
	assert(data_ && "Can't calloc data_ in Code construct\n");

	int cur_size = 0;

	for (int x = 0; x < text_class->get_num_of_lines(); x++)
	{
		for (int y = 0; y < text_class->get_length(x); y++)
		{
			data_[cur_size++] = text_class->get_char(x, y);
			if (isspace(text_class->get_char(x, y)))
				while (isspace(text_class->get_char(x, y + 1)))
					y++;
		}
		if ((cur_size < length_ + 1))
			data_[cur_size++] = ' ';
	}

	data_[cur_size] = '\0';
	int terms = 0;
	terms_ = terms;

	for (int i = 0; i < length_; i++)
		if (data_[i] == ' ')
		{
			terms_++;
			while (isspace(data_[i]))
				i++;
		}

	if(need_dump)
		dump();
}

void Code::dump()
{
	assert(this && "You passed nullptr to dump\n");

	FILE *code_text = fopen("[!]code_dump.txt", "w");
	assert(code_text && "Can't open [!]code_dump.txt in Code dump\n");

	fwrite(data_, sizeof(char), strlen(data_), code_text); // length_ -> strlen(data_);
}

Code::~Code()
{
	assert(this && "You passed nullptr to Code destruct\n");

	free(data_);
	data_ = nullptr;

	length_ 	= -1;
	terms_	 	= -1;
	cur_size_ 	= -1;
}

int Code::get_terms()
{
	assert(this && "You passed nullptr to get_terms\n");
	return terms_;
}

void Code::set_cur_size(size_t number)
{
	assert(this && "You passed nullptr to set_cur_size\n");
	cur_size_ = number;
}

int Code::get_cur_size()
{
	assert(this && "You passed nullptr to get_cur_size\n");
	return cur_size_;
}

char Code::get_char(size_t number)
{
	return data_[number];
}

Bytecode::Bytecode(Code *code_class, bool need_debug) :
    error_state_(0),
    bytecode_capacity_(0)
{
	assert(code_class && "You passed nullptr(code_class) to Bytecode construct\n");
	assert(this && "You passed nullptr(this) to Bytecode \n");

	using namespace my_commands;
	bool IS_LAST_COMMAND_ADD = false;
	bool IS_LAST_COMMAND_CMP = false;

	Label *labels = (Label *)calloc(MAX_LABELS + 1, sizeof(Label));
	assert(labels);

	int amount_labels = get_labels(labels, code_class);

	data_ = (double *) calloc(code_class->get_terms(), sizeof(double));
	assert(data_ && "Can't calloc memory for data_\n");

	unknown_command_ = (char*) calloc(MAX_SIZE_COMMAND, sizeof(char));
	assert(unknown_command_ && "Can't calloc memory for unknown_command_\n");

	double *specifiers = (double *)calloc(code_class->get_terms(), sizeof(double));
	assert(specifiers);

	int flags_size = 0;
	code_class->set_cur_size(0); // cur_size = 0;

	char *temp = (char *)calloc(MAX_SIZE_COMMAND, sizeof(char));
	assert(temp);

	bool FIND_HLT = false;

	int i = 0;
	for (i; (i < code_class->get_terms()) && !FIND_HLT; i++)
	{
		if (error_state_)
		{
            printf("error state\n");
			break;
        }
		int j = 0;
		get_lexeme(&j, code_class, temp);

		code_class->set_cur_size(j + 1 + code_class->get_cur_size()); //code_class->cur_size += j + 1;

		if (!strcmp(temp, "push"))
		{
			data_[i] = CMD_PUSH;
			IS_LAST_COMMAND_PUSH = true;
			//printf("\tfind push on i = %d\n", i);
		}
		else if (!strcmp(temp, "pop"))
		{
			data_[i] = CMD_POP;
		}
		else if (!strcmp(temp, "add"))
		{
			data_[i] = CMD_ADD;
			IS_LAST_COMMAND_ADD = true;
			printf("FIND ADD\n");
		}
		else if (!strcmp(temp, "cmp"))
		{
			data_[i] = CMD_CMP;
			IS_LAST_COMMAND_CMP = true;
		}
		else if (!strcmp(temp, "hlt"))
		{
			data_[i] = CMD_HLT;
			FIND_HLT = true;
			printf("FIND HLT i = %d\n", i);
		}
		cmd_check(mul, CMD_MUL)
		cmd_check(div, CMD_DIV)
		cmd_check(sub, CMD_SUB)
		cmd_check(in, CMD_IN)
		cmd_check(out, CMD_OUT)
		cmd_check(del, CMD_DEL)
		cmd_check(ret, CMD_RET)
		cmd_check(dmp, CMD_DUMP)
		else if (IS_LAST_COMMAND_CMP)
		{
			for (int y = 0; y < 2; y++)
			{
				if (isdigit(temp[0]))
				{
					data_[i] = (double)std::atof(temp);
					specifiers[flags_size++] = S_NUMBER_SPEC;
				}
				CHECK_ALL_REGISTERS()
				else printf("dich\n");

				if (y < 1)
				{
					i++;
					get_lexeme(&j, code_class, temp);
					code_class->set_cur_size(j + 1 + code_class->get_cur_size());
				}

			}

			bytecode_capacity_++;
			IS_LAST_COMMAND_CMP = false;
		}
		else if (IS_LAST_COMMAND_ADD)
		{
			printf("IN ADD\n");
			for (int y = 0; y < 3; y++)
			{
				if (isdigit(temp[0]))
				{
					data_[i] = (double)std::atof(temp);
					specifiers[flags_size++] = S_NUMBER_SPEC;
				}
				CHECK_ALL_REGISTERS()
				else printf("dich\n");

				if (y < 2)
				{
					i++;
					get_lexeme(&j, code_class, temp);
					code_class->set_cur_size(j + 1 + code_class->get_cur_size());
				}

			} 
			bytecode_capacity_ += 2;
			IS_LAST_COMMAND_ADD = false;
		}

		CHECK_ALL_REGISTERS()

		else if (IS_LAST_COMMAND_PUSH)
		{
			//printf("\tfind push argument on i = %d\n", i);
			data_[i] = (double)std::atof(temp);
			specifiers[flags_size++] = S_NUMBER_SPEC;
			IS_LAST_COMMAND_PUSH = false;
		}

		transition_check(je, CMD_JE)
		transition_check(jab, CMD_JAB)
		transition_check(jae, CMD_JAE)
		transition_check(jbe, CMD_JBE)
		transition_check(ja, CMD_JA)
		transition_check(jb, CMD_JB)
		transition_check(call, CMD_CALL)
		transition_check(jmp, CMD_JMP)

		else if (IS_LAST_COMMAND_JMP)
		{
			temp++;

			bool FIND_LABEL = false;
			for (int index = 0; index < amount_labels; index++)
				if (!strcmp(temp, labels[index].name))
				{
					data_[i] = labels[index].adress;
					FIND_LABEL = true;
					break;
				}
			if (!FIND_LABEL)
			{
				set_error_state(get_error_state() + ERROR_FIND_LABEL);
				break;
			}
			temp--;
			IS_LAST_COMMAND_JMP = false;
		}
		else
		{
			set_error_state(get_error_state() + error_process(i, temp));
			//!
			set_unknown_command(temp);
            //strcpy(byte_struct->unknown_command, temp);
			free(temp);
			temp = nullptr;
			break;
		}

		bytecode_capacity_++;
	}

	printf("AT THE END i = %d, bytecode_capacity_  = %d\n", i, bytecode_capacity_);
	if (get_error_state())
	{
		free(specifiers);
        specifiers = nullptr;

		free(labels);
        labels = nullptr;

        free(temp);
        temp = nullptr;

        FILE *assembler_txt = fopen("[!]assembler_code.txt", "w");
        assert(assembler_txt && "Can't open file assembler_code.txt");

        fprintf(assembler_txt, "666");

		determine_status();
		fclose(assembler_txt);
		return;

	}

	determine_status();

	FILE *assembler_txt = fopen("[!]assembler_code.txt", "w");
	assert(assembler_txt && "Can't open file assembler_code.txt");


    print_assem_id(assembler_txt)

	for (int i = 0; i < flags_size; i++)
	{
		printf("[%lg]", specifiers[i]);
	}
	printf("\n");
	for (int i = 0; i < bytecode_capacity_; i++)
	{
		printf("[%lg]", data_[i]);
	}

    flags_size = 0;
	//printf("\n\n");
	for (int i = 0; i < bytecode_capacity_ ; i++)
	{
		if ((static_cast<int>(data_[i]) == CMD_POP) || (static_cast<int>(data_[i]) == CMD_PUSH))
		{
			//fprintf(assembler_txt,"\n1. \t");
			fprintf(assembler_txt, "%lg %lg ", data_[i++], specifiers[flags_size++]);
			fprintf(assembler_txt, "%lg ", data_[i]);
		}
		else if (static_cast<int>(data_[i]) == CMD_ADD)
		{
			//fprintf(assembler_txt, "\n2. \t");
			fprintf(assembler_txt, "%lg ", data_[i++]);
			fprintf(assembler_txt, "%lg %lg ", specifiers[flags_size++], data_[i++]);
			fprintf(assembler_txt, "%lg %lg ", specifiers[flags_size++], data_[i++]);
			fprintf(assembler_txt, "%lg %lg ", specifiers[flags_size++], data_[i]);
		}
		else if (static_cast<int>(data_[i]) == CMD_CMP)
		{
			//fprintf(assembler_txt, "\n3. \t");
			fprintf(assembler_txt, "%lg ", data_[i++]);
			fprintf(assembler_txt, "%lg %lg ", specifiers[flags_size++], data_[i++]);
			fprintf(assembler_txt, "%lg %lg ", specifiers[flags_size++], data_[i]);
		}
		else
		{
			//fprintf(assembler_txt, "\n4. \t");
			printf("i = %d, cap = %d\n", i, bytecode_capacity_);
			fprintf(assembler_txt, "%lg ", data_[i]);
		}
	}
	free(specifiers);
    specifiers = nullptr;

	/*for (int y = 0; y < amount_labels; y++)
		if (labels[y].name)
			free(labels[y].name);*/

	free(labels);
	labels = nullptr;

	free(temp);
	temp = nullptr;

	fclose(assembler_txt);
}

void Bytecode::set_error_state(int number)
{
	assert(this && "You passed nullptr to set_error_state");
	error_state_ = number;
}

int Bytecode::get_error_state()
{
	assert(this && "You passed nullptr to get_error_state");
	return error_state_;

}

char* Bytecode::get_unknown_command()
{
	assert(this && "You passed nullptr to get_unknown_command\n");
	return unknown_command_;
}

void Bytecode::set_unknown_command(char* command)
{
	assert(this && "You passed nullptr(this) to set_unknown command");
	assert(command && "You passed nullptr command\n");

	for(int i = 0; i < strlen(command); i++)
		unknown_command_[i] = command[i];
}

void Bytecode::determine_status()
{
	using namespace my_commands;

	FILE *error = fopen("[!]DUMP_ASSEM.txt", "w");
	assert(error);

	fprintf(error, "\tData of DUMP in Assembler : %s (dd/mm/yy)\n\n", define_date());

	if (!error_state_)
		print_good(error);
	else
		for (int i = 0; i < NUMBER_OF_ERRORS; i++)
			if (get_byte(error_state_, i + 1))
				print_error(error, i + 1);

	fclose(error);
}

void Bytecode::print_good(FILE* error)
{
	assert(error && "file is nullptr\n");
	fprintf(error, "Assem ended without any errors\n");
}

void Bytecode::print_error(FILE* error, int error_bit)
{
	using namespace my_commands;
	switch (error_bit)
	{
	case ID_UNKNOWN_COM:
		fprintf(error, "Assembler met unknown command #%s#\n", unknown_command_);
		break;
	case ID_FIND_LABEL:
		fprintf(error, "Cann't find label\n");
		break;
	case ID_PROC_BRACKET:
		fprintf(error, "Error in processing of brackets\n");
		break;
	case ID_UNK_BRACKET:
		fprintf(error, "Unknown type of bracket\n");
		break;
	default:
		fprintf(error, "Error in ERRORS. IT means that program has unknown error\n");
		break;
	}
}

Bytecode::~Bytecode()
{
	assert(this && "You passed nullptr to destruct\n");

	free(data_);
	data_ = nullptr;

	free(unknown_command_);
	unknown_command_ = nullptr;

	bytecode_capacity_ = -1;
	error_state_ = -1;
}

inline void get_lexeme(int *j, Code *code_class, char *temp)
{
	for ((*j) = 0; (*j) < MAX_SIZE_COMMAND; (*j)++)
	{
		if (code_class->get_char(*j + code_class->get_cur_size()) != ' ')
			temp[*j] = code_class->get_char(*j + code_class->get_cur_size());
		else
		{
			temp[*j] = '\0';
			break;
		}
	}
}

auto get_labels(Label *labels, Code *code_class) -> number_of_labels
{
	/*for (int y = 0; y < MAX_LABELS; y++)
	{
		labels[y].name = (char *)calloc(MAX_LABEL_SIZE, sizeof(char));
		assert(labels[y].name);
	}*/

	char *temp = (char *)calloc(MAX_SIZE_COMMAND, sizeof(char));
	assert(temp);

	int cur_labels = 0;
	code_class->set_cur_size(0);

	for (int i = 0; i < code_class->get_terms(); i++)
	{
		int iter = 0;
		get_lexeme(&iter, code_class, temp);

		if (temp[strlen(temp) - 1] == ':')
		{
			strncpy(labels[cur_labels].name, temp, strlen(temp) - 1);

			labels[cur_labels].length = strlen(temp);

			labels[cur_labels++].adress = i;
		}
		code_class->set_cur_size(code_class->get_cur_size() + iter + 1);
		//code_struct->cur_size += iter + 1;
	}

	code_class->set_cur_size(0); // = 0;
	free(temp);

	return cur_labels; //int amount_labels = cur_labels;
}

    // [rbx] <- temp
inline void bracket_exe(char spec, char *temp, Bytecode *byte_class, int *flags_size, double *specifiers, int i)
{
	using namespace my_commands;

	int SPEC_NUMBER = 0;
	int SPEC_REGIST = 0;

	byte_class->set_error_state(byte_class->get_error_state() + define_specs(&SPEC_NUMBER, &SPEC_REGIST, spec));

	if (isdigit(*(temp + 1)))
	{
		byte_class->set_int_to_data(i, std::atoi(temp + 1) );
		//byte_struct->data[i] = std::atoi(temp + 1);
		specifiers[(*flags_size)++] = SPEC_NUMBER;
		IS_LAST_COMMAND_PUSH = false;
	}
	else if (strlen(temp) == 5)
	{
		char new_temp[] = {temp[1], temp[2], temp[3]};
		if (!strncmp(new_temp, "rax", 3))
		{
			byte_class->set_int_to_data(i, CMD_RAX);
			//byte_struct->data[i] = CMD_RAX;
			specifiers[(*flags_size)++] = SPEC_REGIST;
			IS_LAST_COMMAND_PUSH = false;
		}
		else if (!strncmp(new_temp, "rbx", 3))
		{
			byte_class->set_int_to_data(i, CMD_RBX);
			//byte_struct->data[i] = CMD_RBX;
			specifiers[(*flags_size)++] = SPEC_REGIST;
			IS_LAST_COMMAND_PUSH = false;
		}
		else if (!strncmp(new_temp, "rcx", 3))
		{
			byte_class->set_int_to_data(i, CMD_RCX);//
			//byte_struct->data[i] = CMD_RCX;
			specifiers[(*flags_size)++] = SPEC_REGIST;
			IS_LAST_COMMAND_PUSH = false;
		}
		else if (!strncmp(new_temp, "rdx", 3))
		{
			byte_class->set_int_to_data(i, CMD_RDX);
			//byte_struct->data[i] = CMD_RDX;
			specifiers[(*flags_size)++] = SPEC_REGIST;
			IS_LAST_COMMAND_PUSH = false;
		}
	}
	else
	{
		printf("Something went wrong in ()\n");
		byte_class->set_error_state(byte_class->get_error_state() + ERROR_PROC_BRACKET);
		//byte_struct->error_state += ERROR_PROC_BRACKET;
	}
}

void Bytecode::set_int_to_data(size_t number, int digit)
{
	assert(this && "You passed nullptr to sen_int_to_data\n");
	data_[number] = digit;
}

auto error_process(int i, char *temp) -> int
{
	using namespace my_commands;


	printf("Unknown command error in i = %d\n", i);

	return ERROR_UNKNOWN_COM;
}

auto set_time(struct tm *time) -> char *
{
	char string_time[size_time] = {};
	char *tmp = nullptr;

	strftime(string_time, size_time, "%d.%m.%Y %H:%M:%S, %A", time);

	tmp = (char *)malloc(sizeof(string_time));
	strcpy(tmp, string_time);

	return tmp;
}

auto define_date(void) -> char*
{
	const time_t timer = time(nullptr);
	struct tm *local_time = localtime(&timer);

	return set_time(local_time);
}

auto define_specs(int *SPEC_NUMBER, int *SPEC_REGIST, char spec) -> int
{
	using namespace my_commands;

	if (spec == '[')
	{
		*SPEC_NUMBER = OP_DOUBLE_NUMBER;
		*SPEC_REGIST = OP_DOUBLE_REGIST;
	}
	else if (spec == '(')
	{
		*SPEC_NUMBER = OP_CHAR_NUM;
		*SPEC_REGIST = OP_CHAR_REG;
	}
	else
	{
		printf("Something went wrong in define bracket\n");
		return ERROR_UNK_BRACKET;
	}
	return 0;
}

auto get_byte(int digit, int number_of_bit) -> bool
{
    return (bool((1 << (number_of_bit - 1))  &  digit));
}
