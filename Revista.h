#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Revista: public MaterialBibliografico {

    private:
        int numEdicion;
        string mesPublicacion;

    public:
        Revista(int numEdicion, string mesPublicacion, string tituloLibro, string autor, 
                    string isbn, bool prestado);
        void mostrarInformacion() override;
        int getNumEdicion();
        string getMesPublicacion();
};