#include <iostream>
using namespace std;

class Usuario(){
    
    public:

        string nombreUsuario;
        int identificacion;
        MaterialBibliografico* materialesPrestados[5];

        Usuario (string nombreUsuario, int identificacion) : nombreUsuario(nombreUsuario), identificacion(identificacion) {} 

        prestarMaterial(){

        }

        devolverMaterial(){

        }

        mostrarMaterialesPrestados(){

        }

};


