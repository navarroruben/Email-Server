// EmailServer.cpp
// Ruben Navarro
// 07/28/2017
// Version: 1.0.8
// Email Server

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void MainMenu();
void Login();
void ShowInbox(std::string username, std::ostream & sout);
void LoggedInMenu(std::string username);
void RegisterNewUser();
void DeleteUser();
std::string GetUserFile(std::string username);
std::string GetInboxFile(std::string username);
std::string GetLine(std::istream & sin);
bool DoesUserExist(std::string username);
int GetInboxCount(std::string username);
std::string FormatEmailString(std::string from, std::string to, std::string subject, std::string msg);
void SendEmail(std::string username);
std::string GetPassword(std::string username);

//@include(main)
//@addRule(commentAll)

int main()
{
	/*
	int test = 0;
	std::cout << "Choose a function test: \n";
	std::cout << "1. Delete user\n";
	std::cout << "2. Get user file\n";
	std::cout << "3. Get inbox file\n";
	std::cout << "4. Get line\n";
	std::cout << "5. Does user exist?\n";
	std::cout << "6. Format email string\n";
	std::cout << "7. Send mail\n";
	std::cout << "8. Get password\n";
	std::cout << "Selection: ";
	std::cin >> test;

	switch (test)
	{
	case 1:
	{
		std::cout << "Hello World!" << std::endl;
		std::ofstream fout("abc.txt");
		fout.close();
		std::ifstream fin("abc.txt");
		std::cout << "Opened: " << std::boolalpha;
		std::cout << fin.is_open() << std::endl;
		fin.close();
		remove("abc.txt");
		fin.open("abc.txt");
		std::cout << "Opened: " << std::boolalpha;
		std::cout << fin.is_open() << std::endl;

		std::cin.get();

		break;

	}
	case 2:
	{
		std::string user1 = GetUserFile("bob");
		std::string user2 = GetUserFile("joe");
		std::string user3 = GetUserFile("mary");
		std::cout << "Bob's file would be: " << user1 << std::endl;
		std::cout << "Joe's file would be: " << user2 << std::endl;
		std::cout << "Mary's file would be: " << user3 << std::endl;
		break;
	}
	case 3:
	{
		std::string user1 = GetInboxFile("bob");
		std::string user2 = GetInboxFile("joe");
		std::string user3 = GetInboxFile("mary");
		std::cout << "Bob's file would be: " << user1 << std::endl;
		std::cout << "Joe's file would be: " << user2 << std::endl;
		std::cout << "Mary's file would be: " << user3 << std::endl;
		break;
	}
	case 4:
	{
		std::ofstream fout("test.txt");
		fout << "This is line 1" << std::endl;
		fout << "This is line 2" << std::endl;
		fout.close();
		std::ifstream fin("test.txt");
		while (fin.eof() == false)
		{
			std::string line = GetLine(fin);
			if (fin.eof() == false)
			{
				std::cout << "Line: " << line << std::endl;
			}
		}
		break;
	}
	case 5:
	{
		std::ofstream fout("testUser.txt");
		fout.close();
		bool exists = DoesUserExist("testUser");
		std::cout << "Exists: " << std::boolalpha;
		std::cout << exists << std::endl;
		exists = DoesUserExist("banana");
		std::cout << "Exists: " << std::boolalpha;
		std::cout << exists << std::endl;
		break;

	}
	case 6:
	{
		std::string formatted = FormatEmailString("me", "you", "the subject", "the message");
		std::cout << "Here's the formatted string" << std::endl;
		std::cout << "===========================" << std::endl;
		std::cout << formatted;
		std::cout << "===========================" << std::endl;
		break;
	}
	case 7:
	{
		SendEmail("user1");
		break;
	}
	case 8:
	{
		std::string p1 = GetPassword("user1");
		std::string p2 = GetPassword("user2");
		std::cout << "P1: " << p1 << std::endl;
		std::cout << "P2: " << p2 << std::endl;
		break;

	}
	}
	*/
	MainMenu();

	return 0; // make sure your int main function returns an int
}

//@removeRule(commentAll)

void MainMenu()
{
	std::string input = ""; 
	int menuItem = 0;


	while (input != "99")
	{
		std::cout << " 1) Login" << "\n";
		std::cout << " 2) Register new user" << "\n";
		std::cout << " 3) Delete user" << "\n";
		std::cout << "99) Exit" << "\n";
		std::cout << "Selection: ";

		std::cin >> input;
		try
		{
			menuItem = stoi(input);
			switch (menuItem)
			{
			case 1:
				Login();
				break;
			case 2:
				RegisterNewUser();
				break;
			case 3:
				DeleteUser();
				break;
			}
		}
		catch (std::invalid_argument & ia)
		{
			std::cout << "Bad option!" << std::endl;
			std::cout << ia.what() << std::endl;
		}
	}
}

// Now you fill in the rest
void RegisterNewUser()
{
	std::string username = ""; // declare string variable to hold username
	std::string password = ""; // declare string variable to hold password
	std::ofstream outPutFile; // output stream for file object
	bool check; // bool type to hold return from exist function

	std::cout << "Enter new username: "; // ask user for username
	std::cin >> username; // user inputs user name to username string variable

	if ( username.length() < 3 ) // limit username from passing 3 characters
	{
		std::cout << "Username must be at least 3 characters!\n"; // display error message
		std::cout << std::endl; // end line for format spacing
		return; // returns to main menu
	}

	check = DoesUserExist(username); // check holds true or false on wether file exists

	if ( check ) // if file does exist display following message
	{
		std::cout << "User already exists!" << std::endl; // displays that user already exists
		std::cout << std::endl; // end line for format spacing
		return; // returns to main menu
	}

	std::cout << "Enter new password: "; // asks user to enter new password
	std::cin >> password; // store password by user on password string variable

	if ( password.length() < 6 ) // check is length of username is greater than 3 characters, if test is false give error message.
	{
		std::cout << "Password must be at least 6 characters\n"; // tell user that username much be 3 characters or greater
		std::cout << std::endl; // end line for format spacing
		return; // exit function if password is less than 6 characters
	}
		
	outPutFile.open(GetUserFile(username), std::ios::out); // open output file for [username].txt

	outPutFile << "username " << username << std::endl; // prints username to file
	outPutFile << "password " << password << std::endl; // prints password to file
	outPutFile.close(); // close file after using

	outPutFile.open(GetInboxFile(username), std::ios::out);  // open output file for [username]-inbox.txt

	outPutFile << "#email" << std::endl; // prints email preprocessor directive to file
	outPutFile << "mailservice" << std::endl; // prints mailservice text to file
	outPutFile << username << std::endl; // prints user name to file
	outPutFile << "Intro" << std::endl; // prints subject to file
	outPutFile << "Hello, " << username << "! Welcome to our service"; // prints message to file
	std::cout << std::endl; // end line for format spacing
	outPutFile.close(); // close output file
}
void Login()
{
	std::string username = ""; // declare string variable to hold username
	std::string password = ""; // declare string variable to hold password

	std::cout << "Enter username: "; // ask user to enter username
	std::cin >> username; // store username in username string variable

	if ( !DoesUserExist(username) ) // check if user does NOT exist
	{
		std::cout << "User does not exist!" << std::endl; // prints user does not exist
		std::cout << std::endl; // end line for format spacing
		return;
	}

	std::cout << "Enter password: "; // ask user to enter password
	std::cin >> password; // store password in string variable
	std::cout << std::endl; // end line for format spacing

	if ( password == GetPassword(username) ) // evalute if string contained in password is the same as password stored in user file
	{
		LoggedInMenu(username); // function call to Logged in Menu
	}
	else
	{
		std::cout << "Incorrect password!" << std::endl; // if password was incorrect... prints error message
		std::cout << std::endl; // end line for format spacing
		return; // return to main menu
	}

}
void ShowInbox(std::string username, std::ostream & sout)
{
	std::ifstream fin; // inuput file stream
	std::string holdUser = ""; // declare string variable to hold password

	holdUser = GetInboxFile(username); // holds inbox file name in holdUser variable

	fin.open(holdUser, std::ios::in); // opens inbox file to receive stream

	while (!fin.eof()) // loop while not at end of file
	{
		GetLine(fin); // read first line of file
		sout << "From: " << GetLine(fin) << std::endl; // read second line of file and send to sout stream
		sout << "To: " << GetLine(fin) << std::endl; // read third line of file and send to sout stream
		sout << "Subject: " << GetLine(fin) << std::endl; // read fourth line of file and send to sout stream
		sout << "Message: " << GetLine(fin) << std::endl; // read fifth line of file and send to sout stream
		std::cout << std::endl; // end line for format spacing
	} // end while loop
}
void LoggedInMenu(std::string username)
{
	int selection = 0; // declare and identify variable to hold user choice
	std::ofstream fout; // declare output file stream

	std::cout << " 1) Inbox[" << GetInboxCount(username) << "]\n"; // displace first menu choice
	std::cout << " 2) Send Email\n"; // displace second menu choice
	std::cout << "99) Logout\n"; // displace third menu choice
	std::cout << "Selection: "; // ask user for choice
	std::cin >> selection; // store choice in selection variable
	std::cout << std::endl; // end line for format spacing


	switch (selection) // switch statement to call various functions and actions
	{
		case 1:
		{
			ShowInbox(username, std::cout); // call show inbox function
			LoggedInMenu(username); // call logged in menu function
			break; // break statement to prevent cascading
		}
		case 2:
		{
			SendEmail(username);  // call send email function
			std::cout << std::endl; // end line for format spacing
			LoggedInMenu(username); // call logged in menu function
			break; // break statement to prevent cascading
		}
		case 99:
		{
			std::cout << std::endl; // end line for format spacing
			return; // break statement to prevent cascading
		}
		}
}
void DeleteUser()
{
	std::string hold = ""; // declare string variable to hold string line
	std::string name = ""; // declare string variable to hold name to delete
	std::cout << "What do you want to delete? "; // ask user what user to delete
	std::cin >> name; // store user in name string variable

	if ( DoesUserExist(name) ) // check to see if file exists
	{
		hold = GetUserFile(name); // assigns [username].txt
		remove(hold.c_str()); // removes [username].txt
		hold = GetInboxFile(name); // assigns [username]-index.txt
		remove(hold.c_str()); // removes [username]-indox.txt
		std::cout << std::endl; // end line for format spacing
	}
	else
	{
		std::cout << "User does not exist!" << std::endl; // display user does not exist message
		std::cout << std::endl; // end line for format spacing
	}
}
std::string GetUserFile(std::string username)
{
	return username.append(".txt"); // returns username with .txt appended
}
std::string GetInboxFile(std::string username)
{
	return username.append("-inbox.txt"); // returns username with -inbox.txt appended
}
std::string GetLine(std::istream & sin)
{
	std::string nLine; // declare string variable to hold string name
	getline(sin, nLine); // read file stream and copy to nLine string variable
	return nLine; // returns string variable
}
bool DoesUserExist(std::string username)
{
	std::ifstream doesExist; // input filestream

	doesExist.open(username.append(".txt"), std::ios::in); // open file

	if (doesExist) // check is file is open
	{
		return true; // returns true is file is open
	}
	else
	{
		return false; // returns false if file is not open
	}
}
int GetInboxCount(std::string username)
{
	std::ifstream inUserFile; // input file stream
	std::string line = ""; // declare string variable to hold string line
	int count = 0; // declare and assign value to counter

	inUserFile.open(GetInboxFile(username), std::ios::in); // open inbox file

	while (!inUserFile.eof()) // loop while not at end of file
	{
		line = GetLine(inUserFile); // read file line into line string variale
		if (line == "#email") // check if line read is equal to email preprocessor directive 
		{
			++count; // counter for amount of #email lines found
		}
	} // end while loop
	return count; // return amount of lines found
}
std::string FormatEmailString(std::string from, std::string to, std::string subject, std::string msg)
{
	std::string line = "";  // declare string variable to hold string line
	line = "#email\n" + from + "\n" + to + "\n" + subject + "\n" + msg; // assigns user input and formatting ques to line string variable
	return line; // returns string variable
}
void SendEmail(std::string username)
{
	std::ofstream fout; // output stream
	std::string who = ""; // declare string variable to hold who to send email to
	std::string subject = ""; // declare string variable to hold subject line
	std::string message = ""; // declare string variable to hold message line
	std::string holdUser = ""; // declare string variable to hold file names

	std::cout << "Send email to who: "; // ask user who to send email to
	std::cin >> who; // store user input in who string variable

	if ( !DoesUserExist(who) ) // check if file does NOT exist
	{
		std::cout << "User does not exist!" << std::endl; // prints message if file not found
		std::cout << std::endl; // end line for format spacing
		return; // returns to menu
	}

	std::cin.ignore();
	std::cout << "Subject: "; // asks user to input subject line
	getline (std::cin, subject); // stores subject line

	std::cout << "Message: "; // asks user to input message line
	getline(std::cin, message); // stores message line

	std::cout << "Sending: " << std::endl; // prints sending to screen

	std::cout << FormatEmailString(username, who, subject, message); // prints Format email string function to screen
	std::cout << std::endl; // end line for format spacing

	holdUser = GetInboxFile(who); // assigns inbox file name to holdUser string variable
	fout.open(holdUser, std::ios::out | std::ios::app); // opens inbox file and initizalizes append

	fout << std::endl; // end line for format spacing
	fout << FormatEmailString(username, who, subject, message); // prints Format email string to file
}
std::string GetPassword(std::string username)
{
	std::ifstream inUserFile; // input file stream
	std::string holdUsername = ""; // declare string variable to hold username text
	std::string holdUser = ""; // declare string variable to hold username
	std::string holdPassword = ""; // declare string variable to hold password text
	std::string holdPw = ""; // declare string variable to hold password
	std::string holdAppUsername = ""; // declare string variable to hold user file name

	holdAppUsername = GetUserFile(username); // assins user file name with append to string variable

	inUserFile.open(holdAppUsername, std::ios::in); // opens username file in order to obtain password
	
	while (!inUserFile.eof()) // loop while not end of file
	{
		inUserFile >> holdUsername >> holdUser >> holdPassword >> holdPw; // assigns text found in file to string variables
	} // end while loop
	return holdPw; // returns password string
}
