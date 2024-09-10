#include <iostream>
#include "Libro.h"
#include "MaterialBibliografico.h"
using namespace std;

Libro :: Libro (string fechaPublicacion, string resumen, string tituloLibro, string autor, string isbn,
                bool prestado) 
    : MaterialBibliografico(tituloLibro, autor, isbn, prestado) {

    this -> fechaPublicacion = fechaPublicacion;
    this -> resumen = resumen;
}

void Libro :: mostrarInformacion() {
    cout << "Título: " << getTituloLibro() << endl;
    cout << "Autor: " << getAutor() << endl;
    cout << "ISBN: " << getIsbn() << endl;
    cout << "Prestado: " << (getPrestado() ? "Sí" : "No") << endl;
    cout << "Fecha de publicación: " << getFechaPublicacion() << endl;
    cout << "Resumen: " << getResumen() << endl;
}

string Libro :: getFechaPublicacion() { return fechaPublicacion; }
string Libro :: getResumen() { return resumen; }
