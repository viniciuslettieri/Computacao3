#include <initializer_list>
#include <iostream>
#include <memory>

using namespace std;

class AbstractPair {
    public:
        virtual void imprime( std::ostream& o ) = 0;
        virtual ~AbstractPair() { };
};

template <typename A, typename B>
class ImplPair : public AbstractPair {
    public:
        // Constructor
        ImplPair( A& a, B& b ) : a(a), b(b) { }

        // Copy Constructor
        ImplPair( const ImplPair& par ) {
            a = par.a;
            b = par.b;
        }

        // Move Constructor
        ImplPair( ImplPair&& par ) : a(par.a), b(par.b) { }

        // Move Assignment
        const ImplPair& operator = ( ImplPair&& par ) {
            a = par.a;
            b = par.b;
            return *this;
        }

        void imprime( std::ostream& o ) {
            o << a << " = " << b << std::endl;
        }

    private:
        A a;
        B b;
};

class Pair {
    public:
        // Constructor
        template <typename A, typename B>
        Pair( A a, B b ) {
            p = std::make_shared< ImplPair<A, B> >( a, b );
        }

        std::shared_ptr<AbstractPair> get_p() const {
            return p;
        }
    private:
        std::shared_ptr<AbstractPair> p;
};

void print( std::ostream& o, std::initializer_list<Pair> lista ) {
    for( auto itr = std::begin(lista); itr != std::end(lista); ++itr ){
        (*itr).get_p()->imprime(o);
    }
}


int main() {
 
    print( cout, { { "jan", 1 }, { 2, "fev" } } );

    return 0;  

}