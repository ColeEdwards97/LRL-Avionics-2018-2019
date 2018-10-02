// 
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//                                                                            
// Author:        Cole Edwards
// Date Created:  1 October 2018
// Date Revised:  1 October 2018
// Description:   A sample piece of code, formatted for LRL
//

#include <iostream>
#include <string>
using namespace std;

int main() {

	// a test program with formatting
	cout << "This is the first code for this project\n";

	string name;
	int age;
	string ans;

	cout << "please enter your name:\n";
	cin >> name;
	cout << "welcome " << name << "!\n";
	cout << "please enter your age:\n";
	cin >> age;

	if (age >= 18) {
		cout << "congratulations! you are old enough to enter\n";
	}
	else {
		cout << "sorry, you may not enter\n";
		return 0;
	}

	cout << "would you like to stay? Y/N\n";
	cin >> ans;

	if (ans == "Y") {
		cout << "cool! no one usually stays\n";
	}
	else if (ans == "N") {
		cout << "bye. loser.\n";
		return 0;
	}
	else if (ans == "pippity poppity") {
		cout << "give me the zoppity\n";
		return 0;
	}

	return 0;

}