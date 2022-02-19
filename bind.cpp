#include <iostream>
#include <utility>
#include <type_traits>
#include <array>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

template < typename F, typename... Params >
auto bind( F f, Params... p ) {
    if constexpr ( std::is_invocable< decltype(f), decltype(p)... >::value )
        return __invoke( f, p... );
    else
        return [f, p...]( auto... new_p ){ return bind( f, p..., new_p... ); };
}


void func4( int a, string b, int c, double d ) {
    cout << "Func 4: " << a << b << c << d << endl;
}

int main() {
    auto f3 = bind( func4, 5 );

    f3( "b", 7, 2.1 );
    
    auto f2 = bind( f3, "b" );
    auto f2_a = f3( "b" );
    auto f2_b = f3( "b" );
    auto f1 = f3( "b", 8 );
    f3(1.0);

//   cout << f1( 1.1 ) << endl; 
//   cout << f2( 2, 1.1 ) << endl; 
//   cout << f2_a( 2, 1.1 ) << endl; 
//   cout << f2_b( 2, 1.1 ) << endl; 
}