#include<bits/stdc++.h>
using namespace std;
class Passenger{
    public:
        static int id;
        string name;
        int age;
        string preference;
        int pass_id=id++;
        string gender;
        string alloted;
        int number;
        Passenger(string n="", int a=0, string g="", string pref=""){
            name=n;
            age=a;
            gender=g;
            preference=pref;
            id++;
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
    // else if()
}
int main(){
    int choice;
    bool close=true;
    cout<<"Welcome to railway reservation"<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"Main menu"<<endl;
    // while(close){
        cout<<"1. Book"<<endl;
        cout<<"2. Booked tickets"<<endl;
        cout<<"3. Exit"<<endl;
    //     cout<<"Enter the option: ";
    //     cin>>choice;
    //     switch(choice)
    //     {
    //         case 1:{
                string name,gender, pref;
                int age;
    //             bool child=false;
    //             string childname;
    //             int childAge;
                cout<<"Enter name: ";
                cin>>name;
                cout<<"enter age: ";
                cin>>age;
                cout<<"enter gender [M/F]: ";
                cin>>gender;
    //             if(gender == "F"){
    //                 cout<<"1. If you have a child, press 1."<<endl;
    //                 cout<<"2. If you don't have a child, press 2."<<endl;
    //                 int option;
    //                 cin>>option;
    //                 if(option == 1){
    //                     cout<<"Enter child name: ";
    //                     cin>>childname;
    //                     cout<<"Enter child age: ";
    //                     cin>>childAge;
    //                     child=true;
    //                 }
    //                 else child=false;
    //             }
                cout<<"enter berth preference [L/M/U]: ";
                cin>>pref;
                Passenger p(name,age, gender, pref);
                // bookTicket(p);
    //             // t.addTicket(name,age,gender, pref);
    //             cout<<"Tickets booked successfully!"<<endl;
    //             cout<<"----------------------------"<<endl;
    //             break;}
    //         case 2:
    //             {  
    //                 break;
    //             }
    //         case 3:{
    //             close=false;
    //             break;
    //         }
    //     }
    // }
    
    Tickets t1;
    t1.availableTickets();
    t1.passengerDetails();

}
