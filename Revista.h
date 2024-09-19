#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

/**
 * @class Revista
 * @brief Clase hija de MaterialBibliografico que representa un material bibliográfico de tipo Revista.
 *
 * Esta clase contiene la información común de una Revista,
 * como el títuloLibro, el autor, el isbn y el prestado, sumado a sus atributos específicos como el numEdicion y el mesPublicacion.
 */

class Revista: public MaterialBibliografico {

    private:
        int numEdicion; /**< Número de edición de la revista */
        int mesPublicacion; /**< Mes de publicación de la revista */

    public:
        
        /**
         * 
         * @brief Constructor de Revista.
         * 
         * @param numEdicion El número de edición de la Revista
         * @param mesPublicacion El mes de publicación de la Revista.
         * @param tituloLibro El título de la Revista.
         * @param autor El autor de la Revista.
         * @param isbn El isbn de la Revista.
         * @param prestado Variable que indica el estado de la Revista.
         * 
         * 
         */

        Revista(int numEdicion, int mesPublicacion, string tituloLibro, string autor, 
                    string isbn, bool prestado);
        
        /**
         * @brief Método para mostrar la información de la Revista.
         */

        void mostrarInformacion() override;

        /**
         * @brief Consigue el número de edición de la revista.
         */

        int getNumEdicion() const;

        /**
         * @brief Consigue el mes de publicación de la revista.
         */

        int getMesPublicacion() const;
};