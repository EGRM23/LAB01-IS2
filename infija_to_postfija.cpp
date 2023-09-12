#include <iostream>
#include <string>
#define MAS '+'
#define MENOS '-'
#define NUM 255
#define FIN -1
using namespace std;

char lexema[80];
string cadena = "";
int tok;

void parea(int);
void error();
void Resto();
void Term();
int scanner();

void Exp()
{
    if (tok == NUM)
    {
        Term();
        Resto();
    }
    else error();
}

void Resto()
{
    if (tok == MAS)
    {
        parea(MAS);
        Term();
        printf("+ ");
        cadena += "+ ";
        Resto();
    }
    else if (tok == MENOS)
    {
        parea(MENOS);
        Term();
        printf("- ");
        cadena += "- ";
        Resto();
    }
    else {}
}

void Term()
{
    if (tok == NUM)
    {
        printf("%s ",lexema);
        int i = 0;
        while(lexema[i] != 0) cadena += lexema[i++];
        cadena += ' ';
        parea(NUM);
    }
    else error();
}

void error()
{
    printf("Error de sintaxis");
}

void parea(int t)
{
    if (tok == t)
        tok = scanner();
    else
        error();
}

int scanner()
{
    int c,i;

    do
        c = getchar();
    while (c == ' ');

    if (c == '\n') return FIN;
    if (c == MAS || c == MENOS) return c;

    if (isdigit(c))
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = getchar();
        }
        while (isdigit(c));

        lexema[i] = 0;
        ungetc(c,stdin);
        return NUM;
    }
    return FIN;
}

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

void post_fija()
{
    pila<string>  c  = pila<string>();
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
    cout << "INGRESE SU CADENA:\n";
    tok = scanner();
    cout << "EXPRESION POSTFIJA:\n";
    Exp();
    cout << cadena;
    post_fija();
}