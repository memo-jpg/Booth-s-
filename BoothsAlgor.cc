// Lab4_QuestionMark.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <bitset>
unsigned short cycle_counter = 15; //when making the while-loop, -- this var 
unsigned short ac = 0;	 
std::bitset<16>ACC(ac);
unsigned short MQ_0 = 0;
std::bitset<16>result;
int tracker = 0;

//1) Implement a simulator for 1-bit ALU, which manipulates addition and subtraction operations
int OneALU(int a, int b, int CarryIn, std::string OP){
	int CarryOut = 0;
	if(OP == "add" or OP == "Add" or OP == "ADD"){
		if(tracker < 16){
			result[tracker] = a^b^CarryIn;
			tracker++;
		}//end of this if
	CarryOut = (a*b) + CarryIn*(a^b);
	//CarryOut = (!a && b) || (!(a^b) && CarryIn);
	return CarryOut;
	} //end of this if
	
	else if(OP == "sub" or OP == "Sub" or OP == "SUB"){
		if(b == 0) b = 1;
		else b = 0;
		if(tracker < 16){
			result[tracker] = a^b^CarryIn;
            tracker++;
        }//end of this if
	CarryOut = (a*b) + CarryIn*(a^b);
	//CarryOut = (!a && b) || (!(a^b) && CarryIn);
	return CarryOut;
	}//end of else if
} //end OneALU_Add()


//2) Implement a simulator for 16-bit ALU, which uses 1-bit ALU as a subcomponent
int ALU(std::bitset<16>a, std::bitset<16>b, std::string OP){
	int CarryIn = 0;
	tracker = 0; //reset tracker back to 0
	result = 0; //reset result back to 0
	if(OP == "sub" or OP == "Sub" or OP == "SUB"){
		if(a[0] == 0 && b[0] == 1) CarryIn = 1;
	}//end of if(sub)
	for(int i = 0; i < 16; i++){
		CarryIn = OneALU(a[i], b[i], CarryIn, OP);
	}//end of for() loop
	
	if(OP == "add" or OP == "Add" or OP == "ADD"){
		ACC[0] = CarryIn; 	
	}

	ACC = result;
	return CarryIn;

} //end of ALU()


//3) Implement a simulator for the Booth's multiplier, which uses 16bit ALU as a subcomponent;
	// This midule should have the following subcomponents too:
		// registers MD, AC, MQ (16 bits each), and 4-bit cycle_counter (initialized to binary "1111")
		// This module is responible for displaying the contents of the registers at each cycle and returns product
void BoothsAlgor(std::bitset<16>MD, std::bitset<16>MQ){ 
	int Carry = 0;
	std::bitset<1> MQ_1{MQ_0}; //always starts at 0
	std::bitset<4>CC{cycle_counter};

	std::cout << "Cycle Counter: \t\t MD: \t\t\t AC: \t\t\t MQ: \t\t\t MQ_1 BIT: " << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << CC << " \t\t\t " << MD << " \t " << ACC << " \t " << MQ << " \t " << MQ_1 << std::endl;
	std::cout << std::endl;
	for(int i = 0; i < 16; i++){
		//int q = 0;
		//short e = 1;
	//Store the original value of MQ & MQ_1
	std::bitset<16>MQ_OG = MQ;
	std::bitset<1>MQ_1_OG = MQ_1;

		//Manually setting the thingy-thing up
		//std::cout << MQ[0] << " is MQ[0] and MQ_1[0] is: " << MQ_1[0] << std::endl;
		if(MQ[0] == 0 and MQ_1[0] == 0) {} //AC no change, so y call ALU()?
		else if(MQ[0] == 0 and MQ_1[0] == 1) {Carry = ALU(ACC, MD, "Add");} //not reaching this?
		else if(MQ[0] == 1 and MQ_1[0] == 0) {Carry = ALU(ACC, MD, "Sub");} //not reachign this?
		else if(MQ[0] == 1 and MQ_1[0] == 1) {} //AC no change, so y call ALU() pt.2?

	//Restoring the original values of MQ and MQ_1
	MQ = MQ_OG;
	MQ_1 = MQ_1_OG;

	//and now we do shifting
	MQ_1[0] = MQ[0];
	MQ = MQ >> 1;
	MQ[15] = ACC[0];

	ACC = ACC >> 1;
	ACC[15] = ACC[14];

	std::cout << CC << " \t\t\t " << MD << " \t " << ACC << " \t " << MQ << " \t " << MQ_1 << std::endl; 
	std::cout << std::endl;
	cycle_counter--;
	CC = cycle_counter;
	}//end of for loop()

	std::cout << "Final Product: " << ACC << MQ << std::endl;
} //end of Booth's Algorithm


//4) You should write a driver (i.e main function), which accesses 2 input operands (16 bit binary each) from keyboard or data file, 
	// calls the Booth's multiplier by passing the operands as arguments, and displays the product return from the Booth's multiplier.
int main(){ //start main
std::bitset<16>mulcand;
std::bitset<16>mulplier;

std::cout << "Enter 16-bit multiplicand(MD): " << std::endl;
std::cin >> mulcand;
std::cout << "Enter 16-bit multiplier(MQ): " << std::endl;
std::cin >> mulplier;

std::cout << mulcand << "\t" << mulcand[0] << " " << mulcand[15] << std::endl;

BoothsAlgor(mulcand, mulplier);


} //end of main()

