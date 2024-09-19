/**
 * 
 * @file Usuario.h
 * @brief Definición de la clase Usuario
 * 
 * Este archivo contiene la definición de la clase Usuario, el cual representa un usuario que interactúa con la 
 * biblioteca y posee atributos como un nombre, una id y un vector que contiene los materiales prestados en la biblioteca.
 * 
 */


#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

/**
 * @class Usuario
 * @brief Clase que representa a un usuario de la biblioteca.
 *
 * Esta clase contiene información de un usuario común de la biblioteca,
 * como el nombre, su id y un vector de los materiales que tiene prestados.
 */


class Usuario {

    private:
        string nombre; /**< Nombre del usuario */
        int id; /**< Id del usuario */
        MaterialBibliografico* materialesPrestados[5] = {nullptr, nullptr, nullptr, nullptr, nullptr}; /**< Arreglo de tipo puntero que guarda en la memoria los materiales que el usuario prestó en la biblioteca */

    public:
        
        /**
         * 
         * @brief Constructor de Usuario.
         * 
         * @param nombre El nombre del usuario.
         * @param id La identificación (id) del usuario.
         *
         */

        Usuario(string nombre, int id);
        
        /**
         * @brief Consigue el nombre del usuario.
         */

        string getNombre() const;

        /**
         * @brief Consigue la identificación (id) del usuario.
         */

        int getId() const;

        /**
         * @brief Obtiene los materiales prestados por el usuario.
         * 
         * @return MaterialBibliografico** Un doble puntero a un arreglo de materiales prestados.
         * 
         * @details Esta función devuelve un puntero doble a un arreglo de objetos de tipo MaterialBibliografico
         * que representan los materiales que el usuario tiene actualmente prestados. El puntero doble permite
         * acceder a cada uno de los materiales prestados.
         */
        
        MaterialBibliografico** getMaterialesPrestados();

        /**
         * @brief Presta un material al usuario.
         * 
         * @param material Puntero a un objeto de tipo MaterialBibliografico que se desea prestar.
         * 
         * @details Esta función permite que el usuario pueda tomar prestado un material de la biblioteca (Libro o Revista).
         * El parámetro es un puntero, lo que significa que se trabaja directamente con el material
         * sin hacer una copia del mismo. Si el material ya está prestado, la función puede manejar
         * esa lógica internamente.
         */

        void prestarMaterial(MaterialBibliografico* material, string propietario);

        /**
         * @brief Devuelve un material prestado por el usuario.
         * 
         * @param material Puntero a un objeto de tipo MaterialBibliografico que se desea devolver.
         * 
         * @details Esta función permite que el usuario pueda devolver un material que previamente ha tomado prestado.
         * El parámetro "material" es un puntero, lo que permite devolver directamente el material original. La función
         * maneja la lógica de actualizar el estado del material (prestado o no prestado).
         */

        void devolverMaterial(MaterialBibliografico* material);
        
        /**
         * @brief Muestra los materiales que el usuario prestó en la biblioteca.
         */

        void mostrarMaterialesPrestados();

};