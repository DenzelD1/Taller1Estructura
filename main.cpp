#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MaterialBibliografico.h"
#include "Revista.h"
#include "Libro.h"

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

//                          MOSTRAR QUE ESTÁN GUARDADOS CORRECTAMENTE
void mostrarBiblioteca(const vector<MaterialBibliografico*>& biblioteca) {
    for (MaterialBibliografico* material : biblioteca) {
        material->mostrarInformacion();
        cout << "-------------------------------" << endl;
    }
}

//                          MAIN

int main() {
    vector<MaterialBibliografico*> biblioteca = leerMaterialBibliografico("materialbibliografico.txt");
    
    mostrarBiblioteca(biblioteca);

    // Liberar la memoria de los objetos creados
    for (MaterialBibliografico* material : biblioteca) {
        delete material;
    }

    return 0;
}
