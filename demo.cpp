#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<conio.h>
#include<windows.h>
#include<time.h>


using namespace std;

void logo();
void intro();



class account
{

  long long deposit, withdraw, balance;
  char m, n, ad_ch, ac_ch, menu_choice, ac_name[30], date[10], time[5];
  string ad_id, ad_pw, ad_cid, ad_cpw, ac_id, ac_pw, ac_cid, ac_cpw, ac_no, filename, filename1;


  public:
    void admin() ;
    void menu();
    void create_ac();
    void deposit_ac();
    void withdraw_ac();
    void statement_ac();
    void listof_ac();
    void logout();

};


void account :: admin()
{

        loop:
        system("CLS");
        intro();
        cout << endl;
        cout << "\tLOG IN" << endl;;
        cout << "\t-------\n" << endl ;

        cout << "\tAdmin ID\t:\t"  ; cin >> ad_id;
        cout << "\tPassword\t:\t" ;

        while ((ad_ch = _getch()) != 13)
        {
            if (ad_ch == 8)
                {
                    if (ad_pw.length() != 0)
                    {
                        cout << "\b \b";
                        ad_pw.resize(ad_pw.length() - 1);
                    }
                }

            else
                {
                    ad_pw.push_back(ad_ch);
                    cout << '*';
                }
        }


        filename ="Administrative/" +ad_id+".bin";

        ifstream read(filename.c_str());
        getline(read, ad_cid);
        getline(read, ad_cpw);

        if (ad_id == ad_cid && ad_pw == ad_cpw)
             menu();
        else
            {

                system("CLS");
                cout << "\n\n\n\n\tIncorrect ID or Password.\n\n\tPress ENTER to Return to ADMIN LOG IN Panel .......... ";
                cin.get();
                cin.ignore();
                ad_id.clear();
                ad_pw.clear();
                ad_cid.clear();
                ad_cpw.clear();
                goto loop;

            }
}



void account :: menu()
{
    loop:
    system("CLS");
    cout << "\n\t\t  Main Menu ";
    cout << "\n\t\t-------------\n";
    cout << "\n\t1. Create A/C";
    cout << "\n\t2. Deposit Money";
    cout << "\n\t3. Withdraw Money";
    cout << "\n\t4. Get A/C Statement";
    cout << "\n\t5. A/C List";
    cout << "\n\t6. Log Out";


    cout << "\n\n\t";
    menu_choice = _getch();

    switch (menu_choice)
    {
    case ('1'):
        create_ac();
        break;

    case ('2'):
        deposit_ac();
        break;

    case  ('3'):
        withdraw_ac();
        break;

    case ('4'):
        statement_ac();
        break;

    case ('5'):
        listof_ac();
        break;

    case ('6'):
        logout();
        break;

    default:
        goto loop;
        break;

    }

}

void account :: create_ac()
{
    balance = withdraw = deposit = 0;
    system("CLS");
    cout << "\n\t  Creating Account";
    cout << "\n\t--------------------\n\n";

    cout << "\tEnter A/C No.\t:\t";
    cin >> ac_no;
    filename = "ACC Holders/"+ac_no+".bin";

    ifstream check;
    check.open(filename.c_str());

    if(!check.is_open())

        {
            cout << "\tEnter A/C Name\t:\t";
            cin.ignore();
            cin.getline(ac_name,30);
            cout << "\tInitial Deposit\t:\t";
            cin >> deposit;
            balance = deposit;


            filename1 = "Administrative/List_AC.bin";

            ofstream create_ac, list_ac;

            create_ac.open(filename.c_str());

            create_ac << "\n\nA/C Name\t:\t" << ac_name << endl;
            create_ac << "A/C No.\t\t:\t" << ac_no << "\n\n";
            create_ac << "Statements : \n";
            create_ac << "\n\tDate\t\tTime\t\tDeposit\t\t\tWithdraw\t\t\tBalance\n";
            create_ac << "\t--------\t--------\t--------\t\t---------\t\t\t--------\n" ;
            create_ac << "\t" << _strdate(date) << "\t" << _strtime(time) << "\t" << deposit << "\t\t\t" << withdraw << "\t\t\t\t" << balance << " ";

            create_ac.close();

            list_ac.open(filename1.c_str(), ios :: app);

            list_ac << "\n\t " << ac_no << "\t\t\t " << ac_name << "\t";

            list_ac.close();

            cout << "\n\n\n\tAccount Successfully Created\n";
            cout << "\tPress ENTER to return to Main Menu ......... ";
            ac_no.clear();
            filename.clear();
            filename1.clear();
            cin.ignore();
            cin.get();
            menu();
        }

    else
        {
            check.close();
            system("CLS");
            cout << "\n\n\n\tA/C already exists.\n\tPlease choose different A/C No.\n";
            cout << "\tPress ENTER to return to Main Menu ......... ";
            ac_no.clear();
            filename.clear();
            cin.ignore();
            cin.get();
            menu();
        }
}


void account :: deposit_ac()
{
     loop:
     string temp;
     balance = withdraw = deposit = 0;
     system("CLS");
     cout << "\n\t  Deposit Money";
     cout << "\n\t--------------------\n\n";

     cout << "\tEnter A/C No.\t:\t";
     cin >> ac_no;
     filename = "ACC Holders/"+ac_no+".bin";
     ifstream deposit_ac;
     deposit_ac.open(filename.c_str());
     if(deposit_ac.is_open())
     {

        while(!deposit_ac.eof())
         {
            deposit_ac >> temp;
         }
         deposit_ac.close();
         balance = atoll(temp.c_str());
         ofstream dep;
         cout << "\tDeposit Amount\t:\t";
         cin >> deposit;
         balance = balance + deposit;
         dep.open(filename.c_str(), ios :: app);
         dep << "\n\t" << _strdate(date) << "\t" << _strtime(time) << "\t" << deposit << "\t\t\t" << withdraw << "\t\t\t\t" << balance << " ";
         dep.close();

         cout << "\n\n\n\tDeposit Completed.";
         cout << "\n\tPress ENTER to get back to Main Menu...";
         cin.get();
         cin.ignore();
         filename.clear();
         temp.clear();
         ac_no.clear();
         menu();

     }

     else
     {
       cout << "\n\n\n\tA/C does not EXIST in the database." ;
         cout << "\n\tPress ENTER to Search A/C again.\n\tPress M to go to Main Menu......... ";
         ac_no.clear();
         filename.clear();
         cin.ignore();
         char c;
         c=_getch();
         if( c == 'M' || c == 'm')
            menu();
         else
            goto loop;
     }


}

void account :: withdraw_ac()
{
     loop:
     string temp;
     balance = withdraw = deposit = 0;
     system("CLS");
     cout << "\n\t   Withdraw Money";
     cout << "\n\t--------------------\n\n";

     cout << "\tEnter A/C No.\t:\t";
     cin >> ac_no;
     filename = "ACC Holders/"+ac_no+".bin";
     ifstream withdraw_ac;
     withdraw_ac.open(filename.c_str());
     if(withdraw_ac.is_open())
     {

        while(!withdraw_ac.eof())
         {
            withdraw_ac >> temp;
         }

         withdraw_ac.close();
         balance = atoll(temp.c_str());
         ofstream wid;
         cout << "\tWithdraw Amount\t:\t";
         cin >> withdraw;
         if(balance>withdraw+370)
         {
         balance = balance - withdraw;
         wid.open(filename.c_str(), ios :: app);
         wid << "\n\t" << _strdate(date) << "\t" << _strtime(time) << "\t" << deposit << "\t\t\t" << withdraw << "\t\t\t\t" << balance << " ";
         wid.close();

         cout << "\n\n\n\tWithdraw Completed.";
         cout << "\n\tPress ENTER to get back to Main Menu...";
         cin.get();
         cin.ignore();
         filename.clear();
         temp.clear();
         ac_no.clear();
         menu();
         }
         else
         {
           cout << "\n\n\n\tInsufficient Balance. A/C must hold at least TK. 370." ;
         cout << "\n\tPress ENTER to Search A/C again.\n\tPress M to go to Main Menu......... ";
         ac_no.clear();
         filename.clear();
         temp.clear();
         cin.ignore();
         char c;
         c=_getch();
         if( c == 'M' || c == 'm')
            menu();
         else
            goto loop;
         }

     }

     else
     {
        cout << "\n\n\n\tA/C does not EXIST in the database." ;
         cout << "\n\tPress ENTER to Search A/C again.\n\tPress M to go to Main Menu......... ";
         ac_no.clear();
         filename.clear();
         cin.ignore();
         char c;
         c=_getch();
         if( c == 'M' || c == 'm')
            menu();
         else
            goto loop;
     }


}

void account :: statement_ac()
{
   loop:
    system("CLS");
     cout << "\n\t   A/C Statement";
     cout << "\n\t--------------------\n\n";
     cout << "\tEnter A/C No.\t:\t";
     cin >> ac_no;
     filename = "ACC Holders/"+ac_no+".bin";
    fstream stat;
    stat.open(filename.c_str());
    if(stat.is_open())

    {
        char ch;
        system("CLS");
        while(!stat.eof())
        {
            stat.get(ch);
            cout << ch;
        }
        stat.close();
        cout << "\n\n\n\tPress ENTER to get back to Main Menu...";
         cin.get();
         cin.ignore();
         filename.clear();
         ac_no.clear();
         menu();
    }

    else
    {
        cout << "\n\n\n\tA/C does not EXIST in the database." ;
         cout << "\n\tPress ENTER to Search A/C again.\n\tPress M to go to Main Menu......... ";
         ac_no.clear();
         filename.clear();
         cin.ignore();
         char c;
         c=_getch();
         if( c == 'M' || c == 'm')
            menu();
         else
            goto loop;
    }

}

void account :: listof_ac()
{
    system("CLS");
    ifstream ac_list;
    filename1 = "Administrative/List_AC.bin";
    ac_list.open(filename1.c_str());
    char c;
    while(!ac_list.eof())
    {
        ac_list.get(c) ;
        cout << c;
    }

    ac_list.close();

    filename1.clear();
    cout << "\n\n\n\tPress ENTER to get back to Main Menu.....";
    cin.get();
    cin.ignore();
    menu();

}

void account :: logout()
{
        loop:
        system("CLS");
        cout << "\n\n\n\n\t\tSuccessfully Logged Out." ;
        cout << "\n\n\t\tPress ENTER to Return to ADMIN LOG IN Panel\n\t\t\tOR\n\t\tPress 'X' key to EXIT......." ;
        char t;
        t= _getch();
        if(t=='X' || t=='x')
        {
            cout << "\n\n\n\n";
            exit(0);
        }
        else if (t==13)
        {
            admin();
        }

        else
        {
            goto loop;
        }

}

int main()
{


    logo();
    account obj;
    obj.admin();


    return 0;
}


//Function Definitions..........

void logo()
{
    fstream logo;
    logo.open("Administrative/logo.bin");
    char ch;
    while(!logo.eof())
    {
        logo.get(ch);
        cout << ch;
    }

    cout << "\n\t\t\t\t\tSSL Bank Management System.\n";
    cout << "\n\t\t\t\t\tDeveloped by MD. Asif Hossain." ;
    cout << "\n\n\t\t\t\t\tSystem Initializing ";
    for(int i=1;i<=20;i++)
    {
        Sleep(200);
        cout << ".";
    }

}

void intro()
{
    cout<< "\n\n\t\t\t-----------------------------------------"  ;
    cout << "\n\t\t\t| Welcome to SSL Bank Management System |" ;
    cout<< "\n\t\t\t-----------------------------------------\n\n"  ;

}





