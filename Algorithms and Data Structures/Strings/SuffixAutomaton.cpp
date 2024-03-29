
// implementation for lowercase letters only

const int ALPH = 30;

struct state{
  // size: size of the set endpos
  int len, link, size;
  int next[ALPH];
  state() { size = 0; memset(next, -1, sizeof(next)); }
};

struct SuffixAutomaton{
  int cnt, last;
  vector<state> st;
  int f(char ch) { return ch - 'a'; }

  void extend(char ch) {
    int now = cnt++, c = f(ch);
    st[now].size = 1;
    st[now].len = st[last].len + 1;
    int p = last;
    while (p != -1 && st[p].next[c] == -1) {
      st[p].next[c] = now;
      p = st[p].link;
    }
    if (p == -1) {
      st[now].link = 0;
    } else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len) {
        st[now].link = q;
      } else {
        int clone = cnt++;
        st[clone].len = st[p].len + 1;
        st[clone].link = st[q].link;
        for (int i = 0; i < ALPH; ++i) {
          st[clone].next[i] = st[q].next[i];
        }
        while (p != -1 && st[p].next[c] == q) {
          st[p].next[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[now].link = clone;
      }
    }
    last = now;
  }

  SuffixAutomaton(string &s) {
    int n = s.size();
    st.resize(2 * n + 5);
    st[0].len = 0;
    st[0].link = -1;
    cnt = 1;
    last = 0;
    for (char ch : s) {
      extend(ch);
    }
    // build endpos size in O(n)
    // not always necessary
    vector< vector<int> > at(n + 1);
    for (int i = 1; i < cnt; ++i) {
      at[st[i].len].push_back(i);
    }
    for (int len = n; len > 0; --len) {
      for (int u: at[len]) {
        int link = st[u].link;
        st[link].size += st[u].size;
      }
    }
  }
};
