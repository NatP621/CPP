// natane.djedou@gmail.com //
#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
#include <sstream>
class Complex {
private:
    double real;   // Real part
    double imag;   // Imaginary part
public:
    // Default constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    // Getters
    double getReal() const { return real; }
    double getImag() const { return imag; }
    // Setters
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }
    // Stream output operator
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << " + " << c.imag << "i)";
        return os;
    }
};
#endif // COMPLEX_HPP