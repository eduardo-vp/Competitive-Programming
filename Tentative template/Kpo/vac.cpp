#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using namespace __gnu_pbds;
#define all(v) (v).begin(),(v).end()
#define pb(x) push_back(x)
#define REP(i,x,y) for(int (i)=(x);(i)<(y);(i)++)
#define REPIT(it,A) for(typeof(A.begin()) it = (A.begin()); it!=A.end();it++)
#define sqr(x) ((x)*(x))
#define mp(x,y) make_pair((x),(y))
#define fast_io() ios_base::sync_with_stdio(0);cin.tie(0); 
#define NDEBUG 1
#ifdef NDEBUG
#define debug(x)
#else
#define debug(x) cerr << #x << ": " << x << endl;
#endif
#ifdef NDEBUG
#define wbug(x)
#else
#define wbug(x) cerr << x;
#endif
#define fst first
#define snd second
#define itm1 fst.fst
#define itm2 fst.snd
#define itm3 snd
#define mt(a,b,c) mp(mp(a,b),c)
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ii, int> tri;
typedef unsigned int ui;
typedef tree<int, null_type, less<int>, rb_tree_tag, 
         tree_order_statistics_node_update> ordered_set;

const double PI = acos(-1);
const double E = 2.718281828459;
const double INF = 1e32;
const double EPS = 1e-10;


// ---------------------------------------------------------------------------------------------------------
// Part 1: Input and graph buliding
// ---------------------------------------------------------------------------------------------------------
int n, m; // Number of rooms and corridors respectively

map<string, int> toId; // Get id for room name s
string toName[10]; // Get name for room v

double tv[10];  // Time to clean room v
double te[20];  // Time to clean corridor e
vector<ii> adj[10]; // Room graph. Elements are (v, e)

int FULL; // Full mask (all corridors clean)

void init(){
  cin >> n >> m;
  string s;
  
  REP(i,0,n){
    cin >> s >> tv[i];
    toId[s] = i;
    toName[i] = s;
    adj[i].clear();
  }

  FULL = (1 << m) -1;

  string s2;
  REP(i,0,m){
    cin >> s >> s2 >> te[i];
    int u = toId[s];
    int v = toId[s2];
    adj[u].pb(mp(v, i));
    adj[v].pb(mp(u, i));
  }
}
// ---------------------------------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------------------------------
// Part 2: Building the graph for the state transitions (which may contain cycles)
// ---------------------------------------------------------------------------------------------------------

int stgid;  // maximum state id for the ones built
int nst;
map<int, int> stid[10]; // id of the state (u, msk)
vector<ii> stadj[2200000];  // State graph. Elements are (st, e)
int nodeOf[2200000]; // node of state i
int mskOf[2200000]; // mask of state i

void print(ostream& ss, ii pr){
  ss << "(" << pr.fst << "," << pr.snd << ")";
}

// Builds the graph for states which stem from state (u,msk)
void build(int u, int msk){
  if (stid[u].count(msk)) return;
  stadj[stgid].clear();
  int st1 = stgid;
  nodeOf[stgid] = u;
  mskOf[stgid] = msk;
  stid[u][msk] = stgid++;

  REP(i,0,adj[u].size()){
    int v = adj[u][i].fst;
    int e = adj[u][i].snd;
    build(v, msk | (1 << e));
    
    int st2 = stid[v][msk | (1<<e)];
    stadj[st1].pb(mp(st2, e));
  }
}


void build(){
  stgid = 0;
  REP(i,0,n) stid[i].clear();

  REP(i,0,n) build(i, 0);
  
  nst = stgid;

  #ifndef NDEBUG
  REP(i,0,nst){
    cerr << "State " << i << endl;
    cerr << "\tNode: " << nodeOf[i] << " (" << toName[nodeOf[i]] << "), Msk: " << mskOf[i] << endl;
    cerr << "\tAdj: ";
    REP(j,0,stadj[i].size()) print(cerr, stadj[i][j]); cerr << ", ";
    cerr << endl << endl;
  }
  #endif
}
// ---------------------------------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------------------------------
// Part 3: Finding the SCC of the state graph using tarjan
// ---------------------------------------------------------------------------------------------------------

int gid;            // Current highest node pre value
int pre[2200000];            // Id of visited nodes, 0 for unseen
int lo[2200000];          // Lowest vertex id reachable from state u
stack<int> stk;       // Stack for tarjan's SCC
int onStack[2200000];
int nsc;            // Number of SCC
vector<int> sc[2200000];  // Vector representation of each SCC
int scOf[2200000];      // SCC of state st

vector<int> scadj[2200000]; // Adjacency of SCC to solve dependencies first

int dfs(int u){
  pre[u] = lo[u] = gid++;
  stk.push(u);
  onStack[u] = 1;

  int v;
  REP(i,0,stadj[u].size()){
    v = stadj[u][i].fst;
    if (!pre[v]) {
      dfs(v);
      lo[u] = min(lo[u], lo[v]);
    }
    else if (onStack[v]){
      lo[u] = min(lo[u], pre[v]);
    }
  }

  if (lo[u] == pre[u]){
    sc[nsc].clear();
    do{
      v = stk.top(); 
      stk.pop();
      onStack[v] = 0;
      sc[nsc].pb(v);
      scOf[v] = nsc;
    } while (v != u);
    nsc++;
  }
}

void findscc(){
  REP(i,0,stgid) pre[i] = 0;
  nsc = 0;
  gid = 1;
  while (!stk.empty()) stk.pop();
  REP(i,0,nst) if (!pre[i]) dfs(i);

  REP(i,0,nsc){
    scadj[i].clear();
    set<int> curr;
    REP(j,0,sc[i].size()){
      int u = sc[i][j];
      REP(k,0,stadj[u].size()){
        int v = stadj[u][k].fst;
        curr.insert(scOf[v]);
      } 
    }
    curr.erase(i);
    REPIT(it, curr) scadj[i].pb(*it);
  }

  #ifndef NDEBUG
  cerr << "---------------------------------" << endl;
  cerr << "Components for state transitions:" << endl;
  cerr << "---------------------------------" << endl;
  REP(i,0,nsc){
    cerr << "Component " <<  i << ":" << endl;
    cerr << "\t States: "; REP(j,0,sc[i].size()) cerr << sc[i][j] << ", ";
    cerr << endl;
    cerr << "\t Adj: "; REP(j,0,scadj[i].size()) cerr << scadj[i][j] << ", ";
    cerr << endl << endl;
  }
  cerr << endl;
  #endif
}

// ---------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------
// Gauss-Jordan elimination in O(n^3) with full pivoting.
//
// INPUT:    a[][] = an nxn matrix
//           b[][] = an nxm matrix
//
// OUTPUT:   X      = an nxm matrix (stored in b[][])
//           A^{-1} = an nxn matrix (stored in a[][])
//           returns determinant of a[][]

typedef double T;
typedef vector<T> vt;
typedef vector<vt> vvt;

T GaussJordan(vvt &a, vvt &b) {
  const int n = a.size();
  const int m = b[0].size();
  vi irow(n), icol(n), ipiv(n);
  T det = 1;

  for (int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for (int j = 0; j < n; j++) if (!ipiv[j])
      for (int k = 0; k < n; k++) if (!ipiv[k])
   if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
    if (fabs(a[pj][pk]) < EPS) { cerr << "Matrix is singular." << endl; exit(0); }
    ipiv[pk]++;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk) det *= -1;
    irow[i] = pj;
    icol[i] = pk;

    T c = 1.0 / a[pk][pk];
    det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for (int p = 0; p < n; p++) a[pk][p] *= c;
    for (int p = 0; p < m; p++) b[pk][p] *= c;
    for (int p = 0; p < n; p++) if (p != pk) {
      c = a[p][pk];
      a[p][pk] = 0;
      for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
      for (int q = 0; q < m; q++) b[p][q] -= b[pk][q] * c;      
    }
  }

  for (int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
    for (int k = 0; k < n; k++) swap(a[k][irow[p]], a[k][icol[p]]);
  }

  return det;
}

// ---------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------
// Part 4: Getting the expected time for each state 
// ---------------------------------------------------------------------------------------------------------

vector<int> ans;  // optimal starting nodes
double best;
int ok[2200000]; // linear system for component i has been solved

double dp[2200000]; // expected time for state i


// Solve this component's children, then this component.
void solve(int scu){
  REP(i,0,scadj[scu].size()){
    int scv = scadj[scu][i];
    if (!ok[scv]) solve(scv);
  }
  
  int msk = mskOf[sc[scu][0]];

  #ifndef NDEBUG
  cerr << "Solved all children of component " << scu << endl;
  cerr << "Mask: " << msk << " (full is " << FULL << ")" << endl;
  #endif

  if (msk == FULL){
    REP(i,0,sc[scu].size()) {
      int st = sc[scu][i];
      int v = nodeOf[st];
      if (adj[v].size() == 1) dp[st] = tv[v];
      else dp[st] = 0;
    }
    ok[scu] = 1;

    #ifndef NDEBUG
    cerr << "Final times:" << endl;
    REP(i,0,sc[scu].size()){
      int st = sc[scu][i];
      cerr << "\tState " << st << ": " << dp[st] << endl;
    }
    cerr << endl << endl;
    #endif
    return;
  }

  int r = sc[scu].size();

  vvt a(r);
  vvt b(r);


  REP(i,0,r) {
    a[i] = vt(r);
    b[i] = vt(1);
    
    int st = sc[scu][i];
    int e = stadj[st].size();
     
    REP(j,0,r) a[i][j] = 0;
    REP(k,0,e)
      REP(j,0,r) 
        if (sc[scu][j] == stadj[st][k].fst) a[i][j] = (-1.0)/double(e);
    a[i][i] = 1;

    int u = nodeOf[st];
    b[i][0] = tv[u];

    REP(k,0,e){
      int edg = stadj[st][k].snd;
      int st2 = stadj[st][k].fst;
      b[i][0] += (dp[st2] + te[edg])/double(e);
    }
  }

  #ifndef NDEBUG
  cerr.setf(ios::showpos);
  cerr.setf(ios::fixed);
  cerr << setprecision(2);
  cerr << "Matrices:" << endl;
  REP(i,0,r) {
    REP(j,0,r) cerr << a[i][j] << " ";
    cerr << "\t|\t" << b[i][0] << endl;
  }
  cerr << endl;
  #endif

  GaussJordan(a,b);

  REP(i,0,r){
    int st = sc[scu][i];
    dp[st] = b[i][0];
  }

  #ifndef NDEBUG
  cerr << "Final times:" << endl;
  REP(i,0,sc[scu].size()){
    int st = sc[scu][i];
    cerr << "\tState " << st << ": " << dp[st] << endl;
  }
  cerr << endl << endl;
  #endif

  ok[scu] = 1;
}


void go(){

  #ifndef NDEBUG
  cerr << "---------------------" << endl;
  cerr << "Solving components:" << endl;
  cerr << "--------------------" << endl << endl;
  #endif

  REP(i,0,nsc) ok[i] = 0;
  REP(i,0,nsc) if (!ok[i]) solve(i); 

  #ifndef NDEBUG
  cerr << "------------------------" << endl;
  cerr << "Finding best positions" << endl;
  cerr << "------------------------" << endl;
  #endif

  ans.clear();
  best = INF;
  REP(u,0,n){
    int st = stid[u][0];
    
    #ifndef NDEBUG
    cerr << "State " << st << " (starting at node " << u << ", ";
    cerr << toName[u] << "): " << dp[st] << endl;
    #endif

    if (dp[st] < best - EPS){
      best = dp[st];
      ans.clear();
      ans.pb(u);
    }
    else if (dp[st] < best + EPS) ans.pb(u);
  }
}


// ---------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------
// Part 5: Printing the output in the desired format 
// ---------------------------------------------------------------------------------------------------------

set<string> zz;

void show(){
  zz.clear();
  REP(i,0,ans.size()) zz.insert(toName[ans[i]]);
  int flg = 0;

  cout.setf(ios::fixed);
  cout << setprecision(9);
  
  REPIT(it, zz){
    if (flg) cout << " ";
    flg = 1;
    cout << *it;
  }
  cout << endl;
  cout << best << endl;
} 


// ----------------------------------------------------------------------------------------------------------

int main(){
  fast_io();
  
  init();
  build();
  findscc();
  go();
  show();

  return 0;
}
