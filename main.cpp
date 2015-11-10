#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

using namespace std;

typedef struct node {
    int val;
    struct node * next;
} Node;

void initNode(Node *n, int v) {
    n->val = v;
    n->next = NULL;
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

void reverseString(char * s) {
    char * start = s;
    char * end = s;
    
    while (*s != '\0') {
        end = s++;
    }
    
    while (start != end) {
        char t = *start;
        *start = *end;
        *end = t;
        
        start++;
        end--;
    }
}

void NtoS(char * o, int n, int * idx) {
    if (n > 9)
        NtoS(o, n/10, idx);
   
    o[*idx] = (char)('0' + (char)(n%10));
    cout<<*idx<<"-> "<<o[*idx]<<endl;
    *idx = *idx + 1;    
}

char * numToString(int n) {
    int cnt = 0;
    int origN = n;
    
    /* assume positive number, for negative, put abs() and +/- char */
    while (n > 0) {
        n /= 10;
        cnt++;
    }
    n = origN;
    
    char * out = (char *)malloc(cnt+1);
    int idx = 0;
    NtoS(out, n, &idx);
    out[cnt] = '\0';
    
    return out;
}

char * compstr(char *s) {
    char * orig = s;
    int cnt = 0;
    
    while (*s++ != '\0')
        cnt++;
    s = orig;
    
    char * out = (char *)malloc(cnt+1);
    int outp = 0;
    for (int i=0;i<cnt;i++) {
        out[outp++] = s[i];
        
        int rep = 0;
        for (int j=i+1;j<cnt;j++) {
            if (s[i] == s[j])
                rep++;
            else
                break;
        }
        i += rep;
        if (rep > 0) {
            char * ns = numToString(rep+1);        
            while (*ns != '\0') {
                out[outp++] = *ns;
                ns++;
            }
        }
    }
    
    out[outp] = '\0';
    if ((outp-1)<cnt)
        return out;
    else
        return s;
}

void swap(int n[], int x, int y) {
    int t = n[x];
    n[x] = n[y];
    n[y] = t;
}

void sort(int n[], int size) {
    for (int i=0;i<size-1;i++) {
        int idx = 0;

        for (int j=1;j<size-i;j++) {
            if (n[j] < n[idx]) {
                swap(n, idx, j);
            }
            idx++;
        }
    }

    for (int i=0;i<size;i++) {
        cout<<n[i]<<" ";
    }

    cout<<endl;
}

void insert(int n[], int size, int v) {
    int idx = -1;
    for (int i=0;i<size;i++) {
        if (n[i] > v) {
            idx = i;
            break;
        }
    }

    if (idx == -1)
        return;

    for (int i=idx;i<size;i++) {
        int t = n[i];
        n[i] = v;
        v = t;
    }

    for (int i=0;i<size;i++) {
        cout<<n[i]<<" ";
    }
    cout<<endl;
}

void rotate(int n[], int size, int rot) {
    if (rot == 0)
        return;

    rot = rot%size;

    if (rot < 0)
        rot = size + rot;

    int idx_to = 0;
    int idx_from = (size - rot)%size;
    int val = n[idx_from];

    for (int i=0;i<size;i++) {
        int t = val;
        val = n[idx_to];
        n[idx_to] = t;
        idx_to = (idx_to+rot)%size;
    }

    for (int i=0;i<size;i++) {
        cout<<n[i]<<" ";
    }
    cout<<endl;
}

void swaps(char s[], int m, int n) {
    char t = s[m];
    s[m] = s[n];
    s[n] = t;
}
void permus(char s[], int size, int start) {
    if (start == (size -1)) {
        cout<<"permus: "<<s<<endl;
        return;
    }

    for (int i=start;i<size;i++) {
        swaps(s, start, i);
        permus(s, size, start+1);
        swaps(s, i, start);
    }
}

char word[1000];
int wordIdx;
int comboCnt;

void combo(char s[], int size, int start, int gnum) {
    if (gnum > size)
        return;

    for (int i=start;i<size; i++) {
       word[wordIdx++] = s[i];
        if (wordIdx == gnum) {
            comboCnt++;
            word[wordIdx+1] = '\0';
            cout<<"combo: "<<word<<endl;
        } else {
            combo(s, size, i+1, gnum);
        }
        wordIdx--;
    }
}

void comboPrint(char s[], int size, int start, int gnum) {
    comboCnt = 0;
    wordIdx = 0;
    combo(s, size, start, gnum);
    cout<<"combo total = "<<comboCnt<<endl;
}

/*
 * GCD (a, b, c) = GCD (a, GCD (b, c))
              = GCD (b, GCD (a, c))
              = GCD (c, GCD (a, b))
              = ...

To calculate the LCM, use...

                a * b
LCM (a, b) = ----------
             GCD (a, b)

The logic for that is based on prime factorization. The more general form (more than two variables) is...

                                          a                 b        
LCM (a, b, ...) = GCD (a, b, ...) * --------------- * --------------- * ...
                                    GCD (a, b, ...)   GCD (a, b, ...)
 */

int GCD(int x, int y) {
    return (y==0?x:GCD(y, x%y));
}

int LCM(int x, int y) {
    int ret = x*y;
    
    return ret/GCD(x, y);
}

int countFreq(int a[], int size) {
    /* 
     * a[i] must be > 0 
     */
    
    cout<<"Count Freq = "<<endl;
    for (int i=0;i<size;i++) {
        cout<<a[i]<<", ";
    }
    cout<<endl;

    int to;     
    for (int i=0;i<size;i++) {
        to = a[i];  
        if (a[i] > 0)
            a[i] = 0;
        
        while (to > 0) {
            int tmp = a[to-1];
            if (a[to-1] > 0)
                a[to-1] = -1;
            else
                a[to-1] += -1;
            to = tmp;
        }
    }
    
    cout<<"-----------------------"<<endl;
    for (int i=0;i<size;i++) {
        cout<<(i+1)<<" - "<<abs(a[i])<<endl;
    }
}

void printNode(Node *head) {
    cout<<"---- Node Printer -----"<<endl;
    while (head != NULL) {
        cout<<head->val<<" ";
        head = head->next;
    }
    
    cout<<endl;
}

void swapTwo(Node** headOrig, int x, int y) {
    Node * head;
    Node * nodeA = NULL;
    Node * nodeAParent = NULL;
    Node * nodeB = NULL;
    Node * nodeBParent = NULL;
    
    head = *headOrig;
    nodeAParent = (Node *)headOrig;
    while (head != NULL) {
        if (head->val == x) {
            nodeA = head;
            break;
        } else {
            nodeAParent = head;
            head = head->next;
        }
    }
    
    if (nodeA == NULL)
        return;

    head = *headOrig;
    nodeBParent = (Node *)headOrig;
    while (head != NULL) {
        if (head->val == y) {
            nodeB = head;
            break;
        } else {
            nodeBParent = head;
            head = head->next;
        }
    }
    
    if (nodeB == NULL)
        return;
    
    Node * tmp;
    if ((nodeB->next == nodeA) || (nodeA->next == nodeB)) {
        if (nodeAParent == (Node *)headOrig) {
            *headOrig = nodeB;
            tmp = nodeB->next;
            nodeB->next = nodeA;
            nodeA->next = tmp;            
        } else if (nodeBParent == (Node *)headOrig) {
            *headOrig = nodeA;
            tmp = nodeA->next;
            nodeA->next = nodeB;
            nodeB->next = tmp;            
        } else {
            if (nodeA->next == nodeB) {
                nodeAParent->next = nodeB;
                tmp = nodeB->next;
                nodeB->next = nodeA;
                nodeA->next = tmp;                        
            } else {
                nodeBParent->next = nodeA;
                tmp = nodeA->next;
                nodeA->next = nodeB;
                nodeB->next = tmp;                                        
            }
        }        
    } else {
        if (nodeAParent == (Node *)headOrig) {
            *headOrig = nodeB;
            
            tmp = nodeB->next;
            nodeB->next = nodeA->next;
            nodeBParent->next = nodeA;
            nodeA->next = tmp;
        } else if (nodeBParent == (Node *)headOrig) {
            *headOrig = nodeA;
            
            tmp = nodeA->next;
            nodeA->next = nodeB->next;
            nodeAParent->next = nodeB;
            nodeB->next = tmp;
        } else {
            tmp = nodeA->next;
            nodeA->next = nodeB->next;
            nodeAParent->next = nodeB;
            nodeB->next = tmp;            
            nodeBParent->next = nodeA;
        }
    }
}

int main() {
    string name;

    /*
    cout << "What's your name" << name.length() << endl;

    getline(cin, name);

    cout << "your name is " << name << name.length()<<endl;

    for (int i=0;i<name.length();i++)
        cout<<name[i];

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

    char s[] = "Joon Rhee";
    cout<<"reverse of "<<s<<" = ";
    reverseString(s);
    cout<<s<<endl;
    
    n1 = 12345;
    cout<<"numToString of "<<dec<<n1<<" = "<<dec<<numToString(n1);
    
    char cstr[] = "aabcddddefff";
    
    cout<<"compress string "<<cstr<<" = "<<compstr(cstr)<<endl;

    int ia[] = {10, 5, 2, 12, 6, 5, 4, 14, 1, 0, 999, 999, 999};
    int ia_size = sizeof(ia)/sizeof(ia[0]);

    sort(ia, ia_size);
    insert(ia, ia_size, 8);
    insert(ia, ia_size, 3);
    rotate (ia, ia_size, -2);

    char tstr[] = "ABCDE";
    int tstr_size = sizeof(tstr)/sizeof(tstr[0])-1;
    //cout<<"tsize = "<<tstr_size<<endl;
    //permus(tstr, tstr_size - 1, 0);
    //comboPrint(tstr, tstr_size, 0, 3);
    
    for (int i=1;i<=tstr_size;i++) {
        comboPrint(tstr, tstr_size, 0, i);
        cout<<"--------------"<<endl;
    }

    int gcd = GCD(128, 64);
    int lcm = LCM(128, 64);
    cout<<"gcd = "<<gcd<<" "<<" lcm = "<<lcm<<endl;
    
    int ia2[] = {2,4,3,6,2,1};
    countFreq(ia2, 6);
    
    Node *head = NULL;
    Node *tail = NULL;
    for (int i=0;i<10;i++) {
       Node *n = (Node *) malloc(sizeof(Node));
       initNode(n, i);
       
       if (head == NULL)
           head = tail = n;
       else {
           tail->next = n;
           tail = n;
       }            
    }
    
    printNode(head);
    swapTwo(&head, 1, 0);
    printNode(head);
    
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
