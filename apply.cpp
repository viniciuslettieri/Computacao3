#include <type_traits>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>

using namespace std;

double seno( double n ) { return sin(n); }
int id( int n ) { return n; }
int potencia( int n ) { return n*n; }

string roman( int n ) {
    map<int,string> rom = { { 1, "I" }, { 2, "II" }, { 3, "III" }, { 4, "IV" }, { 5, "V" }, { 6, "VI" }, { 7, "VII" }, { 8, "VIII" } } ; 

    return rom[n]; 
}

struct FunctorSimples { 
    string operator()( int n ) { return roman( n ) + "!"; }
};

struct FunctorTemplate { 
    template <typename T>
    T operator()( T n ) { return n+n; }
};

template <typename T>
ostream& operator << ( ostream& o, const std::vector<T>& v ) {
    o << "[ ";
    for( auto x : v )
        o << x << " ";
        
    return o << "]";
}

// -------------------------------------------------

template<typename T>
auto apply( const T &t, auto f ) {
    auto itr = std::begin(t);
    std::vector< decltype( f(*itr) ) > saida;
    for( auto elem : t ){
         saida.push_back( f(elem) );
    }
    return saida;
}

template<typename T, int n>
std::vector<T> apply( const T(& t)[n], auto f ) {
    std::vector< decltype( f(t[0]) ) > saida;
    for( int i=0; i<n; i++ ){
        saida.push_back( f(t[i]) );
    }
    return saida;
}

// ----------------------------------------------------

int main( int argc, char* argv[]) {     
    int t1[] = {1,2,3,4,5,6};
    std::vector<int> r1 = apply( t1, potencia );
    for(auto elem : r1) cout << elem << " ";
    cout << endl;

    std::vector<int> t2{1,2,3,4,5,6};
    std::vector<int> r2 = apply( t2, potencia );
    for(auto elem : r2) cout << elem << " ";
    cout << endl;

    std::vector<int> t3{1,2,3,4,5,6};
    std::vector<string> r3 = apply( t2, roman );
    for(auto elem : r3) cout << elem << " ";
    cout << endl;

    return 0;
}