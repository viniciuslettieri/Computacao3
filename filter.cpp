// NEEDS C++17 TO COMPILE

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <type_traits>
#include <functional>

using namespace std;


// -----------------------------------------------------
// Applies a stream or filter to a list or iterable
// if f returns bools, behaves like filter
// if not, behaves like stream


// first template for the filter (when fprim is bool)
template< typename fprim, typename tprim, typename T, typename T2 >

std::enable_if_t< std::is_same< bool, fprim >::value, std::vector<tprim> > 
operador_pipe( const T &a, T2 f ) {
    std::vector< tprim > saida;
    for( auto elem : a ){
        std::enable_if_t< std::is_same< bool, fprim >::value, bool > retorno = std::invoke( f, elem );
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
        std::invoke( f, elem );
    }
}

// third template for the stream (when fprim is not bool nor void)
template< typename fprim, typename tprim, typename T, typename T2 >

std::enable_if_t< !( std::is_same< bool, fprim >::value ) && !( std::is_void< fprim >::value ), std::vector< fprim > > 
operador_pipe( const T &a, T2 f ) {
    std::vector< fprim > saida;
    for( auto elem : a ){
        saida.push_back( std::invoke( f, elem ) );
    }
    return saida;
}

// pipe operator that behaves like stream or filter depending on 'f' return type
template< typename T, typename T2 >
auto operator | ( const T &a, T2 f ) {
    auto prim = *( std::begin( a ) );

    return operador_pipe< std::invoke_result_t< decltype( f ), decltype( prim ) >, decltype( prim ), T, T2 > ( a, f );
}


// -----------------------------------------------------


template <typename T> 
void myPrint( T t ) {
    cout << t << " ";
}

struct PrintM {
  void operator() ( vector<int> v ) {
      cout << "[ " << v[0] << ", " << v[1] << " ] ";
  }
};

struct PrintM2 {
  void operator() ( vector<int> v ) {
      v | myPrint<int>;
  }
};

string StringToUpper(string strToConvert)
{
   for (std::string::iterator p = strToConvert.begin(); strToConvert.end() != p; ++p)
       *p = toupper(*p);

   return strToConvert;
}

struct PrintM3 {
    void operator()( string st ) {
        cout << StringToUpper( st ) << " ";
    }
};

int main( int argc, char* argv[]) {
    int caso = 0;
    double v = 0;

    cout << "Testes do professor" << endl;

    vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
    auto result = v1 | []( int x ) { return x % 2 == 0; };
    for( auto x : result )
        cout << x << " ";

    cout << endl;

    map<string,string> vk = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" } };
    vk | []( auto x ){ return pair{ x.first, stod( x.second ) }; } | []( auto p ) { cout << p.second + 1.1 << " "; };

    cout << endl;

    vector<string> v2 = { "janeiro", "fevereiro", "março", "abril", "maio" };
    v2 | &string::length | [] ( int x ) { cout << x << " "; };

    cout << "Outros testes" << endl;

    cin >> caso >> v;

    switch( caso ) {
        case 0: {
            int vetor[] = {1, 2, 3, 4, 5, 6};
            vetor | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << endl; };
            cout << "end " << endl;
            break;
        }

        case 1: {
            vector<int> v1 = { 2, 9, 8, 8 };
            vector<string> v2 = { "jose", "casado" };
            vector<double> v3 = { 3.11, 5, 7.9 };
            
            v1 | []( int n ){ cout << n << " "; };
            cout << endl;
            v2 | []( string n ){ cout << n << " "; };
            cout << endl;
            v3 | []( double n ){ cout << n << " "; };
            cout << endl;
            break;
        }

        case 2: {
            int tabInt[] = { 1, 5, 9, 3 };
            double tabDouble[] = { 3.1, 5.3, 9 };
            string tabString[] = { "a", "e", "i", "o", "u", "ypsilon" };
            
            tabInt | []( int n ){ cout << n << " "; };
            cout << endl;
            tabDouble | []( double n ){ cout << n << " "; };
            cout << endl;
            tabString | []( string n ){ cout << n << " "; };
            cout << endl;
            break;
        }

        case 3: {
            vector<int> v1 = { 1, 9, 5, 8 };
            vector<string> v2 = { "joao", "Solteiro" };
            vector<double> v3 = { 3.14, 999, 7.9, 900 };
            
            v1 | myPrint<int>;
            cout << endl;
            v2 | myPrint<string>;
            cout << endl;
            v3 |  myPrint<double>;
            cout << endl;
            break;
        }
        
        case 4: {
            vector<vector<int>> m = { { 1, 2 }, { 4, 6 }, { 6, 7 } };
            string tab[] = { "hello,", "world" };
            
            m | PrintM();
            cout << endl;
            m | PrintM2();
            cout << endl;
            tab | PrintM3();
            break;
        }

        case 5: {
            auto x = { 1, 2, 3 };
            x | []( int x ) { cout << x*x << " "; };
            break;
        }
    }
  
  return 0;
}
