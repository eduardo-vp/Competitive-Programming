
// SQ * BL > N
// SQ = Block size
// BL = Number of blocks
const int SQ = 2000, N = 1e5 + 100, BL = 52;

int block_id[N];

void update_pos(int pos) {
  // update position
}

void update_block(int pos) {
  // update block
}

T query_pos(int pos) {
  // query pos
}

T query_block(int pos) {
  // query block
}

// interval [l,r)
void update(int l, int r, int x) {
  if (block_id[l] == block_id[r]) {
    for(int i = l; i < r; ++i){
      update_pos();
    }
    return;
  }
  while (l % SQ) {
    update_pos();
    l++;
  }
  while (r % SQ) {
    r--;
    update_pos();
  }
  for (int i = block_id[l]; i < block_id[r]; ++i) {
    update_block();
  }
}

// interval [l,r)
int query(int l, int r) {
  int ans = 0;
  if (block_id[l] == block_id[r]) {
    for (int i = l; i < r; ++i) {
      query_pos();
    }
    return ans;
  }
  while (l % SQ) {
    query_pos();
    l++;
  }
  while (r % SQ) {
    r--;
    query_pos();
  }
  for (int i = block_id[l]; i < block_id[r]; ++i) {
    query_block();
  }
  return ans;
}

int main(){

  fastio;
  for (int i = 0; i < N; ++i) {
    block_id[i] = i / SQ;
  }

  return 0;
}
