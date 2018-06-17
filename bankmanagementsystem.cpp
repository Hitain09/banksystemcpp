#include<iostream>
#include<fstream>
#include<cctype>
#include<string.h>
#include<iomanip>
using namespace std;


//account CLASS USED IN PROJECT

class account
{
	int account_no;
	char name[50];
	int deposit;
	char type;
    char mailID[50];
    char phoneNumber[10];
    
public:
	bool getAdminDetails();
	void create_account();				//function to get data from user
	void show_account() const;			//function to show data on screen
	void modify();						//function to add new data
	void dep(int);						//function to accept amount and add to balance amount
	void draw(int);						//function to accept amount and subtract from balance amount
	void report() const;				//function to show data in tabular format
	int return_account_no() const;		//function to return account number
	int return_deposit() const;			//function to return balance amount
	char return_type() const;			//function to return type of account
};         



//MEMBER FUNCTIONS OF CLASS

bool account::getAdminDetails(){
	#pragma warning(suppress: 4101)
	string str = "admin";
	string passKey = "passwords2";
	string user;
	string pass;
	cout<<"\n\n\tEnter Username: ";
	cin>>user;
	cout<<"\tEnter passKey: ";
	cin>>pass;
	if((str == user) && (passKey == pass)){
		return true;
	}
	else{
		return false;
	}
}


void account::create_account()
{
	bool depo = false;
	cout<<"\nEnter The account No. :";
	cin>>account_no;
    cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
    cout<<"\nEnter E-mail ID :";
    cin>>mailID;
    cout<<"\nEnter phone No. :";
    cin>>phoneNumber;
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
    
	while(depo == false)
	{
		if(type == 'C' )
		{
			if(deposit >= 1000)
				depo = true;
			else
			{
				cout<<"Enter the amount >= 1000 : ";
				cin>>deposit;
			}
		}
		if(type == 'S' )
		{
			if(deposit >= 500)
				depo = true;
			else
			{
				cout<<"Enter the amount >= 500 : ";
				cin>>deposit;
			}
		}
	}
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<account_no;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
    cout<<"\nAccount Holder Email ID : ";
    cout<<mailID;
    cout<<"\nAccount Holder Contact Number : ";
    cout<<phoneNumber;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<account_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify E-mail ID :";
    cin>>mailID;
    cout<<"\nModify phone No. :";
    cin>>phoneNumber;
    cout<<"\nModify Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance amount : ";
    cin>>deposit;
}

	
void account::dep(int x)
{
	deposit += x;
}
	
void account::draw(int x)
{
	deposit -= x;
}
	
void account::report() const
{
	cout<<account_no<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<deposit<<setw(10)<<mailID<<setw(10)<<phoneNumber<<endl;
}

	
int account::return_account_no() const
{
	return account_no;
}

int account::return_deposit() const
{
	return deposit;
}

char account::return_type() const
{
	return type;
}



//FUNCTION DECLARATION

void write_account();				//function to write record in binary file
void display_sp(int);				//function to display account details given by user
void modify_account(int);			//function to modify record of file
void delete_account(int);			//function to delete record of file
void display_all();					//function to display all account details
void deposit_withdraw(int, int);	// function to desposit/withdraw amount for given account
void intro();						//introductory screen function



//FUNCTION TO ADD ACCOUNT IN DATABASE

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}


//FUNCTION TO DISPLAY SPECIFIC ACCOUNT

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File not found !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.return_account_no()==n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if(flag == false)
		cout<<"\n\nAccount number does not exist";
}



//FUNCTION TO MODIFY THE PREVIOUS RECORD

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File not found !! Press any Key...";
		return;
	}
	while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.return_account_no() == n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account : "<<endl;
			ac.modify();
			int pos = (-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found = true;
		  }
	}
	File.close();
	if(found == false)
		cout<<"\n\n Record Not Found ";
}


//FUNCTION TO DELETE RECORD FROM FILE


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File not found !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.return_account_no() != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}



//FUNCTION TO DISPLAY ALL RECORDS FROM FILE

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File not found !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"=======================================================================================\n";
	cout<<"A/c no.      NAME           Type          Balance          Mail-ID          PhoneNumber\n";
	cout<<"=======================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}



//FUNCTION TO DEPOSIT AND WITHDRAW 

void deposit_withdraw(int n, int option)
{
	int amount;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File not found !! Press any Key...";
		return;
	}
	while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.return_account_no() == n)
		{
			ac.show_account();
			if(option == 1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amount;
				ac.dep(amount);
			}
			if(option == 2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw : ";
				cin>>amount;
				int bal = ac.return_deposit()-amount;
				if((bal<500 && ac.return_type()=='S') || (bal<1000 && ac.return_type()=='C'))
					cout<<"Low balance";
				else
					ac.draw(amount);
			}
			int pos = (-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found = true;
	       }
         }
	File.close();
	if(found == false)
		cout<<"\n\n Record Not Found ";
}


//INTRODUCTION FUNCTION

void intro()
{
	cout<<"\n\n\n\t  BANK"<<"\n\n\tMANAGEMENT"<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : Hitain Goyal";
	cin.get();
}


//MAIN FUNCTION OF THE PROGRAM.

int main()
{
	char ch;
	int num;
	intro();
	account acc;
<<<<<<< Updated upstream
	#pragma warning(suppress: 4101)
=======
>>>>>>> Stashed changes
	bool admin = acc.getAdminDetails();
	if(admin == true){
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		default :
			cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
}
else{
	cout<<"\n\n\t\tAUTHENTICATION DENIED!!!!";
	cout<<"\n\t\tLogin Again: ";
	acc.getAdminDetails();
}
	return 0;
}
