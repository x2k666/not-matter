#include <iostream>
#include <cmath>

class ComplexNumber {
private:
    double real;
    double imag;

public:
    ComplexNumber(double real, double imag) : real(real), imag(imag) {}

    double getReal() const { return real; }
    void setReal(double real) { this->real = real; }

    double getImag() const { return imag; }
    void setImag(double imag) { this->imag = imag; }

    ComplexNumber add(const ComplexNumber& other) const
    {
        return ComplexNumber(real + other.real, imag + other.imag);
    }

    ComplexNumber subtract(const ComplexNumber& other) const
    {
        return ComplexNumber(real - other.real, imag - other.imag);
    }

    ComplexNumber multiply(const ComplexNumber& other) const
    {
        double real_part = real * other.real - imag * other.imag;
        double imag_part = real * other.imag + imag * other.real;
        return ComplexNumber(real_part, imag_part);
    }

    ComplexNumber divide(const ComplexNumber& other) const
    {
        double denominator = other.real * other.real + other.imag * other.imag;
        double real_part = (real * other.real + imag * other.imag) / denominator;
        double imag_part = (imag * other.real - real * other.imag) / denominator;
        return ComplexNumber(real_part, imag_part);
    }

    bool operator==(const ComplexNumber& other) const { return real == other.real && imag == other.imag; }

    bool operator!=(const ComplexNumber& other) const { return !(*this == other); }
    // Сравнение комплексных чисел с целыми и с дробными
    bool operator==(int num) const { return (real == static_cast<double>(num) && imag == 0); }

    bool operator!=(int num) const { return !(*this == num); }

    bool operator==(float num) const { return (real == static_cast<double>(num) && imag == 0); }

    bool operator!=(float num) const { return !(*this == num); }

    bool operator==(double num) const { return (real == num && imag == 0); }

    bool operator!=(double num) const { return !(*this == num); }

    void display() const
    {
        std::cout << real << " + " << imag << "i" << std::endl;
    }

    ComplexNumber power(int n) const // аргумент - степень
    {
        // Получение модуля и аргумента текущего комплексного числа
        double r = std::pow(modulus(), n);
        double theta = n * argument();

        // Вычисление новых действительной и мнимой частей по формуле Эйлера
        // z^n = r^n * (cos(n * theta) + i * sin(n * theta))
        double real_part = r * std::cos(theta);
        double imag_part = r * std::sin(theta);
        return ComplexNumber(real_part, imag_part);
    }

    double modulus() const { return std::sqrt(real * real + imag * imag); }

    double argument() const { return std::atan2(imag, real); }
};

int main() {
    ComplexNumber num1(2, 3);
    ComplexNumber num2(1, 2);

    // Получение/установка действительной и мнимой части
    std::cout << "Real part of num1: " << num1.getReal() << std::endl;
    std::cout << "Imaginary part of num1: " << num1.getImag() << std::endl;

    num1.setReal(5);
    num1.setImag(7);

    std::cout << "Updated num1: ";
    num1.display();

    // Сложение, вычитание, умножение, деление
    ComplexNumber sum_result = num1.add(num2);
    std::cout << "Sum: ";
    sum_result.display();

    ComplexNumber diff_result = num1.subtract(num2);
    std::cout << "Difference: ";
    diff_result.display();

    ComplexNumber product_result = num1.multiply(num2);
    std::cout << "Product: ";
    product_result.display();

    ComplexNumber divide_result = num1.divide(num2);
    std::cout << "Divide: ";
    divide_result.display();

    // Сравнение
    if (num1 == num2)
        std::cout << "num1 is equal to num2" << std::endl;
    else
        std::cout << "num1 is not equal to num2" << std::endl;

    // Возведение в степень
    ComplexNumber power_result = num1.power(2);
    std::cout << "num1 squared: ";
    power_result.display();

    // Модуль и аргумент
    std::cout << "Modulus of num1: " << num1.modulus() << std::endl;
    std::cout << "Argument of num1: " << num1.argument() << " radians" << std::endl;

}
