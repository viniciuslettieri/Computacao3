#include <iostream>
using namespace std;

class PilhaInt {
    public:
        PilhaInt() {
            idx_topo = 0;
        }
        
        const PilhaInt& operator = ( PilhaInt& b ) {
            for(int i=0; i<b.idx_topo; i++){
                pilha[i] = b.pilha[i];
            }
            idx_topo = b.idx_topo;

            return *this;
        }

        void empilha( int valor ) {
            if( idx_topo < MAX_VALORES ) {
                pilha[ idx_topo++ ] = valor;
            } else {
                // erro
                std::cout << "erro maximo" << std::endl;
            }
        }
        int desempilha() {
            if( idx_topo > 0 ){
                return pilha[ --idx_topo ];
            } else {
                // erro
                std::cout << "erro minimo" << std::endl;
                return -1;
            }
        }
        void print( std::ostream& o ) {
            o << "[ ";
            for(int i=0; i<idx_topo; i++){
                if( i < idx_topo-1 )
                    o << pilha[i] << ", ";
                else 
                    o << pilha[i] << " ";
            }
            o << "]";
        }

        PilhaInt& operator << (const int val) {
            this->empilha( val );
            return (*this);
        }

    private:
        static const int MAX_VALORES = 500;
        int pilha[ MAX_VALORES ];
        int idx_topo;
};

int main(){
    PilhaInt pilha;
    
    pilha.desempilha();

    pilha.empilha( 1 );
    pilha.empilha( 2 );
    
    int val1 = pilha.desempilha();
    
    pilha.empilha( 3 );
    pilha.empilha( 4 );

    int val2 = pilha.desempilha();

    pilha << 5 << 6 << 7;

    std::cout << "Pilha atual: ";
    pilha.print( std::cout );
    std::cout << std::endl;

    std::cout << "Valores retirados: " << val1 << " " << val2 << std::endl;


    PilhaInt pilha2 = pilha;

    pilha2 << 8;

    std::cout << "Pilha2 atual: ";
    pilha2.print( std::cout );
    std::cout << std::endl;


    return 0;
}