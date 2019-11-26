#include "Main.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main() {

	size_t eofMarker;
	size_t marker;
	size_t characterCtr = 0;
	string line;
	fstream inOutFile;

	// This program modifies censusdata.txt. So, after you run it,
	// you will have to restore censusdata.txt.
	string file = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework7\\";
	inOutFile.open(file+"censusdata.txt", fstream::ate | fstream::in | fstream::out);
	if (!inOutFile)
	{
		cout << "File open error" << endl;
		return EXIT_FAILURE;
	}

	eofMarker = inOutFile.tellg(); //assind inputstream marker to eof marker
	//inOutFile << " 0 -> ";
	cout << "endl of file marker: " << eofMarker<<endl;

	inOutFile.seekg(0, fstream::beg); //reposition the inputstream marker to 0 distance from beg //marker that reads the file
	int i = 0;
	marker = inOutFile.tellg();
	cout << "assigned marker: " << marker  << endl;

	while (getline(inOutFile, line)) {
		
		characterCtr = characterCtr + line.length() + 1;
		cout << i++ << " - " <<characterCtr<<" - "<< line << endl;

		inOutFile.seekg(characterCtr);
		marker = inOutFile.tellg();
		cout << "marker: " << marker << endl;
		
	}
	inOutFile.clear();
	inOutFile.seekg(402);
	marker = inOutFile.tellg();
	cout << "marker: " << marker << endl;
	getline(inOutFile, line);
	cout << "line at 402 marker: " << line << endl;

	inOutFile.close();
	//while (inOutFile.good() &&
	//	inOutFile.tellg() != eofMarker && //inputfile marker != eofmarker
	//	getline(inOutFile, line))	//store a line in line
	//{
	//	characterCtr = characterCtr + line.length() + 1; //get the sum of all read characters
	//	marker = inOutFile.tellg();		//reassign inputfile marker to the 1st character in the stream
	//	//inOutFile.seekp(0, fstream::end);	//reposition the outputstream f the maerker
	//	cout <<i++<<" -> "<< characterCtr << "->" << line << endl;
	//	//inOutFile << line << endl;			//display lines
	//	//inOutFile << characterCtr << " -> ";//displays the number of characters
	//	inOutFile.seekg(marker);			//reposition the imputfile marker original position
	//}
	////inOutFile.seekp(0, fstream::end);		//reposition the outputfile stream
	////inOutFile << "   EOF" << endl;
	//inOutFile.close();

	//Open the file.
	//Save the offset of the next record to be read.
	//Read the unique identifier(i.e., the key) from the record as an int.
	/*Insert the key into the B - tree and set the associated offset to point to the 
	location of the record in the file.*/
	//Skip the rest of the record.
	//Repeat steps b to e until the end - of - file is encountered.
	//Close the file.



	return 0;
}
