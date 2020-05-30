
// Usage:
// Node* x[N];
// for(int i = 0; i < n; ++i)
//   x[i] = new Node();
// connect a,b -> link(x[a], x[b])
// cut a,b -> cut(x[a], x[b])
// check connectivity -> connected(x[a], x[b])

struct Node{
  bool rev;
  Node *l, *r, *p;
  Node() : rev(0), l(0), r(0), p(0){ }
  bool isRoot(){ return !p || (p->l != this && p->r != this);}
  void push(){
    if(rev){
      rev = 0;
      swap(l, r);
      if(l) l->rev = !l->rev; 
	  if(r) r->rev = !r->rev;
    }
  }
};

void connect(Node *ch, Node *p, int isLeftChild){
  if(ch) ch->p = p; 
  if(isLeftChild < 0) return;
  if(isLeftChild) p->l = ch; 
  else p->r = ch;
}

void rotate(Node *x){
  Node *p = x->p, *g = p->p;
  bool isRootP = p->isRoot(), leftChildX = (x == p->l);
  connect(leftChildX ? x->r : x->l, p, leftChildX);
  connect(p, x, !leftChildX);
  connect(x, g, isRootP ? -1 : (p == g->l));
}

void splay(Node *x){
  while(!x->isRoot()){
    Node *p = x->p, *g = p->p;
    if(!p->isRoot()) g->push();
    p->push(); 
	x->push();
    if(!p->isRoot()) rotate((x == p->l) == (p == g->l) ? p : x);
    rotate(x);
  }
  x->push();
}

Node* expose(Node *x){
  Node *last = 0;
  for(Node *y = x; y; y = y->p) 
  	splay(y), y->l = last, last = y;
  splay(x);
  return last;
}

void makeRoot(Node *x){
	expose(x); 
	x->rev = !x->rev;
}

bool connected(Node *x, Node *y){
	if(x == y) return true; 
	expose(x); 
	expose(y); 
	return x->p != 0;
}

void link(Node *x, Node *y){
	makeRoot(x); 
	x->p = y;
}

void cut(Node *x, Node *y){
  makeRoot(x); 
  expose(y); 
  y->r->p = 0; 
  y->r = 0;
}
