

ll dist(ii a, ii b){
  a.first -= b.first; a.second -= b.second;
  return ll(a.first)*a.first + ll(a.second)*a.second;
}

ll dot(ii o, ii a, ii b){
  return ll(a.first-o.first)*(b.first-o.first)
      + ll(a.second-o.second)*(b.second-o.second);
}

ll cross(ii o, ii a, ii b){
  return ll(a.first-o.first)*(b.second-o.second)
      - ll(a.second-o.second)*(b.first-o.first);
}

vector<ii> convexHull(vector<ii> &P){
  sort(P.begin(),P.end());
  P.erase(unique(P.begin(),P.end()),P.end());
  int n = sz(P);
  if(n == 1) return P;

  vector<ii> bot = {P[0]};
  FOR(i,1,n){
    while(sz(bot) > 1 and cross(bot[sz(bot)-2],bot.back(),P[i]) <= 0)
      bot.pop_back();
    bot.pb(P[i]);
  }
  bot.pop_back();

  vector<ii> up = {P[n-1]};
  for(int i = n-1; i >= 0; --i){
    while(sz(up) > 1 and cross(up[sz(up)-2],up.back(),P[i]) <= 0)
      up.pop_back();
    up.pb(P[i]);
  }
  up.pop_back();
  bot.insert(bot.end(),up.begin(),up.end());
  return bot;
}
