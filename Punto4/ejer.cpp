#include <iostream>
using namespace std;

struct Grade
{
    int studentId;
    double grade;
};

void leerNotas(Grade notas[], int n)
{
    char respuesta;
    cout << "¿Desea ingresar las notas manualmente? (s/n): ";
    cin >> respuesta; // Faltaba leer la respuesta

    if (respuesta == 's' || respuesta == 'S')
    {
        for (int i = 0; i < n; i++)
        {
            cout << "Ingrese las notas del estudiante " << i + 1 << " (id, nota): ";
            cin >> notas[i].studentId >> notas[i].grade;
        }
    }
    else
    {
        cout << "Usando valores predeterminados...\n";
        notas[0] = {1010, 1.0};
        notas[1] = {1020, 1.0};
        notas[2] = {1030, 1.0};
        notas[3] = {2056, 1.0};
    }
}

double calcularPromedio(Grade notas[], int n, int &indiceNotaMasAlta)
{
    double suma = 0;
    indiceNotaMasAlta = 0;
    for (int i = 0; i < n; i++)
    {
        suma += notas[i].grade;
        if (notas[i].grade > notas[indiceNotaMasAlta].grade)
        {
            indiceNotaMasAlta = i;
        }
    }
    return suma / n;
}

void mostrarResultado(Grade notas[], int indiceNotaMasAlta, double promedio)
{
    cout << "El id del estudiante con mejor calificación es: " << notas[indiceNotaMasAlta].studentId
         << ", con una nota de " << notas[indiceNotaMasAlta].grade << "\n";
    cout << "La calificación promedio del arreglo es: " << promedio << std::endl;
}

int main()
{
    int n;

    cout << "Ingrese el número de estudiantes (mínimo 2): ";
    cin >> n;

    if (n < 2)
    {
        cout << "Se necesitan al menos 2 estudiantes para determinar el promedio.\n";
        return 1;
    }

    Grade notas[n];

    leerNotas(notas, n);

    int indiceNotaMasAlta;
    double promedio = calcularPromedio(notas, n, indiceNotaMasAlta);
    mostrarResultado(notas, indiceNotaMasAlta, promedio);

    return 0;
}