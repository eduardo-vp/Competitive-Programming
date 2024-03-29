
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
 
class node {
  public:
  int id;
  node* l;
  node* r;
  node* p;
  bool rev;
  int sz;
  // declare extra variables:
  int P;
 
  node(int _id) {
    id = _id;
    l = r = p = NULL;
    rev = false;
    sz = 1;
    // init extra variables:
    P = rng();
  }
 
  void unsafe_reverse() {
    rev ^= 1;
    swap(l, r);
    pull();
  }
 
  // apply changes:
  void unsafe_apply() {
    
  }
 
  void push() {
    if (rev) {
      if (l != NULL) {
        l->unsafe_reverse();
      }
      if (r != NULL) {
        r->unsafe_reverse();
      }
      rev = 0;
    }
    // now push everything else:
 
  }
 
  void pull() {
    sz = 1;
    // now init from self:
 
    if (l != NULL) {
      l->p = this;
      sz += l->sz;
      // now pull from l:
 
    }
    if (r != NULL) {
      r->p = this;
      sz += r->sz;
      // now pull from r:
 
    }
  }
};
 
void debug_node(node* v, string pref = "") {
  #ifdef LOCAL
    if (v != NULL) {
      debug_node(v->r, pref + " ");
      cerr << pref << "-" << " " << v->id << '\n';
      debug_node(v->l, pref + " ");
    } else {
      cerr << pref << "-" << " " << "NULL" << '\n';
    }
  #endif
}
 
namespace treap {
  pair<node*,int> find(node* v, const function<int(node*)> &go_to) {
    // go_to returns: 0 -- found; -1 -- go left; 1 -- go right
    // find returns the last vertex on the descent and its go_to
    if (v == NULL) {
      return {NULL, 0};
    }
    int dir;
    while (true) {
      v->push();
      dir = go_to(v);
      if (dir == 0) {
        break;
      }
      node* u = (dir == -1 ? v->l : v->r);
      if (u == NULL) {
        break;
      }
      v = u;
    }
    return {v, dir};
  }
 
  node* get_leftmost(node* v) {
    return find(v, [&](node*) { return -1; }).first;
  }
 
  node* get_rightmost(node* v) {
    return find(v, [&](node*) { return 1; }).first;
  }
 
  node* get_kth(node* v, int k) { // 0-indexed
    pair<node*,int> p = find(v, [&](node* u) {
      if (u->l != NULL) {
        if (u->l->sz > k) {
          return -1;
        }
        k -= u->l->sz;
      }
      if (k == 0) {
        return 0;
      }
      k--;
      return 1;
    });
    return (p.second == 0 ? p.first : NULL);
  }
 
  int get_position(node* v) { // 0-indexed
    int k = (v->l != NULL ? v->l->sz : 0);
    while (v->p != NULL) {
      if (v == v->p->r) {
        k++;
        if (v->p->l != NULL) {
          k += v->p->l->sz;
        }
      }
      v = v->p;
    }
    return k;
  }
 
  node* get_bst_root(node* v) {
    while (v->p != NULL) {
      v = v->p;
    }
    return v;
  }
 
  pair<node*,node*> split(node* v, const function<bool(node*)> &is_right) {
    if (v == NULL) {
      return {NULL, NULL};
    }
    v->push();
    if (is_right(v)) {
      pair<node*,node*> p = split(v->l, is_right);
      if (p.first != NULL) {
        p.first->p = NULL;
      }
      v->l = p.second;
      v->pull();
      return {p.first, v};
    } else {
      pair<node*,node*> p = split(v->r, is_right);
      v->r = p.first;
      if (p.second != NULL) {
        p.second->p = NULL;
      }
      v->pull();
      return {v, p.second};
    }
  }
 
  pair<node*,node*> split_left(node* v, int k) {
    return split(v, [&](node* u) {
      int left_and_me = (u->l != NULL ? u->l->sz : 0) + 1;
      if (k >= left_and_me) {
        k -= left_and_me;
        return false;
      }
      return true;
    });
  }
 
  node* merge(node* v, node* u) {
    if (v == NULL) {
      return u;
    }
    if (u == NULL) {
      return v;
    }
    if (v->P > u->P) {
      v->push();
      v->r = merge(v->r, u);
      v->pull();
      return v;
    } else {
      u->push();
      u->l = merge(v, u->l);
      u->pull();
      return u;
    }
  }
 
  node* add(node* r, node* v, const function<bool(node*)> &go_left) {
    pair<node*,node*> p = split(r, go_left);
    return merge(p.first, merge(v, p.second));
  }
 
  node* remove(node* v) { // returns the new root
    v->push();
    node* x = v->l;
    node* y = v->r;
    node* p = v->p;
    v->l = v->r = v->p = NULL;
    v->push();
    v->pull(); // now v might be reusable...
    node* z = merge(x, y);
    if (p == NULL) {
      if (z != NULL) {
        z->p = NULL;
      }
      return z;
    }
    if (p->l == v) {
      p->l = z;
    }
    if (p->r == v) {
      p->r = z;
    }
    while (true) {
      p->push();
      p->pull();
      if (p->p == NULL) {
        break;
      }
      p = p->p;
    }
    return p;
  }
 
  node* next(node* v) {
    if (v->r == NULL) {
      while (v->p != NULL && v->p->r == v) {
        v = v->p;
      }
      return v->p;
    }
    v->push();
    v = v->r;
    while (v->l != NULL) {
      v->push();
      v = v->l;
    }
    return v;
  }
 
  node* prev(node* v) {
    if (v->l == NULL) {
      while (v->p != NULL && v->p->l == v) {
        v = v->p;
      }
      return v->p;
    }
    v->push();
    v = v->l;
    while (v->r != NULL) {
      v->push();
      v = v->r;
    }
    return v;
  }
 
  int get_size(node* v) {
    return (v != NULL ? v->sz : 0);
  }
 
  template<typename... T>
  void apply(node* v, T... args) {
    v->unsafe_apply(args...);
  }
 
  void reverse(node* v) {
    v->unsafe_reverse();
  }
}
 
using namespace treap;
