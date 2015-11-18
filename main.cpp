#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <ctime> 
#include <bitset>

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

void bubbleSort(int n[], int size) {
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

void rotateIntArray(int n[], int size, int rot) {
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

char word[512];
int comboCnt;

void combo(char s[], int size, int start, int comboSize, int idx) {
    if (comboSize > size || comboSize <= 0)
        return;

    for (int i=start;i<size; i++) {
       word[idx] = s[i];
        if (idx == (comboSize-1)) {
            comboCnt++;
            word[idx+1] = '\0';
            cout<<"combo: "<<word<<endl;
        } else {
            combo(s, size, i+1, comboSize, idx+1);
        }
    }
}

void combo2(char s[], int size, int start, int comboSize, int idx) {
    if (comboSize > size || comboSize <= 0)
        return;

    /*
     |------------------------------------------------|
     idx           <endSize>   comboSize <--------- size
     */
    int endSize = (size - comboSize) + idx + 1;
    if (endSize > size)
        return;
    
    for (int i=start;i<endSize; i++) {
       word[idx] = s[i];
        if (idx == (comboSize-1)) {
            comboCnt++;
            word[idx+1] = '\0';
            cout<<"combo: "<<word<<endl;
        } else {
            combo(s, size, i+1, comboSize, idx+1);
        }
    }
}

void comboPrint(char s[], int size, int start, int comboSize) {
    comboCnt = 0;
    combo(s, size, start, comboSize, 0);
    cout<<"combo total = "<<comboCnt<<endl;
    
    /* TODO:
     * Optimization     
     * 
     * int endSize = arraySize - start - idx;
     * for (int i=start;i<; i++) {
     * 
     */
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
 void countFreq(int a[], int size) {
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

/* int findNextBigSub(int a[], int s, int e, int v) {
    if (v < a[s])
        return s;
    
    int m = (e-s)*(v-a[s])/(a[e]-a[s]) + s;
    if (m > e)
        m = e;
    
    int idx = m;
    if (v < a[m]) {
        for (int i=m-1;i>=0;i--) {
            if (v > a[m])
                break;
            else {
                idx = i+1;
            }
        }
    } else {
        
    }
        
        
    return findNextBigSub(a, )
}*/


int findNextBigIdx(int a[], int size, int v) {
    for (int i=0;i<size;i++) {
        if (a[i] > v)
            return i;
    }
    
    return -1;
}


int findNextBigIdxAdv(int a[], int size, int v) {
    int end = size-1;
    
    if (v < a[0])
        return 0;

    if (v >= a[end])
        return -1;
        
    int m = end*(v-a[0])/(a[end]-a[0]);
    if (m > end)
        m = end;
    
    int idx = m;
    if (v < a[m]) {
        for (int i=m-1;i>=0;i--) {
            if (v > a[i]) {
                idx = i+1;
                break;                
            }
        }
    } else {
        for (int i=m+1;i<size;i++) {
            if (v < a[i]) {
                idx = i;
                break;
            }
        }        
    }
   
    return idx;
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

void quickSwap(int x, int y) {
    
    cout<<"Quick Swap before = "<<x<<", "<<y<<endl;
    
    x = x + y;
    y = x - y;
    x = x - y;
    
    cout<<"Quick Swap after = "<<x<<", "<<y<<endl;
}

void quickSwap2(int x, int y) {
    
    cout<<"Quick Swap2 before = "<<x<<", "<<y<<endl;

    x = x^y;
    y = x^y;
    x = x^y;
    
    cout<<"Quick Swap2 after = "<<x<<", "<<y<<endl;
}

int clearLastBit(int x) {
    return x&(x-1);
}

int getLastBit(int x) {
    return x&!(x-1);
}

#define GBIT(a, b) (((a & (1<<b))>>b) & 0x1)
#define SBIT(a, v, b) ((a & ~(1<<b)) | (v<<b))

void reverseBit(int x) {
    int s = 0;
    int e = 31;
 
    cout<<"Before reverseBit = 0x"<<bitset<32>(x)<<endl;
    while (s <= e) {
        int a = GBIT(x, s);
        int b = GBIT(x, e);       
        
        x = SBIT(x, a, e);                
        x = SBIT(x, b, s);
        
        s++;
        e--;
    }
    cout<<"After reverseBit  = 0x"<<bitset<32>(x)<<endl;
 }

 typedef struct charNode {
     char c;
     int cnt;
     int sorted;
     struct charNode * next;
 } CNODE;
 
 #define CNODE_SIZE 26
 CNODE cnodes[CNODE_SIZE];
 CNODE * chead;
 CNODE * ctail;
 
 void cnodeInit() {
     chead = NULL;
     ctail = NULL;
    CNODE * prev = NULL;
    for (int i=0;i<CNODE_SIZE;i++) {
        cnodes[i].c = 'a'+i;
        cnodes[i].cnt = 0;
        cnodes[i].sorted = 0;
        cnodes[i].next = NULL;
        if (prev != NULL)
            prev->next = &cnodes[i];
        prev = &cnodes[i];
    }

    if (prev != NULL)
        prev->next = &cnodes[CNODE_SIZE-1];     
 }
 
 void cnodePut(char c) {
     cnodes[c-'a'].cnt++;
 }
 
 void cnode_swap(CNODE *a, CNODE *b) {
     char c = a->c;
     int cnt = a->cnt;
     
     a->c = b->c;
     a->cnt = b->cnt;
     b->c = c;
     b->cnt = cnt;
 }
 
 void cnodeSquash() {
    for (int i=0;i<CNODE_SIZE;i++) {
        if (cnodes[i].cnt > 0) {
            if (chead == NULL) {
                chead = ctail = &cnodes[i];
            } else {
                ctail->next = &cnodes[i];
                ctail = ctail->next;
            }           
        }
    }
    ctail->next = NULL;
 }
 
 void cnodeReSquash() {
     CNODE *head = chead;
     CNODE *prev = NULL;
     while (head != NULL) {
         if (head->cnt == 0) {
             if (chead == head)
                 chead = chead->next;
             else {
                 if (prev != NULL)
                    prev->next = head->next;                    
             }
         }
         prev = head;
         head = head->next;
     }
 }
 
 void cnodeSort() {
     cnodeSquash();
     
     while (chead->sorted == 0) {
         CNODE *head = chead;
         
         while (head != NULL) {
            if (head->next == NULL || head->next->sorted == 1) {
                 head->sorted = 1;
                 break;
            } else {
                 if (head->cnt < head->next->cnt) {
                   cnode_swap(head, head->next);
                }
            }
            head = head->next;
         }
     }
     
    CNODE *head = chead;
    while (head != NULL) {
        ctail = head;
        head = head->next;
    }
 }
  
 void alternateString(char a[]) {
    cnodeInit();
    
    while (*a != '\0') {
        cnodePut(*a++);
    }
    
    cnodeSort();
        
    CNODE *head = chead;
    while (head != NULL) {
        cout<<"AS: "<<head->c<<" cnt:"<<head->cnt<<endl;
        head = head->next;
    }    
    
    char outs[256] = "";
    int outPos = 0;
    int result = 1;
    int binary = 0;
        
    while (chead != NULL) {
        head = chead;
        CNODE *target;
        
        if (outPos == 0) {
            target = head;
        } else {
            if (outs[outPos-1] != head->c)
                target = head;
            else if (head->next != NULL && outs[outPos-1] != head->next->c) {
                target = head->next;
            } else {
                result = 0;
                break;
            }
        }
        
        outs[outPos++] = target->c;
        target->cnt--;
        
        cnodeReSquash();
    }
    
    outs[outPos] = '\0';
    cout<<"alternateString result:"<<result<<" = "<<outs<<endl;
    
 }
 
 Node * mergeLL(Node * n1, Node *n2) {
     Node * head = NULL;
     Node * tail = NULL;
     Node * node;
     
     while (n1 != NULL || n2 != NULL) {
         if (n1 == NULL) {
             node = n2;
             n2 = n2->next;
         } else if (n2 == NULL) {
             node = n1;
             n1 = n1->next;
         } else {
             if (n1->val <= n2->val) {
                 node = n1;
                 n1 = n1->next;
             } else {
                 node = n2;
                 n2 = n2->next;
             }
         }
         
         node->next = NULL;
         if (head == NULL) {
             head = tail = node;             
         } else {
             tail->next = node;
             tail = node;             
         }
     }
     
     return head;
 }
 
 Node * mergeLLsort(Node * head) {
     if (head == NULL)
         return NULL;
     
    int size=0;
    Node *t = head;
    Node *prev;
    
     while (t != NULL) {
         size++;
         t = t->next;
     }
     
     if (size == 1)
         return head;
          
     t = prev = head;
     size /= 2;
     while (t != NULL & size-- > 0) {
         prev = t;
         t = t->next;
     }     
     prev->next = NULL;     
     
     Node * n1 = mergeLLsort(head);
     Node * n2 = mergeLLsort(t);
     
     return mergeLL(n1, n2);
 }

  Node * findKNode(Node * nd, int * k) {
     Node * ret = NULL;     
     if (nd->next != NULL)
         ret = findKNode(nd->next, k);
     
     if (ret == NULL) {
        if (*k == 0)
         return nd;
         
        (*k)--;
     }
     
     return ret;
 }
  
 Node * findKnodeFromTail(Node * head, int k) {
     if (head == NULL && k < 0)
         return NULL;
         
     return findKNode(head, &k);
 }
 
 
 void * aligned_alloc(int size, int alignment) {
        int offset = (alignment - 1)+1;

        void * orig = (void *)malloc(size + offset);
        if (orig == NULL)
            return NULL;

        void ** pp = (void **) (((size_t)orig + offset) & ~(alignment - 1));

        pp[-1] = orig;

        return (void *)pp;
}

void aligned_free(void * p) {
        void ** actual = (void **)p;
        free(actual[-1]);
}

int bitLocation (int val) {
    int loc = 0;

    while (!(val & 0x1)) {
        loc++;
        val = val>>1;
    }

    return loc;
}

void squashArray(int a[], int size) {
    int tzcnt = 0;
    
    for (int i=0;i<size;i++) {
        if (a[i] == 0) {
            tzcnt++;
        } else if (tzcnt > 0) {
            a[i-tzcnt] = a[i];
            a[i] = 0;
        }
    }
}

void drawSolidRect(char * sc, int x1, int y1, int x2, int y2, int W) {
    for (int y = y1;y <= y2; y++){
        for (int x = x1;x <= x2; x++){
            *(char *)(sc+x+W*y) = '0';
        }
    }
}

void drawRect(char * sc, int x1, int y1, int x2, int y2, int W) {
    drawSolidRect(sc, x1, y1, x2, y1, W);
    drawSolidRect(sc, x1, y2, x2, y2, W);
    drawSolidRect(sc, x1, y1+1, x1, y2-1, W);
    drawSolidRect(sc, x2, y1+1, x2, y2-1, W);

}

#define GET_BIT(v, n) (((v)>>(n)) & 0x1)
#define SET_BIT(v, n, a) (((v)&~(1<<(n))) | (a) << (n))

int swapBit2(int val, int i, int j) {
    int v = GET_BIT(val, i);
    val = SET_BIT(val, i, GET_BIT(val, j));
    val = SET_BIT(val, j, v);

    return val;
}

int swapBit(int val, int i, int j) {
    int vi = GET_BIT(val, i);
    int vj = GET_BIT(val, j);

    if (vi == vj)
        return val;

    val ^= 1<<i;
    val ^= 1<<j;

    return val;
}

int strToInt(char str[]) {
    int size = 0;
    int neg = 0;
    int sum = 0;

    char *orig = str;

    while (*str != '\0') {
        char c = *str;
        if (c >= '0' && c <= '9') {
            size++;
        } else if (c == '-') {
            neg = 1;
        } else {
            return 0;
        }

        str++;
    }

    if (size == 0)
        return 0;

    str = orig;
    while (*str != '\0') {
        char c = *str;
        if (c >= '0' && c <= '9') {
            size--;
            int d = c - '0';
            d *= power(10, size);
            sum += d;
        }

        str++;
    }

    if (neg)
        sum = -sum;

    return sum;
}

string ToString(int x) {
    char ret[2];
    ret[0] = '0'+x;
    ret[1] = '\0';
    
    return ret;
}

string DecToBin2(int dec) {
    /* only works for postive */
    if (dec <= 1){
        return ToString(dec);
    } else {
        //Divide the number by two and append '0' if even or '1' if odd.
        return DecToBin2(dec / 2) + ToString(dec % 2);
    }
}

string DecToBin(int dec) {
    int max = sizeof(dec)*8;
    string ret = "";
    
    if (dec == 0)
        return "0";
    
    //while (dec != 0 && max > 0) {
    while (max > 0) {
        if (dec & 1) {
            ret = "1"+ret;            
        } else {
            ret = "0"+ret;            
        }
        
        dec = (dec>>1) & 0x7fffffff;
        max--;                
    }
    
    return ret;
}

string FloatToBin(int * dec) {
    int max = sizeof(*dec)*8;
    string ret = "";
    
    if (*dec == 0)
        return "0";
    
    while (*dec != 0 && max > 0) {
        if (*dec & 1) {
            ret = "1"+ret;            
        } else {
            ret = "0"+ret;            
        }
        
        *dec = (*dec>>1) & 0x7fffffff;
        max--;                
    }
    
    return ret;
}


static Node * shead = NULL;
static Node * stail = NULL;

void insertN(int v) {
    Node * n = (Node *)malloc(sizeof(Node));
    n->val = v;
    n->next = NULL;

    if (shead == NULL) {
        shead = n;
        return;
    }

    Node *t = shead;
    Node *prev = shead;

    while (t != NULL) {
        if (n->val < t->val)
            break;

        prev = t;
        t = t->next;
    }

    if (prev == shead) {
        shead = n;
        n->next = t;
    } else {
        prev->next = n;
        n->next = t;
    }
}

void deleteN(int v) {
    Node * t = shead;
    Node * prev = shead;

    cout<<"delete "<<v<<endl;
    while (t != NULL) {
        if (t->val == v)
            break;

        prev = t;
        t = t->next;
    }

    if (t == NULL)
        return;

    if (t == shead) {
        shead = shead->next;
    } else {
        prev->next = t->next;
    }

    free(t);
}

void printN() {
    cout<<"------------- Node Print -------------"<<endl;

    Node *n = shead;

    while (n != NULL){
        cout<<n->val<<" -> ";
        n = n->next;
    }
    cout<<"NULL"<<endl;
    cout<<"--------------------------------------"<<endl<<endl;
}

Node * reverseHeadSub(Node * n) {
    Node * prev = NULL;
    if (n->next != NULL)
        prev = reverseHeadSub(n->next);

    n->next = NULL;
    if (prev == NULL)
        shead = n;
    else
        prev->next = n;

    return n;
}

void reverseHead() {
    if (shead == NULL || shead->next == NULL)
        return;

    reverseHeadSub(shead);
}

Node * getN(int val){
    Node * t = shead;

    while (t != NULL) {
        if (t->val ==  val)
            return t;
        t = t->next;
    }

    return NULL;
}

int isLoopN() {
    if (shead == NULL || shead->next == NULL)
        return 0;

    Node * n1 = shead;
    Node * n2 = shead->next;

    while (n1 != NULL && n2 != NULL) {
        if (n1 == n2)
            return 1;

        n1 = n1->next;
        if (n2->next == NULL)
            n2 = NULL;
        else
            n2 = n2->next->next;
    }

    return 0;
}

Node * loopStartNode() {
    if (shead == NULL || shead->next == NULL || isLoopN == 0)
        return NULL;

    Node * n1 = shead;
    Node * n2 = shead->next;

    int state = 0;
    int cnt = 0;
    while (1) {
        if (n1 == n2) {
            if (state == 0) {
                state = 1;
                cnt = 0;
            } else {
                break;
            }
        }

        n1 = n1->next;
        cnt++;

        if (state == 0) {
           n2 = n2->next->next;
        }
    }

    n1 = shead;
    n2 = shead;
    while (cnt-- > 0) {
        n2 = n2->next;
    }

    while (1) {
        if (n1 == n2) {
            return n1;
        }

        n1 = n1->next;
        n2 = n2->next;
    }
}

float stringToFloat(char s[]) {
    if (s == NULL)
        return 0;

    float ret = 0;
    int neg = 0;
    if (s[0] == '-') {
        neg = 1;
        s++;
    }

    char *t = s;
    int cnt = 0;
    while (*t != '.' && *t != '\0') {
        cnt++;
        t++;
    }

    for (int i=0;i<cnt;i++) {
        ret += (s[i]-'0')*pow(10,cnt-i-1);
    }

    cnt = 1;
    if (*t == '.') {
        t++;
        while (*t != '\0') {
            ret += (*t -'0')/pow(10,cnt);
            t++;
            cnt++;
        }
    }

    if (neg)
        ret = -ret;

    return ret;
}

int squashBitToLeft(int v) {
    int cnt = 0;

    for (int i=0;i<32;i++) {
        if (v & (1<<i)) {
            cnt++;
        }
    }

    int ret = 0;
    int s = 31;
    while (cnt > 0) {
       ret |= (1<<s);
        s--;
        cnt--;
    }

    return ret;
}

int bitToMax(int v) {
    if (v == 0xffffffff || v == 0)
        return v;

    int cnt = 0;

    for (int i=0;i<32;i++) {
        if (v & (1<<i)) {
            cnt++;
        }
    }

    int ret = 0;
    int s = 30;
    while (cnt > 0) {
        ret |= (1<<s);
        s--;
        cnt--;
    }

    return ret;
}


int bitToMin(int v) {
    if (v == 0xffffffff || v == 0)
        return v;

    int cnt = 0;

    for (int i=0;i<32;i++) {
        if (v & (1<<i)) {
            cnt++;
        }
    }

    int ret = 0x80000000;
    cnt--;
    int s = 30;
    while (cnt > 0) {
        ret |= (1<<s);
        s--;
        cnt--;
    }

    return ret;
}

static int binsIdx;
void doBinarySearch(int a[], int val, int l, int r) {
    if (binsIdx != -1)
        return;

    if (l > r)
        return;

   int mid = (l+r)/2;

    if (a[mid] == val) {
        binsIdx = mid;
        return;
    }

    if (a[mid] > val)
        doBinarySearch(a, val, l, mid-1);
    else
        doBinarySearch(a, val, mid+1, r);

}

int binarySearch(int a[], int size, int val) {
    binsIdx = -1;

    doBinarySearch(a, val, 0, size-1);

    return binsIdx;
}

void doRBS(int a[], int l, int r, int size) {
    if (binsIdx != -1)
        return;

    if (l > r)
        return;

    int mid = (l+r)/2;
    int val = a[mid];

    int prev = mid-1;
    if (prev < 0)
        prev = size-1;

    /* is this the turning index? */
    if (val < a[prev]) {
        binsIdx = mid;
        return;
    }

    if (a[l] > val)
        doRBS(a, l, mid-1, size);
    else if (a[r] < val)
        doRBS(a, mid+1, r, size);
    else {
        binsIdx = l;
        return;
    }
}

int findRotateIdx(int a[], int size) {
    binsIdx = -1;

    doRBS(a, 0, size-1, size);

    return binsIdx;
}

void rotateIntArrayCopy(int a[], int size, int n) {
    int fa[size];
    for (int i=0;i<size;i++) {
        fa[i] = a[i];
    }

    for (int i=0;i<size;i++) {
        int from = (size - n +i)%size;
        a[i] = fa[from];
    }
}

void printIntArray(int a[], int size) {
    cout<<endl;
    for (int i=0;i<size;i++)
        cout<<a[i]<<" ";

    cout<<endl;
}

int countBits(int x) {
    int cnt = 0;
    int idx = 1;

    while (idx != 0) {
        if (x & idx)
            cnt++;
        idx = idx<<1;
    }

    return cnt;
}

void insertionSort(int a[], int size) {
    if (size < 2)
        return;

    for (int i=1;i<size;i++) {
        int loc = -1;
        int val = a[i];
        for (int j=0;j<i;j++) {
            if (val < a[j]) {
                loc = j;
                break;
            }
        }

        /* needs to insert and shift */
        if (loc != -1) {
            for (int m=i;m>loc;m--) {
                a[m] = a[m-1];
            }
            a[loc] = val;
        }
    }
}

void doIS(char *s, int size, int sidx, int widx, char *word) {
    if (sidx == size-1) {
        word[widx++] = s[sidx];
        word[widx++] = '\0';
        cout<<word<<endl;
        return;
    }

    word[widx++] = s[sidx];

    for (int i=0;i<2;i++) {
        if (i==0)
            word[widx++] = ' ';

        doIS(s, size, sidx+1, widx, word);

        if (i==0)
            widx--;
    }

}

void insertSpace(char * s) {
    int size = strlen(s);

    if (size == 0)
        return;

    char wbuf[size*2];
    cout<<"InsertSpace -----------"<<endl;

    doIS(s, size, 0, 0, wbuf);
}

void findTripletLessThanSum(int a[], int size, int sum) {
    if (size < 3)
        return;

    cout<<"findTripletLessThanSum()------"<<endl;
    bubbleSort(a, size);
    cout<<"SUM = "<<sum<<endl;
    for (int i=0;i<size-2;i++) {
        for (int j=i+1;j<size-1;j++) {
            for (int m=j+1;m<size;m++) {
               int s = a[i] + a[j] + a[m];
                if (s < sum)
                    cout<<"sum = "<<s<<" : ["<<a[i]<<" "<<a[j]<<" "<<a[m]<<"]"<<endl;
                else
                    break;
            }
        }
    }
}

int myDiv(int n, int d) {
    int sign = 1;
    
    if (d == 0 || n == 0)
        return 0;
    
    if (n<0) {
        n = -n;
        sign *= -1;
    }
    
    if (d<0) {
        d = -d;
        sign *= -1;
    }
    
    int cnt = 0;
    
    while (n >= d) {
        cnt++;
        n -= d;
    }
    
    return sign*cnt;
}

void swapChar(char *x, char *y) {
    char t = *x;
    *x = *y;
    *y = t;
}


void interArrayToDo(char a[], int size, int m) {
    /* need to use interArray algorithm below
     * 
     */
}

/*
 First swap elements in the middle pair
Next swap elements in the middle two pairs
Next swap elements in the middle three pairs
iterate n-1 steps.

Ex: with n = 4.
a1 a2 a3 a4 b1 b2 b3 b4
a1 a2 a3 b1 a4 b2 b3 b4
a1 a2 b1 a3 b2 a4 b3 b4
a1 b1 a2 b2 a3 b3 a4 b4
 */

void interArray(char a[], int size) {
    if (size%2)
        return;
    
    int m = size/2;
    
    for (int i=m-1;i>0;i--) {
        int end = (m-i) + m-1;
        
        for (int j=i;j<end;j+= 2) {
            swapChar(&a[j], &a[j+1]);
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

    bubbleSort(ia, ia_size);
    insert(ia, ia_size, 8);
    insert(ia, ia_size, 3);
    rotateIntArray (ia, ia_size, -2);

    char tstr[] = "ABCDE";
    int tstr_size = sizeof(tstr)/sizeof(tstr[0])-1;
    //cout<<"tsize = "<<tstr_size<<endl;
    //permus(tstr, tstr_size - 1, 0);
    //comboPrint(tstr, tstr_size, 0, 3);

    comboPrint(tstr, tstr_size, 0, tstr_size);

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

    int biSize = 1000;
    int bi[biSize];

    for (int i=0;i<biSize;i++)
        bi[i] = i;

    int r1, r2, rv;
    for (int i=0;i<100;i++) {
        rv = rand()%biSize;
        r1 = findNextBigIdx (bi, biSize, rv);
        r2 = findNextBigIdxAdv (bi, biSize, rv);

        if (r1 != r2)
            cout<<" FAILURE!!!!!!"<<endl;
    }

    //int LOOPS = 3000000;
    int LOOPS = 30;
    clock_t begin = clock();
    for (int i=0;i<LOOPS;i++) {
        rv = rand()%biSize;
        r1 = findNextBigIdx (bi, biSize, rv);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Regular e.time findNextBigIdx = "<<elapsed_secs<<endl;


    begin = clock();
    for (int i=0;i<LOOPS;i++) {
        rv = rand()%biSize;
        r1 = findNextBigIdxAdv (bi, biSize, rv);
    }
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Advanced e.time findNextBigIdx = "<<elapsed_secs<<endl;

    quickSwap(-5, -13);
    quickSwap2(-5, -13);

    reverseBit(0xF70a0030);

    int m = 10;
    int n = 9;
    while (m-- > 0) {
        while (n-- > 0) {
            cout<<"m="<<m<<" n="<<n<<endl;
            if (n <5)
                break;
        }
    }

    char asString[] = "aabbbdef";
    alternateString(asString);


    int nsize = 50;
    Node nodes[nsize];
    for (int i=0;i<nsize;i++) {
        nodes[i].val = rand()%100;
        nodes[i].next = &nodes[i+1];
    }
    nodes[nsize-1].next = NULL;

    Node * hn = mergeLLsort(nodes);
    Node * hno = hn;

    cout<<"LL merge sort ----"<<endl;
    while (hn != NULL) {
        cout<<hn->val<<" ";
        hn = hn->next;
    }
    cout<<endl;

    Node * knode = findKnodeFromTail(hno, 5);
    if (knode != NULL)
        cout<<"5 node from hn = "<<knode->val<<endl;

    int alignSize = 0x100;
    void * mem = aligned_alloc(100, alignSize);
    cout<<"aligned size = 0x"<<hex<<alignSize<<"  -  addr = "<<hex<<mem<<endl;
    aligned_free(mem);

    int xh = 0xffffffff;
    int xhn = 32;

    while (xhn-- > 0) {
        cout<<hex<<"0x"<<xh<<endl;
        xh = xh>>1;
        xhn--;
    }

    const int const_a = 10;
    //const_a = 5;
    //cout<<const_a

    unsigned int uia = 10;
    unsigned int uib = -200;
    unsigned int uisum = (uia+uib);

    cout<<"ui sum = 0x"<<hex<<uia<<" + 0x"<<uib<<" = "<<dec<<uisum<<endl;

    int si[] = {1, 0, 0, 2, 3, 0, 5, 19, 8, 0};
    int si_size = sizeof(si)/sizeof(si[0]);
    squashArray(si, si_size);
    cout<<"squash array = ";
    for (int i=0;i<si_size;i++)
        cout<<si[i]<<" ";
    cout<<endl;

    unsigned int la = -1;
    la = la >> 1;

    cout<<hex<<" Long Int Max = 0x"<<la<<"  dec="<<dec<<la<<endl;

    int W = 100;
    int H = 50;
    char screen[100*50];
    for (int i=0;i<W*H;i++)
        screen[i] = '*';

    drawRect(screen, 5, 6, 30, 36, W);

    cout<<endl;
    char *sc = screen;
    for (int i=0;i<H;i++) {
        for (int j = 0; j < W; j++) {
            cout << *sc++;
        }
        cout<<endl;
    }

    int ihex = 0xF8000;
    cout<<"SWAP BIT = 0x"<<hex<<swapBit(ihex, 1, 15)<<endl;

    char stri[] = "-58276201";
    cout<<endl<<stri<<" = "<<dec<<strToInt(stri)<<endl;

    
    cout<<hex<<" Long Int Max = 0x"<<la<<"  dec="<<dec<<la<<endl;


    cout<<" dec2bin = " << DecToBin(10)<<endl;
    cout<<" dec2bin = " << DecToBin2(8)<<endl;

    float f1 = 0.2;
    cout<<"size of float = "<<sizeof(f1)<<endl;
    cout<<f1<<" float2bin = " << FloatToBin((int *)&f1)<<endl;

    int rn[3];
    for (int i=0;i<3;i++) {
        rn[i] = -(i+2);
        insertN(rn[i]);
    }
    
    for (int i=0;i<15;i++) {
        int val = rand()%100;
        insertN(val);
    }
    insertN(-1);
    insertN(1000);    
    printN();

    for (int i=0;i<2;i++) {
        deleteN(rn[i]);
        printN();
    }
    
    deleteN(-1);
    printN();
    //deleteN(1000);
    //printN();

    cout<<"detect loop = "<<isLoopN()<<endl;
    Node * nd1 = getN(1000);
    Node * nd2 = getN(rn[2]);
    nd1->next = nd2;
    cout<<"detect loop = "<<isLoopN()<<endl;
    Node * nds = loopStartNode();
    if (nds != NULL)
        cout<<"loopstartnode = "<<nds->val<<endl;
    nd1->next = NULL;

    reverseHead();
    printN();

    char fstr[] = "-123.14";
    cout<<"floatToString = "<<stringToFloat(fstr)<<endl;

    int sqi = 0xa01100;
    cout<<"squashToLeft of "<<hex<<DecToBin(sqi)<<endl;
    cout<<"squashToLeft is "<<hex<<DecToBin(squashBitToLeft(sqi))<<endl;

    cout<<"max bit = "<<DecToBin(bitToMax(sqi))<<endl;
    cout<<"min bit = "<<DecToBin(bitToMin(sqi))<<endl;

    int bina[]= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int binasize = sizeof(bina)/sizeof(bina[0]);
    int sidx = binarySearch(bina, binasize, 7);
    cout<<"binary search = "<<dec<<sidx<<endl;

    printIntArray(bina, binasize);
    int ridx = findRotateIdx(bina, binasize);
    cout<<" rot idx = "<<ridx<<endl;

    rotateIntArray(bina, binasize, binasize-1);
    printIntArray(bina, binasize);
    ridx = findRotateIdx(bina, binasize);
    cout<<" rot idx = "<<ridx<<endl;

    rotateIntArray(bina, binasize, 3);
    printIntArray(bina, binasize);
    ridx = findRotateIdx(bina, binasize);
    cout<<" rot idx = "<<ridx<<endl;

    int cnti = 0xf000a0f1;
    cout<<" cnt bits = "<<countBits(cnti)<<endl;

    int insa[]= {0, 1, -2, 6, 3, 7, 8, 19, 10};
    int insaSize = sizeof(insa)/sizeof(insa[0]);
    insertionSort(insa, insaSize);
    printIntArray(insa, insaSize);

    char isStr[] = "ABCDEF";
    insertSpace(isStr);

    findTripletLessThanSum(insa, insaSize, 10);
    
    unsigned int ui = 0x10000000;
    ui = ui>>1;
    cout<<"unsigned int shift = "<<hex<<DecToBin(ui)<<endl;

    cout<<" my div = "<<dec<<myDiv(-803, -2)<<endl;
    
    //char inta[]= {'0', '1', '2', '3', '4', '5', 'A', 'B', 'C', 'D'};
    char inta[]= {'1', '2', '3', '4', '5', 'A', 'B', 'C', 'D', 'E'};
    int intaSize = sizeof(inta)/sizeof(inta[0]);
    inta[intaSize] = '\0';

    interArray(inta, intaSize);
    cout<<"interArray = "<<inta<<endl;
    
    //cout<<"findNextBigIdx = "<<ri<<endl;
    //cout<<"adv.findNextBigIdx = "<<ri<<endl;
    /*
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
    */
    return 0;
}
