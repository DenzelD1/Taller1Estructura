#pragma once
#include <iostream>
using namespace std;

class MaterialBibliografico {

    private:
        string tituloLibro;
        string autor;
        int isbn;
        bool prestado;
    
    public:
        MaterialBibliografico(string tituloLibro, string autor, int isbn, bool prestado);
        virtual void mostrarInformacion();
        string getTituloLibro();
        string getAutor();
        int getIsbn();
        bool getPrestado();
        void setPrestado(bool prestado);
};