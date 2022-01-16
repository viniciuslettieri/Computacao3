#include <initializer_list>
#include <iostream>

using namespace std;


class AbstractPair {
    public:
        virtual void imprime( std::ostream& o ) = 0;
};

template <typename A, typename B>
class ImplPair : public AbstractPair {
    public:
        ImplPair( A a, B b ) : a(a), b(b) {}

        void imprime( std::ostream& o ) {
            o << a << " = " << b << std::endl;
        }

    private:
        A a;
        B b;
};

class Pair {
    public:
        template <typename A, typename B>
        Pair( A a, B b ) {
            p = new ImplPair<A, B>( a, b );
        }
        AbstractPair* get_p() {
            return p;
        }
    private:
        AbstractPair *p;
};

void print( std::ostream& o, std::initializer_list<Pair> lista ) {
    for( auto elem : lista ){
        elem.get_p()->imprime(o);
    }
}


int main() {
 
    Pair p( "1", 2 );

    print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

    return 0;  

}