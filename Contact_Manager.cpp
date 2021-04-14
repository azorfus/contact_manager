#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>


void main_menu()
{
	std::cout << "==================================\n\n";
	std::cout << "\t[1] List all Contacts\n";
	std::cout << "\t[2] Add Contact\n";
	std::cout << "\t[3] Delete Contact\n";
	std::cout << "\t[4] Search Contact\n";
	std::cout << "\t[5] Edit Contact\n";
	std::cout << "\t[6] Exit\n";
	std::cout << "==================================\n\nEnter option: ";
}

void returnM()
{
	char op;
	std::cout << "\nReturn to main menu? [y/n] ";
	std::cin >> op;
	
	if(op=='N'||op=='n')
	{
		exit(0);
	}
}

void list_all()
{
	std::string line;
	std::string name, number;
	int lineno = 1;
	std::ifstream Data("Database.txt");
	if(!Data.is_open())
	{
			std::cout << "Error reading data! [Quitting]\n";
			returnM();
	}
	std::cout << "\n=================================\n";
	while(std::getline(Data, line))
	{
			std::cout << "[" << lineno << "] " << line << "\n";
			lineno++;
	}
	Data.close();
	returnM();
}

void add_contact()
{
	size_t ast, com;

	std::string name, phone, email;
	std::cout << "\n===================================\n";
	std::cout << "Enter Contact Information\n===================================\n";

	std::cout << "Name: ";
	std::getline(std::cin, name);

	std::cout << "Phone: ";
	std::getline(std::cin, phone);

	do{
		std::cout << "Email: ";
		std::getline(std::cin, email);
		ast = email.find("@");
		com = email.find(".com");
	}while(ast==std::string::npos && com==std::string::npos);
	
	std::cout << name << '|' << phone << '|' << email << std::endl;
	
	std::ofstream Data;
	Data.open("Database.txt", std::ios::app);
	if(!Data.is_open())
	{
		std::cout << "Error reading data! [Quitting]\n";
		returnM();
	}
	else
	{
		std::cout << "Writing data to file....\n";
		Data << name << '|' << phone << '|' << email << std::endl;
		Data.close();
		returnM();
	}
}

void delete_contact()
{
	std::ifstream Data;
	std::vector <std::string> lines;
	std::string line;
	
	Data.open("Database.txt");
	if(!Data.is_open())
	{
		std::cout << "File not open!.\n";
		returnM();
	}
	else
	{
		while(std::getline(Data, line))
		{
			lines.push_back(line);
		}
		Data.close();
		int lineRM;

		for(int i=0;i<lines.size();i++)
		{
			std::cout << "[" << i+1 << "] " << lines[i] << std::endl;
		}
		std::cout << "Line to remove: ";
		std::cin >> lineRM;
		std::cin.ignore();
	
		if(lineRM < 1, lineRM - 1 > lines.size())
		{
			std::cout << "Line specified does not exist!\n";
			returnM();
		}
		else
		{
			lines.erase(lines.begin() + lineRM - 1);

			std::ofstream Data;
			Data.open("Database.txt", std::ios::trunc);
			Data.close();

			Data.open("Database.txt", std::ios::app);
			
			if(!Data.is_open())
			{
				std::cout << "file open error!.\n";
				returnM();
			}
			else
			{
				for(int i=0;i<lines.size();i++)
				{
					Data << lines[i] << std::endl;
				}
			}
			Data.close();
		}
	}
	lines.clear();
}

void search_contact()
{
	std::ifstream Data("Database.txt");
	std::vector <std::string> lines;
	std::string search, line;

	while(std::getline(Data, line))
	{
		lines.push_back(line);
	}	

	std::cout << "Search: ";
	std::getline(std::cin, search);

	size_t foundat;
	int I;

	for(size_t i=0;i<lines.size();i++)
	{
		foundat = lines[i].find(search);
		if(foundat!=std::string::npos)
		{
			std::cout << "Results: " << lines[i] << std::endl;
			break;
		}
	}
	std::cout << "\n";
}

void edit_contact()
{

}

int main()
{
	std::string CurrentLine;
	int option;

	while(option!=6)
	{
		main_menu();
		std::cin >> option;
		std::cin.ignore();
		if (option > 6 || option < 1)
		{
			std::cout << "Invalid Option. [Quitting]\n";
			exit(0);
		}
		switch(option)
		{
			case 1:
					list_all();
					break;
			case 2:
					add_contact();
					break;
			case 3:
					delete_contact();
					break;
			case 4:
					search_contact();
					break;
			case 5:
					edit_contact();
					break;
			case 6:
					std::cout << "Exitting!\n" << std::endl;
					exit(0);
					break;
		}
	}

	return 0;
}
