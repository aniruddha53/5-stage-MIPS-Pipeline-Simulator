/*
main file
*/


#include "functions.h"
#include "read_trace.h"

int main()
{
	int Program_Counter;
	int No_of_Instructions = 0;

	read_file();	//Read the trace file

	for (int i = 0; i < Instruction_Array.size(); i++)
	{

		Dynamic_Ins_Opcode.push_back(Instruction_Array[i].substr(0, 6));
		Current_Pipelined_Ins.push_back(Instruction_Array[i]);

		No_of_Instructions++;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		//////////////////////////////////////////// R-Type Instructions ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ((Opcode_field[i] == "000000") || (Opcode_field[i] == "000010") || (Opcode_field[i] == "000100") || (Opcode_field[i] == "000110") || (Opcode_field[i] == "001000") || (Opcode_field[i] == "001010"))
		{

			int register_Rd = REG_Array[Integer_Conversion(Instruction_Array[i].substr(16, 5))];	// 17 to 21
			int register_Rs = REG_Array[Integer_Conversion(Instruction_Array[i].substr(6, 5))];		//  6 to 11
			int register_Rt = REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))];	// 12 to 16


			if (Opcode_field[i] == "000000") //ADD	
			{
				Arith_Ins_Count++;		// Increment the Arithmetic instruction counter
				register_Rd = register_Rs + register_Rt;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(16, 5))] = register_Rd;	//	Store the result to Register array
			}

			else if (Opcode_field[i] == "000010")  //SUB
			{
				Arith_Ins_Count++;
				register_Rd = register_Rs - register_Rt;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(16, 5))] = register_Rd;
			}

			else if (Opcode_field[i] == "000100") //MUL
			{
				Arith_Ins_Count++;
				register_Rd = register_Rs * register_Rt;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(16, 5))] = register_Rd;
			}

			else if (Opcode_field[i] == "000110") //OR
			{
				Logical_Ins_Count++;
				register_Rd = register_Rs | register_Rt;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(16, 5))] = register_Rd;
			}

			else if (Opcode_field[i] == "001000") //AND
			{
				Logical_Ins_Count++;
				register_Rd = register_Rs & register_Rt;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(16, 5))] = register_Rd;
			}

			else if (Opcode_field[i] == "001010") //XOR
			{
				Logical_Ins_Count++;
				register_Rd = register_Rs ^ register_Rt;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(16, 5))] = register_Rd;
			}



		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		//////////////////////////////////////////// I-Type Instructions ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ((Opcode_field[i] == "000001") || (Opcode_field[i] == "000011") || (Opcode_field[i] == "000101") || (Opcode_field[i] == "000111") || (Opcode_field[i] == "001001") || (Opcode_field[i] == "001011"))
		{

			short int Immediate_Value = Integer_Conversion(Instruction_Array[i].substr(16, 16));
			int register_Rs = REG_Array[Integer_Conversion(Instruction_Array[i].substr(6, 5))];
			int register_Rt = REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))];


			if (Opcode_field[i] == "000001")	//ADDI
			{
				Arith_Ins_Count++;
				register_Rt = register_Rs + Immediate_Value;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))] = register_Rt;
			}

			else if (Opcode_field[i] == "000011")	//SUBI
			{
				Arith_Ins_Count++;
				register_Rt = register_Rs - Immediate_Value;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))] = register_Rt;
			}

			else if (Opcode_field[i] == "000101")	//MULI
			{
				Arith_Ins_Count++;
				register_Rt = register_Rs * Immediate_Value;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))] = register_Rt;
			}

			else if (Opcode_field[i] == "000111")	//ORI
			{
				Logical_Ins_Count++;
				register_Rt = register_Rs | Immediate_Value;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))] = register_Rt;
			}

			else if (Opcode_field[i] == "001001")	//ANDI
			{
				Logical_Ins_Count++;
				register_Rt = register_Rs & Immediate_Value;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))] = register_Rt;
			}

			else if (Opcode_field[i] == "001011")	//XORI
			{
				Logical_Ins_Count++;
				register_Rt = register_Rs ^ Immediate_Value;
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))] = register_Rt;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		//////////////////////////////////////////// Control Flow Instructions ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if ((Opcode_field[i] == "001110") || (Opcode_field[i] == "001111") || (Opcode_field[i] == "010000"))
		{
			Cont_Flow_Ins_Count++;

			short int Immediate_Value = Integer_Conversion(Instruction_Array[i].substr(16, 16));
			int register_Rs = REG_Array[Integer_Conversion(Instruction_Array[i].substr(6, 5))];
			int register_Rt = REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))];



			if (Opcode_field[i] == "001110")	//BZ 
			{
				if (register_Rs == 0)
				{
					Taken_Branches.push_back(No_of_Instructions);		// .push_back() :: Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
					i = i + Immediate_Value - 1;
				}

			}

			else if (Opcode_field[i] == "001111")	//BEQ
			{
				if (register_Rs == register_Rt)
				{
					Taken_Branches.push_back(No_of_Instructions);		// As we are considering always not-taken logic, we need to see how many branches are taken 
					i = i + Immediate_Value - 1;
				}


			}

			else if (Opcode_field[i] == "010000") //JR
			{
				Taken_Branches.push_back(No_of_Instructions);
				i = (register_Rs / 4) - 1;
			}

		}


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		//////////////////////////////////////////// Memory Access Instructions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ((Opcode_field[i] == "001100") | (Opcode_field[i] == "001101"))
		{
			Mem_Access_Count++;

			short int Immediate_Value = Integer_Conversion(Instruction_Array[i].substr(16, 16));
			int register_Rs = REG_Array[Integer_Conversion(Instruction_Array[i].substr(6, 5))];
			int register_Rt = REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))];


			if (Opcode_field[i] == "001100")	//LDW
			{
				REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))] = Integer_Conversion(Instruction_Array[((register_Rs + Immediate_Value) / 4)]);
			}

			else if (Opcode_field[i] == "001101")  //STW
			{
				MEM_Array[register_Rs + Immediate_Value] = REG_Array[Integer_Conversion(Instruction_Array[i].substr(11, 5))];
				std::string my_string = std::bitset< 32 >(MEM_Array[register_Rs + Immediate_Value]).to_string(); // string conversion
				Instruction_Array[(register_Rs + Immediate_Value) / 4] = my_string;	// Storing in string format
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		//////////////////////////////////////////// HALT Instruction //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Opcode_field[i] == "010001")	//HALT
		{
			Cont_Flow_Ins_Count++;
			Program_Counter = (i + 1) * 4;
			break;							// When HALTed, increment PC and break the loop
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		


	pipelined_execution();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	dynamic_execution();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	printf("Instruction counts:\n\n");
	printf("Total number of instructions: %d \n", No_of_Instructions);
	printf("Arithmetic instructions:%d \n", Arith_Ins_Count);
	printf("Logical instructions:%d \n", Logical_Ins_Count);
	printf("Memory access instructions:%d \n", Mem_Access_Count);
	printf("Control transfer instructions:%d \n", Cont_Flow_Ins_Count);

	printf("\n---------------------------------------------------------------------------------------------------------------\n\n");

	printf("\nFinal register state: \n\n");
	std::map<int, int>::iterator j;
	printf("Program Counter: %d \n", Program_Counter);

	for (j = REG_Array.begin(); j != REG_Array.end(); j++) {
		std::cout << "R" << j->first << ": " << j->second << '\n';	// Printing Key and Printing Value
	}

	printf("\n---------------------------------------------------------------------------------------------------------------\n\n");
	printf("Final Memory state: \n\n");
	std::map<int, int>::iterator k;

	for (k = MEM_Array.begin(); k != MEM_Array.end(); k++) {
		std::cout << "Address: " << k->first << ", Contents: " << k->second << '\n';
	}

	printf("\n---------------------------------------------------------------------------------------------------------------\n\n");

	printf("\nMIPS Pipeline Timing Simulator: \n\n");
	Cycles_Without_Forwarding = (Current_Pipelined_Ins.size() + 4) + Stalls + (Taken_Branches.size() * 2);
	Cycles_With_Forwarding = (Current_Pipelined_Ins.size() + 4) + Dynamic_Load_Ins_Count + (Taken_Branches.size() * 2);


	//	printf("Total number of double stalls: %d \n", Double_Stall);

	printf("\n******Without Forwarding*****: \n\n");

	printf("Total number of stalls without forwarding: %d \n", Stalls);
	printf("Total number of data hazards: %d \n", (Double_Stall + temp_x - temp_y));
	//	printf("Total number of Branch penalties: %d \n" , (Taken_Branches.size() * 2));
	printf("Total number of branches resulting in penalties: %d \n", Taken_Branches.size());
	printf("Total number of clock cycles without forwarding: %d \n", Cycles_Without_Forwarding);

	printf("\n---------------------------------------------------------------------------------------------------------------\n\n");

	printf("\n******With Forwarding*****: \n\n");

	printf("Total number of stalls with forwarding: %d \n", (temp_x - temp_y));
	printf("Total number of data hazards: %d \n", Dynamic_Load_Ins_Count);
	//	printf("Total number of Branch penalties: %d \n" , (Taken_Branches.size() * 2));
	printf("Total number of branches resulting in penalties: %d \n", Taken_Branches.size());
	printf("Total number of clock cycles with forwarding: %d \n", Cycles_With_Forwarding);

	printf("\n---------------------------------------------------------------------------------------------------------------\n\n");

	return 0;
}