#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Libro: public MaterialBibliografico {

    private:
        string fechaPublicacion;
        string resumen;
    
    public:
        Libro(string fechaPublicacion, string resumen, string tituloLibro, string autor, 
                int isbn, bool prestado);
        void mostrarInformacion() override;
        string getFechaPublicacion();
        string getResumen();

};