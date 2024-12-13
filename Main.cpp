///FINISHED: 30-11-22024
///DEVELOPED BY
///     -> MUNTASIR BILLAH NAKEEB
///         (B.Sc IN ECE DEPT. OF KUET, BANGLADESH)

///FINISHED: 30-11-22024
///DEVELOPED BY
///     -> NAKEEB(2109016)
///     -> MAHI  (2109025)
///     -> RAJESH(2109026)
///     -> SHOWMO(2109028)
///     -> SHUVO (2109029)

#include<bits/stdc++.h>
#include<iostream>
#include<windows.h>
#include<stdbool.h>
#include <conio.h>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>
using namespace std;

bool password(string pass);
string upperl();

class BOOK
{
public:
    string title, author, ISBN;
    int no;
    BOOK(string t, string a, string isbn, int n):
        title(t),author(a),ISBN(isbn),no(n) {}
};

class MEMBER
{
public:
    string name, id, pass;
    vector<BOOK>issued_book;
    vector<BOOK>requested_book;
    int availabe=5;///Can issue or request
    int top=0; /// requested book no.
    MEMBER* next;

    ///TAKE A BOOK & RETURN IS ISSUING OR NOT
    bool issue(BOOK& bk)
    {
        if(availabe>0)///CHECKING ISSUE ABILITY
        {
            issued_book.push_back(bk);
            availabe--;
            if(top>availabe)///issuing get the priority
            {
                requested_book.pop_back();
                top--;
            }
            return true;
        }
        else
            return false;
    }

    int issue_no()///RETURN NO. OF ISSUED BOOK
    {
        return 5-availabe;
    }

    int request_no()///RETURN NO. OF REQUESTED BOOK
    {
        return top;
    }


    bool request(BOOK& bk)///request for out of stock book
    {
        if(top<availabe)
        {
            requested_book.push_back(bk);
            return true;
        }
        else
            return false;
    }

    ///Return tittle for increasing available copy
    string deposit(int serial)
    {
        string t;
        t=issued_book[serial].title;
        issued_book.erase(issued_book.begin()+serial);
        availabe++;
        return t;
    }

    ///ASSOCIATED WITH display_member(), deposit(), my_details()
    void display_me()///DISPLAY MEMBER INFORMATION
    {
        cout<<"\tID: "<<id<<"\t\tName: "<<name<<endl;
        cout<<"\tNo. of Issued book: "<<issue_no()<<endl;
        int i=0;
        for(auto bk:issued_book)
        {
            cout<<"\t["<<i++<<"]. TITLE: "<<bk.title<<"\t\tAUTHOR: "<<bk.author<<endl;
        }
        cout<<endl;
        cout<<"\tNo. of requested book: "<<request_no()<<endl;
        for(auto bk:requested_book)
        {
            cout<<"\tTITLE: "<<bk.title<<"\t\tAUTHOR: "<<bk.author<<endl;
        }
        cout<<endl<<endl;
    }
};

///MANAGEMENT CLASS of Recently returned book
class RETURN_ST
{
private:
    stack<BOOK> return_stack;///Store Recently return Book:

public:

    void add_return(const BOOK& book)
    {
        return_stack.push(book);
    }

    ///ASSOCIATED WITH ADMIN
    void print_return()///PRINT THE RECENTLY RETURNED BOOK
    {
        int i=0;
        cout<<"\tRecently returned book: "<<endl;
        if(return_stack.empty())
        {
            cout<<"\tNo Book..."<<endl;
            return;
        }
        stack<BOOK> temp = return_stack;
        while (!temp.empty())
        {
            BOOK book = temp.top();
            cout << "\t["<<i<<"].Book: " << book.title << "\tby " << book.author << endl;
            temp.pop();
            i++;
        }
    }
};

///MANAGEMENT CLASS of Requested book
class REQUEST_Q
{
private:
    queue<BOOK> request_queue;///STORE requested book that are out of stock:
    queue<BOOK> request_to_add;///STORE requested book that are not available:
public:

    void add_request(const BOOK& book)/// ADD UNAVAILABLE BOOK
    {
        request_to_add.push(book);
    }

    void stock_request(const BOOK& book)///ADD OUT OF STOCK
    {
        request_queue.push(book);
    }

    ///ASSOCIATED WITH ADMIN
    void print_request()
    {
        int i=0;
        queue<BOOK>temp = request_queue;
        cout<<"\tOUT OF STOCK: "<<endl;
        if(request_queue.empty())
        {
            cout<<"\tNo Book..."<<endl;
            return;
        }
        while (!temp.empty())///PRINTING OUT OF STOCK
        {
            BOOK book = temp.front();
            cout << "\t["<<i<<"].Book: " << book.title << "\tby " << book.author << endl;
            temp.pop();
            i++;
        }

        temp=request_to_add;
        i=0;
        cout<<"\tNOT AVAILABLE: "<<endl;
        if(request_to_add.empty())
        {
            cout<<"\tNo Book..."<<endl;
            return;
        }
        while (!temp.empty())///PRINTING NOT AVAILABLE
        {
            BOOK book = temp.front();
            cout<< "\t["<<i<<"].Book: " << book.title << "\tby " << book.author << endl;
            temp.pop();
            i++;
        }
    }
};


class SECTION ///LYBRARY SECTION HIERARCHY
{
public:
    string name;
    vector<SECTION*> subs;
    void add_section(SECTION* sub)
    {
        subs.push_back(sub);
    }
};

///GLOBAL VARIABLES;
vector<BOOK> books;
MEMBER *start=NULL;
RETURN_ST rtrns;
REQUEST_Q rqstq;
SECTION *root=NULL ;
int ex=0;

///BOOK MANAGEMENT CLASS(ADD, DELETE, DISPLAY)
class BOOK_CATALOG
{
public:

    void add_book()///ADD BOOK BY PUSHING IN GLOBAL VARIABLE books
    {
        string title, author, ISBN;
        int no;
        cin.ignore();
        cout<<"\tEnter title: ";
        title=upperl();
        cin.ignore();
        cout<<"\tEnter author: ";
        author=upperl();
        cin.ignore();
        cout<<"\tEnter ISBN: ";
        getline(cin,ISBN);
        cin.ignore();
        cout<<"\tNumber of Copy: ";
        cin>>no;
        BOOK newBook(title, author, ISBN, no);
        books.push_back(newBook);
        cout<<endl<<"\tA new Book is added SUCCESSFULLY...";
    }

    bool delete_bookisbn()///DELETE A BOOK USING ISBN
    {
        string ISBN;
        cin.ignore();
        cout<<"\tEnter ISBN no.: ";
        getline(cin,ISBN);
        int i=0;
        for (auto bks:books)
        {
            if (bks.ISBN == ISBN)
            {
                books.erase(books.begin()+i);
                return true;
            }
            i++;
        }
        return false;
    }

    bool delete_booktitle()///DELETE A BOOK USING ISBN
    {
        string title;
        cin.ignore();
        cout<<"\tEnter Title: ";
        title=upperl();
        int i=0;
        for (auto bks:books)
        {
            if (bks.title == title)
            {
                books.erase(books.begin()+i);
                return true;
            }
            i++;
        }
        return false;
    }

    void display_books()
    {
        cout<<"\tALL BOOKS: "<<endl;
        for (auto bks : books)
        {
            cout<<"\t**Title: "<<bks.title<<"\t\t**Author: "<<bks.author<<endl
                <<"\t**ISBN: "<< bks.ISBN<<"\t\t**Available copy: "<<bks.no<<endl<<endl;
        }
    }

    void display_abook()
    {
        string title;
        cin.ignore();
        cout<<"\tEnter title: ";
        title=upperl();
        cout<<"\tBOOK: "<<endl;
        for (auto bks : books)
        {
            if(bks.title==title)
            {
                cout<<"\t**Title: "<<bks.title<<"\t\t**Author: "<<bks.author<<endl
                    <<"\t**ISBN: "<< bks.ISBN<<"\t\t**Available copy: "<<bks.no<<endl<<endl;
                return;
            }
        }
        cout<<"\tEnter wrong title..."<<endl;
        return;
    }
};

///BOOK MANAGEMENT CLASS(ADD, DELETE, DISPLAY)
class MEMBER_CTALOG
{
public:

    ///ADD MEMBER, checking,sorting
    void add_member()
    {
        MEMBER *srt=start, *srt1, *ptr=new MEMBER();

        cin.ignore();
        cout<<"\tEnter member Name: ";
        ptr->name=upperl();
        cin.ignore();
        cout<<"\tEnter ID: ";
        ptr->id=upperl();
        ptr->pass=ptr->id;
        ptr->next=NULL;

        ///Duplicate checking
        if(check_dup(ptr->name,ptr->id))
        {
            cout<<"\tAlready Exist..."<<endl;
            return;
        }
        else
        {
            if(start==NULL)
            {
                start=ptr;
            }
            else if(start->id > ptr->id)
            {
                ptr->next=start;
                start=ptr;
            }
            else
            {
                srt1=srt;
                srt=srt->next;
                while(srt!=NULL)
                {
                    if(srt->id>ptr->id)
                    {
                        ptr->next=srt;
                        srt1->next= ptr;
                        break;
                    }
                    srt1=srt;
                    srt=srt->next;
                }
                if(srt==NULL)
                {
                    srt1->next=ptr;
                }

            }
            cout<<"\tMEMBER ADDED SUCCESSFULLY..."<<endl;
        }

    }

    ///Check duplicate member
    bool check_dup(string name, string id)
    {
        MEMBER *srt=start;
        while(srt!=NULL)
        {
            if(srt->name==name && srt->id==id)
            {
                return true;
                ///break;
            }
            srt=srt->next;
        }
        return false;
        /* if(srt->name==name && srt->id==id)
         {
             return true;
         }
         else

         {
             return false;
         }*/

    }

    ///DELETE MEMBER BY ID
    void delete_member()
    {
        string id;
        MEMBER *ptr=new MEMBER();
        MEMBER *srt=start;
        cin.ignore();
        cout<<"\tEnter studnet ID: ";
        getline(cin,id);
        while(srt->id!=id && srt->next!=NULL)
        {
            ptr=srt;
            srt=srt->next;
        }
        if(srt->id!=id)
        {
            cout<<"\tMember doesn't Exist..."<<endl;
            getch();
            return;
        }
        ptr->next=srt->next;
        cout<<"\tMember DELETED Successfully..."<<endl;
    }

    ///DISPLAY ALL MEMBER
    ///ASSOCIATED WITH MEMBER::display_me()
    void display_member()
    {
        MEMBER *srt=start;
        while(srt->next!=NULL)
        {
            srt->display_me();
            srt=srt->next;
        }
        srt->display_me();
    }
};

/// MANAGEMENT CLASS (SEARCH , SORT)
class SORT_SEARCH
{
public:

    ///PARTITION FOR TITLE
    int partition1( int low, int high)
    {
        string pivot = books[high].title;
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (books[j].title < pivot)
            {
                i++;
                swap(books[i], books[j]);
            }
        }
        swap(books[i + 1], books[high]);
        return i + 1;
    }

    ///PARTITION FOR ISBN
    int partition2( int low, int high)
    {
        string pivot = books[high].ISBN;
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (books[j].ISBN < pivot)
            {
                i++;
                swap(books[i], books[j]);
            }
        }
        swap(books[i + 1], books[high]);
        return i + 1;
    }

    /// Quick Sort BY TITLE
    void sort_title(int low, int high)
    {
        if (low < high)
        {
            /// Partitioning index
            int pi = partition1(low, high);
            sort_title(low, pi - 1);  /// Left sub-array
            sort_title(pi + 1, high); /// Right sub-array
        }
    }

    ///QUICK SORTING BY ISBN
    void sort_isbn(int low, int high)
    {
        if (low < high)
        {
            /// Partitioning index
            int pi = partition2(low, high);
            sort_title(low, pi - 1);  /// Left sub-array
            sort_title(pi + 1, high); /// Right sub-array
        }

    }

    ///BINARY SEARCH BY TITLE
    BOOK* search_title(const string& title)
    {
        int left = 0, right = books.size() - 1;
        sort_title(left,right);
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (books[mid].title == title)
            {
                return &books[mid];
            }
            else if (books[mid].title < title)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
         return nullptr;///NOT FOUND LOGIC
    }

    ///Normal search By ISBN
    BOOK* search_isbn(string ISBN)
    {
        for (auto& book : books)
        {
            if (book.ISBN == ISBN)
            {
                return &book;
            }
        }
        return nullptr;
    }

};

///ADMIN PANNEL INHERITS BOOK CATALOG, MEMBER CATALOG,SORT_SEARCH
class ADMIN: public BOOK_CATALOG, public MEMBER_CTALOG, public SORT_SEARCH
{
    string pass="2210";
public:

    ///Allow to find the desired node
    ///RETURN with ADDRESS FOR ADDING
    SECTION* finds(SECTION* node,string name)
    {
        if (node->name == name)
        {
            return node;
        }
        for (auto& sub: node->subs)
        {
            SECTION* found = finds(sub, name);
            if (found)
            {
                return found;
            }
        }
        return nullptr;
    }

    /// ALLOW ADDING A SECTION BY TAKING PARENT
    void add_hierarchy()
    {
        if(root==NULL)
        {
            cin.ignore();
            cout<<"\tEnter the ROOT of Hierarchy: ";
            root = new SECTION();
            root->name=upperl();
        }
        else
        {
            string pname;
            cout << "\tEnter the name of the parent: ";
            pname=upperl();
            SECTION* parent= finds(root,pname);///Find the parent section
            SECTION* sub=new SECTION();
            if (parent!=nullptr)
            {
                cout << "\tEnter the name of the sub-section: ";
                sub->name=upperl();
                parent->add_section(sub);/// Add it to the parent

                cout<<"\t "<<sub->name<< " added to section "<<pname<<endl;
            }
            else
            {
                cout << "\tSection '" <<pname<< "' not found.\n";
            }
        }
    }

    void print_section(SECTION* node, int level)///PRINT HIERARCHY
    {
        if (!node)
            return;
        cout <<"\t\t"<< string(level, ' ') << node->name << endl;
        for (SECTION* subs : node->subs)
        {
            print_section(subs, level + 1);
        }
    }

    ///TO KEEP DATA SAFE
    void login()
    {
        if (password(pass))
        {
            menu();
        }
        else
        {
            cout<<"\tWrong Password...";
            getch();
        }
    }

    ///ADMINSTRATOR MENU
    void menu()
    {
        system("cls");
        int ch;
        cout<<"\n\n\n\tADMINISTRATOR MENU";
        cout<<"\n\n\t[0].BACK TO MAIN MENU.";
        cout<<"\n\n\t[1].CREATE BOOK.";
        cout<<"\n\n\t[2].DELETE BOOK BY ISBN OR TITLE.";
        cout<<"\n\n\t[3].DISPLAY ALL BOOKS.";
        cout<<"\n\n\t[4].SPECIFIC BOOK INFORMATION.";
        cout<<"\n\n\t[5].SORT BOOK BY ISBN OR TITLE.";
        cout<<"\n\n\t[6].ADD MEMBER RECORD.";
        cout<<"\n\n\t[7].DELETE MEMBER RECORD.";
        cout<<"\n\n\t[8].DISPLAY MEMBERS RECORD.";
        cout<<"\n\n\t[9].SHOW RECENTLY RETURNED BOOK.";
        cout<<"\n\n\t[10].SHOW REQUESTED BOOK.";
        cout<<"\n\n\t[11].ADD SECTION OF THE HIERARCHY.";
        cout<<"\n\n\t[12].PRINT SECTION HIERARCHY.";
        cout<<"\n\n\tPlease Enter Your Choice (0-12): ";
        cin>>ch;
        switch(ch)
        {
        case 0:
        {
            system("cls");
            cout<<endl<<endl;
            return ;
            break;
        }

        case 1:
        {

            system("cls");
            cout<<endl<<endl;
            add_book();
            getch();
            break;
        }

        case 2:
        {
            system("cls");
            cout<<endl<<endl;
            int choice;
            cout<<"\tDelete BOOK BY->";
            cout<<"\n\t[1].ISBN\n\t[2].TITLE."<<endl;
            cout<<"\tEnter your choice(1-2): ";
            cin>>choice;

            if(choice==1)
            {
                if(delete_bookisbn())
                {
                    cout<<"\tBook is Deleted."<<endl;
                }
                else
                {
                    cout<<"\tThere is no book of this ISBN."<<endl;
                }
            }
            else if(choice==2)
            {
                if(delete_booktitle())
                {
                    cout<<"\tBook is Deleted."<<endl;
                }
                else
                {
                    cout<<"\tThere is no book of this ISBN."<<endl;
                }
            }
            else
            {
                cout<<"Invalid choice. TRY again...";
                getch();
                break;
            }
            getch();
            break;
        }

        case 3:
        {
            system("cls");
            cout<<endl<<endl;
            display_books();
            getch();
            break;
        }

        case 4:
        {
            system("cls");
            cout<<endl<<endl;
            display_abook();
            getch();
            break;
        }

        case 5:
        {
            system("cls");
            cout<<endl<<endl;
            int choice;
            cout<<"\tSORT BOOK BY->";
            cout<<"\n\t[1].ISBN\n\t[2].TITLE."<<endl;
            cout<<"\tEnter your choice(1-2): ";
            cin>>choice;

            if(choice==1)
            {
                sort_isbn(0,books.size()-1);
            }
            else if(choice==2)
            {
                sort_title(0,books.size()-1);
            }
            else
            {
                cout<<"Invalid choice. TRY again...";
                getch();
                break;
            }

            string print="\tBOOKS are sorting...";
            for(auto ch:print)
            {
                cout<<ch;
                Sleep(40);
            }
            getch();
            break;
        }

        case 6:
        {
            system("cls");
            cout<<endl<<endl;
            add_member();
            getch();
            break;
        }

        case 7:
        {
            system("cls");
            cout<<endl<<endl;
            delete_member();
            getch();
            break;
        }

        case 8:
        {
            system("cls");
            cout<<endl<<endl;
            display_member();
            getch();
            break;
        }

        case 9:
        {
            system("cls");
            cout<<endl<<endl;
            rtrns.print_return();
            getch();
            break;
        }

        case 10:
        {
            system("cls");
            cout<<endl<<endl;
            rqstq.print_request();
            getch();
            break;
        }

        case 11:
        {
            system("cls");
            cout<<endl<<endl;
            add_hierarchy();
            getch();
            break;
        }

        case 12:
        {
            system("cls");
            cout<<endl<<endl;
            print_section(root,0);
            getch();
            break;
        }

        default:
            cout<<"\t\t";
        }
        menu();
    }

};

///USE TO ISSUE A BOOK BY ISBN
///REQUEST MEMBER TO LOG IN LOGIN
void book_issue()
{
    string id;
    MEMBER *srt=start;
    BOOK *bk;
    string ISBN;
    SORT_SEARCH bro;

    cin.ignore();
    cout<<"\tEnter your ID: ";
    getline(cin,id);

    while(srt->id!=id)///checking ID
    {
        srt=srt->next;
    }
    if(srt->id!=id)
    {
        cout<<"\tSorry. You are not in the Member list."<<endl;
        return;
    }

    cin.ignore();
    cout<<"\tEnter ISBN: ";
    getline(cin,ISBN);
    bk= bro.search_isbn(ISBN);

    if(bk==nullptr)///CHECKING BOOK
    {
        cout<<"\tYou enterd wrong ISBN."<<endl;
        getch();
        return;
    }
    else if(bk->no>0)///CHECKING BOOK STOCK AVAILABLE OR NOT
    {
        if(password(srt->pass))///CHECKING USER OR NOT
        {
            if(srt->issue(*bk))///CHECKING ABILITY FOR ISSUING
            {
                cout<<"\tIssued successfully..."<<endl;
                bk->no--;
            }
            else
            {
                cout<<"\tYou are not able to issue..."<<endl;
            }

        }
        else
        {
            cout<<"\tYou entered wrong password..."<<endl;
        }
    }
    else
    {
        cout<<"\tNot available..."<<endl;
        if(srt->request(*bk))
        {
            rqstq.stock_request(*bk);
        }
    }
}

void add_request()
{
    string title, author, ISBN;
    cin.ignore();
    cout<<"\tEnter title: ";
    title=upperl();
    cin.ignore();
    cout<<"\tEnter author: ";
    author=upperl();
    cin.ignore();
    cout<<"\tEnter ISBN: ";
    getline(cin,ISBN);
    cin.ignore();
    BOOK newBook(title, author, ISBN, 0);
    rqstq.add_request(newBook);
}

///USE TO RETURN BOOK FROM MEMBER ISSUED BOOK
///REQUEST MEMBER TO LOG IN LOGIN
void book_deposit()
{
    string id,title;
    int serial;
    MEMBER *srt=start;
    cin.ignore();
    cout<<"\tEnter your ID: ";
    getline(cin,id);
    while(srt->id!=id)
    {
        srt=srt->next;
    }
    if(srt->id!=id)
    {
        cout<<"\tSorry. You are not in the Member list."<<endl;
        return;
    }
    if(password(srt->pass))
    {
        if(srt->availabe<5)
        {
            srt->display_me();
            cout<<"Enter the seial no: ";
            cin>>serial;
            title=srt->deposit(serial);
            for(auto &bk:books)
            {
                if(bk.title==title)
                {
                    bk.no--;
                    rtrns.add_return(bk);
                    cout<<"Returned SUCCESSFULLY..."<<endl;
                }
            }
        }
        else
        {
            cout<<"You have no issued Book..."<<endl;
        }
    }
    else
    {
        cout<<"\tYou entered wrong password..."<<endl;
    }
}

///REQUEST MEMBER TO LOG IN LOGIN
/// TO SHOW DETAILS
void my_details()
{
    string id;
    MEMBER *srt=start;
    cin.ignore();
    cout<<"\tEnter your ID: ";
    getline(cin,id);

    while(srt!=NULL)///ID CHECKING
    {
        if(srt->id==id)
        {
            break;
        }
    }
    if(srt!=NULL)
    {
        if(password(id))///USER CHECKING
        {
            system("cls");
            cout<<"\tYour INFORMATION: "<<endl<<endl;
            srt->display_me();
        }
        else
        {
            cout<<"Wrong password..."<<endl;
        }
    }
    else
    {
        cout<<"Wrong ID..."<<endl;
    }


}

///CHEKCING PASSWORD TO LOGIN;
bool password(string pass)
{
    string pw;
    cin.ignore();
    cout<<"\tEnter the pasword: ";
    getline(cin, pw);
    return pass==pw;
}

///GET INPUT AND GIVE UPPER CASE;
string upperl()
{
    string s;
    getline(cin,s);
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

///FOR BEAUTY
void front_page()
{
    system("cls");
    system("color 27");
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t     |-----------------------------------------------|\n";
    cout<<"\t\t\t     |                                               |\n";
    cout<<"\t\t\t     |                                               |\n";
    cout<<"\t\t\t     |         ----------------------------          |\n";
    cout<<"\t\t\t     |                   WELCOME TO                  |\n";
    cout<<"\t\t\t     |                      /-/                      |\n";
    cout<<"\t\t\t     |           LIBRARY MANAGEMENT SYSTEM           |\n";
    cout<<"\t\t\t     |         ----------------------------          |\n";
    cout<<"\t\t\t     |                                               |\n";
    cout<<"\t\t\t     |                                               |\n";
    cout<<"\t\t\t     |                 DEVELOPED BY                  |\n";
    cout<<"\t\t\t     |             MUNTASIR BILLAH NAKEEB            |\n";
    cout<<"\t\t\t     |   (B.Sc IN DEPT. OF ECE OF KUET, BANGLADESH)  |\n";
    cout<<"\t\t\t     |-----------------------------------------------|\n";
    cout<<endl<<endl;
    cout<<"\t\t\t               Press any key to continue:";
    getch();
}

void starting()
{
    system("cls");
    cout<<endl<<endl<<endl<<"\t\t\t";
    char AppStarting[100] = "Application is Starting....";
    for(int i=0;i<strlen(AppStarting);i++)
    {
        cout<<AppStarting[i];
        Sleep(60);
    }
}

int main()
{
    front_page();
    starting();
    do
    {
        system("cls");
        system("color 17");
        cout<<"\n\n\n\t MAIN MENU";
        cout<<"\n\n\t[1]. ADMINISTRATOR MENU";
        cout<<"\n\n\t[2]. MY DETAILS";
        cout<<"\n\n\t[3]. BOOK ISSUE";
        cout<<"\n\n\t[4]. BOOK DEPOSIT";
        cout<<"\n\n\t[5]. SEARCH BOOK BY TITLE";
        cout<<"\n\n\t[6]. SEARCH BOOK BY ISBN";
        cout<<"\n\n\t[7]. REQUEST TO ADD BOOK";
        cout<<"\n\n\t[0]. EXIT";
        cout<<"\n\n\tPlease Select Your Option (0-7): ";
        int ch;
        cin>>ch;
        switch(ch)
        {
        case 0:
        {
            system("color 40");
            ex=1;
            getch();
            break;
        }

        case 1:
        {
            system("cls");
            cout<<endl<<endl;
            ADMIN admin;
            admin.login();
            break;
        }

        case 2:
        {
            system("cls");
            cout<<endl<<endl;
            my_details();
            getch();
            break;
        }

        case 3:
        {
            system("cls");
            cout<<endl<<endl;
            book_issue();
            getch();
            break;
        }

        case 4:
        {
            system("cls");
            cout<<endl<<endl;
            book_deposit();
            getch();
            break;
        }

        case 5:
        {
            system("cls");
            cout<<endl<<endl;
            SORT_SEARCH s;
            string title;
            BOOK *bk;

            cin.ignore();
            cout<<"\tEnter BOOK TITLE: ";
            getline(cin,title);

            bk=s.search_title(title);
            if(bk==nullptr)
            {
                cout<<"\tWRONG INPUT...";
                getch();
                break;
            }
            cout<<"\t**Title: "<<bk->title<<"\t**Author: "<<bk->author<<endl
                <<"\t**ISBN: "<< bk->ISBN<<"\t**Available copy: "<<bk->no<<endl<<endl;
            getch();
            break;
        }

        case 6:
        {
            system("cls");
            cout<<endl<<endl;
            SORT_SEARCH s;
            string ISBN;
            BOOK *bk;

            cin.ignore();
            cout<<"\tEnter BOOK ISBN: ";
            getline(cin,ISBN);

            bk=s.search_isbn(ISBN);
            if(bk==nullptr)
            {
                cout<<"\tWRONG INPUT...";
                getch();
                break;
            }
            cout<<"\t**Title: "<<bk->title<<"\t**Author: "<<bk->author<<endl
                <<"\t**ISBN: "<< bk->ISBN<<"\t**Available copy: "<<bk->no<<endl<<endl;
            getch();
            break;
        }

        case 7:
        {
            system("cls");
            cout<<endl<<endl;
            add_request();
            getch();
            break;
        }

        default :
        {
            system("cls");
            cout<<endl<<endl;
            cout<<"\tInvalid Choice...";
            getch();
            break;
        }
        }
    }
    while(ex==0);
}



