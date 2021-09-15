#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<cmath>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <sstream>
#include <fstream>

class pwGen {
	// Non-modifiable variable
	int passwordLength; 
	int passwordVar;
	int specSymbSpec;
	int numbSpec;
	int upCaseSpec;
	int lowCaseSpec;
	int numbPW;
	std::map <int, std::vector<int> > genPWStorage;

public:
	int userDesiredLength; // Modifiable variable

	pwGen();
	~pwGen();

	void executorFunction(); // Main Operator Function
	void pwGeneration(); 	// High Strenght Password Generation
	std::vector<int> randomASCIIvector(int userDesiredLength); // ASCII Generator
	bool asciiQualityCheck(std::vector<int> randVector, int specSymbSpec, int numbSpec, int upCaseSpec, int lowCaseSpec); // Checks if meets desired specifications
	std::map<int, std::string> convertToString();
	void printPW(); // Output Generated Password in a File

	// Functions related to private parameter passwordLength.
	void writeToPWLength(int userDesiredLength); 
	int readFromPWLength();

	// Functions related to private parameter passwordVar.
	void writeToPWVar(int genPassword);
	int readFromPWVar();

	// Function related to private parameter specSymbSpec.
	void writeToSpecSymbSpec(int specSymbSpec);
	int readFromSpecSymbSpec();

	// Function related to private parameter numbSpec.
	void writeToNumbSpec(int numbSpec);
	int readFromNumbSpec();

	// Function related to private parameter upCaseSpec.
	void writeToUpCaseSpec(int upCaseSpec);
	int readFromUpCaseSpec();

	// Function related to private parameter lowCaseSpec.
	void writeToLowCaseSpec(int lowCaseSpec);
	int readFromLowCaseSpec();

	// Function related to private parameter lowCaseSpec.
	void writeToNumbPW(int numbPW);
	int readFromNumbPW();

	// Functions related to private parameter genPWStorage.
	void writeToGenPWStore(std::map<int,std::vector<int>>genPW);
	std::map<int, std::vector<int>> readFromGenPWStore();
};

