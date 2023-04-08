
// returns d = gcd(a,b); finds x, y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
  int xx = y = 0;
  int yy = x = 1;
  while (b) {
    int q = a / b;
    int t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}

// let phi(x) = number of integers y < x such that gcd(x, y) = 1
// let p1, p2, ..., pk be the distinct primes dividing x, then
// phi(x) = x * (1 - (1 / p1)) * (1 - (1 / p2)) * ... * (1 - (1 / pk))

int phi(int x) {
  int ans = x;
  // primes[x] = primes that divide x
  for (int p: primes[x]) {
    ans -= ans / p;
  }
  return ans;
}
