#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Revista: public MaterialBibliografico {

    private:
        int numEdicion;
        int mesPublicacion;

    public:
        Revista(int numEdicion, int mesPublicacion, string tituloLibro, string autor, 
                    int isbn, bool prestado);
        void mostrarInformacion() override;
        int getNumEdicion();
        int getMesPublicacion();
};