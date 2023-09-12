#include <iostream>
#include <string>
using namespace std;

template <class R>
class nodo
{
public:
    R valor;
    nodo* sig;
    nodo(R v)
    {
        valor = v;
        sig = NULL;
    }
};

template <class R>
class pila
{
private:
    nodo<R>* head;
public:
    pila()
    {
        head = NULL;
    }

    void push(R v)
    {
        nodo<R>* temp = new nodo(v);
        if (head) temp->sig = head;
        head = temp;
    }

    R pop()
    {
        R v;
        nodo<R>* temp = head;

        if (head)
        {
            v = temp->valor;
            head = temp->sig;
        }
        
        delete temp;
        return v;
    }

    R get_cabeza() {return head->valor;}
};

void post_fija(string& cadena)
{
    pila<string> EXP = pila<string>();
    string aux = "";
    string o1, o2;
    
    int i = 0;
    while (i < cadena.size())
    {
        while (cadena[i] == ' ') i++;

        while (cadena[i] != ' ' && cadena[i] != '\0')
        {
            aux += cadena[i];
            i++;
        }

        int v;

        if (aux == "+" || aux == "-" || aux == "*" || aux == "/")
        {
            o2 = EXP.pop();
            o1 = EXP.pop();

            if (o1 == "" || o2 == "")
            {
                cout << "EXPRESION INVALIDA!\n";
                break;
            }

            if (aux == "+") v = stoi(o2) + stoi(o1);
            if (aux == "-") v = stoi(o2) - stoi(o1);
            if (aux == "*") v = stoi(o2) * stoi(o1);
            if (aux == "/") v = stoi(o2) / stoi(o1);
            aux = to_string(v);
        }

        EXP.push(aux);
        aux = "";
    }

    cout << "RESULTADO: " << EXP.get_cabeza();
}

int main()
{
    string cadena;
    cout << "INGRESE SU CADENA: ";
    getline(cin,cadena);
    post_fija(cadena);
}