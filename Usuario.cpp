#include <iostream>
#include "Usuario.h"
using namespace std;

Usuario :: Usuario(string nombre, int id) {
    this -> nombre = nombre;
    this -> id = id;
}

void Usuario :: prestarMaterial(MaterialBibliografico* material) {
    for (int i = 0; i < 5; i++) {
        
        if (material -> getPrestado()) {
            cout << "Este material ya está prestado." << endl;
            return;
        } else {
            if (materialesPrestados[i] == nullptr) {
                materialesPrestados[i] = material;
                material -> setPrestado(true);
                cout << "Material prestado con éxito." << endl;
                return;
            }
        }
    }

    cout << "Ya tienes 5 materiales prestados. Devuelve alguno antes de prestar otro." << endl;
}

void Usuario :: devolverMaterial(MaterialBibliografico* material) {
    for (int i = 0; i < 5; i++) {
        if (materialesPrestados[i] == material) {
            materialesPrestados[i] = nullptr; 
            material -> setPrestado(false);
            cout << "Material devuelto exitosamente." << endl;
            return;
        }
    }

    cout << "Este material no está en tu lista de prestados." << endl;
}

void Usuario :: mostrarMaterialesPrestados() {
    cout << "Materiales prestados por " << nombre << " (ID: " << id << "):" << endl;
    cout << "-----------------------------------------------" << endl;
    bool tieneMaterial = false;

    for (int i = 0; i < 5; i++) {
        if (materialesPrestados[i] != nullptr) {
            materialesPrestados[i] -> mostrarInformacion();
            tieneMaterial = true;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    if (!tieneMaterial) { cout << "No tienes materiales prestados actualmente." << endl; }
}