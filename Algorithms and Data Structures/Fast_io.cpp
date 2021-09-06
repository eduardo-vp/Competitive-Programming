
template<class num> inline void rd(num &x) {
  char c;
  while(isspace(c = getchar()));
  bool neg = false;
  if(!isdigit(c)) neg = (c == '-'), x = 0;
  else x = c - '0';
  while(isdigit(c = getchar()))
    x = (x << 3) + (x << 1) + c - '0';
  if(neg) x = -x;
}
