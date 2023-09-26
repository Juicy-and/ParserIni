#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>

#define CHAR_SIZE 1024;

class Parser_ini
{
private:
	std::ifstream file;
	std::string buf[100];
public:
	Parser_ini(const char name[])
	{
		file.open(name);
		// исключения
	}
	template <typename T>  
	T get_value(const std::string& value)
	{
		std::string sect, temp, var;
		file.seekg(0);
		auto x = 0;
		for (; value[x] != '.'; x++)
			temp += value[x];
		sect = "[" + temp + "]";
		x++;
		for (; value[x] != '\0'; x++)
			var += value[x];
		int i = 0;
		while (!file.eof())
		{
			std::getline(file, buf[i]);
			if (buf[i] == sect)
			{
				i++;
				do
				{
					std::getline(file, buf[i]);
					auto fnd = -1;
					if (!buf[i].find(var))
					{
						fnd = buf[i].find("=");
						if (fnd != -1)
						{

							temp.clear();
							for (int j = fnd + 1; buf[i][j] != '\0'; j++)
								temp += buf[i][j];
							T ret;
							if (typeid(T).name() == typeid(int).name())
								ret = stoi(temp);
							else if (typeid(T).name() == typeid(float).name())
								ret = stof(temp);
							//else
								//	ret = temp;

								return ret;
						}
					}
				} while (buf[i][0] != '[');
			}
		}
		return 0;
	}
};
