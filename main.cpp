#include <iostream>
#include <cstring>
#include <set>
#include <typeinfo>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>

using namespace std;
class casa;

class locuinta
{
protected:
    char numeClient[30];
    float suprafataUtila;
    float discount;
    float chirie;
    float pret;

public:
    float getChirie()
    {
        return this->chirie;
    };
    float getSuprafata() const{
        return this->suprafataUtila;
    };
    locuinta(char*,float, float);
    locuinta(const locuinta&);
    friend istream& operator>>(istream&,locuinta&);
    friend ostream& operator<<(ostream&,locuinta&);
    locuinta operator=(locuinta& ob)
    {
    strcpy(this->numeClient,ob.numeClient);
    this->suprafataUtila=ob.suprafataUtila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pret=ob.pret;
    }
    virtual void afisare() const
    {
       cout<<endl;
       cout<<"Nume client: "<<numeClient<<endl;
       cout<<"Suprafata utila: "<<suprafataUtila<<" metri patrati"<<endl;
       cout<<"Discount: "<<discount<<" %"<<endl;
       cout<<"Chirie: "<<chirie<<" $"<<endl;
    }
    virtual ~locuinta(){
        strcpy(numeClient,"Nedefinit");
        suprafataUtila=0;
        discount=0;}
    template <class tip> friend void calculChirie(tip&);
    template <class tip> friend int identificare(tip&);
//    template<>friend void calculChirie(casa&);
};


locuinta::locuinta(char* s="Nedefinit",float f=0, float d=0)
{
    strcpy(this->numeClient,s);
    this->suprafataUtila=f;
    this->discount=d;
    this->chirie=0;
    this->pret=0;
}

locuinta::locuinta(const locuinta &ob)
{
    strcpy(this->numeClient,ob.numeClient);
    this->suprafataUtila=ob.suprafataUtila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pret=ob.pret;
}

istream& operator>>(istream &in,locuinta &ob)
{
    cout<<endl<<"Nume client: ";
    in>>ob.numeClient;
    cout<<endl<<"Suprafata utila: ";

    char s[30];
    int ok=0;
    do
{
    try{
    in>>s;
    ob.suprafataUtila=atof(s);

       if(ob.suprafataUtila<=0){
           throw(2);
       }
       ok=0;
   }

   catch(int n)
   {
       cout<<"NUMARUL trebuie sa fie POZITIV!"<<endl;
       ok=1;
   }


}while(ok);
    cout<<endl<<"Discount (0-10%): ";
    char s2[30];
    int ok2=0;
    do
{
    try{
    in>>s2;
    ob.discount=atof(s2);

       if(ob.discount<0 || ob.discount>10){
           throw(2);
       }
       ok2=0;
   }

   catch(int n)
   {
       cout<<"NUMARUL trebuie sa fie INTRE 0 SI 10!"<<endl;
       ok2=1;
   }


}while(ok2);
    cout<<endl<<"Pret pe metru patrat: ";
    in>>ob.pret;
    return in;
}

ostream& operator<<(ostream& out,locuinta &ob)
{
    out<<endl;
    out<<"Nume client: "<<ob.numeClient<<endl;
    out<<"Suprafata utila: "<<ob.suprafataUtila<<endl;
    out<<"Discount: "<<ob.discount<<endl;
    return out;
}

class apartament : public locuinta
{
    int numarApartament;
    int etaj;
public:
    apartament(char*,float,float,int,int);
    apartament(const apartament &ob)
    {
    strcpy(this->numeClient,ob.numeClient);
    this->suprafataUtila=ob.suprafataUtila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pret=ob.pret;
    this->numarApartament=ob.numarApartament;
    this->etaj=ob.etaj;
    }
    ~apartament(){numarApartament=0;
    etaj=-2;}
    void afisare() const
    {
       cout<<endl;
       cout<<"Nume client: "<<numeClient<<endl;
       cout<<"Suprafata utila: "<<suprafataUtila<<" metri patrati"<<endl;
       cout<<"Discount: "<<discount<<" %"<<endl;
       cout<<"Numar apartament: "<<numarApartament<<endl;
       cout<<"Etaj: "<<etaj<<endl;
       cout<<"Chirie: "<<chirie<<" $"<<endl;
    }
    apartament operator=(const apartament& ob)
    {
        strcpy(this->numeClient,ob.numeClient);
    this->suprafataUtila=ob.suprafataUtila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pret=ob.pret;
    this->numarApartament=ob.numarApartament;
    this->etaj=ob.etaj;
    }
    friend istream& operator>>(istream&,apartament&);
    friend ostream& operator<<(ostream&,apartament&);
};



istream& operator>>(istream &in,apartament &ob)
{

    in>>dynamic_cast<locuinta &>(ob);
    cout<<endl<<"Numar: ";
    char s[30];
    int ok=0;
    do
{
    try{
    in>>s;
    ob.numarApartament=atoi(s);

       if(ob.numarApartament<=0){
           throw(2);
       }
       ok=0;
   }

   catch(int n)
   {
       cout<<"NUMARUL trebuie sa fie  MAI MARE CA 0!"<<endl;
       ok=1;
   }


}while(ok);
    cout<<endl<<"Etaj: ";
    char s2[30];
    int ok2=0;
    do
{
    try{
    in>>s2;
    ob.etaj=atoi(s2);

       if(ob.etaj<-1 || ob.etaj>10){
           throw(2);
       }
       ok2=0;
   }

   catch(int n)
   {
       cout<<"NUMARUL trebuie sa fie INTRE -1 SI 10!"<<endl;
       ok2=1;
   }


}while(ok2);
    return in;
}



apartament::apartament(char* s="Nedefinit",float f=0, float d=0,int nr=-2,int et=0):locuinta(s,f,d)
{
  this->numarApartament=nr;
  this->etaj=et;
}

class casa: public locuinta
{
    float suprafataUtilaCurte;
    int numarEtaje;
    float pretCurte;
    float* suprafataEtaj;
public:
    casa(char*,float,float,float,int);
    casa(const casa &ob)
    {
    strcpy(this->numeClient,ob.numeClient);
    this->suprafataUtila=ob.suprafataUtila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pret=ob.pret;
    this->suprafataUtilaCurte=ob.suprafataUtilaCurte;
    this->numarEtaje=ob.numarEtaje;
    this->pretCurte=ob.pretCurte;
     this->suprafataEtaj=ob.suprafataEtaj;
    };
    ~casa(){
    suprafataUtilaCurte=0;
    numarEtaje=0;
    delete(suprafataEtaj);}
    void afisare ()const
    {
       int i;
       cout<<endl;
       cout<<"Nume client: "<<numeClient<<endl;
       cout<<"Suprafata utila: "<<suprafataUtila<<" metri patrati"<<endl;
       cout<<"Discount: "<<discount<<" %"<<endl;
       cout<<"Suprafata utila a curtii: "<<suprafataUtilaCurte<<" metri patrati"<<endl;
       cout<<"Numar de etaje: ";
       if(numarEtaje==0) cout<<"Nu are etaje"<<endl;
       else cout<<numarEtaje<<endl;
       for(i=0;i<=numarEtaje;i++)
       {
           if(i==0) cout<<"Suprafata utila parter: "<<suprafataEtaj[i]<<endl;
           else cout<<"Suprafata utila pentru etajul "<<i<<": "<<suprafataEtaj[i]<<endl;
       }
       cout<<"Chirie: "<<chirie<<" $"<<endl;
    }
    friend istream& operator>>(istream&,casa&);
    friend ostream& operator<<(ostream&,casa&);
    casa operator=(const casa &ob)
    {
        strcpy(this->numeClient,ob.numeClient);
    this->suprafataUtila=ob.suprafataUtila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pret=ob.pret;
    this->suprafataUtilaCurte=ob.suprafataUtilaCurte;
    this->numarEtaje=ob.numarEtaje;
    this->pretCurte=ob.pretCurte;
    this->suprafataEtaj=ob.suprafataEtaj;
    }
    friend void calculChirie(casa&);
};

istream& operator>>(istream &in,casa &ob)
{

    in>>dynamic_cast<locuinta &>(ob);
    cout<<endl<<"Suprafata utila a curtii: ";
    char s[30];
    int ok=0;
    do
{
    try{
    in>>s;
    ob.suprafataUtilaCurte=atoi(s);

       if(ob.suprafataUtilaCurte<=0){
           throw(2);
       }
       ok=0;
   }

   catch(int n)
   {
       cout<<"NUMARUL trebuie sa fie  MAI MARE CA 0!"<<endl;
       ok=1;
   }


}while(ok);
    cout<<endl<<"Pret pe metru patrat de curte: ";
    in>>ob.pretCurte;
    cout<<endl<<"Numar de etaje: ";
    in>>ob.numarEtaje;
    int i;
    for(i=0;i<=ob.numarEtaje;i++)
    {
        if(i==0) cout<<endl<<"Suprafata utila parter: ";
        else
             cout<<endl<<"Suprafata utila pentru etajul "<<i<<": ";
        in>>ob.suprafataEtaj[i];
    }
    return in;
}

casa::casa(char* s="Nedefinit",float f=0, float d=0,float curte=0,int nr=0):locuinta(s,f,d)
{
    this->suprafataUtilaCurte=curte;
    this->numarEtaje=nr;
    this->suprafataEtaj=new float[numarEtaje];
    this->pretCurte=0;
    int i;
    for(i=0;i<=numarEtaje;i++)
    {
        suprafataEtaj[i]=0;
    }
}
bool operator<(const locuinta &ob,const locuinta &ob2)
    {
        return ob.getSuprafata()>ob2.getSuprafata();
    }
template<class tip> void calculChirie(tip& X)  ///FUNCTIE TEMPLATE PENTRU CALCUL CHIRIE
{
    float total=X.pret*X.suprafataUtila;
    total=total-(X.discount*(total/100));
    X.chirie=total;
}

template <class tip> int identificare(tip& X)
{
     if(typeid(X)==typeid(apartament))
        {
            cout<<"\n Locuinta este de tip apartament! \n";
                return 1;
        }
     if(typeid(X)==typeid(casa))
        {
            cout<<"\n Locuinta este de tip casa! \n";
                return 2;
        }
     if(typeid(X)==typeid(locuinta))
        {
                cout<<"\n Locuinta nu are un tip specific!!\n ";
                return 3;
        }
}


void calculChirie(casa& X)
{
    float total=X.pret*X.suprafataUtila;
    total=total-(X.discount*(total/100))+X.pretCurte*X.suprafataUtilaCurte;
    X.chirie=total;
}




void afisareCase(set<pair<int,casa> > v)
{
    set<pair<int,casa> >::iterator i;
    for (i=v.begin(); i != v.end(); ++i)
    {
        cout<< i->first<<" ";
        i->second.afisare();
        cout<<"\n";
    }
}

void afisareApartamente(set<pair<int,apartament> > v)
{
    set<pair<int,apartament> >::iterator i;
    for (i=v.begin(); i != v.end(); i++)
    {
        cout<< i->first<<" ";
        i->second.afisare();
        cout<<"\n";
    }
}

template <class tip> class Gestiune
{
   vector <tip> vect;
   int nr=0;
   int nrCase=0;
   casa Casele[20];
   float totalCase=0;
public:
    template<typename X>
    void adaugare(X& ob)
    {
        vect.insert(&ob);
        nr++;
    }
    void afisare()
    {
        typename vector <tip>::iterator i;
        for(i=vect.begin();i!=vect.end();i++)
        {
            afisare(i);
        }

    }
    void calculCastig(casa &ob)
    {
        Casele[nrCase]=ob;
        nrCase++;
        totalCase=totalCase+ob.getChirie();
    }
    void adaugareCasa(casa& ob)
    {
        vect.insert(&ob);
        calculCastig(&ob);
        nr++;
    }


};

int main()
{

    int alegere;
    int nrCase=0;
    int nrApartamente=0;
    casa *c;
    apartament *a;
    set<pair<int,casa> > casele;
    set<pair<int,apartament> > apartamentele;


    do{
    cout<<"\n Alege o optiune din cele de mai jos.";
    cout<<"\n 1- Adauga o locuinta \n 2- Afisare locuinte \n 3- Verificare case/apartamente \n"; ///Functia verificare case/apartamente parcurge cele doua seturi, verifica daca sunt respectate
    cin>>alegere;                                                                             ///datele (daca este vreun element ce nu corespunde) si returneaza un mesaj corespunzator
    int alegere2;
    switch(alegere)
    {
    case 1:
        {
            cout<<"\n Ce doresti sa adaugi? \n 1- Apartament \n 2-Casa \n" ;
            cin>>alegere2;
            switch(alegere2)
            {
                case 1:
                    {
                        cout<<"\n Ai ales apartament! \n";

                                a = new apartament;
                                cin>>*a;
                                calculChirie(*a);
                                pair<int,apartament> p1 = make_pair(nrApartamente,*a);
                                apartamentele.insert(p1);

                        nrApartamente++;
                        system("cls");
                        cout<<"Apartament adaugat cu succes!";
                        Sleep(5000);
                        system("cls");
                        break;
                    }
                case 2:
                    {
                        cout<<"\n Ai ales casa \n";

                                c = new casa;
                                cin>>*c;
                                calculChirie(*c);
                                pair<int,casa> p1 = make_pair(nrCase,*c);
                                casele.insert(p1);

                        nrCase++;
                        system("cls");
                        cout<<"Casa adaugata cu succes!";
                        Sleep(5000);
                        system("cls");
                        break;
                    }
                default:
                    {
                        cout<<"\n Optiune nedefinita. Alegeti o optiune valida. \n ";
                        Sleep(5000);
                        system("cls");
                        break;
                    }
            }
            break;
        }
    case 2:
        {
            cout<<"\n Lista apartamentelor: \n";
            afisareApartamente(apartamentele);
            cout<<"\n \n Lista caselor: \n";
            afisareCase(casele);
            Sleep(5000);
            system("cls");
            break;
        }
    case 3:
        {

            int okcase=1;
            int okapartamente=1;
            set<pair<int,apartament> >::iterator i;
            for (i=apartamentele.begin(); i != apartamentele.end(); i++)
                {
                    if(identificare(i->second)==2 || identificare(i->second)==3) okapartamente=0;
                }
            set<pair<int,casa> >::iterator j;
            for (j=casele.begin();j!=casele.end();j++)
                {
                    if(identificare(j->second)==1 || identificare(j->second)==3) okcase=0;
                }
            if(okcase==1 && okapartamente==1) cout<<"\n Seturi verificate, nicio eroare \n";
            else if(okcase==1 && okapartamente==0) cout<<"\n Exista o problema la setul de apartamente \n";
            else if(okcase==0 && okapartamente==1) cout<<"\n Exista o problema la setul de case \n";
            else cout<<"\n Exista o problema la ambele seturi";
            Sleep(5000);
            system("cls");
        }

    }




    /*casa a;
    cin>>a;
    calculChirie(a);
    a.afisare();*/
    }while(alegere>0&&alegere<4);
    return 0;
}
