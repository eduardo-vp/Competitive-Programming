
int number_of_trailing_zeros(int x) {
  int ans = 0;
  for (int i = 5; i <= x; i *= 5) {
    ans += x / i;
  }
  return ans;
}

int base[] = {1, 1, 2, 6, 4}; // base[x] = x! % 10
int pmod[] = {2, 4, 8, 6}; // pmod[x] = (2 ^ x) % 10

int f(int x) {
  if (x < 5) return base[x];
  int d = x / 5;
  return (f(d) * pmod[(d - 1) % 4] * base[x % 5]) % 10;
}

int rightmost_non_zero_digit(int x) {
  return f(x);
}

