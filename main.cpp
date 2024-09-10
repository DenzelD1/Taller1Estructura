#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MaterialBibliografico.cpp"
using namespace std;

vector<MaterialBibliografico> crearBiblioteca();

int main() {

    cout << "hokla" << endl;
    cout << "Margot Robbie y Anya Taylor-Joy son mis actrices favoritas :>" << endl;

    vector<MaterialBibliografico> biblioteca = crearBiblioteca();
    

    return 0;
}

vector<MaterialBibliografico> crearBiblioteca(){

    vector<MaterialBibliografico> biblioteca;

    ifstream archivo("materialbibliografico.txt");

   
    string linea;

    while (getline(archivo, linea)){
        stringstream ss(linea);
        string titulo, isbn, autor;
        bool prestado;

        getline(ss, titulo, ',');
        getline(ss, isbn, ',');
        getline(ss, autor, ',');
        ss >> boolalpha >> prestado;

        MaterialBibliografico material(titulo, isbn, autor, prestado);
        biblioteca.push_back(material);
    }
    archivo.close();

    return biblioteca;
}