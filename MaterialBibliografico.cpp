#include <iostream>
using namespace std;

class MaterialBibliografico (){

    public:
        string nombre;
        int isbn;
        string autor;
        virtual void mostrarInformacion(){

        }

        MaterialBibliografico(string nombre, int isbn, string autor) : nombre(nombre), isbn(isbn), autor(autor) {}
};

