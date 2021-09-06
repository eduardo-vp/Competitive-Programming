#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
using namespace std;
#define LIM 3000000
const double two_pi = 4 * acos(0);
typedef complex<double> cpx;

cpx a[LIM] , b[LIM],A[LIM] , B[LIM],AB[LIM] , aconvb[LIM];

cpx EXP(double theta)
{
  return cpx(cos(theta),sin(theta));
  //return polar(1.0,theta);
}

// in:     input array
// out:    output array
// step:   {SET TO 1} (used internally)
// size:   length of the input/output {MUST BE A POWER OF 2}
// dir:    either plus or minus one (direction of the FFT)
// RESULT: out[k] = \sum_{j=0}^{size - 1} in[j] * exp(dir * 2pi * i * j * k / size)
void FFT(cpx *in, cpx *out, int step, int size, int dir)
{
  if(size < 1) return;
  if(size == 1)
  {
    out[0] = in[0];
    return;
  }
  FFT(in, out, step * 2, size / 2, dir);
  FFT(in + step, out + size / 2, step * 2, size / 2, dir);
  for(int i = 0 ; i < size / 2 ; i++)
  {
    cpx even = out[i];
    cpx odd = out[i + size / 2];
    out[i] = even + EXP(dir * two_pi * i / size) * odd;
    out[i + size / 2] = even + EXP(dir * two_pi * (i + size / 2) / size) * odd;
  }
}
// To compute h[] in O(N log N) time, do the following:
//   1. Compute F and G (pass dir = 1 as the argument).
//   2. Get H by element-wise multiplying F and G.
//   3. Get h by taking the inverse FFT (use dir = -1 as the argument)
//      and *dividing by N*. DO NOT FORGET THIS SCALING FACTOR.


int main() {
  //Agregar ceros si tam no es potencia de 2
  
  FFT(a,A,1,tam,1); // PASO 1
  FFT(b,B,1,tam,1); // PASO 1
 
  
  for(int i = 0 ; i < tam ; i++){   //PASO 2
      AB[i] = A[i] * B[i];      //PASO 2
  }
  
    FFT(AB, aconvb, 1, tam, -1);    //PASO 3    
  
  for(int i=0;i<tam;i++)    {       //PASO 3
    aconvb[i] = aconvb[i]/(1.0*tam);    //PASO 3
  }
  for(int i=0;i<tam;i++){
    cout<<aconvb[i].real()<<" ";
  }
  return 0;
}