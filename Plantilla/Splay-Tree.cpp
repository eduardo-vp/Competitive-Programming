// dile a la jardinera que traigo flores
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
#define sz(x) int(x.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)

#define N 100005
#define MOD 1000000007
#define N1 105
#define sqr(x) (x)*(x)
#define INF 1000000000000000000

using namespace std;
using namespace __gnu_pbds;

typedef int ll;
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
//Lazy splay tree propagation
//make -> n, preprocess() y build()
//Be careful about the lazy push values 

struct Node{
    Node *child[2], *p;
    bool r;
    ll val, ta, sum, add;
};

struct SplayTree{
    Node *nil, *root;
    ll ar[N], n;
    inline void preprocess(){
        nil=new Node();
        nil->child[0] = nil->child[1] = nil->p=nil;
        nil->val=nil->ta=nil->sum=0;
        nil->r=false;
        nil->add=0;
        root=nil;
    }
    inline void upd(Node *x){
        x->ta=x->child[0]->ta + x->child[1]->ta+1;
        x->sum=x->child[0]->sum + x->child[1]->sum+x->val;
    }
    inline void updpro(Node * x, ll val){
        x->add+=val;
        x->val+=val;
        x->sum+=x->ta*val;
    }
    inline void push(Node *x){
        if(x==nil) return;
        if(x->add!=0){
            if(x->child[0]!=nil) updpro(x->child[0], x->add);
            if(x->child[1]!=nil) updpro(x->child[1], x->add);
            x->add=0;
        }
        if(x->r){
            swap(x->child[0], x->child[1]);
            x->child[0]->r=!x->child[0]->r;
            x->child[1]->r=!x->child[1]->r;
            x->r=false;
        }
    }
    inline void set(Node *x, Node *y, ll d){
        x->child[d]=y;
        y->p=x;
    }
    inline ll get(Node *x, Node *y){
        return x->child[0]==y? 0:1;
    }
    inline ll rot(Node *x, ll d){
        Node *y=x->child[d], *z=x->p;
        set(x, y->child[d^1], d);
        set(y, x, d^1);
        set(z, y, get(z, x));
        upd(x), upd(y);
    }
    inline void splay(Node *x){
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
    inline void Reverse(ll l, ll r){
        Node * t1, * t2, * t3;
        split(root, r, t1, t3);
        split(t1, l, t1, t2);
        t2->r=!t2->r;
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
        ll ans=t2->sum;
        root=unir(unir(t1, t2), t3);
        return ans;
    }
    inline Node * build1(ll l, ll r){
        if(l==r) return nil;
        ll mid=(l+r)>>1;
        Node *x=new Node();
        x->val=ar[mid];
        x->p=nil;
        x->r=false;
        set(x, build1(l, mid), 0);
        set(x, build1(mid+1, r), 1);
        upd(x);
        return x;
    }
    inline void build(){
        Node *root1=build1(0, n);
        root=root1;
    }
}spytree;

int main(){
    fastio;
    ll t, q=0; cin>>t;
    string s;
    map<char, ll> m;
    map<ll, char> m1;
    for(char i='a'; i<='z'; i++) m[i]=q, m1[q++]=i;
    while(t--){
        cin>>s>>q;
        SplayTree st;
        st.n=sz(s);
        ll pos=0, l, r, l1, r1;
        for(auto xd: s) st.ar[pos++]=m[xd];
        st.preprocess(), st.build();
        FER(i,0,q){
            cin>>l>>r>>l1>>r1; 
            ll add=l1-r-1;
            l--; l1--;
            ll ja1=l, ja2=ja1+r1-l1;
            ll jo1=ja2+add, jo2=jo1+r-l;
            st.move(l, r, l1, r1);
            st.Reverse(ja1, ja2);
            st.Reverse(jo1, jo2);
            st.AddRange(ja1, ja2, 1);
            st.AddRange(jo1, jo2, 1);
        }
        string cur;
        FER(i,0,sz(s)){
            ll ans=st.que(i, i+1);
            cur+=m1[ans%26];
        }
        cout<<cur<<endl;
    }
    return 0;
}