#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
using namespace std;
class bank
{
    int complete;
    struct customer
    {
        string name, accounttype, address;
        double id, mobilenumber, balance; 
    }customer[100];   
    private:
    public:
           bank()
           {
               complete=complete+0;
           }
           void menu();
           void display();
           void createaccount();
           void deposit();
           void withdraw();
           void checkbalance();
};
void bank::menu()
{    
    int n;
    char x;
menustart:
    cout<<"\t\t\t================================"<<endl;
    cout<<"\t\t\t|    BANK MANAGEMENT SYSTEM    |"<<endl;
    cout<<"\t\t\t================================"<<endl;
    cout<<"\t\t\t 1. Create account."<<endl;
    cout<<"\t\t\t 2. Deposit."<<endl;
    cout<<"\t\t\t 3. Withdraw."<<endl;
    cout<<"\t\t\t 4. Check balance."<<endl;
    cout<<"\t\t\t 5. Display all customers."<<endl;
    cout<<"\t\t\t 6. Exit."<<endl;
    cout<<"\t\t\t----------------------------"<<endl;
    cout<<"\t\t\t|CHOOSE OPTION [1/2/3/4/5/6]:|"<<endl;
    cout<<"\t\t\t----------------------------"<<endl;
    cout<<"Enter your option:"<<endl;
    cin>>n;
    switch(n)
    {
        case 1:
                do
              {
                  createaccount();
                  cout<<"\n\t\t\t Add another studentrecord (Y/N):";
                  cin>>x;
              } 
              while(x=='y' || x=='Y');
              break;
        case 2:
               deposit();
               break;
        case 3:
               withdraw();
               break;
        case 4:
               checkbalance();
               break;
        case 5:
               display();
               break;
        case 6:
               cout<<"Thank you for using our bank management system."<<endl;
               getch();
               exit(0);

        default:
        system("cls");
               cout<<"Invalid choice... Please try again"<<endl;
               goto menustart;
    }
    getch(); 
    goto menustart;
}  
void bank::display()
{
    system("cls");
    cout<<"You have selected to display all customer records."<<endl;
    for(int i=0; i<complete; i++)
    {
        cout<<"Customer name: "<<customer[i].name<<endl;
        cout<<"Customer id: "<<customer[i].id<<endl;
        cout<<"Customer account type: "<<customer[i].accounttype<<endl;
        cout<<"Customer mobile number: "<<customer[i].mobilenumber<<endl;
        cout<<"Customer address: "<<customer[i].address<<endl;
        cout<<"Customer balance: "<<customer[i].balance<<endl;
        cout<<"--------------------------------"<<endl;
    }
} 
void bank::createaccount()
{
    system("cls");
    fstream file;
    cout<<"You have selected to create account."<<endl;
    cout<<"Enter the record of customer: "<<complete+1<<endl;
    cout<<"Enter customer name: ";
    int i=complete;
    cin>>customer[i].name;
    cout<<"Enter customer id: ";
    cin>>customer[i].id;
    cout<<"Enter customer account type: ";
    cin>>customer[i].accounttype;
    cout<<"Enter customer mobile number: ";
    cin>>customer[i].mobilenumber;
    cout<<"Enter customer address: ";
    cin>>customer[i].address;
    cout<<"Enter customer initial balance: ";
    cin>>customer[i].balance;
    complete++;
    file.open("customerrecord.txt", ios::app | ios::out);
    file<<customer[i].name<<" "<<customer[i].id<<" "<<customer[i].accounttype<<" "<<customer[i].mobilenumber<<" "<<customer[i].address<<" "<<customer[i].balance<<endl;
    file.close();
}
void bank::deposit()
{
    system("cls");
    cout<<"You have selected to deposit money."<<endl;
    int id1, amount;
    int found = 0;
    fstream file, file1;
    file.open("customerrecord.txt", ios::in);
    if(!file)
    {
        cout<<"File not found."<<endl;
        return;
    }
    cout<<"Enter customer id: ";
    cin>>id1;
    file1.open("record.txt", ios::out);
    int i = 0;
    while(file>>customer[i].name>>customer[i].id>>customer[i].accounttype>>customer[i].mobilenumber>>customer[i].address>>customer[i].balance)
    {
        if(customer[i].id != id1)
        {
            file1<<customer[i].name<<" "<<customer[i].id<<" "<<customer[i].accounttype<<" "<<customer[i].mobilenumber<<" "<<customer[i].address<<" "<<customer[i].balance<<endl;
        }
        else
        {
            found++;
            cout<<"Customer found."<<endl;
            cout<<"Customer name: "<<customer[i].name<<endl;
            cout<<"Customer account type: "<<customer[i].accounttype<<endl;
            cout<<"Customer mobile number: "<<customer[i].mobilenumber<<endl;
            cout<<"Customer address: "<<customer[i].address<<endl;
            cout<<"Customer balance: "<<customer[i].balance<<endl;
            cout<<"Enter amount to deposit: ";
            cin>>amount;
            customer[i].balance += amount;
            cout<<"Amount deposited successfully."<<endl;
            cout<<"Customer total balance: "<<customer[i].balance<<endl;
            file1<<customer[i].name<<" "<<customer[i].id<<" "<<customer[i].accounttype<<" "<<customer[i].mobilenumber<<" "<<customer[i].address<<" "<<customer[i].balance<<endl;
        }
        i++;
    }
     file1.close();
     file.close();
    if(found==0)
    {
        cout<<"Customer not found."<<endl;
    }
    else
    {
        remove("customerrecord.txt");
        rename("record.txt", "customerrecord.txt");
    }
   
}
void bank::withdraw()
{
    system("cls");
    cout<<"You have selected to withdraw money."<<endl;
    int id1, amount;
    int found = 0;
    fstream file, file1;
    file.open("customerrecord.txt", ios::in);
    if(!file)   
    {
        cout<<"File not found."<<endl;
        return;
    }   
    cout<<"Enter customer id: ";
    cin>>id1;
    file1.open("record.txt", ios::out);
    int i = 0;
    while(file>>customer[i].name>>customer[i].id>>customer[i].accounttype>>customer[i].mobilenumber>>customer[i].address>>customer[i].balance)
    {
        if(customer[i].id != id1)
        {
            file1<<customer[i].name<<" "<<customer[i].id<<" "<<customer[i].accounttype<<" "<<customer[i].mobilenumber<<" "<<customer[i].address<<" "<<customer[i].balance<<endl;
        }
        else
        {
            found++;
            cout<<"Customer found."<<endl;
            cout<<"Customer name: "<<customer[i].name<<endl;
            cout<<"Customer account type: "<<customer[i].accounttype<<endl;
            cout<<"Customer mobile number: "<<customer[i].mobilenumber<<endl;
            cout<<"Customer address: "<<customer[i].address<<endl;
            cout<<"Customer balance: "<<customer[i].balance<<endl;
            cout<<"Enter amount to withdraw: ";
            cin>>amount;
            if(amount>customer[i].balance)
            {
                cout<<"Insufficient balance."<<endl;
                file1<<customer[i].name<<" "<<customer[i].id<<" "<<customer[i].accounttype<<" "<<customer[i].mobilenumber<<" "<<customer[i].address<<" "<<customer[i].balance<<endl;
            }
            else
            {
                customer[i].balance -= amount;
                cout<<"Amount withdrawn successfully."<<endl;
                cout<<"Customer total balance: "<<customer[i].balance<<endl;
                file1<<customer[i].name<<" "<<customer[i].id<<" "<<customer[i].accounttype<<" "<<customer[i].mobilenumber<<" "<<customer[i].address<<" "<<customer[i].balance<<endl;
            }
        }
        i++;
    }  
    if(found==0)
    {
        cout<<"Customer not found."<<endl;
    }
    else
    {
        file1.close();
        file.close();
        remove("customerrecord.txt");
        rename("record.txt", "customerrecord.txt");
    }  
    
}
void bank::checkbalance()
{
    system("cls");
    cout<<"You have selected to check balance."<<endl;
    int id1;
    int found = 0;
    fstream file;
    file.open("customerrecord.txt", ios::in);
    if(!file)
    {
        cout<<"File not found."<<endl;
        return;
    }
    cout<<"Enter customer id: ";
    cin>>id1;
    int i = 0;
    while(file>>customer[i].name>>customer[i].id>>customer[i].accounttype>>customer[i].mobilenumber>>customer[i].address>>customer[i].balance)
    {
        if(customer[i].id == id1)
        {
            found++;
            cout<<"Customer found."<<endl;
            cout<<"Customer name: "<<customer[i].name<<endl;
            cout<<"Customer account type: "<<customer[i].accounttype<<endl;
            cout<<"Customer mobile number: "<<customer[i].mobilenumber<<endl;
            cout<<"Customer address: "<<customer[i].address<<endl;
            cout<<"Customer balance: "<<customer[i].balance<<endl;
        }
        i++;
    }
    if(found==0)
    {
        cout<<"Customer not found."<<endl;
    }
     file.close();
}
int main()
{
    string username, password, username1, password1;
    int n;
    fstream userfile;
    system("cls");
    cout<<"\t\t\t================================"<<endl;
    cout<<"\t\t\t|    BANK MANAGEMENT SYSTEM    |"<<endl;
    cout<<"\t\t\t================================"<<endl;
    cout<<"\t\t\tSign in or login"<<endl;
    cout<<"\t\t\t1. Sign in"<<endl;
    cout<<"\t\t\t2. Login"<<endl;
    cout<<"\t\t\tChoose option [1/2]: ";
    cin>>n;
    switch(n)
    {
        case 1:
                goto signin;
        case 2:
               goto login;
        default:
               cout<<"Invalid choice... Please try again"<<endl;
               getch();
               exit(0);
    }
signin:
    system("cls");   
    userfile.open("userrecord.txt", ios::out);
    cout<<"\t\t\tSign in."<<endl;
    cout<<"\t\t\tEnter your username: ";
    cin>>username;
    cout<<"\t\t\tEnter your password: ";
    cin>>password;
    userfile<<username<<" "<<password<<endl;
    userfile.close();
    cout<<"\t\t\t--------------------------------"<<endl;
    cout<<"\t\t\tYou have successfully signed in."<<endl;
    cout<<"\t\t\t--------------------------------"<<endl;
    cout<<"\t\t\tPress Enter to continue..."<<endl;
    getch(); 
login:
    system("cls");
    userfile.open("userrecord.txt", ios::in);
    cout<<"\t\t\tLogin here."<<endl;
    cout<<"\t\t\tEnter your username: ";
    cin>>username1;
    cout<<"\t\t\tEnter your password: ";
    cin>>password1;
    userfile>>username>>password;
    userfile.close();
    if(username==username1 && password==password1)
    {
        cout<<"\t\t\t--------------------------------"<<endl;
        cout<<"\t\t\tYou have successfully logged in."<<endl;
        cout<<"\t\t\t--------------------------------"<<endl;
        cout<<"\t\t\tPress Enter to continue..."<<endl;
        getch(); 
    }
    else
    {
        cout<<"\t\t\tInvalid username or password."<<endl;
        cout<<"\t\t\tPlease try again."<<endl; 
        getch();  
        goto login;
    } 
    bank project;
    project.menu();
    return 0;
}