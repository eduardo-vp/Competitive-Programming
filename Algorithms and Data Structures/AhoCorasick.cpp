#include <bits/stdc++.h>
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define sz(x) int(x.size())
using namespace std;

/* Considerar el tamanho del alfabeto */
/* Implementacion para letras minusculas, mayusculas y numeros entre [0,9] */

const int N = 1e5+20;

inline int f(char ch){
   if(ch >= 'a' and ch <= 'z') return ch - 'a';
   if(ch >= 'A' and ch <= 'Z') return ch - 'A' + 26;
   return ch - '0' + 52;
} 
 
struct AhoCorasick{
   int cnt;
   char pch[N];
   int t[N][65], gt[N][65],link[N],slink[N],p[N];
   int leaf[N];
 
   AhoCorasick(){
      cnt = 1;
      p[0] = 0;
      fill(t,-1);
      fill(gt,-1);
      fill(link,-1);
      fill(slink,-1);
      fill(leaf,-1);
   }
 
   int add_string(string &s, int id){
      int u = 0;
      for(char ch : s){
         int c = f(ch);
         if(t[u][c] == -1){
            t[u][c] = cnt++;
            p[cnt-1] = u;
         }
         u = t[u][c];
         pch[u] = ch;
      }
      leaf[u] = id;
      return u;
   }
 
   int get_link(int v){
      if(link[v] == -1){
         if(!v or !p[v]) link[v] = 0;
         else link[v] = go(get_link(p[v]),pch[v]);
      }
      return link[v];
   }
   
   int go(int v, char ch){
      int c = f(ch);
      if(gt[v][c] == -1){
         if(t[v][c] != -1) gt[v][c] = t[v][c];
         else gt[v][c] = (v == 0) ? 0 : go(get_link(v),ch);
      }
      return gt[v][c];
   }
 
   int get_slink(int u){
      if(slink[u] == -1){
         int lk = get_link(u);
         if(lk == 0) slink[u] = 0;
         else if(leaf[lk] >= 0) slink[u] = lk;
         else slink[u] = get_slink(lk);
      }
      return slink[u];
   }
};
