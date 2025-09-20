#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Grade {
    int studentId;
    double grade;
};

void leerNotas(vector<Grade> &notas) {
    char respuesta;
    int n = notas.size();

    cout << "¿Desea ingresar las notas manualmente? (s/n): ";
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        for (int i = 0; i < n; ++i) {
            while (true) {
                cout << "Ingrese las notas del estudiante " << i + 1 << " (id nota): ";
                int id;
                double cal;
                cin >> id >> cal;

                if (cin.fail()) {
                    cout << "Entrada invalida. Intente de nuevo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (cal < 0.0 || cal > 5.0) {
                    cout << "La nota debe estar en el rango 0.0 - 5.0. Intente otra vez.\n";
                    continue;
                }

                notas[i].studentId = id;
                notas[i].grade = cal;
                break;
            }
        }
    } else {
        cout << "Usando valores predeterminados...\n";
        // Conjunto predeterminado (si n > defaults.size() usamos repetición/modulo)
        vector<Grade> defaults = {
            {1, 3.0},
            {20, 4.0},
            {56, 5.0},
            {1010, 2.5}
        };
        for (int i = 0; i < n; ++i) {
            notas[i] = defaults[i % defaults.size()];
        }
    }
}

double calcularPromedio(const vector<Grade> &notas, int &indiceNotaMasAlta) {
    double suma = 0.0;
    indiceNotaMasAlta = 0;
    for (size_t i = 0; i < notas.size(); ++i) {
        suma += notas[i].grade;
        if (notas[i].grade > notas[indiceNotaMasAlta].grade) {
            indiceNotaMasAlta = static_cast<int>(i);
        }
    }
    return suma / static_cast<double>(notas.size());
}

void mostrarResultado(const vector<Grade> &notas, int indiceNotaMasAlta, double promedio) {
    cout << "\nEl id del estudiante con mejor calificación es: "
         << notas[indiceNotaMasAlta].studentId
         << ", con una nota de " << notas[indiceNotaMasAlta].grade << "\n";
    cout << "La calificación promedio del arreglo es: " << promedio << endl;
}

int main() {
    int n;
    cout << "Ingrese el número de estudiantes (mínimo 2): ";
    while (!(cin >> n) || n < 2) {
        cout << "Entrada inválida. Ingrese un entero >= 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<Grade> notas(n); // ahora es seguro y portátil

    leerNotas(notas);

    int indiceNotaMasAlta;
    double promedio = calcularPromedio(notas, indiceNotaMasAlta);

    mostrarResultado(notas, indiceNotaMasAlta, promedio);

    return 0;
}