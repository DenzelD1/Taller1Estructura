#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;


MaterialBibliografico :: MaterialBibliografico(string tituloLibro, string autor, string isbn, bool prestado) {
    this -> tituloLibro = tituloLibro; 
    this -> autor = autor; 
    this -> isbn = isbn; 
    this -> prestado = prestado;
}

void MaterialBibliografico :: mostrarInformacion() {
    cout << "Informacion general" << endl;
}

string MaterialBibliografico :: getTituloLibro() { return tituloLibro; }
string MaterialBibliografico :: getAutor() { return autor; }
string MaterialBibliografico :: getIsbn() { return isbn; }
bool MaterialBibliografico :: getPrestado() { return prestado; }
void MaterialBibliografico :: setPrestado(bool prestado) { this -> prestado = prestado; }