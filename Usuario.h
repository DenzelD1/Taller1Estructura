#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Usuario {

    private:
        string nombre;
        int id;
        MaterialBibliografico* materialesPrestados[5];

    public:
        Usuario(string nombre, int id);
        void prestarMaterial();
        void devolverMaterial();
        void mostrarMaterialesPrestados();
};