#include <iostream>
#include "Parser_ini.h"

int main()
{
	Parser_ini parser("test.txt");
	std::cout << "Section1.var1 = " << parser.get_value<float>("Section1.var1") << "\n";
	std::cout << "Section2.var2 = " << parser.get_value<int>("Section2.var2") << "\n";
	return 0;
}