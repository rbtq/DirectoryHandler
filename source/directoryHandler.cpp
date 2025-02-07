/**\file directoryHandler.cpp*/
#include "directoryHandler.h"
#include <iostream>

//get the raw data of the contents in the directory
std::string DirectoryHandler::getRaw(bool debug) {
	//vars
	char output[100];
	std::string outputString = "";
	FILE* pPipe;

	if (debug) std::cout << std::string("dir " + m_path).c_str() << std::endl;

	//run dir music to get the contents of the music directory
	//use rt so the output can be read like a text file
	if ((pPipe = _popen(std::string("dir " + m_path).c_str(), "rt")) == NULL)
	{
		exit(1);
	}

	/* Read pipe until end of file, or an error occurs. */

	while (fgets(output, 100, pPipe))
	{
		outputString += output;
	}
	//debug
	if (debug) std::cout << outputString << std::endl;

	int endOfFileVal = feof(pPipe);
	int closeReturnVal = _pclose(pPipe);

	if (endOfFileVal)
	{
		printf("\nProcess returned %d\n", closeReturnVal);
	}
	else
	{
		printf("Error: Failed to read the pipe to the end.\n");
	}

	return outputString;
}

//get the raw data of the contents in the directory then seperate it into lines
std::vector<std::string> DirectoryHandler::getRawLines(bool debug) {
	std::string data = getRaw();
	std::vector<std::string> lines;
	std::string newLine = "";
	for (unsigned int i = 0; i < data.size(); i++) {
		//if not a newline char
		if (data[i] != '\n') {
			//add it on to the new line
			newLine += data[i];
		}
		//if a newline char
		else {
			//save the new line and reset for the next line
			if (debug) std::cout << newLine << std::endl;
			lines.push_back(newLine);
			newLine = "";
		}
	}
	return lines;
}

//get the directories and files in the directory ONLY and return it in lines
std::vector<std::string> DirectoryHandler::getLines(bool debug) {
	std::vector<std::string> lines = getRawLines();

	bool passedTest = false;
	while (!passedTest) {
		//if the 1st char in the line is outside the range for the numbers 0 to 3 
		//as thats what the 1st number in a date looks like assuming non US (which is 0-1 so would be fine)
		if (lines[0][0] < '0' || lines[0][0] > '3') {
			if (debug) std::cout << "Removed line: " << lines[0] << " from list" << std::endl;
			lines.erase(lines.begin());
		}
		else passedTest = true;
	}
	passedTest = false;
	while (!passedTest) {
		//if the 1st char in the line is outside the range for the numbers 0 to 3 
		//as thats what the 1st number in a date looks like assuming non US (which is 0-1 so would be fine)
		if (lines[lines.size() - 1][0] < '0' || lines[lines.size() - 1][0] > '3') {
			if (debug) std::cout << "Removed line: " << lines[lines.size() - 1] << " from list" << std::endl;
			lines.pop_back();
		}
		else passedTest = true;
	}

	if (debug) {
		//display final result
		std::cout << std::endl;
		std::cout << "Filtered lines:" << std::endl;
		for (unsigned int i = 0; i < lines.size(); i++) {
			std::cout << lines[i] << std::endl;
		}
		std::cout << "END:" << std::endl;
		std::cout << std::endl;
	}

	return lines;
}

//get the directories and files in the directory and parse it
std::vector<DirectoryEntry> DirectoryHandler::getLinesParsed(bool debug) {
	std::vector<std::string> lines = getLines();
	std::vector<DirectoryEntry> entries;

	std::cout << "Parsed lines: " << std::endl;
	for (unsigned int i = 0; i < lines.size(); i++) {
		if (false) {
			//dd mm yyyy
			std::cout << lines[i].substr(0, 2) << " " << lines[i].substr(3, 2) << " " << lines[i].substr(6, 4) << "  ";
			//hh mm
			std::cout << lines[i].substr(12, 2) << " " << lines[i].substr(15, 2) << "     ";
			//isdir
			std::cout << lines[i].substr(22, 3) << " ";
			//size cba rn

			//name
			std::cout << lines[i].substr(36) << std::endl;
		}
		entries.push_back(DirectoryEntry(lines[i].substr(0, 2), lines[i].substr(3, 2), lines[i].substr(6, 4),
										 lines[i].substr(12, 2), lines[i].substr(15, 2), 
			                             lines[i].substr(22, 3) == "DIR", 
										 0, 
										 lines[i].substr(36)));
	}
	//print out all entries if debug mode on
	if (debug) {
		std::cout << std::endl;
		std::cout << "Entries: " << std::endl;
		for (unsigned int i = 0; i < entries.size(); i++) {
			std::cout << entries[i].c_day << " ";
			std::cout << entries[i].c_month << " ";
			std::cout << entries[i].c_year << "    ";
			std::cout << entries[i].c_hour << " ";
			std::cout << entries[i].c_minute << "    ";
			std::cout << entries[i].c_isDirectory << "    ";
			std::cout << entries[i].c_size << "    ";
			std::cout << entries[i].c_name << std::endl;
			
		}

		std::cout << "END" << std::endl;
		std::cout << std::endl;
	}

	return entries;
}