#include <iostream>

using namespace std;

typedef struct node {
    int val;
    struct node * left;
    struct node * right;
} NODE;

void initNode(NODE *n) {
    n->val = 1;
    n->left = NULL;
    n->right = NULL;
}

int detectOF(int x1, int y1, int r1) {
    return ( ((~r1&0x1)&x1&y1) | (r1 & (~x1&0x1) & (~y1&0x1)));
}

int add (int x, int y) {
    int i;
    int c=0;
    int r;
    int b1, b2;
    int rest = 0;

    for (i=0;i<sizeof(x)*8;i++) {
        b1 = (x>>i)&0x1;
        b2 = (y>>i)&0x1;

        if (c == 0) {
            r = b1^b2;
            c = b1&b2;
        } else {
            r = (~(b1^b2))&0x1;
            c = (b1|b2);
        }

        rest |= r<<i;
    }

    int sh = sizeof(x)*8 - 1;
    if (detectOF(x>>sh, y>>sh, rest>>sh)) {
        cout<<"OVERFLOW detected!!!!"<<endl;
    }
    return rest;
}

int sub (int x, int y) {
    int i;
    int c=0;
    int r;
    int b1, b2;
    int rest = 0;

    for (i=0;i<sizeof(x)*8;i++) {
        b1 = (x>>i)&0x1;
        b2 = (y>>i)&0x1;

        if (c == 0) {
            r = b1^b2;
            c = (b2 > b1)?1:0;
        } else {
            r = (~(b1^b2))&0x1;
            c = ~(b1&(~b2&0x1))&0x1;
        }

        rest |= r<<i;
    }

    int sh = sizeof(x)*8 - 1;
    if (detectOF(x>>sh, ~(y>>sh)&0x1, rest>>sh)) {
        cout<<"OVERFLOW detected!!!!"<<endl;
    }
    return rest;

}

int main() {
    string name;

    /*
    cout << "What's your name" << name.length() << endl;

    getline(cin, name);

    cout << "your name is " << name << name.length()<<endl;

    for (int i=0;i<name.length();i++)
        cout<<name[i];

    NODE n[10];
    for (int i=0;i<sizeof(n)/sizeof(NODE);i++) {
        initNode(&n[i]);
        cout << i;
    }
     */

    int max = 0xFFFFFFFF&0x7FFFFFFF;
    cout<<hex<<max<<" = "<<dec<<max<<endl;

    max = 0x80000000;
    cout<<hex<<max<<" = "<<dec<<max<<endl;

    int n1, n2;

    n1 = 0x0fffffff;
    n2 = 0x0fffffff;
    cout<<hex<<n1<<" + "<<hex<<n2<<" = "<<add(n1, n2)<<endl;

    n1 = 0x7fffffff;
    n2 = 0x0fffffff;
    cout<<hex<<n1<<" + "<<hex<<n2<<" = "<<add(n1, n2)<<endl;

    int rst;
    while (1) {
        cout<<"Enter number 1"<<endl;
        cin>>n1;
        cout<<"Enter number 2"<<endl;
        cin>>n2;

        //cout<<hex<<n1<<" + "<<hex<<n2<<" = "<<add(n1, n2)<<endl;
        rst = sub(n1, n2);
        cout<<"0x"<<hex<<n1<<" - "<<"0x"<<hex<<n2<<" = "<<dec<<rst<<" = 0x"<<hex<<rst<<endl;
    }
    return 0;
}
