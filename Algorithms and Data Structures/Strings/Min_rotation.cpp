
// shifts strings or vectors

// finds the point to shift s to make it its lexicographical smallest cyclic shift
int min_rotation(string s) {
  int a = 0, n = s.size();
  s += s;
  for (int b = 0; b < n; ++b) for (int i = 0; i < n; ++i) {
    if (a + i == b || s[a + i] < s[b + i]) { b += max(0, i - 1); break; }
    if (s[a + i] > s[b + i]) { a = b; break; }
  }
  return a;
}


// rotates v
string rot_min(string s) {
  int x = min_rotation(s);
  rotate(s.begin(), s.begin() + x, s.end());
  return s;
}
