#include <iostream>
#include <cmath>
#include <limits> // para numeric_limits

// Definir la estructura de una nota (grade)
struct Grade
{
    int studentId;
    double grade;
};

// Función para leer las coordenadas de varias notas
void leerNotas(Grade notas[], int n)
{
    char respuesta;
    std::cout << "¿Desea ingresar las notas manualmente? (s/n): ";
    std::cin >> respuesta; // leer la respuesta del usuario

    // Verificar si la respuesta es 's' o 'S'
    if (respuesta == 's' || respuesta == 'S')
    {
        for (int i = 0; i < n; ++i)
        {
            while (true)
            {
                std::cout << "Ingrese las notas del estudiante " << i + 1 << " (id nota): ";
                int id;
                double cal;
                std::cin >> id >> cal;

                if (std::cin.fail())
                {
                    std::cout << "Entrada invalida. Intente de nuevo.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                if (cal < 0.0 || cal > 5.0)
                {
                    std::cout << "La nota debe estar en el rango 0.0 - 5.0. Intente otra vez.\n";
                    continue;
                }

                notas[i].studentId = id;
                notas[i].grade = cal;
                break;
            }
        }
    }
    else
    {
        // Usar valores predeterminados (si n > defaults, se reciclan)
        std::cout << "Usando valores predeterminados...\n";
        Grade defaults[4] = {
            {1010, 1.0},
            {1020, 1.0},
            {1030, 1.0},
            {2056, 1.0}
        };
        for (int i = 0; i < n; ++i)
        {
            notas[i] = defaults[i % 4];
        }
    }
}

// Función para calcular la mayor magnitud (promedio) y encontrar índice de nota más alta
double calcularPromedio(Grade notas[], int n, int &indiceNotaMasAlta)
{
    double suma = 0.0;
    indiceNotaMasAlta = 0;

    for (int i = 0; i < n; ++i)
    {
        suma += notas[i].grade;
        if (notas[i].grade > notas[indiceNotaMasAlta].grade)
        {
            indiceNotaMasAlta = i;
        }
    }

    return suma / static_cast<double>(n);
}

// Función para mostrar el promedio y estudiante con mayor nota
void mostrarResultado(Grade notas[], int indiceNotaMasAlta, double promedio)
{
    std::cout << "El id del estudiante con mejor calificación es: " 
              << notas[indiceNotaMasAlta].studentId
              << ", con una nota de " << notas[indiceNotaMasAlta].grade << "\n";
    std::cout << "La calificación promedio del arreglo es: " << promedio << std::endl;
}

int main()
{
    int n;

    std::cout << "Ingrese el número de estudiantes (mínimo 2): ";
    std::cin >> n;

    if (std::cin.fail() || n < 2)
    {
        std::cout << "Se necesitan al menos 2 estudiantes para determinar el promedio.\n";
        return 1;
    }

    // Reservar arreglo dinámico para respetar la firma original (Grade notas[n]; no es estándar)
    Grade *notas = new Grade[n];

    // Leer las notas (manual o predeterminado)
    leerNotas(notas, n);

    // Calcular promedio
    int indiceNotaMasAlta;
    double promedio = calcularPromedio(notas, n, indiceNotaMasAlta);

    // Mostrar el resultado
    mostrarResultado(notas, indiceNotaMasAlta, promedio);

    // Liberar memoria
    delete[] notas;

    return 0;
}