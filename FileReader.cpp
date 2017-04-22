#include<fstream>
#include<string>
#include "FileReader.h"

namespace ava {

	FileReader::FileReader() {

	}

	FileReader::FileReader(const char* file_name)
	{
		fin_.open(file_name);
	}

	void FileReader::chooseFile(const char* file_name) {
		if (fin_.is_open()) {
			fin_.close();
		}
		fin_.open(file_name);
		std::string curr_str;
		while (!fin_.eof())
		{
			std::getline(fin_, curr_str);
			all_strings_.push_back(curr_str);
		}
		fin_.close();
	}

	 std::string FileReader::get_line(int index) {
		 return all_strings_[index];
	}

	 std::size_t FileReader::lines_count() const {
		 return all_strings_.size();
	 }

	FileReader::~FileReader()
	{
		if (fin_.is_open())
		{
			fin_.close();
		}
	}
}
