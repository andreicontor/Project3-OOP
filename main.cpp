#include<iostream>
#include<set>
#include<fstream>
#include<vector>
#include<typeinfo>
using namespace std;

template<class T>
class Gestiune;
template<class T>
istream& operator>>(istream& in, Gestiune<T> & ob);
template<class T>
ostream& operator<<(ostream& in, const Gestiune<T> & ob);


class Locuinta
{
    protected:
        string nume_client;
        float suprafata;
        float discount;
        float pret_m2;
        float chirie;
    public:
        Locuinta() //constructor fara parametrii
        {
            nume_client = "Necunoscut";
            suprafata = 0;
            discount = 0;
            pret_m2 = 0;
            chirie = 0;
        }
        Locuinta(string nume, float a, float b, float c) //constructor cu parametrii
        {
            nume_client = nume;
            suprafata = a;
            discount = b;
            chirie = 0;
            pret_m2 = c;
        }
        Locuinta(const Locuinta &l) //constructor de copiere
        {
            nume_client = l.nume_client;
            suprafata = l.suprafata;
            discount = l.discount;
            chirie = l.chirie;
            pret_m2 = l.pret_m2;
        }
        ~Locuinta(){} //desctructor

        Locuinta operator=(const Locuinta &l) //operator de atribuire
        {
            nume_client = l.nume_client;
            suprafata = l.suprafata;
            discount = l.discount;
            chirie = l.chirie;
            pret_m2 = l.pret_m2;
            return *this;
        }

        virtual istream& citire(istream &in)
        {
            cout<<"INTRODUCETI NUMELE CLIENTULUI: ";
            in>>nume_client;
            suprafata_try:
            try
            {
                cout<<"INTRODUCETI SUPRAFATA IMOBILULUI: ";
                in>>suprafata;
                if(suprafata<=0)
                    throw suprafata;
            }
            catch(float ex1)
            {
                cout<<"SUPRAFATA TREBUIE SA FIE UN NUMAR POZITIV. REINTRODUCETI: "<<'/n';
                goto suprafata_try;
            }

            discount_try:
            try
            {
                cout<<"INTRODUCETI DISCOUNT-UL: ";
                in>>discount;
                if(discount<0||discount>10)
                    throw discount;
            }
            catch(float ex2)
            {
                cout<<"DISCOUNT-UL TREBUIE SA FIE UN NUMAR CUPRINS INTRE 0 SI 10. REINTRODUCETI: "<<'\n';
                goto discount_try;
            }
            pret_try:
            try
            {
                cout<<"INTRODUCETI PRETUL PE METRU PATRAT: ";
                in>>pret_m2;
                if(pret_m2<0)
                    throw pret_m2;
            }
            catch(float ex3)
            {
                cout<<"PRETUL TREBUIE SA FIE UN NUMAR POZITIV. REINTRODUCETI: ";
                goto pret_try;
            }
            cout<<'\n';
            return in;

        }

        friend istream& operator>>(istream &in,Locuinta &l)
        {
            return l.citire(in);
        }

        virtual ostream& afisare(ostream &out)
        {
            out<<"Numele clientului este: "<<nume_client<<'\n';
            out<<"Suprafata imobilului este de: "<<suprafata<<" metri patrati\n";
            out<<"Discount-ul este de: "<<discount<<" %\n";
            out<<"Pretul pe metru patrat este de: "<<pret_m2<<" euro\n";
            out<<"Chiria lunara este de: "<<chirie<<" euro\n";
            return out;
        }

        friend ostream& operator<<(ostream &out,Locuinta &l)
        {
            return l.afisare(out);
        }

        template<class T>
        friend class Gestiune;
        template<class T>
        friend istream& operator>>(istream& in, Gestiune<T> & ob);
        template<class T>
        friend ostream& operator<<(ostream& in, const Gestiune<T> & ob);

};

class Apartament:public Locuinta
{
    protected:
        int etaj;
    public:
        Apartament():Locuinta(),etaj(0){} //constructor fara parametrii
        Apartament(string nume, float a,float b,float c,int e):Locuinta(nume,a,b,c),etaj(e){} //constructor cu parametrii
        Apartament(const Apartament &a) //constructor de copiere
        {
            nume_client = a.nume_client;
            suprafata = a.suprafata;
            discount = a.discount;
            pret_m2 = a.pret_m2;
            chirie = a.chirie;
            etaj = a.etaj;
        }
        ~Apartament(){} //destructor
        void calc_chirie()
        {
            chirie = (pret_m2 * suprafata)*(100-discount)/100;
        }
        Apartament operator=(const Apartament &a)
        {
            nume_client = a.nume_client;
            suprafata = a.suprafata;
            discount = a.discount;
            pret_m2 = a.pret_m2;
            chirie = a.chirie;
            etaj = a.etaj;
            return *this;
        }

        virtual istream& citire(istream &in)
        {
            Locuinta::citire(in);
            etaj_try:
            try
            {
                cout<<"INTRODUCETI ETAJUL: ";
                in>>etaj;
                if(etaj<0)
                    throw etaj;
            }
            catch(int ex5)
            {
                cout<<"ETAJUL TREBUIE SA FIE UN NUMAR POZITIV! REINTRODUCETI: "<<'\n';
                goto etaj_try;
            }
            calc_chirie();
            cout<<'\n';
            return in;
        }
        friend istream &operator>>(istream &in, Apartament &a)
        {
            return a.citire(in);
        }

        virtual ostream& afisare(ostream &out)
        {
            Locuinta::afisare(out);
            cout<<"Apartamentul se afla la etajul "<<etaj<<'\n';
            return out;
        }
        friend ostream &operator<<(ostream &out,Apartament &a)
        {
            return a.afisare(out);
        }

};

class Casa:public Locuinta
{
    protected:
        float curte;
        float pret_curte;
        int nr_etaje;
        float *e;
    public:
        Casa():Locuinta()  //constructor fara parametrii
        {
            curte = 0;
            pret_curte = 0;
            nr_etaje = 0;
            e = NULL;
            calc_chirie();
        }
        Casa(string nume,float a,float b,float c,float d,float e,int f):Locuinta(nume,a,b,c) //constructor cu parametrii
        {
            curte = d;
            pret_curte = e;
            nr_etaje = f;
            cout<<"INTRODUCETI SUPRAFATA FIECARUI ETAJ: \n";
            this->e = new float[this->nr_etaje];
            for(int i=0;i<nr_etaje;i++)
                cin>>this->e[i];
            calc_chirie();
        }
        Casa(const Casa &c) //constructor de copiere
        {
            nume_client = c.nume_client;
            suprafata = c.suprafata;
            discount = c.discount;
            pret_m2 = c.pret_m2;
            chirie = c.chirie;
            curte = c.curte;
            nr_etaje = c.nr_etaje;
            pret_curte = c.pret_curte;
            delete [] e;
            e = new float[nr_etaje];
            for(int i=0;i<nr_etaje;i++)
                e[i] = c.e[i];
        }

        Casa operator=(const Casa &c)
        {
            nume_client = c.nume_client;
            suprafata = c.suprafata;
            discount = c.discount;
            pret_m2 = c.pret_m2;
            chirie = c.chirie;
            curte = c.curte;
            nr_etaje = c.nr_etaje;
            pret_curte = c.pret_curte;
            delete [] e;
            e = new float[nr_etaje];
            for(int i=0;i<nr_etaje;i++)
                e[i] = c.e[i];
            return *this;
        }

        void calc_chirie()
        {
            chirie = (pret_m2 * suprafata + pret_curte*curte)*(100-discount)/100;
        }
        virtual istream& citire(istream &in)
        {
            Locuinta::citire(in);
            curte_try:
            try
            {
                cout<<"INTRODUCETI SUPRAFATA PE CARE O ARE CURTEA: ";
                in>>curte;
                if(curte<0)
                    throw curte;
            }
            catch(float ex6)
            {
                cout<<"SUPRAFATA TREBUIE SA FIE UN NUMAR POZITIV! REINTRODUCETI: \n";
                goto curte_try;
            }
            pretcurte_try:
            try
            {
                cout<<"INTRODUCETI PRETUL PE METRU PATRAT AL CURTII: ";
                in>>pret_curte;
                if(pret_curte<0)
                    throw pret_curte;
            }
            catch(float ex7)
            {
                cout<<"PRETUL TREBUIE SA FIE UN NUMAR POZITIV! REINTRODUCETI: \n";
                goto pretcurte_try;
            }
            numaretaje_try:
            try
            {
                cout<<"INTRODUCETI NUMARUL DE ETAJE: ";
                in>>nr_etaje;
                if(nr_etaje<0)
                    throw nr_etaje;
            }
            catch(int ex8)
            {
                cout<<"NUMARUL DE ETAJE TREBUIE SA FIE POZITIV! REINTRODUCETI: \n";
                goto numaretaje_try;
            }
            float suma=0;
            suprafataetaje_try:
            try
            {
                suma = 0;
                cout<<"INTRODUCETI SUPRAFATA PE FIECARE ETAJ: \n";
                e = new float[nr_etaje];
                for(int i=0;i<nr_etaje;i++)
                {
                    in>>e[i];
                    if(e[i]<0)
                        throw 1;
                    suma = suma + e[i];
                }
                if(suma!=suprafata)
                    throw suma;
            }
            catch (int ex9)
            {
                cout<<"SUMA SUPRAFETELOR NU CORESPUNDE CU SUPRAFATA TOTALA! REINTRODUCETI: \n";
                goto suprafataetaje_try;
            }
            catch(float ex10)
            {
                cout<<"SUPRAFATA PE FIECARE ETAJ TREBUIE SA FIE POZITIVA! REINTRODUCETI: \n";
                goto suprafataetaje_try;
            }
            calc_chirie();
            cout<<'\n';
            return in;
        }
        friend istream& operator>>(istream &in,Casa &c)
        {
            return c.citire(in);
        }

        virtual ostream& afisare(ostream &out)
        {
            Locuinta::afisare(out);
            out<<"Curtea are o suprafata de "<<curte<<" metri patrati\n";
            out<<"Pretul pe metru patrat al curtii este de "<<pret_curte<<" euro\n";
            out<<"Casa are "<<nr_etaje<<" etaje\n";
            for (int i=0;i<nr_etaje;i++)
                out<<"Suprafata pe etajul "<<i<<" este de "<<e[i]<<" metri patrati\n";
            return out;
        }
        friend ostream& operator<<(ostream &out, Casa &c)
        {
            return c.afisare(out);
        }


};


template<class T>
istream& operator>>(istream&, Gestiune<T> &);

template<class T>
ostream& operator<<(ostream&, const Gestiune<T>&);

template<class T>
class Gestiune
{
    set< pair<Locuinta*,char> > loc;
    vector<Locuinta*> p;
    vector<T> tip;
    vector<float> ch;
public:
    Gestiune()
    {
        p.resize(0);
        tip.resize(0);
        ch.resize(0);
        loc.empty();
    }

    Gestiune(int nr)
    {
        cout<<"UN OBIECT CU "<<nr<<" LOCUINTE SE CREAZA!"<<'\n';
        char optiune;
        for(int i=0;i<nr;i++)
        {
            cout<<"INTRODUCETI TIPUL LOCUINTEI "<<i+1<<'\n';
            cin>>optiune;
            if(optiune=='A')
            {
                p.push_back(new Apartament);
                cin>>*(dynamic_cast<Apartament*>(p[i]));
                loc.insert(make_pair(&*p[i],'A'));
            }
            else
            {
                p.push_back(new Casa);
                cin>>*(dynamic_cast<Casa*>(p[i]));
                loc.insert(make_pair(&*p[i],'C'));
            }
        }

        T a;
        for(unsigned i=0;i<p.size();i++)
            if(typeid(*p[i]).name() == typeid(a).name())
            {
                tip.push_back(*(dynamic_cast<T*>(p[i])));
                ch.push_back((tip.end()-1)->chirie);
            }
    }

    Gestiune(const Gestiune<T>& ob)
    {
        p.assign(ob.p.begin(),ob.p.end());
        tip.assign(ob.tip.begin(),ob.tip.end());
        ch.assign(ob.chirie.begin(),ob.ch.end());
    }
    Gestiune operator=(const Gestiune<T>& ob)
    {
        p.assign(ob.p.begin(),ob.p.end());
        tip.assign(ob.tip.begin(),ob.tip.end());
        ch.assign(ob.chirie.begin(),ob.ch.end());
        return *this;
    }

    Locuinta* operator+=(Locuinta* ob)
    {
        Apartament a;
        Casa b;
        if(typeid(*ob).name() == typeid(a).name()) //Apartament
        {
            p.push_back(new Apartament);
            *(dynamic_cast<Apartament*>(*(p.end()-1)))=*(dynamic_cast<Apartament*>(ob));
        }
        else //Casa
        {
            p.push_back(new Casa);
            *(dynamic_cast<Casa*>(*(p.end()-1)))=*(dynamic_cast<Casa*>(ob));
        }
        T t;
        if(typeid(*ob).name() == typeid(t).name())
        {
            tip.push_back(*(dynamic_cast<T*>(ob)));
            ch.push_back((tip.end()-1)->chirie);
        }
        return ob;
    }
    friend istream& operator>><T>(istream&, Gestiune<T> &);
    friend ostream& operator<<<T>(ostream&, const Gestiune<T>&);
};

template<class T>
istream& operator>>(istream& in, Gestiune<T> & ob)
{
    cout<<"Introduceti numarul de locuinte: ";
    int nr;
    in>>nr;
    cout<<endl<<"Un obiect Gestiune cu "<<nr<<" locuinte se creeaza."<<endl;
    char opt;
    for(int i=0;i<nr;i++)
    {
        cout<<"Introduceti tipul locuintei "<<i+1<<" :";
        in>>opt;
        if(opt=='A')
        {
            ob.p.push_back(new Apartament);
            in>>*(dynamic_cast<Apartament*>(ob.p[i]));

        }
        else
        {
                ob.p.push_back(new Casa);
                in>>*(dynamic_cast<Casa*>(ob.p[i]));
        }
    }
    T a;
    for(unsigned i=0;i<ob.p.size();i++)
        if(typeid(*(ob.p[i])).name() == typeid(a).name())
    {
        ob.tip.push_back(*(dynamic_cast<T*>(ob.p[i])));
        ob.ch.push_back(ob.tip.end()->chirie);
    }
    return in;
}

template<class T>
ostream& operator<<(ostream& out, const Gestiune<T>& ob)
{
    out<<"Se afiseaza locuintele aflate in gestiune:"<<"\n\n";
    Apartament a;
    Casa b;
    for(unsigned i=0;i<ob.p.size();i++)
    {
        if(typeid(*(ob.p[i])).name() == typeid(a).name())
            out<<*(dynamic_cast<Apartament*>(ob.p[i]));
        else
            out<<*(dynamic_cast<Casa*>(ob.p[i]));

    }

    return out;
}

template<>
class Gestiune<Casa>
{
    int nr_case;
    vector<float>chirii;
    float suma;

    Gestiune()
    {
        nr_case=0;
        chirii.resize(0);
        suma=0;
    }
    Gestiune(int a,vector<float> b,float c)
    {
        nr_case=a;
        for(int i=0;i<b.size();i++)
            chirii[i] = b[i];
        suma = c;
    }
    Gestiune(const Gestiune &g)
    {
        nr_case = g.nr_case;
        for(int i=0;i<g.chirii.size();i++)
            chirii[i] = g.chirii[i];
        suma = g.suma;
    }
    ~Gestiune()
    {
        nr_case = 0;
        chirii.empty();
        suma = 0;
    }
    Gestiune operator=(Gestiune &g)
    {
        nr_case = g.nr_case;
        for(int i=0;i<g.chirii.size();i++)
            chirii[i] = g.chirii[i];
        suma = g.suma;
        return *this;
    }
    friend ostream& operator<<(ostream &out,Gestiune<Casa> &g)
    {
        out<<"Numarul de case din gestiune este: "<<g.nr_case<<'\n';
        for(int i=0;i<g.chirii.size();i++)
        {
            out<<"Casa "<<i+1<<" are chiria "<<g.chirii[i]<<" euro\n";
            g.suma = g.suma + g.chirii[i];
        }
        out<<"Agentia a obtinut suma de "<<g.suma<<" euro";
        return out;
    }
    /*friend Gestiune& operator+=(Gestiune &g, Casa &c)
    {

    }*/


};
int main()
{
    int i,n;
    Locuinta *l;
    set<pair <Locuinta*,char> > locuinte;
    char tip;
    cout<<"INTRODUCETI NUMARUL DE LOCUINTE PE CARE TREBUIE SA LE GESTIONAM: ";
    cin>>n;
    cout<<'\n';
    for(i=1;i<=n;i++)
    {
        cout<<"INTRODUCETI TIPUL LOCUINTEI "<<i<<" :";
        cin>>tip;
        if(tip=='A')
        {
            l = new Apartament;
            cin>>static_cast<Apartament&>(*(l));
            locuinte.insert(make_pair(&*l,tip));
        }
        else
        if(tip=='C')
        {
            l = new Casa;
            cin>>static_cast<Casa&>(*(l));
            locuinte.insert(make_pair(&*l,tip));
        }
        else
            cout<<"TIPUL INTRODUS ESTE INVALID!"<<'\n';
    }
    set<pair <Locuinta*,char> >::iterator ii;
    for(ii=locuinte.begin();ii!=locuinte.end();ii++)
        cout<<(*(*ii).first)<<'\n';
    /*
    Gestiune<Locuinta>g;
    cin>>g;
    cout<<g;*/


    return 0;
}
