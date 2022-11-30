#include <iostream>
#include <memory>

using namespace std;

class Components{
public:
    int nr;
    string componente;
    Components(int nr, string componente):nr(nr),componente(componente){};
    Components& operator=(const Components& rhs)
    {
        if (this == &rhs) return *this;
        nr=rhs.nr;
        componente=rhs.componente;
        return *this;
    }
};

class Product{

private:
    string name;
    int id;
    Components *components;

public:
    Product(string name, int id,Components *components):name(name),id(id),components(components){};
    Product():name(""),id(0),components(new Components(0,"")){};

    Product& operator=(const Product& rhs)
    {
        Components *pOrig = components; // remember original pb
        components = new Components(*rhs.components); // point pb to a copy of rhs’s bitmap
        delete pOrig;
        name=rhs.name;
        id=rhs.id;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const Product& p);
};

class Factory{

private:
    string name;
    string founders;
    string address;
    int nr;
    Product *products;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

public:
    bool closed;
    Factory(string name,string founders,string address,int nr, Product* products):name(name),founders(founders),address(address),closed(0),nr(nr),products(products){};
    Factory():name("nume"),founders("founders"),address("address"),nr(0),closed(0),products(nullptr){};
    friend ostream& operator<<(ostream& os, const Factory& f);
};

ostream& operator<<(ostream& os, const Product& p)
    {
        os<<p.name<<", "<<p.id<<": "<<p.components->nr<<" "<<p.components->componente;
        return os;
    }

ostream& operator<<(ostream& os, const Factory& f)
    {
        os<<f.founders<<" "<<f.address<<" "<<f.nr<<endl;
        for(int i=0;i<f.nr;i++)
            os<<f.products[i]<<endl;
            return os;
    }

Factory* createDefaultFactory() //Functie care creeaza nou obiect alocat dinamic
{
    return (new Factory());
}

void closeFactory(Factory* f) //inchide o fabrica
{
    f->closed=1;
}

void openFactory(Factory* f) //deschide o facbrica
{
    f->closed=0;
}

class Close{  //Clasa RAII pentru inchiderea si deschiderea unei fabrici
public:
    explicit Close(Factory *f):fP(f)
    {
        closeFactory(fP);
    }
    ~Close()
    {
        openFactory(fP);
    }
private:
    Factory *fP;
    Close(const Close&) = delete;
    Close& operator=(const Close&) = delete;
};

int main()
{
    /*
    int nr,id;
    Components *c=new Components(3,"c1 c2 c3");

    string founder,namef,name,address;
    Product products[100];
        cin>>namef>>founder>>address>>nr;
        for(int i=0;i<nr;i++)
        {
            cin>>name>>id;
            Product p(name,id,c);
            products[i]=p;
        }
        Factory f(namef,founder,address,nr,products);
        cout<<f;*/
    //Factory f1(f);
    //Factory f2("a","b",0,nullptr);
    //f2=f;


    //Item 13

    auto_ptr<Factory> p(createDefaultFactory());
    auto_ptr<Factory> p2(p);
    cout<<*p2;
    //cout<<*p; Nu functioneaz pentru ca p e null dupa copiere.
    shared_ptr<Factory> s(createDefaultFactory());
    shared_ptr<Factory> s2(s);
    cout<<*s2;
    cout<<*s; //s si s2 sunt pointeri catre acelasi spatiu de memorie

    //Item 14

    Factory *f=new Factory();
    cout<<f->closed<<endl; //open factory from constructor
    Close close(f);        //close the factory
    cout<<f->closed<<endl; //factory is closed
    delete &close;         //object is deletede, open factory
    cout<<f->closed<<endl; //factory is open
    Close c(f);
    cout<<f->closed<<endl; //factory is closed, will be open at the end of function main
   // Close c2(c);  Compilation error, Close class is uncopyable
    return 0;
}
