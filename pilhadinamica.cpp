#include <iostream>
using namespace std;

class PilhaInt {
    public:
        PilhaInt( int tamanho = 10 ) {
            max_valores = tamanho;
            pilha = (int *) malloc( sizeof(int) * tamanho );
            for( int i=0; i<tamanho; i++)
                pilha[i] = 0;
            idx_topo = 0;
        }
        PilhaInt( const PilhaInt& p ) {
            max_valores = p.max_valores;
            pilha = (int *) malloc( sizeof(int) * p.max_valores );
            for( int i=0; i<p.max_valores; i++ )
                pilha[i] = p.pilha[i];
            idx_topo = p.idx_topo;
        }

        ~PilhaInt() {
            free(pilha);
        }
        
        const PilhaInt& operator = ( PilhaInt& b ) {
            idx_topo = b.idx_topo;
            max_valores = b.max_valores;
            redimensiona( b.max_valores );
            for( int i=0; i<b.idx_topo; i++ ){
                pilha[i] = b.pilha[i];
            }
            return *this;
        }

        int capacidade() {
            return max_valores;
        }
        void redimensiona( int n ) {
            pilha = (int*) realloc(pilha, sizeof(int)*n);
            max_valores = n;
            idx_topo = std::min(n, idx_topo);
        }

        void empilha( int valor ) {
            if( idx_topo == max_valores ) {
                redimensiona( max_valores*2 );
            }
            pilha[ idx_topo++ ] = valor;
        }
        int desempilha() {
            if( idx_topo > 0 ){
                return pilha[ --idx_topo ];
            } else {
                std::cout << "erro minimo" << std::endl;
                return -1;
            }
        }
        void print( std::ostream& o ) {
            o << "[ ";
            for( int i=0; i<idx_topo; i++ ){
                if( i < idx_topo-1 )
                    o << pilha[i] << ", ";
                else 
                    o << pilha[i] << " ";
            }
            o << "]";
        }

        PilhaInt& operator << ( const int val ) {
            this->empilha( val );
            return ( *this );
        }

    private:
        int max_valores;
        int *pilha;
        int idx_topo;
};

int main(){
    PilhaInt pilha(2);
    
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

    return 0;
}