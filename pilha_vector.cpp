#include <iostream>
#include <vector>
using namespace std;

class PilhaInt {
    public:
        PilhaInt( ) { }

        PilhaInt( int c ) {
            redimensiona( c );
        }

        PilhaInt( const PilhaInt& p ) {
            pilha_vec = p.pilha_vec;
            capac = p.capac;
        }

        ~PilhaInt( ) {}
        
        const PilhaInt& operator = ( PilhaInt& p ) {
            pilha_vec = p.pilha_vec;
            capac = p.capac;
            return *this;
        }

        int capacidade() {
            return capac;
        }
        void redimensiona( int n ) {
            if((unsigned) n < pilha_vec.size())
                pilha_vec.resize(n, 0);

            capac = n;
        }

        void empilha( int valor ) {
            if( pilha_vec.size() == (unsigned) capac ) {
                redimensiona( capac*2 );
            }
            pilha_vec.push_back( valor );
        }
        int desempilha() {
            if( pilha_vec.size() > (unsigned) 0 ){
                int valor = pilha_vec.back();
                pilha_vec.pop_back();
                return valor;
            } else {
                std::cout << "erro minimo" << std::endl;
                return -1;
            }
            
        }
        void print( std::ostream& o ) {
            o << "[ ";
            int tam = pilha_vec.size();
            for( int i=0; i<tam; i++ ){
                if( i < tam-1 )
                    o << pilha_vec[i] << ", ";
                else 
                    o << pilha_vec[i] << " ";
            }
            o << "]";
        }

        PilhaInt& operator << ( const int val ) {
            this->empilha( val );
            return ( *this );
        }

    private:
        std::vector<int> pilha_vec;
        int capac;
};


PilhaInt embaralha( PilhaInt q ) {
    int aux = q.desempilha();
    q << 32 << 9 << aux;
    
    return q;
}

int main(){
    PilhaInt pilha;

    std::cout << "Inicio do programa" << std::endl;
    
    pilha.desempilha();

    pilha.empilha( 1 );
    pilha.empilha( 2 );

    std::cout << "Pilha atual: ";
    pilha.print( std::cout );
    std::cout << std::endl;

    int val1 = pilha.desempilha();
    
    pilha.empilha( 3 );
    pilha.empilha( 4 );

    std::cout << "Pilha atual: ";
    pilha.print( std::cout );
    std::cout << std::endl;
    
    int val2 = pilha.desempilha();

    pilha << 5 << 6 << 7;

    std::cout << "Pilha atual: ";
    pilha.print( std::cout );
    std::cout << std::endl;

    std::cout << "Valores retirados: " << val1 << " " << val2 << std::endl;


    PilhaInt pilha2 = pilha;
    
    std::cout << "Pilha2 atual: ";
    pilha2.print( std::cout );
    std::cout << std::endl;

    pilha2 << 8;

    std::cout << "Pilha2 atual: ";
    pilha2.print( std::cout );
    std::cout << std::endl;


    pilha.redimensiona(3);

    std::cout << "Pilha atual: ";
    pilha.print( std::cout );
    std::cout << std::endl;


    embaralha( pilha2 ).print( std::cout );

    return 0;
}