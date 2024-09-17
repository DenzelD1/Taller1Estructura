#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MaterialBibliografico.h"
#include "Revista.h"
#include "Libro.h"
#include "Usuario.h"

using namespace std;

//                      FUNCION QUE LEE Y CONSTRUYE LOS OBJETOS

vector<MaterialBibliografico*> leerMaterialBibliografico(const string& nombreArchivo) {
    vector<MaterialBibliografico*> biblioteca;
    ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return biblioteca;
    }

    string linea;
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string tipo, titulo, autor, isbn;
        bool prestado;
        string prestadoStr;
        
        getline(ss, tipo, ',');  // Tipo (Revista o Libro)

        if (tipo == "Revista") {
            int numEdicion;
            string mesPublicacion;
            getline(ss, titulo, ',');
            getline(ss, autor, ',');
            getline(ss, isbn, ',');
            ss >> numEdicion;
            ss.ignore(); // Ignorar la coma
            ss >> mesPublicacion;
            // Crear objeto de tipo Revista
            biblioteca.push_back(new Revista(numEdicion, mesPublicacion, titulo, autor, isbn, false));
        } else if (tipo == "Libro") {
            string fechaPublicacion, resumen;
            getline(ss, titulo, ',');
            getline(ss, autor, ',');
            getline(ss, isbn, ',');
            getline(ss, fechaPublicacion, ',');
            getline(ss, resumen, ',');
            // Crear objeto de tipo Libro
            biblioteca.push_back(new Libro(fechaPublicacion, resumen, titulo, autor, isbn, false));
        }
    }

    archivo.close();
    return biblioteca;
}

//                    TRANSFIERE LOS RECURSOS DEL VECTOR AL ARRAY BIBLIOTECA
void transferirMaterialesABiblioteca(MaterialBibliografico* biblioteca[], 
    const vector<MaterialBibliografico*>& materiales, int cantidadMateriales) {
    
    for (size_t i = 0; i < materiales.size() && cantidadMateriales < 100; i++) {
        biblioteca[cantidadMateriales] = materiales[i];
        cantidadMateriales++;
    }
}
//                          MOSTRAR QUE ESTÁN GUARDADOS CORRECTAMENTE
void mostrarBiblioteca(MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    for (int i = 0; i < cantidadMateriales; i++) {
        biblioteca[i] -> mostrarInformacion();
        cout << "-------------------------------" << endl;
    }
}

void liberarMemoria(MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    for (int i = 0; i < cantidadMateriales; i++) {
        if (biblioteca[i] != nullptr) {
            cout << "Eliminando " << biblioteca[i] -> getTituloLibro() << "..." << endl;
            delete biblioteca[i];
            biblioteca[i] = nullptr;
        }
    }
}

//                          MAIN

int main() {
    MaterialBibliografico* biblioteca[100];
    int cantidadMateriales = 0;

    vector<MaterialBibliografico*> materiales = leerMaterialBibliografico("materialbibliografico.txt");
    transferirMaterialesABiblioteca(biblioteca, materiales, cantidadMateriales);
    mostrarBiblioteca(biblioteca, cantidadMateriales);
    liberarMemoria(biblioteca, cantidadMateriales);
    return 0;
}
