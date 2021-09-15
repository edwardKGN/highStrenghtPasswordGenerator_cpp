#include "pwGen.h"

pwGen::pwGen() {
	std::cout << "Password Generator Program Online" << std::endl;
}


pwGen::~pwGen() {
	std::cout << "Password Generator Program Offline" << std::endl;
}

void pwGen::executorFunction() {
	// Main Control Function that Operates the Sub-Functions
	int userDesiredLength, userSpecSymb, userNumb, userUpCase, userLowCase;
	int specSymbSpec, numbSpec, upCaseSpec, lowCaseSpec; // TODO create as private (incl. Setters and Getters) to prevent accidental modification
	int desiredNumGenPW; // TODO create as private (incl. Setters and Getters) to prevent accidental modification

	std::cout << "Welcome to the Password Generator Program." << std::endl;

	// Get User Input on how long the password is to be.
	std::cout << "How long would you like to the Password to be?" << std::endl;

	std::cin >> userDesiredLength;

	// Write user Password Length to non-modifiable module
	pwGen::writeToPWLength(userDesiredLength);

	// Write user Password Length to non-modifiable module
	pwGen::writeToPWLength(userDesiredLength);

	std::cout << std::endl << "At least, how many special symbols?" << std::endl;

	std::cin >> specSymbSpec;

	std::cout << std::endl << "At least, how many numbers?" << std::endl;

	std::cin >> numbSpec;
	
	std::cout << std::endl << "At least, how many upper case letters?" << std::endl;

	std::cin >> upCaseSpec;

	std::cout << std::endl << "At least, how many lower case letters?" << std::endl;

	std::cin >> lowCaseSpec;

	std::cout << "How many passwords to generate?" << std::endl;

	std::cin >> desiredNumGenPW;

	std::cout << std::endl;

	pwGen::writeToSpecSymbSpec(specSymbSpec);
	pwGen::writeToNumbSpec(numbSpec);
	pwGen::writeToUpCaseSpec(upCaseSpec);
	pwGen::writeToLowCaseSpec(lowCaseSpec);

	pwGen::writeToNumbPW(desiredNumGenPW);

	// Repeat What the User Input
	int outputLength = pwGen::readFromPWLength();

	int outputSpecSymb = pwGen::readFromSpecSymbSpec();
	int outputNumb = pwGen::readFromNumbSpec();
	int outputUpCase = pwGen::readFromUpCaseSpec();
	int outputLowCase = pwGen::readFromLowCaseSpec();
	int outputNumPW = pwGen::readFromNumbPW();

	std::cout << "Your desired Password is to: " << std::endl;
	std::cout << "Be " << outputLength << " characters long." << std::endl;
	std::cout << "Have at least " << outputSpecSymb << " special symbols, " << std::flush;
	std::cout << outputNumb << " numbers, " << outputUpCase << " upper case letters, " << outputLowCase << " lower case letters." << std::endl;
	std::cout << "Create " << outputNumPW << " passwords." << std::endl;

	std::cout << std::endl; // For tidiness
	pwGen::pwGeneration();

	std::cout << std::endl << std::endl;; // For tidiness
	pwGen::printPW();
}

void pwGen::pwGeneration() {
	std::cout << "Generator Running." << std::endl;

	/* Good Password Criterias:
	Minimum of 10 - 15 Characters
	Non-Dictionary Words
	Have Non-Alphabet Symbols ASCII 33 - 47 & ASCII 58 - 64 & ASCII 91 - 96 & ASCII 123 - 126
	Have Numbers ASCII 48 - 57
	Have Combination of Upper Case and Lower Case Letters ASCII 65 - 90 (Upper Case)
	& ASCII 97 - 122 (Lower Case) */

	// Randomize a set of special symbols to fit into the PW usually about 40% of Password
	// Strategy: Use a Randomizer then account for the restrictions in ASCII for Special Symbols

	// Design Criteria (Based on User Inputs)
	int outputLengthII = pwGen::readFromPWLength();
	int specSymbSpec = pwGen::readFromSpecSymbSpec();
	int numbSpec = pwGen::readFromNumbSpec();
	int upCaseSpec = pwGen::readFromUpCaseSpec();
	int lowCaseSpec = pwGen::readFromLowCaseSpec();
	int desiredNumGenPW = pwGen::readFromNumbPW();

	// Initial Inputs
	int numGenPW = 0;
	bool qualityCtrl = false;
	std::vector<int> genPWVector;
	std::map <int, std::vector<int>> genPW;
	
	srand(time(NULL)); // Seed Randomizer

	while (numGenPW != desiredNumGenPW){

		do {
		// Generate Password based on ASCII to translate to alphabetic system
		std::cout << std::endl;
		genPWVector = pwGen::randomASCIIvector(outputLengthII);
	
		// Check if meet design criteria
		std::cout << std::endl;
		qualityCtrl = pwGen::asciiQualityCheck(genPWVector, specSymbSpec, numbSpec, upCaseSpec, lowCaseSpec);

		std::cout << "Design Criteria Met? " << qualityCtrl << std::endl;

		} while (qualityCtrl == false);

		// Store a set of generated passwords for usage
		genPW[numGenPW] = genPWVector;
		
		/*
		// Diagnostic Code
		std::vector<int> outputVector = genPW[numGenPW];

		std::cout << "Check the Vector stored in the Map-type" << std::endl;

		for (std::vector<int>::iterator it = outputVector.begin(); it != outputVector.end(); it++) {
			std::cout << *it << "; " << std::flush;
		}
		*/

		numGenPW++;
	}

	// Transfer Generated Passwords into Private for Safe Keeping
	pwGen::writeToGenPWStore(genPW);
	}

// ASCII Password Vector Generator
std::vector<int> pwGen::randomASCIIvector(int userDesiredLength) {
	std::cout << "ASCII Vector Generator active." << std::endl;

	int randASCII;
	std::vector<int> randVector;
	
	for (int i = 1; i <= userDesiredLength; i++) {
		randASCII = rand() % 93 + 33; // Randomize between ASCII 33 and 126;
		randVector.push_back(randASCII);
	}

	// Checker
	std::cout << "Generated Vector." << std::endl;

	for (std::vector<int>::iterator it = randVector.begin(); it != randVector.end(); it++) {
		std::cout << "randVector: " << *it << std::endl;
	}

	return randVector;
}

bool pwGen::asciiQualityCheck(std::vector<int> randVector, int specSymbSpec, int numbSpec, int upCaseSpec, int lowCaseSpec) {
	std::cout << "Quality Control Function active." << std::endl;

	// Allocated Spots for each type of symbols
	int checkSpotSpecSymb = 0, checkSpotNumb = 0, checkSpotUpCase = 0, checkSpotLowCase = 0;
	int itemCheckCount = 0;
	
	for (std::vector<int>::iterator it = randVector.begin(); it != randVector.end(); it++) {
		std::cout << "Checking randVector element: " << *it << std::endl;

		itemCheckCount++;
		std::cout << "itemCheckCount: " << itemCheckCount << std::endl;

		if ( (*it >= 33 && *it <= 47) || (*it >= 58 && *it <= 64) || (*it >= 91 && *it <= 96)|| (*it >= 123 && *it <= 126) ) {
			checkSpotSpecSymb++;
			std::cout << "Special Symbols found." << std::endl;
		}
		else if (*it >= 48 && *it <= 57) {
			checkSpotNumb++;
			std::cout << "Number found." << std::endl;
		}
		else if (*it >= 65 && *it <= 90) {
			checkSpotUpCase++;
			std::cout << "Upper Case found." << std::endl;
		}
		else if (*it >= 97 && *it <= 122) {
			checkSpotLowCase++;
			std::cout << "Lower Case found." << std::endl;
		}

		std::cout << std::endl;
	}

	/*
	// Diagnostic Functions
	std::cout << "Special Symbols: " << checkSpotSpecSymb << std::endl;
	std::cout << "Numbers: " << checkSpotNumb << std::endl;
	std::cout << "Upper Case: " << checkSpotUpCase << std::endl;
	std::cout << "Lower Case: " << checkSpotLowCase << std::endl;

	int totalCasesDetermined = checkSpotSpecSymb + checkSpotNumb + checkSpotUpCase + checkSpotLowCase;

	std::cout << "Cases Determined: " << totalCasesDetermined << std::endl;
	*/

	if (checkSpotSpecSymb >= specSymbSpec, checkSpotNumb >= numbSpec, checkSpotUpCase >= upCaseSpec, checkSpotLowCase >= lowCaseSpec) {
		return true;
	}

	return false;
}

std::map<int, std::string> pwGen::convertToString() {
	std::map < int, std::vector<int> > outputPWMap = pwGen::readFromGenPWStore();
	std::map < int, std::string> convertedStringS;

	int mapIter = 0;

	// Output: Store into an Array the Generated ASCII for Printing
	// Diagnostic Program

	for (std::map < int, std::vector<int>>::iterator iter = outputPWMap.begin(); iter != outputPWMap.end(); iter++) {
		std::string convertedPW;
		std::vector<int> extractedVec = iter->second; // Accessing the Stored Vector

		std::cout << "Extracted Vector Elements" << std::endl;


		for (std::vector<int>::iterator it = extractedVec.begin(); it != extractedVec.end(); it++) {
			//std::cout << *it << ", " << std::flush; // Diagnostic Function	

			// Convert to character/string for actual Password
			char extractedElement = *it;
			std::cout << extractedElement << std::flush;

			// Convert Extracted Element into a String
			convertedPW.push_back(extractedElement);

			// Store the Converted Extracted 
			}
		
		std::cout << "; Output String: " << convertedPW << std::flush;

		convertedStringS[mapIter] = convertedPW;

		mapIter++;

		std::cout << std::endl;
		}

	// Diagnostic Function 
	for (std::map < int, std::string>::iterator iterB = convertedStringS.begin(); iterB != convertedStringS.end(); iterB++) {
		std::string outputPWString = iterB->second; // Accessing the Stored Vector

		std::cout << outputPWString << std::endl;
	}

	return convertedStringS;
}

void pwGen::printPW() {
	// Print Generated Password into a Text File for Usage.

	std::map<int, std::string> convertedPWMap = pwGen::convertToString();
	
	std::ofstream outfile;
	std::string docName = "genPW.txt";

	// Modify to Read Specifically
	outfile.open(docName);

	if ( outfile.is_open() ) {
		
		for (std::map < int, std::string>::iterator iter = convertedPWMap.begin(); iter != convertedPWMap.end(); iter++) {
			std::string outputPWString = iter->second; // Accessing the Stored Vector
			outfile << outputPWString << std::endl;
		}
	}
	else {
		std::cout << "File could not be read: " << docName << std::endl;
	}
	
}

// Setter-Type Function
void pwGen::writeToPWLength(int userDesiredLength) {
	pwGen::passwordLength = userDesiredLength;
}

// Getter-Type Function
int pwGen::readFromPWLength() {
	return pwGen::passwordLength;
}

void pwGen::writeToPWVar(int genPassword) {
	pwGen::passwordVar = genPassword;
}

int pwGen::readFromPWVar() {
	return pwGen::passwordVar;
}

void pwGen::writeToSpecSymbSpec(int specSymbSpec) {
	pwGen::specSymbSpec = specSymbSpec;
}

int pwGen::readFromSpecSymbSpec() {
	return pwGen::specSymbSpec;
}

void pwGen::writeToNumbSpec(int numbSpec) {
	pwGen::numbSpec = numbSpec;
}

int pwGen::readFromNumbSpec() {
	return pwGen::numbSpec;
}

void pwGen::writeToUpCaseSpec(int upCaseSpec) {
	pwGen::upCaseSpec = upCaseSpec;
}

int pwGen::readFromUpCaseSpec() {
	return pwGen::upCaseSpec;
}

void pwGen::writeToLowCaseSpec(int lowCaseSpec) {
	pwGen::lowCaseSpec = lowCaseSpec;
}

int pwGen::readFromLowCaseSpec() {
	return pwGen::lowCaseSpec;
}

void pwGen::writeToNumbPW(int numbPW) {
	pwGen::numbPW = numbPW;
}

int pwGen::readFromNumbPW() {
	return pwGen::numbPW;
}

void pwGen::writeToGenPWStore(std::map<int, std::vector<int>> genPW) {
	genPWStorage = genPW;
}

std::map<int, std::vector<int>>  pwGen::readFromGenPWStore() {
	return pwGen::genPWStorage;
}

// Store Data as ASCII, only in final generated form convert to String for Human Use.