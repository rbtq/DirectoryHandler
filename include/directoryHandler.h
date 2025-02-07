/**\file directoryHandler.h*/
#pragma once
#include <string>
#include <vector>

/**\struct DirectoryEntry - structure for an entry in a directory*/
struct DirectoryEntry {
	const std::string c_directoryToken = "DIR"; //!<directory token

	const std::string c_day; //!<day modified of the directory entry
	const std::string c_month; //!<month modified of the directory entry
	const std::string c_year; //!<year modified of the directory entry
	const std::string c_hour; //!<hour modified of the directory entry
	const std::string c_minute; //!<minute modified of the directory entry
	const bool c_isDirectory; //!<is the entry a directory
	const int c_size; //!<size of the entry in bits
	const std::string c_name; //!<name of the entry

	DirectoryEntry(std::string day, std::string month, std::string year, std::string hour,std::string minute, bool isDirectory, int size, std::string name) :
		c_day(day),
		c_month(month),
		c_year(year),
		c_hour(hour),
		c_minute(minute),
		c_isDirectory(isDirectory),
		c_size(size),
		c_name(name)
	{}; //!<constructor
};



/**\class DirectoryHandler - class for getting the contents of a directory in string format and manipulating it*/
class DirectoryHandler {

private:
	std::string m_path; //!<the path of the directory

public:
	DirectoryHandler(std::string path) : m_path(path) {} //!<constructor

	std::string getRaw(bool debug = false); //!<get the raw output of the contents of the directory
	std::vector<std::string> getRawLines(bool debug = false); //!<get the raw output of the contents of the directory and seperate it into lines
	std::vector<std::string> getLines(bool debug = false); //!<get all the files and directories in the directory
	std::vector<DirectoryEntry> getLinesParsed(bool debug = false); //!<get all the files and directories in the directory

};
