#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
using namespace std;
class student
{
    private:
           string name, roll_no, course, marks;
    public:
           void menu();
           void insert();
           void display();
           void update();
           void deleted();
};
void student::menu()
{
    menustart:
    int n;
    char x;
    system("cls");
    cout<<"\t\t\t-----------------------------"<<endl;
    cout<<"\t\t\t| STUDENT MANAGEMENT SYSTEM |"<<endl;
    cout<<"\t\t\t-----------------------------"<<endl;
    cout<<"\t\t\t 1. Add new record."<<endl;
    cout<<"\t\t\t 2. Update record."<<endl;
    cout<<"\t\t\t 3. Delete record."<<endl;
    cout<<"\t\t\t 4. Display record."<<endl;
    cout<<"\t\t\t 5. Exit."<<endl;
    cout<<"\t\t\t----------------------------"<<endl;
    cout<<"\t\t\t|CHOOSE OPTION [1/2/3/4/5]:|"<<endl;
    cout<<"\t\t\t----------------------------"<<endl;
    cout<<"Enter your option:"<<endl;
    cin>>n;
    switch(n)
    {
        case 1:
              do
              {
                   insert();
                  cout<<"\n\t\t\t Add another studentrecord (Y/N):";
                  cin>>x;
              } 
              while(x=='y' || x=='Y');
             
        break;
        case 2:
              update();
              break;
        case 3:
              deleted();
              break;
        case 4:
              display();
              break;
        case 5:
              exit (0); 
        default:
               cout<<"\n\t\t\t Invalid choice... Please try again:";
               
    }getchar();
    goto menustart;
}
void student::insert()
{
    system("cls");
    fstream file;
    cout<<"\n==========Add Student Detail=========="<<endl;
    cout<<"\t\t\t Enter Name:";
    cin>>name;
    cout<<"\t\t\t Enter Roll_No:";
    cin>>roll_no;
    cout<<"\t\t\t Enter Course:";
    cin>>course;
    cout<<"\t\t\t Enter marks:";
    cin>>marks;
    file.open("studentrecord.txt", ios::app | ios::out);
    file<<" "<< name << " "<<roll_no <<" "<< course <<" "<< marks <<" "<<"\n";
    file.close(); 
}
void student::deleted()
{
    system("cls");
    fstream file, file1;
    string rollno;
    int found = 0;

    cout << "\n==========Delete Student Detail==========" << endl;

    file.open("studentrecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t No data is present..." << endl;
        return;
    }

    cout << "\nEnter the roll_no of student to delete:";
    cin >> rollno;

    file1.open("record.txt", ios::out);

    while (file >> name >> roll_no >> course >> marks)
    {
        if (rollno != roll_no)
        {
            file1 << name << " " << roll_no << " " << course << " " << marks << "\n";
        }
        else
        {
            found = 1;
        }
    }

    file.close();
    file1.close();

    if (found == 0)
    {
        cout << "\n\t\t\t Student roll no not found...";
        remove("record.txt");
    }
    else
    {
        remove("studentrecord.txt");
        rename("record.txt", "studentrecord.txt");
    }
}
void student::update()
{
    system("cls");
    fstream file, file1;
    string rollno;
    int found = 0;

    cout << "\n==========Update Student Detail==========" << endl;

    file.open("studentrecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t No data is present..." << endl;
        return ;
    }

    cout << "\nEnter the roll_no of student to update:";
    cin >> rollno;

    file1.open("record.txt", ios::out);

    while (file >> name >> roll_no >> course >> marks)
    {
        if (rollno != roll_no)
        {
            file1 << name << " " << roll_no << " " << course << " " << marks << "\n";
        }
        else
        {
            cout << "\t\t\t Enter Name:";
            cin >> name;
            cout << "\t\t\t Enter Roll_No:";
            cin >> roll_no;
            cout << "\t\t\t Enter Course:";
            cin >> course;
            cout << "\t\t\t Enter marks:";
            cin >> marks;

            file1 << name << " " << roll_no << " " << course << " " << marks << "\n";
            found = 1;
        }
    }

    file.close();
    file1.close();

    if (found == 0)
    {
        cout << "\n\t\t\t Student roll no not found...";
        remove("record.txt");
    }
    else
    {
        remove("studentrecord.txt");
        rename("record.txt", "studentrecord.txt");
    }
}
void student::display()
{
    system("cls");
    fstream file;
    int total=1;
    cout<<"\n==========Display Student Detail=========="<<endl;
    file.open("studentrecord.txt", ios::in);
    if(!file)
    {
        cout<<"\n\t\t\t No data is present..."<<endl;
        file.close();
    }
    else
    {
         file>> name >> roll_no >> course >> marks;
        while(!file.eof())
        {
            cout<<"\t\t\t Student No.:"<< total++ <<endl;
            cout<<"\t\t\t Student Name:"<< name <<endl;
            cout<<"\t\t\t Student Roll_No:"<< roll_no <<endl;
            cout<<"\t\t\t Student Course:"<< course <<endl;
            cout<<"\t\t\t Student Marks:"<< marks <<endl;
            file>> name >> roll_no >> course >> marks;
        }getchar();
        if(total==0)
        {
            cout<<"\n\t\t\t No data is present..."<<endl;
        }
    }
    file.close();
}
int main()
{
    student project;
    project.menu();
    return 0;
}