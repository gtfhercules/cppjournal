#include <iostream>
#include <Windows.h>
#include <string>
#include <ShlObj.h>
#include <ctime>
#include <fstream>
#include <Shlwapi.h>

using namespace std;



void check_settings();
void menu();
void create_entry();
void view_entry();
void new_dir();
void settings();
void exit_program();
void view_folder();
void credits();

int main()
{
	
	int choice;
	cout << "Welcome to the SSD Journal Application!" << endl;
	


	do {
		
		menu();
		cin >> choice;
		cout << endl;

		if (choice == 1){
			create_entry();
			cout << endl;
		}

		

		else if (choice == 2) {
			view_entry();
			cout << endl;
			
		}
		
		else if (choice == 3) {
			new_dir();
			cout << endl;
		}

		
		else if (choice == 4) {
			settings();
			cout << endl;
		
		}

		else if (choice == 5) {
			view_folder();
			cout << endl;
		}

		else if (choice == 6) {
			credits();
			cout << endl;
		}
		
		else if (choice == 7) {
			exit_program();
		}
		
		else {
			cout << "You have entered an invalid option. Please pick an option from the following commands:" << endl;
		}

	} while (choice != 7);
	
	
	
}

void check_settings()
{
	//bool directory_exists;
	ifstream settings;
	string valid_directory;
	string new_directory;
	int choice;
	settings.open("settings.txt");
	getline(settings, valid_directory);
	
	if (PathIsDirectory("C:\\Projects"))
	{
	
	}
	else {
		cout << "It appears you do not have a settings.txt file." << endl;
		Sleep(750);
		cout << "This program will not function without a settings.txt file." << endl;
		Sleep(750);
		cout << "Would you like to set up the save directory?" << endl;
		Sleep(750);
		cout << "The other options can be configured in the settings menu at a later time." << endl;
		Sleep(500);
		cout << "1. Yes" << endl;
		Sleep(500);
		cout << "2. No" << endl;
		cin >> choice;
		if (choice == 1)
		{
			Sleep(1000);
			cout << "Alright, do you want to use an existing directory, or create a new one?" << endl;
			Sleep(500);
			cout << "1. Use an existing directory" << endl;
			Sleep(500);
			cout << "2. Create new directory" << endl;
			do {
				if (choice == 1) 
				{
					ofstream settings;
					string directory;
					settings.open("settings.txt");
					cout << "Please enter in the EXACT directory that you want to save your entries to:" << endl;
					cout << "Example: C:\\Users\\Parker\\Desktop\\" << endl;
					cin.ignore();
					getline(cin, directory);
					settings << directory;
					cout << "Your save directory has been updated." << endl;
					cout << endl;
					settings.close();
					cout << "Returning to main menu..." << endl;
					cout << endl;
					break;
					
				}
				else if (choice == 2)
				{
					new_dir();
					break;
				}
				else {
					cout << "You did not enter a valid option. Please pick a valid option:" << endl;
					
				}


			} while (choice !=2);


		}





	}
	


}


void menu()
{
	cout << "Main Menu:" << endl;
	cout << "1. Create new entry" << endl;
	cout << "2. View existing entry" << endl;
	cout << "3. Create new folder" << endl;
	cout << "4. Settings" << endl;
	cout << "5. View default save folder" << endl;
	cout << "6. View credits" << endl;
	cout << "7. Exit program" << endl;
	cout << "So, what's next?" << endl;
}


void create_entry() {
	ifstream settings;
	string directory;
	string file_name;
	string entry;
	string mom;
		
	settings.open("settings.txt");
	getline(settings, mom);
	cout << "You have chosen to create a new entry." << endl;
	Sleep(1000); //It makes things neater.
	cout << "What do you want your entry to be named?" << endl;
	cin.ignore();
	getline(cin,file_name); //What this line and the following line do is allow you to 
	file_name += ".txt"; //Create whatever name you want for your text file.
	ofstream out(mom + file_name); //This writes the file to the disk.
	cout << "Alright, file created. What's on your mind?" << endl;
	cout << endl;
	getline(cin, entry);
	out << entry;
	cout << "Entry saved. Returning to main menu..." << endl;
	Sleep(1000);
	settings.close(); //This closes the settings file so you can modify it.
	}

void view_entry() {
	string directory;
	string line;
	ifstream entry;
		
	cout << "You have chosen to view an existing entry." << endl;
	cout << "Please enter the exact directory of the entry you want to view:" << endl;
	cin.ignore();
	getline (cin,directory);
	entry.open(directory.c_str());
	cout << endl;
	Sleep(1000);

	if (entry.is_open()) {
		cout << "One second, loading...." << endl;
		Sleep(1000);
		cout << "Here you go:" << endl;
		Sleep(500);
		cout << endl;
		while (getline(entry, line)) {
			cout << line << endl;
			}
		entry.close();
		cout << endl;
		cout << "When you are ready, press enter to return to the main menu." << endl;
		cin.ignore();
		Sleep(500);
	}
	else cout << "Unable to open the file!" << endl;


}

void new_dir() {
	string foldername;
	string directory;
	string combined;
	cout << "I see you want to create a new folder in which to store your entries." << endl;
	Sleep(500);
	cout << "Please enter the directory where you want to put your new folder:" << endl;
	cin.ignore();
	getline(cin, directory);
	cout << "Please enter the name of the folder:" << endl;
	getline(cin, foldername);
	combined = directory + foldername;
	if (CreateDirectory(combined.c_str() , NULL))
	{
		int choice;
		cout << "Folder successfully created." << endl;
		Sleep(500);
		cout << "Would you like to save all new entries to this folder?" << endl;
		Sleep(500);
		cout << "1. Yes" << endl;
		Sleep(500);
		cout << "2. No" << endl;
		do {
		cin >> choice;
		if (choice == 1)
		{
			ofstream settings;
			settings.open("settings.txt");
			settings << combined;
			settings.close();
			Sleep(500);
			cout << "Your save directory has been updated." << endl;
			Sleep(500);
			cout << "Returning to main menu..." << endl;
			Sleep(500);
			break;
		}
		else if (choice == 2)
		{
			cout << "Got it." << endl;
			Sleep(500);
		}
		else
		{
			cout << "You have not entered a valid choice. Please enter either 1 or 2." << endl;
			Sleep(500);
		}
		} while (choice != 2);
		cout << "Returning to main menu..." << endl;
		cout << endl;
		Sleep(500);

	}
	else if (ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Error! The folder already exists!" << endl;
		Sleep(500);
		cout << "Returning to main menu..." << endl;
		cout << endl;
		Sleep(500);
	}
	else 
	{
		cout << "Error! Could not create folder!" << endl;
		Sleep(500);
		cout << "Returning to main menu..." << endl;
		cout << endl;
		Sleep(500);
	}
}

void settings() {
	int selection;
	string directory;
	
	cout << "Here, you can adjust verious settings." << endl;
	Sleep(500);
	cout << "1. Change save directory" << endl;
	cout << "2. Automatically add the date to an entry (Coming soon!)" << endl;
	cout << "3. Go back" << endl;
	cout << "What would you like to do?" << endl;
	cin >> selection;

	do {
		if (selection == 1) {
			ofstream settings;
			settings.open("settings.txt");
			cout << "I see that you want to change the save directory." << endl;
			Sleep(500);
			cout << "Please enter in the EXACT directory that you want to save your entries to:" << endl;
			cout << "Example: C:\\Users\\Parker\\Desktop\\" << endl;
			cin.ignore();
			getline(cin, directory);
			settings << directory;
			cout << "Your save directory has been updated." << endl;
			cout << endl;
			settings.close();
			cout << "Returning to main menu..." << endl;
			cout << endl;
			break;
		}
		if (selection == 2) {
			cout << "This feature is coming soon!" << endl;
			cout << "Returning to main menu..." << endl;
			cout << endl;
			break;
		}

		if (selection == 3)
		{
			cout << "Returning to main menu..." << endl;
			cout << endl;
			break;
		}

	} while (selection != 3);

}


void view_folder(){
	string directory;
	ifstream view;
	view.open("settings.txt");
	getline(view, directory);
	Sleep(1000);
	cout << "You have chosen to view the save folder.";
	cout << " In a moment, an Explorer window will open." << endl;
	Sleep(4000);
	ShellExecute(NULL, "explore", directory.c_str(), NULL, NULL, NULL);
	Sleep(1000);
	cout << "Returning to main menu..." << endl;
	cout << endl;
	view.close();
}

void credits()
{
	Sleep(1000);
	cout << endl;
	cout << "This program was made possible by:" << endl;
	Sleep(2000);
	cout << "Parker Shirazi, programmer/creator/everything" << endl;
	Sleep(2000);
	cout << "Colleen Shirazi, advisor" << endl;
	Sleep(2000);
	cout << "Kasper Meerts, advisor" << endl;
	Sleep(2000);
	cout << "Daniel Moreno, advisor" << endl;
	Sleep(2000);
	cout << "cplusplus.com, main reference" << endl;
	Sleep(2000);
	cout << "Stack Overflow, reference" << endl;
	Sleep(2000);
	cout << "And last but not least, Microsoft, for their wonderful IDE." << endl;
	Sleep(2000);
	cout << "Returning to main menu..." << endl;
	cout << endl;
}



void exit_program()
{
	cout << "Thank you for using the SSD Journal Application." << endl;
	Sleep(500);
	cout << "Please press any key to exit. Goodbye." << endl;
	system("pause");
}