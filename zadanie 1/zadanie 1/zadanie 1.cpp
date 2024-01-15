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

#include <iostream>

void printComplexNumber(const ComplexNumber& num, const std::string& label) {
    std::cout << label << ": ";
     num.display();
    std::cout << std::endl;
}

int main() {
    // Создаем объекты ComplexNumber для тестирования
    ComplexNumber num1(3, 4);
    ComplexNumber num2(1, 2);

    // Выводим первоначальные значения
    printComplexNumber(num1, "Initial Number 1");
    printComplexNumber(num2, "Initial Number 2");

    // Тест для функции add
    ComplexNumber resultAdd = num1.add(num2);
    printComplexNumber(resultAdd, "Addition Result");

    // Тест для функции subtract
    ComplexNumber resultSubtract = num1.subtract(num2);
    printComplexNumber(resultSubtract, "Subtraction Result");

    // Тест для функции multiply
    ComplexNumber resultMultiply = num1.multiply(num2);
    printComplexNumber(resultMultiply, "Multiplication Result");

    // Тест для функции divide
    ComplexNumber resultDivide = num1.divide(num2);
    printComplexNumber(resultDivide, "Division Result");

    // Тест для функции power
    ComplexNumber resultPower = num1.power(2);
    printComplexNumber(resultPower, "Power Result");

    // Тесты для операторов сравнения с целыми и дробными числами
    std::cout << "Equality Test (int): " << (num1 == 3) << std::endl;
    std::cout << "Inequality Test (float): " << (num2 != 2.5f) << std::endl;

    return 0;
}
