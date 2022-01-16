#include <iostream>
using namespace std;


template<int n, typename T>
class MeioDoProdutoVetorial;

template<int n, typename T>
class Vetor;

template<int n, typename T>
class MeioDoProdutoVetorial {
    public:
        MeioDoProdutoVetorial( const Vetor<n,T>& b ) : b(b) { }
        const Vetor<n, T> b;
};

template<int n, typename T>
class Vetor {
    public:
        // List Initialization
        Vetor( const std::initializer_list<T> l ) {
            // cout << "> Construtor: ";
            int i=0;
            for( auto elem : l){
                vetor[i] = elem;
                i++;
            }
        }
        // Move Constructor
        Vetor( Vetor&& v ) { 
            // cout << "> Move Constructor " << endl;
            for( int i=0; i<n; i++ ) {
                vetor[i] = v.vetor[i];
                i++;
            }
        }
        // Const Constructor
        Vetor( const Vetor& v ) {             
            // cout << "> Const Construtor: ";
            for( int i=0; i<n; i++ ) {
                vetor[i] = v.vetor[i];
            }
        }
        // Empty Constructor
        Vetor() { }

        // Assignment
        Vetor& operator = ( const std::initializer_list<T> l ) {
            // cout << "> Assignment ";
            int i=0;
            for( auto elem : l){
                vetor[i] = elem;
                i++;
            }
            return *this;
        }
        // Move Assignment
        const Vetor& operator = ( Vetor&& v ) {
            // cout << "> Move Assignment "<< endl;
            for(int i=0; i<n; i++){
                vetor[i] = v.vetor[i];
            }           
            return *this;
        }

        // Mathematical Operations
        void adicao( const Vetor<n,T>& a, const Vetor<n,T>& b ) {
            // cout << "> Adicao "<< endl;
            for(int i=0; i<n; i++){
                vetor[i] = a.vetor[i] + b.vetor[i];
            }
        }
        T prod_escalar( const Vetor<n,T>& b ) const {
            // cout << "> Prod Escalar "<< endl;
            T tot = 0;
            for(int i=0; i<n; i++){
                tot += vetor[i] * b.vetor[i];
            }
            return tot;
        }
        void prod_por_escalar( const Vetor<n,T>& a, T b ) {
            // cout << "> Prod por Escalar " << endl;
            for(int i=0; i<n; i++){
                vetor[i] = a.vetor[i] * b;
            }
        }
        void prod_vetorial( const Vetor<n,T>& a, const MeioDoProdutoVetorial<n,T>& b ) {
            // cout << "> Prod Vetorial " << endl;
            vetor[0] = a.vetor[1] * b.b.vetor[2] - a.vetor[2]*b.b.vetor[1];
            vetor[1] = a.vetor[2] * b.b.vetor[0] - a.vetor[0]*b.b.vetor[2];
            vetor[2] = a.vetor[0] * b.b.vetor[1] - a.vetor[1]*b.b.vetor[0];
        }

        void imprime( std::ostream& o ) const {
            o << "[ ";
            for(int i=0; i<n; i++){
                if( i < n-1 )
                    o << vetor[i] << ", ";
                else 
                    o << vetor[i] << " ";
            }
            o << "]";
        }

    private:
        T vetor[n];
};

template<int n, typename T>
std::ostream& operator << ( std::ostream& o, const Vetor<n,T>& v ) {
    v.imprime( o );
    return o;
}

// Simulation of Sum
template<int n, typename T>
Vetor<n,T> operator + ( const Vetor<n,T>& a, const Vetor<n,T>& b ) {
    Vetor<n,T> resultado;
    resultado.adicao( a, b );
    return resultado;
}

// Simulation of Dot Product
template<int n, typename T>
T operator * ( const Vetor<n,T>& a, const Vetor<n,T>& b ) {
    return a.prod_escalar( b );
}

// Simulation of Product by Scalar (both ways)
template<int n, typename T>
Vetor<n,T> operator * ( const Vetor<n,T>& a, T b ) {
    Vetor<n,T> resultado;
    resultado.prod_por_escalar( a, b );
    return resultado;
}
template<int n, typename T>
Vetor<n,T> operator * ( T b, const Vetor<n,T>& a ) {
    Vetor<n,T> resultado;
    resultado.prod_por_escalar( a, b );
    return resultado;
}

// Simulation of Cross Product with ** overload
template<int n, typename T>
MeioDoProdutoVetorial<n,T> operator * ( const Vetor<n,T>& b ) {
    MeioDoProdutoVetorial<n,T> meio = b;
    return meio;
}
template<int n, typename T>
Vetor<n,T> operator * ( const Vetor<n,T>& a, const MeioDoProdutoVetorial<n,T>& b ) {
    Vetor<n,T> resultado;
    resultado.prod_vetorial( a, b );
    return resultado;
}

int main( int argc, char* argv[] ) {
    Vetor< 3, double > a;
    int caso;
    double x, y, z;

    cin >> caso >> x >> y >> z;
    a = { x, y, z };
    Vetor< 3, double > b = { 2, 1, 4 };

    switch( caso ) {
        case 1: cout << a << endl; break;
        case 2: cout << a + b << endl; break;
        case 3: {
            Vetor< 3, double> c;
            c = a ** b; 
            cout << c << endl;
            break; 
        }
        case 4: cout << a * b << endl; break;
        case 5: cout << a * 3.0 << endl; break;
        case 6: cout << 2.1 * a << endl; break;
        case 7: cout << a + b + a * 2.0 << endl; break;
  }
  
  return 0;
}