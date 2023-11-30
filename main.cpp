#include<bits/stdc++.h>
using namespace std;
class Passenger{
    public:
        static int id;
        string name;
        int age;
        string gender;
        string cname;
        int cage;
        string bp;
        int pass_id=id++;
        string alloted;
        int number;
        Passenger(string n="", int a=0, string g="",string cName="", int cAge=0, string pref=""){
            name=n;
            age=a;
            gender=g;
            cname=cName;
            cage=cAge;
            bp=pref;
            pass_id=id;
            alloted="";
            number=-1;
        }
};
int Passenger::id=0;

class Tickets{
    public:
        vector<Passenger> pass_detail;
        static int alb;
        static int amb;
        static int aub;
        static int arac;
        static int awl;
        
        static vector<int> lbp;
        static vector<int> mbp;
        static vector<int> ubp;
        static vector<int> Racp;
        static vector<int> Wlp;
        
        static queue<int> wlList;
        static queue<int> racList;
        static vector<int> bookedticketsList;
        static map<int, Passenger> passenger_stored_data;
        
        void bookTicket(Passenger p, int snumber, string alloted_berth){
            p.number=snumber;
            p.alloted=alloted_berth;
            passenger_stored_data.insert({p.pass_id, p});
            bookedticketsList.push_back(p.pass_id);
            cout<<"Passenger Id: "<<p.pass_id<<endl;
            cout<<"Passenger name: "<<p.name<<endl;
            cout<<"Passenger age: "<<p.age<<endl;
            cout<<"Passenger gender: "<<p.gender<<endl;
            cout<<"Alloted Berth: "<<snumber<<alloted_berth<<endl;
            cout<<"--------------------------Booked Successfully"<<endl;
        }
        
        void racTicket(Passenger p, int snumber, string racBerth){
            p.number=snumber;
            p.alloted=racBerth;
            passenger_stored_data.insert({p.pass_id, p});
            racList.push(p.pass_id);
            cout<<"Passenger Id: "<<p.pass_id<<endl;
            cout<<"Passenger name: "<<p.name<<endl;
            cout<<"Passenger age: "<<p.age<<endl;
            cout<<"Passenger gender: "<<p.gender<<endl;
            cout<<"Alloted Berth: "<<snumber<<racBerth<<endl;
            cout<<"--------------------------RAC Berth Given"<<endl;          
        }
        
        void wlTicket(Passenger p, int snumber, string wlBerth){
            p.number=snumber;
            p.alloted=wlBerth;
            passenger_stored_data.insert({p.pass_id, p});
            wlList.push(p.pass_id);
            cout<<"Passenger Id: "<<p.pass_id<<endl;
            cout<<"Passenger name: "<<p.name<<endl;
            cout<<"Passenger age: "<<p.age<<endl;
            cout<<"Passenger gender: "<<p.gender<<endl;
            cout<<"Alloted Berth: "<<snumber<<wlBerth<<endl;
            cout<<"--------------------------RAC Berth Given"<<endl;          
        }
        
        void cancelTicket(int passengerID){
            Passenger p=passenger_stored_data[passengerID];
            passenger_stored_data.erase(passengerID);
            bookedticketsList.erase(std::remove(bookedticketsList.begin(), bookedticketsList.end(), passengerID), bookedticketsList.end());


            int psnumber =p.number;
            cout<<"-------------------Cancelled Successfully"<<endl;
            if(p.alloted == "L"){
                lbp.push_back(psnumber);
                alb++;
            }
            else if(p.alloted == "M"){
                mbp.push_back(psnumber);
                amb++;
            }
            else if(p.alloted == "U"){
                ubp.push_back(psnumber);
                aub++;
            }
            if(racList.size()>0){
                Passenger passfromRac = passenger_stored_data[racList.front()];
                int pracnumber = passfromRac.number;
                Racp.push_back(pracnumber);
                racList.pop();
                arac++;
            if(wlList.size()>0){
                Passenger pfwl = passenger_stored_data[racList.front()];
                int pwlnumber = pfwl.number;
                Wlp.push_back(pwlnumber);
                wlList.pop();
                pfwl.number= Racp[0];
                pfwl.alloted="RAC";
                Racp.erase(Racp.begin());
                racList.push(pfwl.pass_id);
                awl++;
                arac--;
                bookTicket(passfromRac,0,"");
            }
            }
        }
        void availableTickets(){
            cout<<"Lower berth tickets: "<<alb<<endl;
            cout<<"Lower berth tickets: "<<amb<<endl;
            cout<<"Upper berth tickets: "<<aub<<endl;
            cout<<"RAC tickets: "<<arac<<endl;
            cout<<"Waiting List tickets: "<<awl<<endl;
        }
        
        void passengerDetails(){
            if(passenger_stored_data.size()==0){
                cout<<"No data found!"<<endl;
            }
            else {
                for(const auto &p:passenger_stored_data){
                    cout<<"Passenger Id:"<<p.second.pass_id<<endl;
                    cout<<"Passenger Name:"<<p.second.name<<endl;
                    cout<<"Passenger Age: "<<p.second.age<<endl;
                    cout<<"Passenger Gender: "<<p.second.gender<<endl;
                    // cout<<"Passenger Child name: "<<p.cname<<endl;
                    // cout<<"Passenger Child Age: "<<p.cage<<endl;
                    cout << "Alloted Berth:"<<p.second.number<< p.second.alloted<<endl;
                    cout<<"========================================="<<endl;

                }
            }
        }
};

int Tickets::alb=1;
int Tickets::amb=1;
int Tickets::aub=1;
int Tickets::arac=1;
int Tickets::awl=1;

vector<int> Tickets::lbp={1,2};
vector<int> Tickets::mbp={1};
vector<int> Tickets::ubp={1};
vector<int> Tickets::Racp={1};
vector<int> Tickets::Wlp={1};

queue<int> Tickets::wlList;
queue<int> Tickets::racList;
vector<int> Tickets::bookedticketsList;
map<int, Passenger> Tickets::passenger_stored_data;


void bookTicket(Passenger p){
    Tickets tb;
    if(tb.awl==0){ 
        cout<<"No tickets available.";
    return;
    }
    else if(p.age>60 && Tickets::alb>0){
        cout<<"You're Senior Citizen, so we arrange  a Lower Berth."<<endl;
        tb.bookTicket(p,(Tickets::lbp[0]),"L");
        Tickets::lbp.erase(Tickets::lbp.begin());
        Tickets::alb--;
    }
    else if(p.cname!="null" && Tickets::alb >0 ){
        cout<<"You have a child, so we arrange a Lower Berth"<<endl;
        tb.bookTicket(p,(Tickets::lbp[0]),"L");
        Tickets::lbp.erase(Tickets::lbp.begin());
        Tickets::alb--;
    }
    
    else if((p.bp == "L" && Tickets::alb>0) || (p.bp=="M" && Tickets::amb>0) || (p.bp=="U" && Tickets::aub>0)){
        if(p.bp=="L")
        {
            cout<<"Lower Berth Given"<<endl;
            tb.bookTicket(p,(Tickets::lbp[0]),"L");
            Tickets::lbp.erase(Tickets::lbp.begin());
            Tickets::alb--;
        }
        else if(p.bp=="M")
        {
            cout<<"Middle Berth Given"<<endl;
            tb.bookTicket(p,(Tickets::mbp[0]),"M");
            Tickets::mbp.erase(Tickets::mbp.begin());
            Tickets::amb--;
        }
        else if(p.bp=="U")
        {
            cout<<"Upper Berth Given"<<endl;
            tb.bookTicket(p,(Tickets::ubp[0]),"U");
            Tickets::ubp.erase(Tickets::ubp.begin());
            Tickets::aub--;
        }
        else if(Tickets::alb>0){
            cout<<"Lower Berth Given"<<endl;
            tb.bookTicket(p,(Tickets::lbp[0]),"L");
            Tickets::lbp.erase(Tickets::lbp.begin());
            Tickets::alb--;
        }
        else if(Tickets::amb>0){
            cout<<"Middle Berth Given"<<endl;
            tb.bookTicket(p,(Tickets::mbp[0]),"M");
            Tickets::mbp.erase(Tickets::mbp.begin());
            Tickets::amb--;
        }
        else if(Tickets::aub>0){
            cout<<"Upper Berth Given"<<endl;
            tb.bookTicket(p,(Tickets::ubp[0]),"U");
            Tickets::ubp.erase(Tickets::ubp.begin());
            Tickets::aub--;
        }
        else if(Tickets::arac>0){
            cout<<"RAC GIven"<<endl;
            tb.racTicket(p,(Tickets::Racp[0]),"RAC");
            Tickets::Racp.erase(Tickets::Racp.begin());
            Tickets::arac--;
        }
        else if(Tickets::awl > 0){
            cout<<"Waiting List Given"<<endl;
            tb.wlTicket(p,(Tickets::Wlp[0]),"WL");
            Tickets::Wlp.erase(Tickets::Wlp.begin());
            Tickets::awl--;
        }
    }
}

void cancelTicket(int id){
    Tickets tb;
    if (tb.passenger_stored_data.find(id) == tb.passenger_stored_data.end()) 
    {
        cout<<"passenger Id Not Found!"<<endl;
    }
    else{
        tb.cancelTicket(id);
    }
}
int main(){
    int choice;
    bool close=true;
    cout<<"Welcome to railway reservation"<<endl;
    cout<<"------------------------------"<<endl;
    while(close)
    {
        cout<<"Main menu"<<endl;
        cout<<"1. Book"<<endl<<"2. Cancel"<<endl<<"3. Availabe Tickets"<<endl<<"4. Booked Tickets"<<endl<<"5. Exit"<<endl;
        cout<<"Enter the option: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                string name,gender,bp,cname;
                int age,cage;
                string childname;
                int childAge;
                cout<<"Enter name: ";
                cin>>name;
                cout<<"enter age: ";
                cin>>age;
                cout<<"enter gender [M/F]: ";
                cin>>gender;
                if(gender == "F"){
                    cout<<"1. If you have a child, press 1."<<endl;
                    cout<<"2. If you don't have a child, press 2."<<endl;
                    int cchoice;
                    cin>>cchoice;
                    if(cchoice == 1){
                        cout<<"Enter child name: ";
                        cin>>cname;
                        cout<<"Enter child age: ";
                        cin>>cage;
                        cout<<"enter berth preference [L/M/U]: ";
                        cin>>bp;
                        Passenger p(name,age,gender,cname,cage,bp);
                        bookTicket(p);
                    }
                    else if(cchoice==2){
                        cout<<"enter berth preference [L/M/U]: ";
                        cin>>bp;
                        cname="null";
                        cage=0;
                        Passenger p(name,age, gender,cname,cage,bp);
                        bookTicket(p);
                    }
                }
                if(gender=="M"){
                    cout<<"enter berth preference [L/M/U]: ";
                    cin>>bp;
                    cname="null";
                    cage=0;
                    Passenger p(name,age, gender,cname,cage,bp);
                    bookTicket(p);
                }
                break;
            }
            case 2:
            {   cout<<"Enter Passenger ID: ";
                int id;
                cin>>id;
                cancelTicket(id);
                break;
            }
            case 3:
            {
                Tickets tb;
                tb.availableTickets();
                break;
            }
            case 4:
            {   Tickets tb;
                tb.passengerDetails();
                break;            
            }
            case 5:
            {
                close=false;
                break;
            }
        }
    }
    return 0;
}
