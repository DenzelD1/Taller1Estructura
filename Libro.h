#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Libro: public MaterialBibliografico {

    private:
        int fechaPublicacion;
        string resumen;
    
    public:
        Libro(int fechaPublicacion, string resumen, string tituloLibro, string autor, 
                string isbn, bool prestado);
        void mostrarInformacion() override;
        int getFechaPublicacion();
        string getResumen();

};