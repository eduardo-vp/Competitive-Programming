#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> X;
// El primer parametro int es el tipo de dato del set
// El segundo parametro es null_type para set, u otro tipo para map. Por ejemplo tree<string,int,...> es un map<string,int>
// El tercer parámetro es la función de comparación, por defecto usar less<T>
// El cuarto y el quinto se ponen como están
// soportan las operaciones *x.find_by_order(k); x.order_of_key(key);
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> kset;

/*Implementacion usada para el subregional de Moscow 2008*/
template <class T> struct ord{
  bool operator() (const ii &x, const ii& y) const{
    if(x.fst != y.fst)
      return x.fst > y.fst;
    return x.snd < y.snd;
  }
};

typedef tree< ii,string, ord<ii>,rb_tree_tag, tree_order_statistics_node_update> kset;
