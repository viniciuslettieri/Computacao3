#include <memory>
#include <iostream>
#include <functional>
#include <type_traits>
#include <map>
#include <string>

using namespace std;

// In this project, we implement a variable object like the one in python or javascript.
// It has to accept any type and should overload all the operators.
// To do this, we use double dispatch.

class Var {

    public:

    // Child classes
    class Erro {
        public:
        Erro( string msg ): msg( msg ) { }
        string operator()() const { return msg; }
        
        private:
        string msg;
    };

    class Undefined {
        public:
        virtual void print( std::ostream& o ) const {
            o << "undefined";
        }
        
        virtual Var operator () ( const Var &param ) {
            throw Erro("Essa variável não pode ser usada como função");
        }
        virtual Var& operator [] ( const string &s ) {
            throw Erro("Essa variável não é um objeto");
        }

        // Double Dispatch Operators
        virtual Var operator + ( const Undefined &v ) const {
            return Var();
        }
        virtual Var addition( int arg ) const { return Var(); }
        virtual Var addition( double arg ) const { return Var(); }
        virtual Var addition( string arg ) const { return Var(); }
        virtual Var addition( char arg ) const { return Var(); }

        virtual Var operator - ( const Undefined &v ) const {
            return Var();
        }
        virtual Var subtraction( int arg ) const { return Var(); }
        virtual Var subtraction( double arg ) const { return Var(); }
        virtual Var subtraction( char arg ) const { return Var(); }

        virtual Var operator * ( const Undefined &v ) const {
            return Var();
        }
        virtual Var multiplication( int arg ) const { return Var(); }
        virtual Var multiplication( double arg ) const { return Var(); }

        virtual Var operator / ( const Undefined &v ) const {
            return Var();
        }
        virtual Var division( int arg ) const { return Var(); }
        virtual Var division( double arg ) const { return Var(); }
        
        virtual Var operator < ( const Undefined &v ) const{
            return Var();
        }
        virtual Var less( int arg ) const { return Var(); }
        virtual Var less( double arg ) const { return Var(); }
        virtual Var less( string arg ) const { return Var(); }
        virtual Var less( char arg ) const { return Var(); }

        virtual Var operator ! () const {
            return Var();
        }
        
        virtual Var operator && ( const Undefined &v ) const {
            return Var();
        }
        virtual Var logical_and( bool arg ) const { return Var(); }

        virtual Var operator || ( const Undefined &v ) const {
            return Var();
        }
        virtual Var logical_or( bool arg ) const { return Var(); }

    };
    class Int: public Undefined {
        public:
        Int( int n ) : n(n) { }

        void print( std::ostream& o ) const {
            o << n;
        }
        
        // Double Dispatch Operators
        virtual Var operator + ( const Undefined &v ) const {
            return v.addition(n);
        }
        virtual Var addition( int arg ) const { return arg + n; }
        virtual Var addition( double arg ) const { return arg + n; }
        virtual Var addition( char arg ) const { return arg + n; }

        virtual Var operator - ( const Undefined &v ) const {
            return v.subtraction(n);
        }
        virtual Var subtraction( int arg ) const { return arg - n; }
        virtual Var subtraction( double arg ) const { return arg - n; }

        virtual Var operator * ( const Undefined &v ) const {
            return v.multiplication(n);
        }
        virtual Var multiplication( int arg ) const { return arg * n; }
        virtual Var multiplication( double arg ) const { return arg * n; }

        virtual Var operator / ( const Undefined &v ) const {
            return v.division(n);
        }
        virtual Var division( int arg ) const { return arg / n; }
        virtual Var division( double arg ) const { return arg / n; }

        virtual Var operator < ( const Undefined &v ) const {
            return v.less(n);
        }
        virtual Var less( char arg ) const { return arg < n; }
        virtual Var less( int arg ) const { return arg < n; }
        virtual Var less( double arg ) const { return arg < n; }

        private:
        int n;
    };
    class Double: public Undefined {
        public:
        Double( double n ) : n(n) { }

        void print( std::ostream& o ) const {
            o << n;
        }

        // Double Dispatch Operators
        virtual Var operator + ( const Undefined &v ) const {
            return v.addition(n);
        }
        virtual Var addition( int arg ) const { return arg + n; }
        virtual Var addition( double arg ) const { return arg + n; }

        virtual Var operator - ( const Undefined &v ) const {
            return v.subtraction(n);
        }
        virtual Var subtraction( int arg ) const { return arg - n; }
        virtual Var subtraction( double arg ) const { return arg - n; }

        virtual Var operator * ( const Undefined &v ) const {
            return v.multiplication(n);
        }
        virtual Var multiplication( int arg ) const { return arg * n; }
        virtual Var multiplication( double arg ) const { return arg * n; }

        virtual Var operator / ( const Undefined &v ) const {
            return v.division(n);
        }
        virtual Var division( int arg ) const { return arg / n; }
        virtual Var division( double arg ) const { return arg / n; }

        virtual Var operator < ( const Undefined &v ) const {
            return v.less(n);
        }
        virtual Var less( char arg ) const { return arg < n; }
        virtual Var less( int arg ) const { return arg < n; }
        virtual Var less( double arg ) const { return arg < n; }
        
        private:
        double n;
    };
    class Char: public Undefined {
        public:
        Char( char n ) : n(n) { }
        
        void print( std::ostream& o ) const {
            o << n;
        }

        // Double Dispatch Operators
        virtual Var operator + ( const Undefined &v ) const {
            return v.addition(n);
        }
        virtual Var addition( char arg ) const { return std::string(1, arg) + std::string(1, n); }
        virtual Var addition( int arg ) const { return arg + n; }
        virtual Var addition( string arg ) const { return arg + std::string(1, n); }

        virtual Var operator - ( const Undefined &v ) const {
            return v.subtraction(n);
        }
        virtual Var subtraction( char arg ) const { return arg - n; }

        virtual Var operator < ( const Undefined &v ) const {
            return v.less(n);
        }
        virtual Var less( string arg ) const { return arg < std::to_string(n); }
        virtual Var less( char arg ) const { return arg < n; }
        virtual Var less( int arg ) const { return arg < n; }
        virtual Var less( double arg ) const { return arg < n; }

        private:
        char n;
    };
    class String: public Undefined {
        public:
        String( string n ) : n(n) { }
        
        void print( std::ostream& o ) const {
            o << n;
        }

        // Double Dispatch Operators
        virtual Var operator + ( const Undefined &v ) const {
            return v.addition(n);
        }
        virtual Var addition( string arg ) const { return arg + n; }
        virtual Var addition( char arg ) const { return arg + n; }

        virtual Var operator < ( const Undefined &v ) const {
            return v.less(n);
        }
        virtual Var less( string arg ) const { return arg < n; }
        virtual Var less( char arg ) const { return std::to_string(arg) < n; }
        
        private:
        string n;
    };
    class Boolean: public Undefined {
        public:
        Boolean( bool n ) : n(n) { }
        
        void print( std::ostream& o ) const {
            o << ( n ? "true" : "false" );
        }

        // Double Dispatch Operators
        virtual Var operator ! () const {
            return !n;
        }
        
        virtual Var operator && ( const Undefined &v ) const {
            return v.logical_and(n);
        }
        virtual Var logical_and( bool arg ) const { return arg && n; }

        virtual Var operator || ( const Undefined &v ) const {
            return v.logical_or(n);
        }
        virtual Var logical_or( bool arg ) const { return arg || n; }

        private:
        bool n;
    };
    template< typename F >
    class Function: public Undefined {
        public:
        Function( F f ) : f(f) { }
        
        void print( std::ostream& o ) const {
            o << "function";
        }

        virtual Var operator () ( const Var &param ) {
            if constexpr( std::is_invocable< decltype(f), decltype(param) >::value ) {
                return std::invoke( f, param );
            }else{
                throw Erro( "A função não pode ser chamada" );
            }
        }

        private:
        F f;
    };
    class Object: public Undefined {
        public:
        void print( std::ostream& o ) const {
            o << "object";
        }

        virtual Var& operator [] ( const string &s ) {
            return elements[ s ];
        }

        private:
        std::map< string, Var > elements;
    };

    // Class features
    Var( ) : p( new Undefined() ) { }
    Var( int n ) : p( new Int( n ) ) { }
    Var( double n ) : p( new Double( n ) ) { }
    Var( bool n ) : p( new Boolean( n ) ) { }
    Var( string n ) : p( new String( n ) ) { }
    Var( char n ) : p( new Char(n) ) { }
    Var( char *n ) : p( new String( n ) ) { }
    Var( const char *n ) : p( new String( n ) ) { }
    Var( Object *v ) : p( v ) { }


    Var operator = ( int n ) {
        p = shared_ptr<Undefined>( new Int( n ) );
        return *this;
    }
    Var operator = ( double n ) {
        p = shared_ptr<Undefined>( new Double( n ) );
        return *this;
    }
    Var operator = ( string n ) {
        p = shared_ptr<Undefined>( new String( n ) );
        return *this;
    }
    Var operator = ( const char *n ) {
        p = shared_ptr<Undefined>( new String( n ) );
        return (*this);
    }
    Var operator = ( Object *v ) {
        p = shared_ptr<Undefined>( v );
        return (*this);
    }
    template <typename F>
    Var operator = ( F f ) {
        p = shared_ptr<Undefined>( new Function( f ) );
        return *this;
    }

    auto operator () ( const Var &param ) {
        return p->operator()( param );
    }

    Var& operator [] ( const string &s ) const {
        return p->operator[]( s );
    }
    Var& operator ->* ( const string &s ) const {
        return p->operator[]( s );
    }
    Var& operator[] ( const char *s ) const { 
        return operator[]( std::string(s) );
    }

    void print( std::ostream& o ) const {
        p->print( o );
    }

    auto get_p() const {
        return p;
    }

    // Arithmetic, Logic and Relational operators
    Var operator + ( const Var &v ) const {
        return *p + *(v.p);
    }
    Var operator - ( const Var &v ) const {
        return *p - *(v.p);
    }
    Var operator * ( const Var &v ) const {
        return *p * *(v.p);
    }
    Var operator / ( const Var &v ) const {
        return *p / *(v.p);
    }
    Var operator < ( const Var &v ) const{
        return *p < *(v.p);
    }
    Var operator ! () const {
        return !(*p);
    }
    Var operator && ( const Var &v ) const {
        return *p && *(v.p);
    }
    Var operator || ( const Var &v ) const {
        return *p || *(v.p);
    }

    private:

    std::shared_ptr<Undefined> p;
};

// Complementing the other operators
Var operator > ( const Var& a, const Var& b ) { return b<a; }
Var operator != ( const Var& a, const Var& b ) { return (a<b) || (b<a); }
Var operator == ( const Var& a, const Var& b ) { return !(a!=b); }
Var operator <= ( const Var& a, const Var& b ) { return !(b<a); }
Var operator >= ( const Var& a, const Var& b ) { return !(a<b); }

// And Switching sides of operators
Var operator + ( auto k, const Var &v ) {
    return Var(k) + v;
}
Var operator - ( auto k, const Var &v ) {
    return Var(k) - v;
}
Var operator * ( auto k, const Var &v ) {
    return Var(k) * v;
}
Var operator / ( auto k, const Var &v ) {
    return Var(k) / v;
}
Var operator < ( auto k, const Var &v ) {
    return Var(k) < v;
}
Var operator && ( auto k, const Var &v )  {
    return Var(k) && v;
}
Var operator || ( auto k, const Var &v ) {
    return Var(k) || v;
}

std::ostream& operator << ( std::ostream& o, const Var &v ) {
    v.print( o );
    return o;
}

// Create new Map-like Object with variable types
Var::Object* newObject() {
    return new Var::Object;
}


int main() {
    Var ak, bk;

    cout << ak << endl;  // saida: undefined

    ak = 1;
    cout << ak << endl;  // saida: 1

    ak = "hello";
    cout << ak << endl;  // saída: hello

    ak = []( auto x ){ return x; };
    cout << ak( 10 ) << endl;

    ak = 10;
    bk = 2.5;

    cout << ak + bk << " " << ak*bk << " " << ak-bk << " " << ak/bk << " " << (10 + ak)*2.5 << endl;

    ak = newObject();
    auto atr = ak["atr"];
    cout << ak["atr"] << endl;

    atr = 1;
    cout << atr << endl;

    ak["atr"] = 9;
    cout << ak["atr"] << endl;

    ak->*"atr" = 4.5;
    cout << ak["atr"] << endl;

    ak["metodo"] = []( auto x ){ return x*x; };
    cout << ak["metodo"]( 4 ) << endl; // Saída: 16;


    // Testes do Professor
    cout << "Testes do Professor: " << endl;
    
    Var a, b = 10;
    cout << a << " " << b << endl;
    a = 3.14;
    b = "uma string";
    cout << a << " " << b << endl;

    Var n = "ola";
    cout << n << endl;

    a = newObject();
    a["init"] = []( const Var* a ){ return a; };
    // a["atr"] = a["init"]( newObject() );
    
    Var a1[5] = { true, 'X', 2, 2.1, "abracadabra" };
    Var b1 = 200, c1 = 300.1, d1 = "palavra ";
    for( auto& x: a1 ) {
    cout << x+b1 << "," << x+c1 << "," << x+d1 << "," << 3 / x << "," << 1.1 * x << ","
        << Var(x && true) << "," << Var(x && false) <<  "," << Var(b1 >= x) << "," << Var(x < d1) << endl;
    }

    cout << a1[1] + c1 << a1[1] << endl;
    cout << Var( b1 >= a1[2] ) << endl;

    a = 10.1;
    b = []( auto x ){ return x + x; };
    cout << b( a ) << " ";
    cout << b( "oba" ) << " ";
    cout << b( 'X' ) << " ";
    cout << b( true ) << endl;

    a = newObject();
    b = "Jose";
    Var c = "Maria";
   
    a["nome"] = b + ' ' + c;
    a["idade"] = []( auto v ) { return 2019 - v["nascimento"]; };
    a["nascimento"] = 1990;
    b = a;
    cout << a["nome"] << " " << a["idade"](a) << " " << a["nascimento"] << endl;

    cout << b["nome"] << " " << b["idade"](b) << " " << b["nascimento"] << endl;

    return 0;
}