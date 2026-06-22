#pragma once


typedef enum e_input_type {
	INPUT_STDIN,
	INPUT_STRING,
	INPUT_FILE
} t_input_type;


typedef struct s_input {
	t_input_type type;
	char         *data;
} t_input;
