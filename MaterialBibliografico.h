/**
 * 
 * @file MaterialBibliografico.h
 * @brief Definición de la clase MaterialBibliográfico
 * 
 * Este archivo contiene la definición de la clase MaterialBibliografico, el cual representa un material perteneciente
 * a una biblioteca con atributos como tituloLibro, autor, isbn y prestado.
 * 
 */

#pragma once
#include <iostream>
using namespace std;

/**
 * @class MaterialBibliografico
 * @brief Clase base que representa un material bibliográfico.
 *
 * Esta clase contiene información común a todos los materiales bibliográficos,
 * como el títuloLibro, el autor, el isbn y el prestado.
 */


class MaterialBibliografico {

    private:
        string tituloLibro; /**< Titulo del material bibliográfico */
        string autor; /**< Autor del material bibliográfico */
        string isbn; /**< isbn del material bibliográfico */
        bool prestado; /**< variable que indica el estado del material prestado */
    
    public:

        /**
         * 
         * @brief Constructor de MaterialBibliografico.
         * 
         * @param tituloLibro El título del material.
         * @param autor El autor del material.
         * @param isbn El isbn del material.
         * @param prestado Variable que indica el estado del material.
         * 
         * 
         */

        MaterialBibliografico(string tituloLibro, string autor, string isbn, bool prestado);
        
        /**
         * @brief Método virtual para mostrar la información del material.
         *
         * Este método debe ser implementado por las clases derivadas.
         */
        
        virtual void mostrarInformacion();

        /**
         * @brief Consigue el título del material.
         */

        string getTituloLibro() const;

        /**
         * @brief Consigue el nombre del autor.
         */

        string getAutor() const;

        /**
         * @brief Consigue el identificador del libro (isbn).
         */

        string getIsbn() const;

        /**
         * @brief Consigue el estado del material si está prestado o no.
         */

        bool getPrestado() const;

        /**
         * @brief Establece un nuevo estado del material si está prestado o no.
         */

        void setPrestado(bool prestado);
};