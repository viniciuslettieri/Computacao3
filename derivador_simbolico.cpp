
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
     
    We also have methods for printing like strings

********************************************************************************************/


// Truncate double if int
string double_to_str( double x ) {
    string str = ( (std::fmod( x, 1 ) == 0.0) ? std::to_string( (int)x ) : std::to_string( (double)x ) );
    str.erase(str.find_last_not_of('0') + 1, std::string::npos );
    return str;
}

// Our Variable X Class
class X {
    public:
    auto e(auto x) {
        return x;
    }
    auto dx(auto x) {
        return 1;
    }
    
    string str() const {
        return "x";
    }
    string dx_str() const {
        return "1";
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

    string str() const {
        if constexpr ( std::is_same< double, decltype(v) >::value ) {
            return double_to_str(v);
        } else {
            return to_string( v );
        }
    }
    string dx_str() const {
        return "0";
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

    string str() const {
        return "((" + a.str() + ")+(" + b.str() + "))";
    }
    string dx_str() const {
        return "((" + a.dx_str()+ ")+(" + b.dx_str() + "))";
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

    string str() const {
        return "((" + a.str() + ")-(" + b.str() + "))";
    }
    string dx_str() const {
        return "((" + a.dx_str()+ ")-(" + b.dx_str() + "))";
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

    string str() const {
        return "((" + a.str() + ")*(" + b.str() + "))";
    }
    string dx_str() const {
        return "((" + a.dx_str()+ ")*(" + b.str() + ")+(" + a.str()+ ")*(" + b.dx_str() + "))";
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

    string str() const {
        return "((" + a.str() + ")/(" + b.str() + "))";
    }
    string dx_str() const {
        return "(((" + a.dx_str()+ ")*(" + b.str() + ")-(" + a.str()+ ")*(" + b.dx_str() + ")))/(" + b.str()+ ")^2)";
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

    string str() const {
        return "(" + a.str() + ")^" + to_string(b);
    }
    string dx_str() const {
        return "(" + to_string(b) + "*(" + a.dx_str() + ")*(" + a.str() + ")^" + to_string(b-1) + ")";
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

    string str() const {
        return "exp(" + a.str() + ")";
    }
    string dx_str() const {
        return "(exp(" + a.str() + ")*(" + a.dx_str() + "))";
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

    string str() const {
        return "log(" + a.str() + ")";
    }
    string dx_str() const {
        return "(1/("+ a.str() + ")*" + a.dx_str() + ")";
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

    string str() const {
        return "sin(" + a.str() + ")";
    }
    string dx_str() const {
        return "(cos(" + a.str() + ")*" + a.dx_str() + ")";
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

    string str() const {
        return "cos(" + a.str() + ")";
    }
    string dx_str() const {
        return "(-sin(" + a.str() + ")*" + a.dx_str() + ")";
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
    cout << "Numeric Evaluation: " << endl;

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

    cout << "String Evaluation: " << endl;

    auto f8 = 3.0 + x + x;
    cout << f8.str() << endl;
    cout << f8.dx_str() << endl;

    auto f9 = x * x;
    cout << f9.str() << endl;
    cout << f9.dx_str() << endl;

    auto f10 = x - (x - 5.0);
    cout << f10.str() << endl;
    cout << f10.dx_str() << endl;

    auto f11 = (x+7.0)*(x-7.0);
    cout << f11.str() << endl;
    cout << f11.dx_str() << endl;

    auto f12 = x->*3;
    cout << f12.str() << endl;
    cout << f12.dx_str() << endl;

    auto f13 = (7.0*x+5.0)->*3;
    cout << f13.str() << endl;
    cout << f13.dx_str() << endl;

    auto f14 = sin( x + 5 );
    cout << f14.str() << endl;
    cout << f14.dx_str() << endl;

    auto f15 = exp( x + 5 );
    cout << f15.str() << endl;
    cout << f15.dx_str() << endl;

    auto f16 = 1.0 / (sin(x)->*2 + cos(x)->*2)->*4;
    cout << f16.str() << endl;
    cout << f16.dx_str() << endl;

    auto f17 = log( cos( x + 5 ) );
    cout << f17.str() << endl;
    cout << f17.dx_str() << endl;

    auto f18 = exp( x * log( x - 8.0 )  + 1.0 );
    cout << f18.str() << endl;
    cout << f18.dx_str() << endl;

    auto f19 = log( (8.1/(x+1.0)->*3 - 9.2 ) * (x + 3.0) *sin( cos( x / 3.14 ) ) + x );
    cout << f19.str() << endl;
    cout << f19.dx_str() << endl;

    return 0;
}