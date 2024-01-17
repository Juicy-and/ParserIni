#pragma once
#include <string>
#include <fstream>
#include <map>


class Parser_ini
{
private:
	std::map<int, std::map<int, std::string>> contIni;
public:
	Parser_ini(const char name[])
	{
		std::map<int, std::string> tmp;
		std::string buf, tmpStr;
		std::ifstream file;
		int numberOfSection = -1;
		int numberOfVar = 0;
		file.open(name);
		if (file.is_open())
		{
			int j = 0;
			while (!file.eof())
			{
				std::getline(file, buf);
				if (buf[0] == ';')
					continue;
				if (buf.find("Section") != std::string::npos)
				{
					if (numberOfSection != -1)
					{
						if (contIni.find(numberOfSection) != contIni.end())
						{
							for (auto& j : contIni.find(numberOfSection)->second)
								tmp.insert(j);
							contIni.erase(contIni.find(numberOfSection));
						}
						contIni.insert(std::pair<int, std::map<int, std::string>>(numberOfSection, std::move(tmp)));
					}
					auto i = buf.find('n');
					if (buf[i+2] == ']')
						numberOfSection = buf[i+1] - '0';
					j = 0;
				}
				if (buf.find("var") != std::string::npos)
				{
					auto i = buf.find('r');
					tmpStr.clear();
					if (buf[i + 2] == '=')
						numberOfVar = buf[i + 1] - '0';
					i = i + 3;
					while (buf[i] != ';' && i != buf.size())
						tmpStr += buf[i++];
					tmp.insert(std::pair<int, std::string>(numberOfVar, tmpStr));
				}
			}
		}
		if (contIni.find(numberOfSection) != contIni.end())
		{
			for (auto& j : contIni.find(numberOfSection)->second)
				tmp.insert(j);
			contIni.erase(contIni.find(numberOfSection));
		}
		contIni.insert(std::pair<int, std::map<int, std::string>>(numberOfSection, tmp));
		file.close();
	}

	template <typename T>  
	T get_value(const std::string& value)
	{
			if (typeid(T).name() == typeid(int).name())
				return stoi(contIni.find(value[value.find('n') + 1] - '0')->second.find(value[value.find('r') + 1] - '0')->second);
			else if (typeid(T).name() == typeid(float).name())
				return stof(contIni.find(value[value.find('n') + 1] - '0')->second.find(value[value.find('r') + 1] - '0')->second);
	}
	template <>
	std::string get_value(const std::string& value)
	{
		return contIni.find(value[value.find('n') + 1] - '0')->second.find(value[value.find('r') + 1] - '0')->second;
	}
};
