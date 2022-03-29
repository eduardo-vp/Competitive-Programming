
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// for 64 bit
//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){

  cout << rng() << endl;
  
  vector<int> perm(10);
  iota(perm.begin(), perm.end(), 0);
  shuffle(perm.begin(),perm.end(),rng);
   
  // measure time
  auto cl_start = clock();
  while( (clock()-cl_start)<=2.7*CLOCKS_PER_SEC ){  
    // do sth 
  }
  
  // gen random integer in [0,100]
  int x = uniform_int_distribution<int>(0, 100)(rng);
  
  return 0;
}
