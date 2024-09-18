#ifndef ENTRADA_NO_NUMERICA_EXCEPTION_H
#define ENTRADA_NO_NUMERICA_EXCEPTION_H

#include <exception>

class EntradaNoNumericaException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Entrada inválida: tipo de caracter no válido.";
    }
};

#endif