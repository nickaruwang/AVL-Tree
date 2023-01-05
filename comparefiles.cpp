#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) {
		throw invalid_argument("USAGE: ./compare <INPUTFILE> <OUTPUTFILE>");
	}
	ifstream f1;
	ifstream f2;
	f1.open(argv[1]);
	f2.open(argv[2]);

	string s1, s2;
	bool out = true;
	int l = 1;
	while (getline(f1, s1) && getline(f2, s2)) {
		if (s1 != s2) {
			out = false;
			cout << l << endl;
		}
		l++;
	}

	if (out) {
		cout << "PASS" << endl;
	}
	else {
		cout << "FAIL" << endl;
	}

	f1.close();
	f2.close();

	return 0;
}