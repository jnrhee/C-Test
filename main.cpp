#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int power (int x, int y) {
    int ret = 1;
   for (int i=0;i<y;i++) {
       ret *= x;
   }
    return ret;
}

int isIsomorphic(char * s1, char * s2, int size) {
   char * out = new char[size];
    int mapSize = power(2, sizeof(char)*8);
    char map[mapSize];
    memset(map, 0, mapSize);
    memset(out, 0, size);

    int i;
    for (i=0;i<mapSize;i++) {
        if (map[i] != 0)
        cout<<i<<" map "<<hex<<map[i]<<endl;
    }

    for (i=0;i<size;i++) {
        char c = s1[i];
        if (map[c] == 0) {
            map[c] = s2[i];
        }
        cout<<"map "<<hex<<c<<" = "<<map[c]<<endl;
        out[i] = map[c];
    }

    cout<<"out = "<<out;
    for (int i=0;i<size;i++) {
        if (out[i] != s2[i])
            return false;
    }

    return true;
}

int getMin(int x, int y) {
    int c = -(x-y < 0);
    
    /*
    cout<<"c = "<<hex<<c<<endl;
    cout<<"~c = "<<hex<<~c<<endl;
    
    cout<<"x&c = "<<hex<<(x&c)<<endl;
    cout<<"y&~c = "<<hex<<(y&~c)<<endl;
    */
    
    int ret = (x&c) + (y&~c);

    return ret;
}


int getMax(int x, int y) {
    int c = -(x-y > 0);       
    int ret = (x&c) + (y&~c);

    return ret;
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

    char s1[] = "iFooeo";
    char s2[] = "aGeeef";
    int ret = isIsomorphic(s1, s2, sizeof(s1));
    cout<<" isIsomorphic returns "<<ret<<endl;

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

    n1 = 0x80000000;
    cout<<hex<<"0x"<<n1<<" shift by 1 to right = ";
    n1 = n1>>1;
    cout<<hex<<"0x"<<n1<<endl;

    int rst;
    while (1) {
        cout<<"Enter number 1"<<endl;
        cin>>n1;
        cout<<"Enter number 2"<<endl;
        cin>>n2;

        //cout<<hex<<n1<<" + "<<hex<<n2<<" = "<<add(n1, n2)<<endl;
        //rst = sub(n1, n2);
        //cout<<"0x"<<hex<<n1<<" - "<<"0x"<<hex<<n2<<" = "<<dec<<rst<<" = 0x"<<hex<<rst<<endl;

        cout<<"min = "<<dec<<getMin(n1, n2)<<endl;
        cout<<"max = "<<dec<<getMax(n1, n2)<<endl;
    }
    return 0;
}
