#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MaterialBibliografico.h"
#include "Revista.h"
#include "Libro.h"
#include "Usuario.h"
#include <limits>
#include <regex>

using namespace std;

//---------------------------------------------------------------------------------------------------
//                                      FUNCIONES
//---------------------------------------------------------------------------------------------------

//Maneja la entrada de string ante una peticion de un numero entero
int obtenerEntero(string peticion) {
    int valor;
    while (true) {
        cout << "Ingrese " << peticion << ": ";
        cin >> valor;

        if (cin.fail()) {  
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida, ingrese nuevamente el dato." << endl;
        } else {
            break;  
        }
    }
    return valor;
}

//Abre usuarios.txt y los lee, devolviendo el vector de tipo Usuario con punteros.
vector<Usuario*> leerUsuarios(const string& nombreArchivo, MaterialBibliografico* biblioteca[], 
                                int cantidadMateriales) { 
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
        ss.ignore();  

        Usuario* nuevoUsuario = new Usuario(nombre, id);

        string titulo;
        while (getline(ss, titulo, ',')) {
            for (int i = 0; i < cantidadMateriales; i++) {
                if (biblioteca[i] -> getTituloLibro() == titulo) {
                    nuevoUsuario -> prestarMaterial(biblioteca[i], "si");
                    break;
                }
            }
        }

        usuarios.push_back(nuevoUsuario);
    }

    archivo.close();
    return usuarios;
}

//Abre materialbibliográfico.txt y los lee, devolviendo el vector de tipo MaterialBibliografico con punteros.
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

//Comprueba que el formato del ISBN se encuentre correcto
bool validarISBN(const string& isbn) {
    regex formatoISBN("^\\d{1,3}-\\d{1}-\\d{1,4}-\\d{1,4}-\\d{1}$");
    return regex_match(isbn, formatoISBN);
}

//Le devuelve al usuario el ISBN con el formato debido
string obtenerISBN() {
    string isbn;
    while (true) {
        cout << "Ingrese el ISBN (formato general XXX-X-XXXX-XXXX-X):" << endl;
        cin >> isbn;

        if (!validarISBN(isbn)) {
            cout << "El formato no es correcto." << endl;
        } else {
            break;
        }
    }
    return isbn;
}

//Agrega un material que no se encuentre presente a la biblioteca.
void agregarMaterial(MaterialBibliografico* biblioteca[], int& cantidadMateriales) {
    if (cantidadMateriales >= 100) {
        cerr << "Error: Se ha alcanzado la capacidad maxima de materiales en la biblioteca." << endl;
        return;
    }

    cout << "Agregar material a la biblioteca:\n";
    cout << "1. Libro\n";
    cout << "2. Revista\n";
    int opcion = obtenerEntero("el tipo de material");
    cin.ignore();
    
    if (opcion < 1 || opcion > 2) { cerr << "Opcion invalida.\n"; return; }

    string titulo, autor;
    cout << "Ingrese el titulo: ";
    getline(cin, titulo);
    cout << "Ingrese el autor: ";
    getline(cin, autor);

    string isbn = obtenerISBN();

    if (opcion == 1) {
        string resumen;
        int fechaPublicacion = obtenerEntero("el anio de publicacion");
        cin.ignore();
        cout << "Ingrese el resumen: ";
        getline(cin, resumen);
        biblioteca[cantidadMateriales] = new Libro(fechaPublicacion, resumen, titulo, autor, isbn, false);
    } else {
        int numEdicion = obtenerEntero("el numero de edicion");
        cin.ignore();
        int mesPublicacion = obtenerEntero("el mes de publicacion");
        cin.ignore();
        if (mesPublicacion > 12 || mesPublicacion < 1) { cout << "Mes invalido." << endl; return; }
        biblioteca[cantidadMateriales] = new Revista(numEdicion, mesPublicacion, titulo, autor, isbn, false);   
    }
    cantidadMateriales++;
    cout << "Material agregado exitosamente.\n";
}

//Busca un material dentro del arreglo biblioteca.
void buscarMaterial(MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    cout << "Buscar material por:\n";
    cout << "1. Titulo\n";
    cout << "2. Autor\n";
    int opcion = obtenerEntero("el tipo de busqueda");
    cin.ignore(); 

    string busqueda;
    if (opcion == 1) {
        cout << "Ingrese el titulo a buscar: ";
        getline(cin, busqueda);
        cout << "-----------------------------------------------" << endl;
        for (int i = 0; i < cantidadMateriales; i++) {
            if (biblioteca[i] -> getTituloLibro() == busqueda) {
                biblioteca[i] -> mostrarInformacion();
                return;
            }
        }
        cout << "Material con el titulo '" << busqueda << "' no encontrado.\n";
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
        cerr << "Opcion no valida.\n";
    }
}

//Posibilita que el usuario pueda tomar prestado algún material bibliográfico.
void prestarMaterial(Usuario& usuario, MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    string titulo;
    cout << "Ingrese el titulo del material que desea prestar: ";
    getline(cin, titulo);

    for (int i = 0; i < cantidadMateriales; i++) {
        if (biblioteca[i] -> getTituloLibro() == titulo) {
            usuario.prestarMaterial(biblioteca[i], "no");
            return;
        }
    }

    cout << "Material no encontrado o ya prestado.\n";
}

//Posibilita que el usuario pueda devolver algún material bibliogrpafico que tomó prestado.
void devolverMaterial(Usuario& usuario, MaterialBibliografico* biblioteca[], int cantidadMateriales) {
    string titulo;
    cout << "Ingrese el titulo del material que desea devolver: ";
    getline(cin, titulo);

    for (int i = 0; i < cantidadMateriales; i++) {
        if (biblioteca[i] -> getTituloLibro() == titulo) {
            usuario.devolverMaterial(biblioteca[i]);
            return;
        }
    }

    cout << "Material no encontrado en tu lista de prestados.\n";
}

//Permite que se pueda crear un nuevo usuario.
void crearUsuario(vector<Usuario*>& usuarios) {
    string nombre;
    cout << "Ingrese el nombre del nuevo usuario: ";
    getline(cin, nombre);

    int id = obtenerEntero("un ID para el nuevo usuario"); 
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

//Busca un usuario almacenado en el vector usuarios de tipo Usuario.
void buscarUsuario(const vector<Usuario*>& usuarios) {
    int id = obtenerEntero("el ID del usuario a buscar");
    cin.ignore();
    for (Usuario* usuario : usuarios) {
        if (usuario -> getId() == id) {
            cout << "Usuario encontrado: " << usuario -> getNombre() << ", ID: " << usuario -> getId() << ".\n";
            return;
        }
    }

    cout << "Usuario con ID " << id << " no encontrado.\n";
}

//Elimina un usuario que ya estaba almacenado en usuarios.
void eliminarUsuario(vector<Usuario*>& usuarios, Usuario& usuario, bool& eliminarse) {
    int id = obtenerEntero("el ID del usuario a eliminar");
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

//Muestra los usuarios que están actualmente registrados.
void mostrarUsuarios(vector<Usuario*>& usuarios){
    cout << "--------------------------------------------" << endl;
    cout << "Usuarios actualmente registrados..." << endl;
    cout << "--------------------------------------------" << endl;
    for (Usuario* usuario : usuarios) {
        cout << "Nombre: " << usuario -> getNombre() << ", ID: " << usuario -> getId() << endl;
    }
}

void guardarMateriales(const MaterialBibliografico* biblioteca[], int cantidadMateriales, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar los materiales: " << nombreArchivo << endl;
        return;
    }

    // Guardar cada material en el archivo
    for (int i = 0; i < cantidadMateriales; i++) {
        const Libro* libro = dynamic_cast<const Libro*>(biblioteca[i]);
        const Revista* revista = dynamic_cast<const Revista*>(biblioteca[i]);

        if (libro != nullptr) {
            archivo << "Libro," << libro->getTituloLibro() << "," 
                    << libro->getAutor() << "," 
                    << libro->getIsbn() << ","
                    << (libro->getPrestado() ? "true" : "false") << ","
                    << libro->getFechaPublicacion() << ","
                    << libro->getResumen() << "\n";
        } else if (revista != nullptr) {
            archivo << "Revista," << revista->getTituloLibro() << ","
                    << revista->getAutor() << ","
                    << revista->getIsbn() << ","
                    << (revista->getPrestado() ? "true" : "false") << ","
                    << revista->getNumEdicion() << ","
                    << revista->getMesPublicacion() << "\n";
        }
    }

    archivo.close();
}

void guardarUsuarios(vector<Usuario*>& usuarios, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar los usuarios: " << nombreArchivo << endl;
        return;
    }

    // Guardar cada usuario en el archivo
    for (Usuario* usuario : usuarios) {
        archivo << usuario -> getNombre() << "," << usuario -> getId();

        MaterialBibliografico** materialesPrestados = usuario -> getMaterialesPrestados();
        for (int i = 0; i < 5; i++) {
            if (materialesPrestados[i] != nullptr) {
                archivo << "," << materialesPrestados[i] -> getTituloLibro();
            }
        }
        archivo << "\n";
    }

    archivo.close();
}

//Elimina los materiales almacenados en la memoria al cerrar el programa.
void liberarMemoria(MaterialBibliografico* biblioteca[], int cantidadMateriales, vector<Usuario*>& usuarios) {
    for (int i = 0; i < cantidadMateriales; i++) {
        if (biblioteca[i] != nullptr) {
            delete biblioteca[i];
            biblioteca[i] = nullptr;
        }
    }

    for (Usuario* usuario : usuarios) {
        delete usuario;
    } usuarios.clear();
}

//---------------------------------------------------------------------------------------------------
//                                          MAIN
//---------------------------------------------------------------------------------------------------

int main() {
    MaterialBibliografico* biblioteca[100];
    int cantidadMateriales = 0;
    vector<MaterialBibliografico*> materiales = leerMaterialBibliografico("materialbibliografico.txt");
    transferirMaterialesABiblioteca(biblioteca, materiales, cantidadMateriales);

    vector<Usuario*> usuarios = leerUsuarios("usuarios.txt", biblioteca, cantidadMateriales);
    Usuario* usuarioActivo = nullptr;
    mostrarUsuarios(usuarios);

    while (usuarioActivo == nullptr) {
        cout << "---- Iniciar sesion ----\n";
        int id = obtenerEntero("su ID");
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
    int opcionUsuario;
    do {
        if (eliminarse) { opcion = 8; }
        else {
            cout << "\n---- Menu Biblioteca ----\n";
            cout << "1. Mostrar Biblioteca\n";
            cout << "2. Agregar Material\n";
            cout << "3. Buscar Material\n";
            cout << "4. Prestar Material\n";
            cout << "5. Devolver Material\n";
            cout << "6. Mostrar Materiales Prestados\n";
            cout << "7. Gestionar usuarios\n";
            cout << "8. Cerrar sesion\n";
            cout << "9. Salir\n";
            cout << "10. Lista de usuarios actuales\n";
            opcion = obtenerEntero("una opcion");
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
                prestarMaterial(*usuarioActivo, biblioteca, cantidadMateriales); 
                break;
            case 5:
                devolverMaterial(*usuarioActivo, biblioteca, cantidadMateriales);
                break;
            case 6:
                usuarioActivo -> mostrarMaterialesPrestados(); 
                break;
            case 7:
                cout << "1. Crear Usuario\n";
                cout << "2. Buscar Usuario\n";
                cout << "3. Eliminar Usuario\n";
                opcionUsuario = obtenerEntero("una opcion");
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
                        cout << "Opcion no valida.\n";
                        break;
                }
                break;
            case 8:
                if (eliminarse) { 
                    cout << "Cerrando sesion porque se elimino el usuario que estaba usando el sistema..." << endl; 
                    eliminarse = false;
                } else { cout << "Cerrando sesion de " << usuarioActivo -> getNombre() << ".\n"; } 
                usuarioActivo = nullptr;
                while (usuarioActivo == nullptr) {
                    mostrarUsuarios(usuarios);
                    cout << "---- Iniciar sesion ----\n";
                    int id = obtenerEntero("su ID");
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
                guardarMateriales(const_cast<const MaterialBibliografico**>(biblioteca), cantidadMateriales, "materialbibliografico.txt");
                guardarUsuarios(usuarios, "usuarios.txt");
                cout << "Saliendo y guardando el sistema...\n";
                break;
            case 10:
                mostrarUsuarios(usuarios);
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
    } while (opcion != 9);

    liberarMemoria(biblioteca, cantidadMateriales, usuarios);
    return 0;
}