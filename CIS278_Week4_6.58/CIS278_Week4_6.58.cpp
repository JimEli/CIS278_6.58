/*************************************************************************
* Title: Computer-Assisted Instruction: Reducing Student Fatigue
* File: CIS278_Week4_6.57.cpp
* Author: James Eli
* Date: 1/17/2018
*
* Exercise 6.58 on page 281, Computer-Assisted Instruction: Reducing Student
* Fatigue. One problem in CAI environments is student fatigue. This can be
* reduced by varying the computer’s responses to hold the student’s
* attention. Modify the program of Exercise 6.57 so that various comments
* are displayed for each answer as follows:
*   Possible responses to a correct answer:
*     Very good!
*     Excellent!
*     Nice work!
*     Keep up the good work!
*   Possible responses to an incorrect answer :
*     No, Please try again.
*     Wrong. Try once more.
*     Don’t give up.
*     No. Keep trying.
*
* Use random-number generation to choose a number from 1 to 4 that will be
* used to select one of the four appropriate responses to each correct or
* incorrect answer. Use a switch statement to issue the responses.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   01/17/2018: Initial release. JME
*************************************************************************/
#include <iostream>  // cin/cout/endl
#include <string>    // string
#include <ctime>     // time for random seed
#include <random>    // random

using namespace std;

#include <vector>

vector<string> responses = {
	"Very good!", "Excellent!", "Nice work!", "Keep up the good work!",
	"No, Please try again.", "Wrong. Try once more.", "Don't give up.", "No. Keep trying."
};

int getAnswer(string question)
{
	// Validate input of answer.
	while (true)
	{
		// Temporary holds user input.
		int number;

		cout << question;
		// Get user input of product number and quantity.
		cin >> number;
		if (number == -1)
			// Exit.
			return -1;

		// Eat trailing chars in stream.
		while (cin.peek() != '\n')
		{
			if (cin.peek() == -1)
				break;
			cin.ignore(1, '\n');
		}

		// Check for non-integer input.
		if (cin.fail())
		{
			// Clear failure flag and discard any remaining input.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter only integer values.\n";
		}
		else
		{
			// Check quantity not negative.
			if (number < 0 || number > 81)
				cout << "Answer must be between 0 and 81.\n";
			else
				return number;
		}
	}
}

bool askMultiplication(void)
{
	int multiplicand, multiplier, result, answer;
	// Random number generator with input for min-value and range.
	auto rng = [](int low, int range) { return low + int(range * rand() / (RAND_MAX + 1.0)); };

	multiplicand = rng(0, 10);
	multiplier = rng(0, 10);
	result = multiplicand * multiplier;

	// Repeat same question until the student finally gets it right. 
	do {
		answer = getAnswer("How much is " + to_string(multiplicand) + " times " + to_string(multiplier) + "? ");

		if (answer == -1)
			return false;
		else if (answer == result)
			// If it’s correct, display the message 
			cout << responses.at(rng(0, 4)) << endl;
		else
			// If the answer is wrong, display
			cout << responses.at(rng(4, 4)) << endl;
	} while (answer != result);

	return true;
}

int main()
{
	// Seed the rng.
	srand((unsigned)time(0));

	// Continue asking questions.
	while (askMultiplication());

	return 0;
}

