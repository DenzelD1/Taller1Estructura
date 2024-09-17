#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MaterialBibliografico.h"
#include "Revista.h"
#include "Libro.h"
#include "Usuario.h"

using namespace std;

//---------------------------------------------------------------------------------------------------
//                                      FUNCIONES
//---------------------------------------------------------------------------------------------------

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
    const vector<MaterialBibliografico*>& materiales, int& cantidadMateriales) {
    
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

void agregarMaterial(MaterialBibliografico* biblioteca[], int& cantidadMateriales) {
    if (cantidadMateriales >= 100) {
        cerr << "Error: Se ha alcanzado el límite máximo de 100 materiales en la biblioteca." << endl;
        return;
    }

    cout << "Agregar material a la biblioteca:\n";
    cout << "1. Libro\n";
    cout << "2. Revista\n";
    int opcion;
    cin >> opcion;
    cin.ignore();  // Ignorar el salto de línea

    if (opcion < 1 || opcion > 2) { cerr << "Opcion inválida.\n"; return; }

    string titulo, autor, isbn;
    cout << "Ingrese el título: ";
    getline(cin, titulo);
    cout << "Ingrese el autor: ";
    getline(cin, autor);
    cout << "Ingrese el ISBN: ";
    getline(cin, isbn);

    if (opcion == 1) {
        // Agregar un libro
        string fechaPublicacion, resumen;
        cout << "Ingrese la fecha de publicación: ";
        getline(cin, fechaPublicacion);
        cout << "Ingrese el resumen: ";
        getline(cin, resumen);
        biblioteca[cantidadMateriales] = new Libro(fechaPublicacion, resumen, titulo, autor, isbn, false);
    } else {
        // Agregar una revista
        int numEdicion;
        string mesPublicacion;
        cout << "Ingrese el número de edición: ";
        cin >> numEdicion;
        cin.ignore();
        cout << "Ingrese el mes de publicación: ";
        getline(cin, mesPublicacion);
        biblioteca[cantidadMateriales] = new Revista(numEdicion, mesPublicacion, titulo, autor, isbn, false);
    }

    cantidadMateriales++;
    cout << "Material agregado exitosamente.\n";
}

void buscarMaterial(MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    cout << "Buscar material por:\n";
    cout << "1. Título\n";
    cout << "2. Autor\n";
    int opcion;
    cin >> opcion;
    cin.ignore();  // Ignorar salto de línea

    string busqueda;
    if (opcion == 1) {
        cout << "Ingrese el título a buscar: ";
        getline(cin, busqueda);
        for (int i = 0; i < cantidadMateriales; i++) {
            if (biblioteca[i]->getTituloLibro() == busqueda) {
                biblioteca[i]->mostrarInformacion();
                return;
            }
        }
        cout << "Material con el título '" << busqueda << "' no encontrado.\n";
    } else if (opcion == 2) {
        cout << "Ingrese el autor a buscar: ";
        getline(cin, busqueda);
        for (int i = 0; i < cantidadMateriales; i++) {
            if (biblioteca[i]->getAutor() == busqueda) {
                biblioteca[i]->mostrarInformacion();
                return;
            }
        }
        cout << "Material del autor '" << busqueda << "' no encontrado.\n";
    } else {
        cerr << "Opción no válida.\n";
    }
}

void prestarMaterial(Usuario& usuario, MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    string titulo;
    cout << "Ingrese el título del material que desea prestar: ";
    getline(cin, titulo);

    for (int i = 0; i < cantidadMateriales; i++) {
        if (biblioteca[i]->getTituloLibro() == titulo) {
            usuario.prestarMaterial(biblioteca[i]);
            return;
        }
    }

    cout << "Material no encontrado o ya prestado.\n";
}

void devolverMaterial(Usuario& usuario, MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    string titulo;
    cout << "Ingrese el título del material que desea devolver: ";
    getline(cin, titulo);

    for (int i = 0; i < cantidadMateriales; i++) {
        if (biblioteca[i]->getTituloLibro() == titulo) {
            usuario.devolverMaterial(biblioteca[i]);
            return;
        }
    }

    cout << "Material no encontrado en tu lista de prestados.\n";
}

//---------------------------------------------------------------------------------------------------
//                                          MAIN
//---------------------------------------------------------------------------------------------------

int main() {
    MaterialBibliografico* biblioteca[100];
    int cantidadMateriales = 0;

    Usuario usuario("Juan Perez", 1);

    vector<MaterialBibliografico*> materiales = leerMaterialBibliografico("materialbibliografico.txt");
    transferirMaterialesABiblioteca(biblioteca, materiales, cantidadMateriales);
    
    int opcion;
    do {
        cout << "\n---- Menú Biblioteca ----\n";
        cout << "1. Mostrar Biblioteca\n";
        cout << "2. Agregar Material\n";
        cout << "3. Buscar Material\n";
        cout << "4. Prestar Material\n";
        cout << "5. Devolver Material\n";
        cout << "6. Mostrar Materiales Prestados\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); 
        cout << "-----------------------------------------------" << endl;

        switch (opcion) {
            case 1:
                mostrarBiblioteca(biblioteca, cantidadMateriales);
                break;
            case 2:
                agregarMaterial(biblioteca, cantidadMateriales);
                break;
            case 3:
                buscarMaterial(biblioteca, cantidadMateriales);
                break;
            case 4:
                prestarMaterial(usuario, biblioteca, cantidadMateriales);
                break;
            case 5:
                devolverMaterial(usuario, biblioteca, cantidadMateriales);
                break;
            case 6:
                usuario.mostrarMaterialesPrestados();
                break;
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }
    } while (opcion != 7); 

    liberarMemoria(biblioteca, cantidadMateriales);
    return 0;
}
