/*
Header file for reading input trace file
*/

#include "functions.h"
#ifndef READ_TRACE
#define READ_TRACE

void read_file()
{
	unsigned long integer_current_ins;
	std::ifstream input_trace_file("final_proj_trace.txt");	// Reading input trace file
	//std::ifstream input_trace_file("sample_memory_image.txt");
	std::string traced_data((std::istreambuf_iterator<char>(input_trace_file)), (std::istreambuf_iterator<char>()));
	std::stringstream stream_traced_data(traced_data);

	do		
	{
		std::string string_current_ins;
		std::stringstream hex_current_ins;  		//Objects of this class use a string buffer that contains a sequence of characters. This sequence of characters can be accessed directly as a string object, using member str
		getline(stream_traced_data, string_current_ins, '\n');		// from where to read the input, where to store the input, delimiter
		hex_current_ins << std::hex << string_current_ins;		// Convert each line to hex and store in hex_current_ins
		hex_current_ins >> integer_current_ins;							// *Converting to unsigned int format
		std::bitset<32> bit_format(integer_current_ins);				// 32-bit format
		std::string traced_data_string = bit_format.to_string();	// returns the string representation of value
		Opcode_field.push_back(traced_data_string.substr(0, 6)); // Storing first six bits to Opcode_field
		Instruction_Array.push_back(traced_data_string);				// Pushing each line to Instruction_Array
	} while (stream_traced_data.good());	//stream is good enough to work with or not

}

#endif 
