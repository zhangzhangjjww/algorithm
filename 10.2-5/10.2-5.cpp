#include"diction.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    singlelist<int> sl;
    cout<<"enter list:\n";
    cout<<"enter the table(q to quit):";
    int c;string s;
    while(cin>>s&&s!="q")
    {
        cout<<"enter the content:";
        cin>>c;
        sl[s]=c;
        cout<<"enter the table(q to quit):";
    }
    sl.display();
    cout<<endl;
    sl.delete1(sl.search1("zjw"));
    sl.delete1(sl.search1("ss"));
    sl.display();
    return 0;
}
