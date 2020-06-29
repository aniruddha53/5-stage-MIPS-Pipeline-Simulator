/*
Header file for integer conversion, pipelined and dynamic execution functions.
*/


#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>			// cin, cout 
#include <string>			// String objects
#include <map>				// Maps are associative containers that store elements formed by a combination of a key value and a mapped value
#include <vector>			// Vectors are sequence containers representing arrays that can change in size.
#include <fstream>			// input output filestream class
#include <bitset>			// A bitset stores bits (elements with only two possible values: 0 or 1, true or false, ...)
#include <sstream>			// Header providing string stream classes



int Arith_Ins_Count = 0, Logical_Ins_Count = 0, Mem_Access_Count = 0, Cont_Flow_Ins_Count = 0;

int temp_a = 0, temp_x = 0, temp_y = 0, temp_z = 0;

int Stalls, Double_Stall, Single_Stall;

std::vector<int> Double_Stall_Array;
std::vector<int> Single_Stall_Array;

int Dynamic_Load_Ins_Count;
std::vector<std::string> Dynamic_Ins_Opcode;
std::map<int, std::map<int, int>> Current_Dy_Instruction;	// For dynamic pipelined simulation of instructions

int Cycles_Without_Forwarding, Cycles_With_Forwarding;

std::vector<std::string> Opcode_field;	// To store the Opcode_field

std::map<int, int> REG_Array;		// R0 to R31 
std::map<int, int> MEM_Array;		// 0 H to 4096 H
std::vector<std::string> Instruction_Array;	// *For storing data of registers

std::vector<std::string> Current_Pipelined_Ins;	// TO store the pipeline instruction
std::vector<int> Taken_Branches;


int Integer_Conversion(std::string data)
{
	return std::stoul(data, 0, 2);	// Converts string to unsigned integer	
}


void pipelined_execution()
{
	for (int i = 0; i < Current_Pipelined_Ins.size(); i++) // For all the instructions on the Pipeline
	{
		Current_Dy_Instruction[i][0] = Integer_Conversion(Current_Pipelined_Ins[i].substr(0, 6));				// Element 0 :: Getting integer value of Opcode_field


		if (Current_Dy_Instruction[i][0] == 0)	//ADD
		{
			Current_Dy_Instruction[i][3] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 3 :: register_Rs
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 2 :: register_Rt 
			Current_Dy_Instruction[i][1] = Integer_Conversion(Current_Pipelined_Ins[i].substr(16, 5));		// Element 1 :: register_Rd
		}

		else if (Current_Dy_Instruction[i][0] == 2)		//SUB
		{
			Current_Dy_Instruction[i][3] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 3 :: register_Rs
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 2 :: register_Rt 
			Current_Dy_Instruction[i][1] = Integer_Conversion(Current_Pipelined_Ins[i].substr(16, 5));		// Element 1 :: register_Rd
		}

		else if (Current_Dy_Instruction[i][0] == 4)		//MUL
		{
			Current_Dy_Instruction[i][3] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 3 :: register_Rs
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 2 :: register_Rt 
			Current_Dy_Instruction[i][1] = Integer_Conversion(Current_Pipelined_Ins[i].substr(16, 5));		// Element 1 :: register_Rd
		}

		else if (Current_Dy_Instruction[i][0] == 6)		//OR
		{
			Current_Dy_Instruction[i][3] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 3 :: register_Rs
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 2 :: register_Rt 
			Current_Dy_Instruction[i][1] = Integer_Conversion(Current_Pipelined_Ins[i].substr(16, 5));		// Element 1 :: register_Rd
		}

		else if (Current_Dy_Instruction[i][0] == 8)		//AND
		{
			Current_Dy_Instruction[i][3] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 3 :: register_Rs
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 2 :: register_Rt 
			Current_Dy_Instruction[i][1] = Integer_Conversion(Current_Pipelined_Ins[i].substr(16, 5));		// Element 1 :: register_Rd
		}

		else if (Current_Dy_Instruction[i][0] == 10)	//XOR
		{
			Current_Dy_Instruction[i][3] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 3 :: register_Rs
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 2 :: register_Rt 
			Current_Dy_Instruction[i][1] = Integer_Conversion(Current_Pipelined_Ins[i].substr(16, 5));		// Element 1 :: register_Rd
		}

		else if (Current_Dy_Instruction[i][0] == 14)	//BZ
		{
			Current_Dy_Instruction[i][3] == 9999 + i;														// Element 3
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 2 :: register_Rs
			Current_Dy_Instruction[i][1] == 99 + i;															// Element 1 
		}

		else if (Current_Dy_Instruction[i][0] == 15)	//BEQ
		{
			Current_Dy_Instruction[i][3] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 3
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 2 :: register_Rs
			Current_Dy_Instruction[i][1] == 99 + i;															// Element 1 
		}

		else if (Current_Dy_Instruction[i][0] == 16)	//JR
		{
			Current_Dy_Instruction[i][3] == 9999 + i;														// Element 3
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 2 :: register_Rs
			Current_Dy_Instruction[i][1] == 99 + i;															// Element 1  
		}


		else 	// For ADDI, SUBI, MULI,  ORI, ANDI, XORI 
		{
			Current_Dy_Instruction[i][3] == 9999 + i;														// Element 3 ::	Immediate value
			Current_Dy_Instruction[i][2] = Integer_Conversion(Current_Pipelined_Ins[i].substr(6, 5));		// Element 2 ::	register_Rs
			Current_Dy_Instruction[i][1] = Integer_Conversion(Current_Pipelined_Ins[i].substr(11, 5));		// Element 1 :: register_Rt
		}

	}
}

void dynamic_execution()
{
	for (int i = 0; i < Current_Dy_Instruction.size(); i++)
	{
		if (Current_Dy_Instruction[i][0] == 17)
		{			// If HALT string_current_ins, then break the loop
			break;
		}
		if ((Current_Dy_Instruction[i][0] != 13) && (Current_Dy_Instruction[i][0] != 14) && (Current_Dy_Instruction[i][0] != 15) && (Current_Dy_Instruction[i][0] != 16))
		{// When not Store, BZ, BEQ or JR, then : Because they cannot cause the hazards
			if ((temp_z == 0) && ((Current_Dy_Instruction[i][1] == Current_Dy_Instruction[i + 2][2]) || (Current_Dy_Instruction[i][1] == Current_Dy_Instruction[i + 2][3])))
			{
				for (int i = 0; i < Taken_Branches.size(); ++i)
				{
					if (Taken_Branches[i] == (i + 2))
					{
						temp_a = i;
					}
					else
					{
						temp_a = -1;
					}
				}

				if (temp_a == -1)
				{
					Single_Stall_Array.push_back(i);
					Stalls++;
					temp_x += 1;
					temp_z = 1;
				}
			}

			if ((Current_Dy_Instruction[i][1] == Current_Dy_Instruction[i + 1][2]) || (Current_Dy_Instruction[i][1] == Current_Dy_Instruction[i + 1][3]))
			{// When denstination register_Rd of previous string_current_ins is source register_Rs or register_Rt for next string_current_ins
				if (Current_Dy_Instruction[i][0] == 12)
				{
					Dynamic_Load_Ins_Count++;
				}
				if (temp_z == 1)
				{
					Stalls += 1;
					temp_y += 1;
				}
				else
				{
					Stalls += 2;
				}
				Double_Stall_Array.push_back(i);
				Double_Stall++;
				temp_z = 2;
			}

			else
			{
				temp_z = 0;
			}
		}

	}
}

#endif 
