
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <type_traits>

using namespace std;


// -----------------------------------------------------
//                   OLD - FILTER
//
// Applies a stream or filter to a list or iterable
// if f returns bools, behaves like filter
// if not, behaves like stream


// first template for the filter (when fprim is bool)
template< typename fprim, typename tprim, typename T, typename T2 >

std::enable_if_t< std::is_same< bool, fprim >::value, std::vector<tprim> > 
operador_pipe( const T &a, T2 f ) {
    std::vector< tprim > saida;
    for( auto elem : a ){
        std::enable_if_t< std::is_same< bool, fprim >::value, bool > retorno = __invoke( f, elem );
        if( retorno ){
            saida.push_back( elem );
        }
    }
    return saida;
}

// second template for the stream (when fprim is void)
template< typename fprim, typename tprim, typename T, typename T2 >

std::enable_if_t< std::is_void< fprim >::value, void > 
operador_pipe( const T &a, T2 f ) {
    for( auto elem : a ){
        __invoke( f, elem );
    }
}

// third template for the stream (when fprim is not bool nor void)
template< typename fprim, typename tprim, typename T, typename T2 >

std::enable_if_t< !( std::is_same< bool, fprim >::value ) && !( std::is_void< fprim >::value ), std::vector< fprim > > 
operador_pipe( const T &a, T2 f ) {
    std::vector< fprim > saida;
    for( auto elem : a ){
        saida.push_back( __invoke( f, elem ) );
    }
    return saida;
}

// pipe operator that behaves like stream or filter depending on 'f' return type
template< typename T, typename T2 >
auto operator | ( const T &a, T2 f ) {
    auto prim = *( std::begin( a ) );

    return operador_pipe< std::invoke_result_t< decltype( f ), decltype( prim ) >, decltype( prim ), T, T2 > ( a, f );
}

// ========================================================================================================


// Primeiro definimos uma classe que encapsula 
// lambdas para diferenciar das constantes
template<typename F>
class Callable {
    public:
    Callable( F f ): f(f) {}

    auto operator () ( auto v ) const {
        return f(v);
    }

    private:
    F f;
};

// Operador de + para expressões
template< typename A, typename B >
auto operator + ( Callable<A> a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return a(x) + b(x); } }; 
}
template< typename A, typename B >
auto operator + ( Callable<A> a, B b ) {
    return Callable{ [a,b]( auto x ){ return a(x) + b; } }; 
}
template< typename A, typename B >
auto operator + ( A a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return x + b(x); } }; 
}

// Operador de * para expressões
template< typename A, typename B >
auto operator * ( Callable<A> a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return a(x) * b(x); } }; 
}
template< typename A, typename B >
auto operator * ( Callable<A> a, B b ) {
    return Callable{ [a,b]( auto x ){ return a(x) * b; } }; 
}
template< typename A, typename B >
auto operator * ( A a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return x * b(x); } }; 
}

// Operador de % para expressões
template< typename A, typename B >
auto operator % ( Callable<A> a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return a(x) % b(x); } }; 
}
template< typename A, typename B >
auto operator % ( Callable<A> a, B b ) {
    return Callable{ [a,b]( auto x ){ return a(x) % b; } }; 
}
template< typename A, typename B >
auto operator % ( A a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return x % b(x); } }; 
}

// Operador de == para expressões
template< typename A, typename B >
auto operator == ( Callable<A> a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return a(x) == b(x); } }; 
}
template< typename A, typename B >
auto operator == ( Callable<A> a, B b ) {
    return Callable{ [a,b]( auto x ){ return a(x) == b; } }; 
}
template< typename A, typename B >
auto operator == ( A a, Callable<B> b ) {
    return Callable{ [a,b]( auto x ){ return x == b(x); } }; 
}

// Precisamos sobreescrever o << com nosso Callable
template< typename A >
class Print {
    public:
    Print( ostream& o, const Callable<A>& p ) : op( &o ), p(p), b('\0') { }
    Print( Print<A> pr, char b ) : op(pr.op), p(pr.p), b(b) { }

    auto operator() ( auto x ) {
        (*op) << p(x) << b;
    }

    private:
    ostream* op;
    Callable<A> p;
    char b;
};

template< typename A >
auto operator << ( ostream& o, const Callable<A>& p ) {
	return Print<A>( o, p );
}
template< typename A >
auto operator << ( Print<A> m, char s ) {
	return Print<A>( m, s );
}

auto x = Callable{ [](auto x){ return x; } };

int main(){
    

    int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };

    vector<int> v;
    tab | cout << x*x << ' ';
    cout << endl;
    tab | cout << x*(x+5) << ' ';
    cout << endl;
    tab | [ &v ]( int x ) { v.push_back( x ); };
    v | []( int x ) { cout << x << " > "; };
    cout << endl;
    v | x % 2 == 0 | cout << x*x + 1 << ' ';
    cout << endl;
    v | x % 2 == 1 | x*x | cout << x << ' ';
    cout << endl;

    auto f1 = x+x;
    auto f2 = x+3;

    cout << f1(10) << endl;
    cout << f2(10) << endl;


    return 0;
}