// https://codeforces.com/contest/444/submission/80618651

struct Range {
    Range(int l = 0) { this->l = l; }
    Range(int l, int r, int v) {
      this->l = l;
      this->r = r;
      this->v = v;
    }
    int l=0, r=0;
    int v=0;
 
    bool operator < (const Range &b) const { return l < b.l; }
  };
class ColorUpdate {
public:
  
 
  std::set<Range> ranges;
  // RANGES IN THE FORM [l,r) !!!
  std::vector<Range> upd(int l, int r, int v) {
    std::vector<Range> ans;
    if(l >= r) return ans;
    auto it = ranges.lower_bound(l);
    if(it != ranges.begin()) {
      it--;
      
      if(it->r > l) {
        auto cur = *it;
        ranges.erase(it);
        ranges.insert(Range(cur.l, l, cur.v));
        ranges.insert(Range(l, cur.r, cur.v));
 
      }
    }
    it = ranges.lower_bound(r);
    if(it != ranges.begin()) {
      it--;
      
      if(it->r > r) {
        auto cur = *it;
        ranges.erase(it);
        ranges.insert(Range(cur.l, r, cur.v));
        ranges.insert(Range(r, cur.r, cur.v));
      }
    }
    for(it = ranges.lower_bound(l); it != ranges.end() && it->l < r; it++) {
    
      ans.push_back(*it);
    }
    ranges.erase(ranges.lower_bound(l), ranges.lower_bound(r));
    ranges.insert(Range(l, r, v));
 
    return ans;
  }
private:
};
