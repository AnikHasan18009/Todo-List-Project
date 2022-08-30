#include<bits/stdc++.h>
#include<fstream>
#include<thread>
#include<mutex>
#include<windows.h>
#include<mmsystem.h>
#include<time.h>
#include<graphics.h>
using namespace std;
int choice;
mutex m;
struct work
{
    string s;
    int checked=0,hour,minute;
};
vector <work> v;
void alarm()
{
    time_t now;
    struct tm* right_now;
    while(1)
    {
        m.lock();
        time(&now);
        right_now=localtime(&now);
        if(!v.empty())
        {
            for(int i=0; i<v.size(); i++)
            {
                if(v[i].hour==right_now->tm_hour&&v[i].minute==right_now->tm_min)
                {
                    if(v[i].checked==0){
                    PlaySound(TEXT("ac.wav"),NULL,SND_ASYNC);
                    Sleep(5000);
                    v[i].checked=1;}
                }
                else
                {
                    v[i].checked=0;
                }

            }
        }
        //free(right_now);
        m.unlock();
        if(choice==4)
        {
            break;

        }
    }
}

void write_file()
{
    ofstream f;
    f.open("file.txt");
    for(int i=0; i<v.size(); i++)
    {
        f<<v[i].s<<"\n"<<v[i].hour<<":"<<v[i].minute<<"\n";
    }
    f.close();
}
void read_file()
{
    ifstream f;
    char a;

    struct work n;
    f.open("file.txt");
    while(getline(f,n.s))
    {
        string s;
        getline(f,s);
        stringstream ss(s);
        ss>>n.hour>>a>>n.minute;
        v.push_back(n);
    }
    f.close();
}
void seelist()
{
    system("cls");
    if(v.empty())
    {
        cout<<endl<<endl<<"\t\t\t< The list is empty >"<<endl<<endl;
    }
    else
    {
        cout<<"\t\t\t< The todo list is >"<<endl;
        for(int i=0; i<v.size(); i++)
        {
            cout<<"\t\t\t"<<i+1<<". "<<v[i].s;
            cout<<" ||   time=";
            if(v[i].hour<10)
            {
                cout<<"0";
            }
            cout<<v[i].hour<<":";
            if(v[i].minute<10)
            {
                cout<<"0";
            }
            cout<<v[i].minute<<endl;
        }
    }
    system("pause");
}
void addlist()
{
    system("cls");
    char a,b;
    struct work n;
    int hour,minute;
    getchar();
    cout<<"Enter the work"<<endl;
    getline(cin,n.s);
    cout<<"\tAdd the time in 'hour:minute' "<<endl;
    while(1){
            try{
    cin>>hour>>a>>minute;
    if(hour>23 || hour<0 ||minute <0 ||minute>59 ||a!=':')
        throw "Please enter the date in correct format";
    else{
        n.hour=hour;
        n.minute=minute;
    v.push_back(n);
    break;
        }
            }
            catch(const char* exc)
                {cout<<exc<<endl;}
    }
    write_file();
    seelist();

}
void deletelist()
{
    system("cls");
    seelist();
    int i,j,n;
    i=v.size();
    if(i==0)
    {
        cout<<"\t\t\tthere is nothing to delete"<<endl;
        system("pause");
    }
    else if(i>0)
    {
        cout<<"\t\t\tEnter the number which want to delete"<<endl;
        cin>>n;
        if(n>i)
        {
            cout<<"\t\t\tThere is no such element"<<endl;
            system("pause");
        }
        else
        {
            j=n-1;
            v.erase(v.begin()+j);
            write_file();
            seelist();
        }
    }

}
void welcome()
{
    read_file();
    system("color B");
    cout<<endl<<endl;
    cout<<"\t\t\t########To do list app########"<<endl;
    cout<<"\t\t\t------------------------------"<<endl;
    cout<<"\t\t\t###########Welcome############"<<endl;

    system("pause");
    while(1)
    {
        int ch;
        system("cls");
        cout<<endl<<endl;
        cout<<"\t\t\t----------------------------------"<<endl;
        cout<<"\t\t\t| press 1 to see the list        |"<<endl;
        cout<<"\t\t\t| press 2 to add in the list     |"<<endl;
        cout<<"\t\t\t| press 3 to delete from the list|"<<endl;
        cout<<"\t\t\t| press 4 to exit the app        |"<<endl;
        cout<<"\t\t\t----------------------------------"<<endl;
        while(1)
        {try{
        cin>>ch;
        if(ch>=1 &&ch<=4)
            {
                choice=ch;
                break;}
        else
         throw "Please try again\n";
        }
        catch(const char* exc)
        {
            cout<<exc;
        }}
        if(choice==1)
        {
            seelist();
        }
        else if(choice==2)
        {
            addlist();
        }
        else if(choice==3)
        {
            deletelist();
        }
        else if(choice==4)
        {
            break;
        }

    }
}
void digiclock()
{
    int gm,gd=DETECT;
    initgraph(&gd,&gm,"");
    time_t rawTime;
    struct tm *currentTime;
    char a[100];
while(1){
        if(choice==4)
        {
            closegraph();
            break;
        }
    rawTime=time(NULL);
    currentTime=localtime(&rawTime);
    strftime(a,100,"%H:%M:%S",currentTime);
    setcolor(11);
    settextstyle(6,HORIZ_DIR,7);
    outtextxy(130,100,a);
    strftime(a,100,"%A,%d %B,%Y",currentTime);
    settextstyle(6,HORIZ_DIR,4);
    outtextxy(70,250,a);
    delay(1000);
}
}
int main()
{

    thread t2(welcome);
    thread t1(alarm);
    thread t3(digiclock);
    t2.join();
    t1.join();
    t3.join();
    return 0;
}
