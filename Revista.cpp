#include <iostream>
#include "Revista.h"
#include "MaterialBibliografico.h"
using namespace std;

Revista :: Revista(int numEdicion, int mesPublicacion, string tituloLibro, string autor, string isbn, 
                    bool prestado) 
    : MaterialBibliografico(tituloLibro, autor, isbn, prestado) {

    this -> numEdicion = numEdicion;
    this -> mesPublicacion = mesPublicacion;
}

void Revista :: mostrarInformacion() {
    cout << "Titulo: " << getTituloLibro() << endl;
    cout << "Autor: " << getAutor() << endl;
    cout << "ISBN: " << getIsbn() << endl;
    cout << "Prestado: " << (getPrestado() ? "Si" : "No") << endl;
    cout << "Edicion: " << getNumEdicion() << endl;
    cout << "Mes de publicacion: " <<  getMesPublicacion() << endl;
}

int Revista :: getNumEdicion() const { return numEdicion; }
int Revista :: getMesPublicacion() const { return mesPublicacion; }