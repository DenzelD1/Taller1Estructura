#include <iostream>
using namespace std;

class Libro : public MaterialBibliografico{

    private:
        string fechaPublicacion;
        string resumen;

    public:

        Libro(string nombre, int isbn, string autor, string fechaPublicacion, string resumen) : MaterialBibliografico(string nombre, int isbn, string autor), Libro(fechaPublicacion, resumen) {}

        mostrarInformacion(){
            
        }

}