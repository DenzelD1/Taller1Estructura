#include <iostream>
#include "Revista.h"
#include "MaterialBibliografico.h"
using namespace std;

Revista :: Revista(int numEdicion, int mesPublicacion, string tituloLibro, string autor, int isbn, 
                    bool prestado) 
    : MaterialBibliografico(tituloLibro, autor, isbn, prestado) {

    this -> numEdicion = numEdicion;
    this -> mesPublicacion = mesPublicacion;
}

void Revista :: mostrarInformacion() {
    cout << "Título: " << getTituloLibro() << endl;
    cout << "Autor: " << getAutor() << endl;
    cout << "ISBN: " << getIsbn() << endl;
    cout << "Prestado: " << (getPrestado() ? "Sí" : "No") << endl;
    cout << "Edición: " << getNumEdicion() << endl;
    cout << "Mes de publicación: " <<  getMesPublicacion() << endl;
}

int Revista :: getNumEdicion() { return numEdicion; }
int Revista :: getMesPublicacion() { return mesPublicacion; }