#include "Interpolation.h"

#include <iostream>
#include <stdexcept>

void printMenu()
{
	std::cout << " 0 - Exit " << std::endl;
	std::cout << " 1 - Input file name with reference points" << std::endl;
	std::cout << " 2 - Input file name with points coordinates" << std::endl;
	std::cout << " 3 - Calculate points" << std::endl;
	std::cout << " 4 - Write points" << std::endl;
	std::cout << " 5 - Change interpolation method" << std::endl;
	std::cout << " Enter your choice: ";
}

int main()
{
	Interpolation interp;
	char variant = 's';
	std::string file_name;
	while (variant != '0')
	{
		printMenu();
		std::cin >> variant;
		switch (variant)
		{
		case '0':
			break;
		case '1':
		{		
			std::cout << "Enter file name: ";
			std::cin >> file_name;
			interp.readReferencePoints(file_name);
			break;
		}
		case '2':
		{
			std::cout << "Enter file name: ";
			std::cin >> file_name;
			interp.readPoints(file_name);
			break;
		}
		case '3':
		{
			try
			{
				interp.calculate();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		}
		case '4':
		{
			std::cout << "Enter file name: ";
			std::cin >> file_name;
			try
			{
				interp.writeData(file_name);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		}
		case '5':
		{
			std::cout << " 0 - Exit " << std::endl;
			std::cout << " 1 - step" << std::endl;
			std::cout << " 2 - linear" << std::endl;
			std::cout << " 3 - quadratic" << std::endl;
			std::cout << " Enter your choice: ";
			std::cin >> variant;
			switch (variant)
			{
			case  '0':
				break;
			case '1':
				interp.setMethod(STEP);
				break;
			case '2':
				interp.setMethod(LINEAR);
				break;
			case '3':
				interp.setMethod(QUADRATIÑ);
				break;
			default:
				std::cout << "There is no such choice!" << std::endl;
			}
			break;
		}
		default:
			std::cout << "There is no such choice!" << std::endl;
		}
	}
	
	return 0;
}