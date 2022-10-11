#include<iostream>
#include<string>
#include<algorithm>
#define MAX 20
using namespace std;


void push(char);
char pop();
string in2postfix(string);
int priority ( char );
char stk[20];
int top=-1;
bool isFull();
bool isEmpty();
void in2prefix(string);

int main()
{
    int cont;
    string infix, postfix, prefix;
    cout<<"masukkan infix : ";
    cin>>infix;
    in2prefix(infix);

    return 0;
}

bool isFull(){
    if(top == MAX - 1){
        return true;
    }
    else{
        return false;
    }
}

bool isEmpty(){
    if(top == -1){
        return true;
    }
    else{
        return false;
    }
}

// prosedur memasukkan operator ke stack
void push(char oper)
{
    if(isFull())
    {
        cout<<"stack penuh";
    }

    else
    {
        top++;
        stk[top]=oper;
    }
}

// fungsi untuk menghapus data dari stack
char pop()
{
    char ch;
    if(isEmpty())
    {
        cout<<"stack kosong!!!!";
    }
    else
    {
        ch=stk[top];
        top--;
        return(ch);
    }
    return 0;
}

string in2postfix(string infix)
{
    int i=0;
    string pst = "";

    // looping selama urutan terakhir string tidak kosong
    while(infix[i]!='\0')
    {
        // jika ketemu alfabet, maka masukkan ke variabel
        if(infix[i]>='a' && infix[i]<='z')
        {
            pst.insert(pst.end(),infix[i]);
            i++;
        }


        // jika ketemu kurung buka, push ke stack
        else if(infix[i]=='(' || infix[i]=='{'  || infix[i]=='[')
        {
            push(infix[i]);
            i++;
        }


        //jika ketemu kurung tutup, pop dari stack
        else if(infix[i]==')' || infix[i]=='}'  || infix[i]==']')
        {
            if(infix[i]==')')
            {
                while(stk[top]!='(')
                {
                    pst.insert(pst.end(),pop());
                }
                pop();
                i++;
            }

            if(infix[i]==']')
            {
                while(stk[top]!='[')
                {
                    pst.insert(pst.end(),pop());
                }
                pop();
                i++;
            }

            if(infix[i]=='}')
            {
                while(stk[top]!='{')
                {
                    pst.insert(pst.end(),pop());
                }
                pop();
                i++;
            }
        }

        //kalo ga ada kurung tutup, berarti cuma ada operator aja, lakukan blok berikut
        else
        {

            // jika stack kosong, push ke stack
            if(isEmpty())
            {
                push(infix[i]);
                i++;
            }

            // jika prioritas operator kurang dari atau sama dengan operator yang ada di top of stack
            // pop operator yang di stack, kemudian masukkan ke pst
            else if( priority(infix[i]) <= priority(stk[top])) {
                pst.insert(pst.end(),pop());

                // jika prioritas operator sama dengan operator di stack, pop
                while(priority(stk[top]) == priority(infix[i])){
                    pst.insert(pst.end(),pop());
                    if(top < 0) {
                        break;
                    }
                }
                push(infix[i]);
                i++;
            }

            // jika prioritas operator lebih tinggi, push operator ke stack
            else if(priority(infix[i]) > priority(stk[top])) {
                push(infix[i]);
                i++;
            }
        }
    }

    // pada akhirnya, remove semua operator dari stack
    while(top!=-1)
    {
        pst.insert(pst.end(),pop());
    }

    //cout<<"Hasil konversi ke postfix : "<<pst;
    return pst;
}

void in2prefix(string infix)
{
    int l = infix.size();

    // Reverse infix
    reverse(infix.begin(), infix.end());
    cout << "1 " << infix << endl;

    // Replace ( with ) and vice versa
    for (int i = 0; i < l; i++) {

        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    string prefix = in2postfix(infix);

    cout << "2 " << prefix << endl;
    // Reverse postfix
    reverse(prefix.begin(),prefix.end());

    cout << "3 " << prefix;
}



// fungsi untuk mencari prioritas operator
int priority ( char alpha )
{
    if(alpha == '+' || alpha =='-')
    {
        return 1;
    }

    if(alpha == '*' || alpha =='/')
    {
        return 2;
    }

    if(alpha == '$')
    {
        return 3;
    }

    return 0;
}
