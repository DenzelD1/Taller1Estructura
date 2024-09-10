#pragma once
#include <iostream>
using namespace std;

class MaterialBibliografico {

    private:
        string tituloLibro;
        string autor;
        string isbn;
        bool prestado;
    
    public:
        MaterialBibliografico(string tituloLibro, string autor, string isbn, bool prestado);
        virtual void mostrarInformacion();
        string getTituloLibro();
        string getAutor();
        string getIsbn();
        bool getPrestado();
        void setPrestado(bool prestado);
};