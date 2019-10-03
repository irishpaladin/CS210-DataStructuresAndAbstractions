#include <iostream>
#include <string>
#include <fstream>
#include <array>
using namespace std;

int main() {
		//input file needed
		string filename;
		cout << "Enter Filename: ";
		getline(cin, filename);

		//read file
		string line;
		ifstream myfile(filename);

		if (myfile.good())
		{
			while (getline(myfile, line))
			{
				//removing comment
				//line.erase(std::find(line.begin(), line.end(), '/'), line.end());
				//removing whitespaces
				//line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
				cout << line << endl;
				

			}
			myfile.close();

			
		}
		else cout << "Invalid input file!\n";

	return 0;
}