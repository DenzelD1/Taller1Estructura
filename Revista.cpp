#include <iostream>
using namespace std;

class Revista : public MaterialBibliografico{

    private:
        int numeroEdicion;
        string mesPublicacion;

    public:

        Revista(string nombre, int isbn, string autor, int numeroEdicion, string mesPublicacion) : MaterialBibliografico(string nombre, int isbn, string autor), Revista(numeroEdicion, mesPublicacion) {}

        mostrarInformacion(){
            
        }

}