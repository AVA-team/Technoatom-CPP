#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include<fstream>
#include<string>
#include<vector>

namespace ava {
	class FileReader
	{
	public:
		FileReader();
		FileReader(const char* file_name);
		void chooseFile(const char* file_name);
		 std::string get_line(int index);
		 std::size_t lines_count() const;
		~FileReader();
	private:
		std::ifstream fin_;
		std::vector<std::string> all_strings_;
	};
}

#endif
