#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

/**
 * @class Libro
 * @brief Clase hija de MaterialBibliografico que representa un material bibliográfico de tipo Libro.
 *
 * Esta clase contiene la información común de un Libro,
 * como el títuloLibro, el autor, el isbn y el prestado, sumado a sus atributos específicos como la fechaPublicacion y el resumen.
 */

class Libro: public MaterialBibliografico {

    private:
        int fechaPublicacion; /**< Fecha de publicación del Libro */
        string resumen; /**< Resumen del Libro */
    
    public:

        /**
         * 
         * @brief Constructor de Libro.
         * 
         * @param fechaPublicacion La fecha de publicación del Libro
         * @param resumen Variable que explica un pequeño resumen del Libro.
         * @param tituloLibro El título del Libro.
         * @param autor El autor del Libro.
         * @param isbn El isbn del Libro.
         * @param prestado Variable que indica el estado del Libro.
         * 
         * 
         */

        Libro(int fechaPublicacion, string resumen, string tituloLibro, string autor, 
                string isbn, bool prestado);
        
        /**
         * @brief Método para mostrar la información del Libro.
         */
        
        void mostrarInformacion() override;
        
        /**
         * @brief Consigue la fecha de publicación del Libro.
         */

        int getFechaPublicacion() const;

        /**
         * @brief Consigue el resumen del Libro.
         */

        string getResumen() const;

};