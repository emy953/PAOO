#include <iostream>

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
    Product():name(""),id(0){};

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
    Factory(string name,string founders,string address,int nr, Product* products):name(name),founders(founders),address(address),nr(nr),products(products){};
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

int main()
{
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
        cout<<f;
    //Factory f1(f);
    //Factory f2("a","b",0,nullptr);
    //f2=f;
    return 0;
}
