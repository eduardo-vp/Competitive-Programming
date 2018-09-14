#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <bitset>
#include <queue>
#include <list>
#include <vector>
#include <climits>
#include <map>
#include <set>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#define FOR(i,A) for(typeof (A).begin() i = (A).begin() ; i != (A).end() ; i++)
#define f(i,a,b) for(int i = a ; i < b ; i++)
#define fd(i,a,b) for(int i = a ; i >= b ; i--)
#define debug( x ) cout << #x << " = " << x << endl
#define clr(v,x) memset( v, x , sizeof v )
#define all(x) (x).begin() , (x).end()
#define mp make_pair
#define rall(x) (x).rbegin() , (x).rend()
#define PI acos( -1.0 )
#define EPS 1E-9
#define TAM 210
  
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
int A[TAM][TAM];
// Implementation of Kadane's algorithm for 1D array. The function returns the
// maximum sum and stores starting and ending indexes of the maximum sum subarray
// at addresses pointed by start and finish pointers respectively.
int kadane(int* arr, int* start, int* finish, int n)
{
    // initialize sum, maxSum and
    int sum = 0, maxSum = INT_MIN, i;
 
    // Just some initial value to check for all negative values case
    *finish = -1;
 
    // local variable
    int local_start = 0;
 
    f(i,0,n) {
        sum += arr[i];
        if (sum < 0)
        {
            sum = 0;
            local_start = i+1;
        }
        else if (sum > maxSum)
        {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }
 
     // There is at-least one non-negative number
    if (*finish != -1)
        return maxSum;
 
    // Special Case: When all numbers in arr[] are negative
    maxSum = arr[0];
    *start = *finish = 0;
 
    // Find the maximum element in array
    for (i = 1; i < n; i++)
    {
        if (arr[i] > maxSum)
        {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }
    return maxSum;
}
 
int main() {
     int t,n;//numero de casos
   	 scanf("%d",&n);
     	f(left,0,n){
     		f(right,0,n){
     			scanf("%d",&A[left][right]);
     		}
     	}
     	//procedimiento para el calculo del MAX 2D-SUM
     	int max_sum=INT_MIN,final_top,final_bottom,final_left,final_right;
        int temp[n+1];int sum, start, finish;
     	f(left,0,n){
     		//inicializo temp a 0
     		clr(temp,0);
     		f(right,left,n){
     			// Calculate sum between current left and right for every row 'i'
                f(k,0,n) temp[k] += A[k][right];
                // Find the maximum sum subarray in temp[]. The kadane() function
                // also sets values of start and finish.  So 'sum' is sum of
                // rectangle between (start, i) and (finish, j) which is the
                //  maximum sum with boundary columns strictly as i and j.
                sum = kadane(temp, &start, &finish, n);
                // Compare sum with maximum sum so far. If sum is more, then update
	            // maxSum and other output values
	            if (sum > max_sum)
	            {
	                max_sum = sum;
	                final_left = left;
	                final_right = right;
	                final_top = start;
	                final_bottom = finish;
	            }
     		}
     	}
     	// Print final values
	    //printf("(Top, Left) (%d, %d)\n", final_top, final_left);
	    //printf("(Bottom, Right) (%d, %d)\n", final_bottom, final_right);
	    printf("%d\n", max_sum);
     
    return 0;
}