#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Usuario {

    private:
        string nombre;
        int id;
        MaterialBibliografico* materialesPrestados[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};

    public:
        Usuario(string nombre, int id);
        void prestarMaterial(MaterialBibliografico* material);
        void devolverMaterial(MaterialBibliografico* material);
        void mostrarMaterialesPrestados();
};