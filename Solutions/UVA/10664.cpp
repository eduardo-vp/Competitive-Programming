#include <bits/stdc++.h>
#define trace(x) cout << #x << " = " << x << endl
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define MOD 1000000
using namespace std;
typedef vector<int> vi;
typedef long long ll;

int obj,n;
bool poss;
vi nums;
bool dp[25][4100];

void backtrack(int idx,int sum){
	if(poss) return;
	if(dp[idx][sum]) return;
	if(sum == obj){
		poss = true;
		return;
	}
	if(idx == n) return;
	if( (sum + nums[idx]) <= obj) backtrack(idx+1,sum+nums[idx]);
	backtrack(idx+1,sum);
	dp[idx][sum] = true;
}

int main(){

	int tc;
	string cad;
	cin >> tc;
	cin.ignore();
	while(tc--){
		getline(cin,cad);
		istringstream iss(cad);
		nums.clear();
		int x;
		int sum = 0;
		while(iss >> x){
			nums.pb(x); sum += x;
		}
		if(sum % 2 != 0){
			cout << "NO" << endl; continue;
		}
		n = (int)nums.size();
		obj = sum / 2;
		poss = false;
		fill(dp,false);
		backtrack(0,0);
		if(poss) cout << "YES" << endl;
		else cout << "NO" << endl;
	}

	return 0;
}