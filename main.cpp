#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MaterialBibliografico.h"
#include "Revista.h"
#include "Libro.h"
#include "Usuario.h"
#include <limits>
#include "EntradaNoNumericaException.h"

using namespace std;

//---------------------------------------------------------------------------------------------------
//                                      FUNCIONES
//---------------------------------------------------------------------------------------------------

vector<Usuario*> leerUsuarios(const string& nombreArchivo) {
    vector<Usuario*> usuarios;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de usuarios: " << nombreArchivo << endl;
        return usuarios;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        int id;
        
        getline(ss, nombre, ','); 
        ss >> id;  

        Usuario* nuevoUsuario = new Usuario(nombre, id);
        usuarios.push_back(nuevoUsuario);
    }

    archivo.close();
    return usuarios;
}

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
        string tipo, titulo, autor, isbn, prestadoStr;
        bool prestado;
        
        getline(ss, tipo, ',');  

        if (tipo == "Revista") {
            int numEdicion;
            int mesPublicacion;
            getline(ss, titulo, ',');
            getline(ss, autor, ',');
            getline(ss, isbn, ',');
            getline(ss, prestadoStr, ',');
            prestado = (prestadoStr == "true");
            ss >> numEdicion;
            ss.ignore(); 
            ss >> mesPublicacion;
            ss.ignore();
            biblioteca.push_back(new Revista(numEdicion, mesPublicacion, titulo, autor, isbn, prestado));
        } else if (tipo == "Libro") {
            string resumen;
            int fechaPublicacion;
            getline(ss, titulo, ',');
            getline(ss, autor, ',');
            getline(ss, isbn, ',');
            getline(ss, prestadoStr, ',');
            prestado = (prestadoStr == "true");
            ss >> fechaPublicacion;
            ss.ignore();
            getline(ss, resumen, ',');
            biblioteca.push_back(new Libro(fechaPublicacion, resumen, titulo, autor, isbn, prestado));
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
//                          MUESTRA LOS MATERIALES ACTUALES
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
    cin.ignore(); 

    if (opcion < 1 || opcion > 2) { cerr << "Opcion inválida.\n"; return; }

    string titulo, autor, isbn;
    cout << "Ingrese el título: ";
    getline(cin, titulo);
    cout << "Ingrese el autor: ";
    getline(cin, autor);
    cout << "Ingrese el ISBN: ";
    getline(cin, isbn);

    if (opcion == 1) {
        string resumen;
        int fechaPublicacion;
        cout << "Ingrese el anio de publicación: ";
        cin >> fechaPublicacion;
        cin.ignore();
        cout << "Ingrese el resumen: ";
        getline(cin, resumen);
        biblioteca[cantidadMateriales] = new Libro(fechaPublicacion, resumen, titulo, autor, isbn, false);
    } else {
        
        int numEdicion;
        int mesPublicacion;
        cout << "Ingrese el número de edición: ";
        cin >> numEdicion;
        cin.ignore();
        cout << "Ingrese el mes de publicación: ";
        cin >> mesPublicacion;
        cin.ignore();
        if (mesPublicacion > 12 || mesPublicacion < 1) { cout << "Mes inválido." << endl; return; }
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
    cin.ignore();  

    string busqueda;
    if (opcion == 1) {
        cout << "Ingrese el título a buscar: ";
        getline(cin, busqueda);
        for (int i = 0; i < cantidadMateriales; i++) {
            if (biblioteca[i] -> getTituloLibro() == busqueda) {
                biblioteca[i] -> mostrarInformacion();
                return;
            }
        }
        cout << "Material con el título '" << busqueda << "' no encontrado.\n";
    } else if (opcion == 2) {
        cout << "Ingrese el autor a buscar: ";
        getline(cin, busqueda);
        for (int i = 0; i < cantidadMateriales; i++) {
            if (biblioteca[i] -> getAutor() == busqueda) {
                biblioteca[i] -> mostrarInformacion();
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
        if (biblioteca[i] -> getTituloLibro() == titulo) {
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
        if (biblioteca[i] -> getTituloLibro() == titulo) {
            usuario.devolverMaterial(biblioteca[i]);
            return;
        }
    }

    cout << "Material no encontrado en tu lista de prestados.\n";
}

void crearUsuario(vector<Usuario*>& usuarios) {
    string nombre;
    int id;

    cout << "Ingrese el nombre del nuevo usuario: ";
    getline(cin, nombre);
    cout << "Ingrese la ID del nuevo usuario: ";
    cin >> id;
    cin.ignore(); 

    for (Usuario* usuario : usuarios) {
        if (usuario -> getId() == id) {
            cout << "Error: Ya existe un usuario con esa ID.\n";
            return;
        }
    }

    Usuario* nuevoUsuario = new Usuario(nombre, id);
    usuarios.push_back(nuevoUsuario);
    cout << "Usuario " << nombre << " agregado exitosamente.\n";
}

void buscarUsuario(const vector<Usuario*>& usuarios) {
    int id;
    cout << "Ingrese la ID del usuario que desea buscar: ";
    cin >> id;
    cin.ignore(); 

    for (Usuario* usuario : usuarios) {
        if (usuario -> getId() == id) {
            cout << "Usuario encontrado: " << usuario -> getNombre() << ", ID: " << usuario -> getId() << ".\n";
            return;
        }
    }

    cout << "Usuario con ID " << id << " no encontrado.\n";
}

void eliminarUsuario(vector<Usuario*>& usuarios, Usuario& usuario, bool& eliminarse) {
    int id;
    cout << "Ingrese la ID del usuario que desea eliminar: ";
    cin >> id;
    cin.ignore(); 

    for (size_t i = 0; i < usuarios.size(); i++) {
        if (usuarios[i] -> getId() == id) {
            MaterialBibliografico** materialesPrestados = usuarios[i] -> getMaterialesPrestados();
            if (usuarios[i] -> getId() == usuario.getId()) { eliminarse = true; }
            for (int j = 0; j < 5; j++) {
                if (materialesPrestados[j] != nullptr) { 
                    materialesPrestados[j] -> setPrestado(false);
                    materialesPrestados[j] = nullptr;
                }
            }
            cout << "Eliminando usuario " << usuarios[i] -> getNombre() << ".\n";
            delete usuarios[i];
            usuarios.erase(usuarios.begin() + i);
            cout << "Usuario eliminado exitosamente.\n";
            return;
        }
    }

    cout << "Usuario con ID " << id << " no encontrado.\n";
}

void mostrarUsuarios(vector<Usuario*>& usuarios){
    for (Usuario* usuario : usuarios) {
        cout << "Nombre: " << usuario -> getNombre() << ", ID: " << usuario -> getId() << endl;
    }
}

//---------------------------------------------------------------------------------------------------
//                                          MAIN
//---------------------------------------------------------------------------------------------------

int main() {
    MaterialBibliografico* biblioteca[100];
    int cantidadMateriales = 0;
    vector<MaterialBibliografico*> materiales = leerMaterialBibliografico("materialbibliografico.txt");
    transferirMaterialesABiblioteca(biblioteca, materiales, cantidadMateriales);

    vector<Usuario*> usuarios = leerUsuarios("usuarios.txt");
    Usuario* usuarioActivo = nullptr;

    cout << "Usuarios actualmente registrados..." << endl;
    mostrarUsuarios(usuarios);

    
    while (usuarioActivo == nullptr) {
        cout << "---- Iniciar sesión ----\n";
        cout << "Ingrese su ID: ";
        int id;
        cin >> id;
        cin.ignore();

        for (Usuario* usuario : usuarios) {
            if (usuario -> getId() == id) {
                usuarioActivo = usuario;
                cout << "Bienvenido(a), " << usuarioActivo->getNombre() << ".\n";
                break;
            }
        }

        if (usuarioActivo == nullptr) {
            cout << "ID no encontrado. Intente nuevamente.\n";
        }
    }
    
    bool eliminarse = false;
    int opcion;
    do {
        if (eliminarse) { opcion = 8; }
        else {
            cout << "\n---- Menú Biblioteca ----\n";
            cout << "1. Mostrar Biblioteca\n";
            cout << "2. Agregar Material\n";
            cout << "3. Buscar Material\n";
            cout << "4. Prestar Material\n";
            cout << "5. Devolver Material\n";
            cout << "6. Mostrar Materiales Prestados\n";
            cout << "7. Gestionar usuarios\n";
            cout << "8. Cerrar sesión\n";
            cout << "9. Salir\n";
            cout << "10. Lista de usuarios actuales\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;
            cin.ignore();
        }
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
                if (usuarioActivo != nullptr) { prestarMaterial(*usuarioActivo, biblioteca, cantidadMateriales); } 
                else { cout << "No hay un usuario activo. Inicie sesión primero.\n"; }
                break;
            case 5:
                if (usuarioActivo != nullptr) { devolverMaterial(*usuarioActivo, biblioteca, cantidadMateriales); } 
                else { cout << "No hay un usuario activo. Inicie sesión primero.\n"; }
                break;
            case 6:
                if (usuarioActivo != nullptr) { usuarioActivo -> mostrarMaterialesPrestados(); } 
                else { cout << "No hay un usuario activo. Inicie sesión primero.\n"; }
                break;
            case 7:
                cout << "1. Crear Usuario\n";
                cout << "2. Buscar Usuario\n";
                cout << "3. Eliminar Usuario\n";
                cout << "Seleccione una opción: ";
                int opcionUsuario;
                cin >> opcionUsuario;
                cin.ignore();
                switch (opcionUsuario) {
                    case 1:
                        crearUsuario(usuarios);
                        break;
                    case 2:
                        buscarUsuario(usuarios);
                        break;
                    case 3:
                        eliminarUsuario(usuarios, *usuarioActivo, eliminarse);
                        break;
                    default:
                        cout << "Opción no válida.\n";
                        break;
                }
                break;
            case 8:
                if (eliminarse) { 
                    cout << "Cerrando sesión porque se eliminó el usuario que estaba usando el sistema..." << endl; 
                    eliminarse = false;
                } else { cout << "Cerrando sesión de " << usuarioActivo -> getNombre() << ".\n"; } 
                usuarioActivo = nullptr;
                while (usuarioActivo == nullptr) {
                    cout << "---- Iniciar sesión ----\n";
                    cout << "Ingrese su ID: ";
                    int id;
                    cin >> id;
                    cin.ignore(); 

                    for (Usuario* usuario : usuarios) {
                        if (usuario -> getId() == id) {
                            usuarioActivo = usuario;
                            cout << "Bienvenido, " << usuarioActivo -> getNombre() << ".\n";
                            break;
                        }
                    }
                    if (usuarioActivo == nullptr) { cout << "ID no encontrado. Intente nuevamente.\n"; }
                }
                break;
            case 9:
                cout << "Saliendo del sistema...\n";
                break;
            case 10:
                mostrarUsuarios(usuarios);
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }
    } while (opcion != 9); 
    liberarMemoria(biblioteca, cantidadMateriales);
    for (Usuario* usuario : usuarios) { delete usuario; }
    return 0;
}
