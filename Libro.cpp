#include <iostream>
#include "Libro.h"
#include "MaterialBibliografico.h"
using namespace std;

Libro :: Libro (int fechaPublicacion, string resumen, string tituloLibro, string autor, string isbn,
                bool prestado) 
    : MaterialBibliografico(tituloLibro, autor, isbn, prestado) {

    this -> fechaPublicacion = fechaPublicacion;
    this -> resumen = resumen;
}

void Libro :: mostrarInformacion() {
    cout << "Titulo: " << getTituloLibro() << endl;
    cout << "Autor: " << getAutor() << endl;
    cout << "ISBN: " << getIsbn() << endl;
    cout << "Prestado: " << (getPrestado() ? "Si" : "No") << endl;
    cout << "Fecha de publicacion: " << getFechaPublicacion() << endl;
    cout << "Resumen: " << getResumen() << endl;
}

int Libro :: getFechaPublicacion() const { return fechaPublicacion; }
string Libro :: getResumen() const { return resumen; }
