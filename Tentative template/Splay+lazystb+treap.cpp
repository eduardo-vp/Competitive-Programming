#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
 
#define pb push_back
#define ff  first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) ll(x.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
 
#define N 8800015
#define M 21
#define sqr(x) (x)*(x)
#define INF 20000000000000000
#define mod 1000000007
#define bas 31
#define pi acos(-1) 
 
using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii > tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> set_t;
 
#define trace(...) f(#__VA_ARGS__, __VA_ARGS__)
 
template<typename t> void f(const char* x, t&& val1){
    cout<<x<< " : "<<val1<<endl;
}
template<typename t1, typename... t2> void f(const char* x, t1&& val1, t2&&... val2){
    const char* xd=strchr(x+1, ',');
    cout.write(x, xd-x)<<" : "<<val1<<" | ";
    f(xd+1, val2...);
}

//-----------------------------------------------
// Lazy splay tree propagation
// make -> n, preprocess() y build()
// Be careful about the lazy push values
// there isn't need to use an Op function (this may cause TL)

struct Node{
    Node *child[2], *p;
    bool t;
    ll val, ta, sum, add, l, r, mid;
    inline void clear(){
        ta=-INF;
    }
};
 
struct SplayTree{
    Node *nil, *root;
    ll ar[1<<18], n;
    inline void preprocess(){
        nil=new Node();
        nil->child[0] = nil->child[1] = nil->p=nil;
        nil->val=nil->ta=nil->sum=0;
        nil->t=false;
        nil->l=-INF;
        nil->r=-INF;
        nil->mid=-INF;
        nil->add=0;
        root=nil;
    }
    inline void upd(Node *&x){
        x->ta=x->child[0]->ta + x->child[1]->ta+1;
        x->sum=x->child[0]->sum+x->child[1]->sum+x->val;
        ll l=max(x->child[0]->l, x->child[0]->sum+x->val);
        ll r=max(x->val, x->child[0]->r+x->val);
        ll mid=max(l, max(r, max(x->val, max(x->child[0]->mid, x->child[0]->r+x->val))));
        ll l1=max(l, x->child[0]->sum+x->val+x->child[1]->l);
        ll r1=max(x->child[1]->r, x->child[1]->sum+r);
        ll mid1=max(l1, max(r1, max(x->child[1]->mid, max(mid, r+x->child[1]->l))));
        x->l=l1, x->r=r1, x->mid=mid1;
    }
    inline void updpro(Node *&x, ll val){
        x->add+=val;
        x->val+=val;
        x->sum+=x->ta*val;
        x->l+=x->ta*val;
        x->r+=x->ta*val;
        x->mid+=x->ta*val;
    }
    inline void push(Node *&x){
        if(x==nil) return;
        if(x->add!=0){
            if(x->child[0]!=nil) updpro(x->child[0], x->add);
            if(x->child[1]!=nil) updpro(x->child[1], x->add);
            x->add=0;
        }
        if(x->t){
            swap(x->child[0], x->child[1]);
            x->child[0]->t=!x->child[0]->t;
            x->child[1]->t=!x->child[1]->t;
            x->t=false;
        }
    }
    inline void set(Node *x, Node *y, ll d){
        x->child[d]=y;
        y->p=x;
    }
    inline ll get(Node *x, Node *y){
        return x->child[0]==y? 0 : 1;
    }
    inline ll rot(Node *&x, ll d){
        Node *y=x->child[d], *z=x->p;
        set(x, y->child[d^1], d);
        set(y, x, d^1);
        set(z, y, get(z, x));
        upd(x), upd(y);
    }
    inline void splay(Node *&x){
        push(x);
        while(x->p != nil){
            Node *y=x->p, *z=y->p;
            ll dy=get(y, x), dz=get(z, y);
            if(z==nil) rot(y, dy);
            else if(dy==dz) rot(z, dz), rot(y, dy);
            else rot(y, dy), rot(z, dz);
        }
        upd(x);
    }
    inline Node * getnode(Node *x, ll pos){
        while(push(x), x->child[0]->ta!=pos){
            pos<x->child[0]->ta? x=x->child[0]: (pos-=x->child[0]->ta+1, x=x->child[1]);
        }
        return splay(x), x;
    }
    inline void split(Node *x, ll l, Node * &t1, Node * &t2){
        if(l==0) t1=nil, t2=x;
        else{
            t1=getnode(x, l-1);
            t2=t1->child[1];
            t1->child[1]=t2->p =nil;
            upd(t1);
        }
    }
    inline Node * unir(Node *x, Node *y){
        if(x==nil) return y;
        x=getnode(x, x->ta-1);
        set(x, y, 1);
        upd(x);
        return x;
    }
    inline void AddRange(ll l, ll r, ll add){
        Node *t1, * t2, * t3;
        split(root, r, t1, t3);
        split(t1, l, t1, t2);
        t2->add+=add;
        t2->val+=add;
        t2->sum+=t2->ta * add;
        root=unir(t1, unir(t2, t3));
    }
    inline void modify(ll pos, ll val){
        root=getnode(root, pos);
        root->val=val;
        upd(root);
    }
    inline void AddVal(ll pos, ll val){
        Node *t1, *t2;
        Node *cur=new Node();
        cur->val=val, cur->p=nil, cur->t=false;
        cur->ta=1, cur->sum=val;
        cur->child[0]=cur->child[1]=nil;
        ll r=pos;
        if(r==root->ta || r==0){
            if(r==0) root=unir(cur, root);
            else root=unir(root, cur);
            return;
        }
        split(root, r, t1, t2);
        root=unir(unir(t1, cur), t2);
    } 
    inline void DelVal(ll pos){
        Node *t1, *t2, *t3;
        ll l=pos, r=pos+1;
        if(l==0 || r==root->ta){
            if(l==0){
                split(root, r, t1, t2);
                root=t2;
            }
            else{
                split(root, l, t1, t2);
                root=t1;
            }
            return;
        } 
        split(root, r, t1, t3);
        split(t1, l, t1, t2);
        root=unir(t1, t3);
        delete t2;
        return;
    }
    inline void Reverse(ll l, ll r){
        Node * t1, * t2, * t3;
        split(root, r, t1, t3);
        split(t1, l, t1, t2);
        t2->t=!t2->t;
        root=unir(unir(t1, t2), t3);
    }
    inline void move(ll l, ll r, ll l1, ll r1){
        Node *t1, *t2, *t3, *t4, *t5;
        split(root, r1, t4, t5);
        split(t4, l1, t3, t4);
        split(t3, r, t2, t3);
        split(t2, l, t1, t2);
        root=unir(unir(t1,unir(t4, t3)), unir(t2, t5));
    }
    inline ll que(ll l, ll r){
        Node *t1, * t2, *t3;
        split(root, r, t1, t3);
        split(t1, l, t1, t2);
        ll ans=t2->mid;
        root=unir(unir(t1, t2), t3);
        return ans;
    }
    inline ll Permute(ll l, ll r){
        ll x=que(r-1, r);
        AddVal(l, x);
        DelVal(r);
    }
    inline Node * build1(ll l, ll r){
        if(l==r) return nil;
        ll mid=(l+r)>>1;
        Node *x=new Node();
        x->val=ar[mid];
        x->sum=ar[mid];
        x->mid=ar[mid];
        x->l=ar[mid];
        x->r=ar[mid];
        x->p=nil;
        x->t=false;
        x->add=0;
        set(x, build1(l, mid), 0);
        set(x, build1(mid+1, r), 1);
        upd(x);
        return x;
    }
    inline void build(){
        Node *root1=build1(0, n);
        root=root1;
    }
}st;


int main(){
    ll n; scanf("%lld", &n);
    st.n=n;
    FER(i,0,n) scanf("%lld", &st.ar[i]);
    st.preprocess();
    st.build();
    ll q, l, r; scanf("%lld", &q);
    char s;
    FER(i,0,q){
        scanf(" %c", &s);
        if(s=='I'){
            scanf("%lld%lld", &l, &r); l--;
            st.AddVal(l, r);
        }
        else if(s=='D'){
            scanf("%lld", &l); l--;
            st.DelVal(l);
        }
        else if(s=='R'){
            scanf("%lld%lld", &l, &r); l--;
            st.modify(l, r);
        }
        else{
            scanf("%lld%lld", &l, &r); l--;
            ll froz=st.que(l, r);
            printf("%lld\n", froz);
        }
    }
    return 0;
}
