#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

MaterialBibliografico :: MaterialBibliografico(string tituloLibro, string autor, int isbn, bool prestado) {
    this -> tituloLibro = tituloLibro;
    this -> autor = autor;
    this -> isbn = isbn;
    this -> prestado = prestado;
}

string MaterialBibliografico :: getTituloLibro() { return tituloLibro; }
string MaterialBibliografico :: getAutor() { return autor; }
int MaterialBibliografico :: getIsbn() { return isbn; }
bool MaterialBibliografico :: getPrestado() { return prestado; }
void MaterialBibliografico :: setPrestado(bool prestado) { this -> prestado = prestado; }