
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <type_traits>
#include <functional>
#include <cmath>

using namespace std;

/********************************************************************************************
    
    In this essay, I implement a symbolic derivative. 
    We need to implement variable X, constante Const, the operators of multiplication, 
    division, addition, subtraction and the functions exp, log, sin and cos.

    Listing derivative rules:
    * Const()' -> 0
    * X' -> 1
    * Prod(A, B)' -> Addition( Prod(A', B), Prod(A, B') )
    * Div(A, B)' -> Div( Sub( Prod(A', B), Prod(A, B) ), Prod(B, B) )
    * exp(A)' -> Prod( exp(A), A' )
    * log(A)' -> Prod( Div( Const(1), A ), A' )
    * sin(A)' -> cos( A ) * A'
    * cos(A)' -> -sin( A ) * A'

********************************************************************************************/

// Our Variable X Class
class X {
    public:
    auto e(auto x) {
        return x;
    }
    auto dx(auto x) {
        return 1;
    }
};

// Our Constant Class
template< typename C >
class Const {
    public:
    Const(C x) : v(x) { }

    auto e(auto x) {
        return v;
    }
    auto dx(auto x) {
        return 0;
    }

    private:
    C v;
};

// Our Addition Operator Class
template< typename F1, typename F2 >
class Addition {
    public:
    Addition( F1 a, F2 b ): a(a), b(b) {}

    auto e( auto x ) {
        return a.e( x ) + b.e( x );
    }
    auto dx( auto x ) {
        return a.dx( x ) + b.dx( x );
    }

    private:
    F1 a; 
    F2 b;
};

// Our Subtraction Operator Class
template< typename F1, typename F2 >
class Subtraction {
    public:
    Subtraction( F1 a, F2 b ): a(a), b(b) {}

    auto e( auto x ) {
        return a.e( x ) - b.e( x );
    }
    auto dx( auto x ) {
        return a.dx( x ) - b.dx( x );
    }

    private:
    F1 a; 
    F2 b;
};

// Our Multiplication Operator Class
template< typename F1, typename F2 >
class Product {
    public:
    Product( F1 a, F2 b ): a(a), b(b) {}

    auto e( auto x ) {
        return a.e( x ) * b.e( x );
    }
    auto dx( auto x ) {
        return a.dx( x ) * b.e( x ) + a.e( x ) * b.dx( x );
    }

    private:
    F1 a; 
    F2 b;
};

// Our Division Operator Class
template< typename F1, typename F2 >
class Division {
    public:
    Division( F1 a, F2 b ): a(a), b(b) {}

    auto e( auto x ) {
        return a.e( x ) / b.e( x );
    }
    auto dx( auto x ) {
        return ( ( ( a.dx( x ) * b.e( x ) ) - ( a.e( x ) * b.dx( x ) ) ) ) / ( b.e( x ) * b.e( x ) );
    }

    private:
    F1 a; 
    F2 b;
};

// Our Pow Operator Class
template< typename F1, typename F2 >
class Pow {
    public:
    Pow( F1 a, F2 b ): a(a), b(b) {}

    auto e( auto x ) {
        return pow( a.e( x ) , b );
    }
    auto dx( auto x ) {
        return b * pow( a.e( x ), b-1 ) * a.dx( x );
    }

    private:
    F1 a; 
    F2 b;
};

// Our Exp Class
template< typename F1 >
class Exp{
    public:
    Exp( F1 a ): a(a) {}

    auto e( auto x ) {
        return exp( a.e( x ) );
    }
    auto dx( auto x ) {
        return exp( a.e( x ) ) * a.dx( x );
    }

    private:
    F1 a;
};

// Our Log Class
template< typename F1 >
class Log{
    public:
    Log( F1 a ): a(a) {}

    auto e( auto x ) {
        return log( a.e( x ) );
    }
    auto dx( auto x ) {
        return ( 1.0 / a.e( x ) ) * a.dx( x );
    }

    private:
    F1 a;
};

// Our Sin Class
template< typename F1 >
class Sin{
    public:
    Sin( F1 a ): a(a) {}

    auto e( auto x ) {
        return sin( a.e( x ) );
    }
    auto dx( auto x ) {
        return cos( a.e( x ) ) * a.dx( x );
    }

    private:
    F1 a;
};

// Our Sin Class
template< typename F1 >
class Cos{
    public:
    Cos( F1 a ): a(a) {}

    auto e( auto x ) {
        return cos( a.e( x ) );
    }
    auto dx( auto x ) {
        return -sin( a.e( x ) ) * a.dx( x );
    }

    private:
    F1 a;
};

/* With the Class Operators created, we need to overload the 
   actual operators to call those classes. */

// Operator + for expressions
template< typename A, typename B >
auto operator + ( A a, B b ) {
    return Addition(a, b); 
}
template< typename A >
auto operator + ( A a, int b ) {
    return Addition(a, Const(b)); 
}
template< typename A >
auto operator + ( A a, double b ) {
    return Addition(a, Const(b)); 
}
template< typename B >
auto operator + ( int a, B b ) {
    return Addition(Const(a), b); 
}
template< typename B >
auto operator + ( double a, B b ) {
    return Addition(Const(a), b); 
}

// Operator - for expressions
template< typename A, typename B >
auto operator - ( A a, B b ) {
    return Subtraction(a, b); 
}
template< typename A >
auto operator - ( A a, int b ) {
    return Subtraction(a, Const(b)); 
}
template< typename A >
auto operator - ( A a, double b ) {
    return Subtraction(a, Const(b)); 
}
template< typename B >
auto operator - ( int a, B b ) {
    return Subtraction(Const(a), b); 
}
template< typename B >
auto operator - ( double a, B b ) {
    return Subtraction(Const(a), b); 
}

// Operator * for expressions
template< typename A, typename B >
auto operator * ( A a, B b ) {
    return Product(a, b); 
}
template< typename A >
auto operator * ( A a, int b ) {
    return Product(a, Const(b)); 
}
template< typename A >
auto operator * ( A a, double b ) {
    return Product(a, Const(b)); 
}
template< typename B >
auto operator * ( int a, B b ) {
    return Product(Const(a), b); 
}
template< typename B >
auto operator * ( double a, B b ) {
    return Product(Const(a), b); 
}

// Operator / for expressions
template< typename A, typename B >
auto operator / ( A a, B b ) {
    return Division(a, b); 
}
template< typename A >
auto operator / ( A a, int b ) {
    return Division(a, Const(b)); 
}
template< typename A >
auto operator / ( A a, double b ) {
    return Division(a, Const(b)); 
}
template< typename B >
auto operator / ( int a, B b ) {
    return Division(Const(a), b); 
}
template< typename B >
auto operator / ( double a, B b ) {
    return Division(Const(a), b); 
}

// Our Pow(x, v) Operator
template< typename A >
auto operator ->* ( A a, auto v ) {
    static_assert( std::is_same_v< int, decltype( v ) >, "Operador de potenciação definido apenas para inteiros" );
    return Pow(a, v);
}

// Function exp
template< typename A >
Exp<A> exp ( A a ) {
    return Exp(a); 
}

// Function log
template< typename A >
Log<A> log ( A a ) {
    return Log(a); 
}

// Function cos
template< typename A >
Cos<A> cos ( A a ) {
    return Cos(a); 
}

// Function sin
template< typename A >
Sin<A> sin ( A a ) {
    return Sin(a); 
}

X x;

int main(){
    auto f1 = 3*x*x*x*2;
    cout << f1.dx(10) << endl;

    auto f2 = exp( f1 );
    auto f2l = f2.dx(1);
    cout << f2l << endl;

    auto f3 = 10 * cos( f1 );
    auto f3l = f3.dx(2);
    cout << f3l << endl;

    auto f4 = cos( f1 ) * f2;
    auto f4l = f4.dx(2);
    cout << f4l << endl;

    auto f5 = x->*5;
    cout << f5.dx(2) << endl;

    auto f6 = 3*(x->*3)*2;
    cout << f6.dx(10) << endl; 

    auto f7 = exp( ( 3 * ( x->*3 ) ) / sin( x ) );
    cout << f7.dx(2) << endl;

    return 0;
}