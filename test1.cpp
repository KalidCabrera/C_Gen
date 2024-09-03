#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <vector>

// Función para obtener la primera vocal interna del apellido
std::string obtenerVocalInterna(const std::string& apellido) {
    for (char c : apellido) {
        if (std::tolower(c) != apellido[0] && (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
            return std::string(1, c);
        }
    }
    return "X";
}

// Función para obtener la primera consonante interna de una cadena
std::string obtenerConsonanteInterna(const std::string& cadena) {
    for (char c : cadena) {
        if (std::tolower(c) != cadena[0] && !(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
            return std::string(1, c);
        }
    }
    return "X";
}

// Función para generar un dígito verificador aleatorio
char generarDigitoVerificador() {
    int random = rand() % 36; // 0-9 + A-Z (10 números + 26 letras)
    if (random < 10) {
        return '0' + random; // Números
    } else {
        return 'A' + (random - 10); // Letras
    }
}

// Función para validar si una cadena contiene solo caracteres alfabéticos
bool esAlfabetico(const std::string& cadena) {
    for (char c : cadena) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

// Función para validar si una cadena contiene solo dígitos numéricos
bool esNumerico(const std::string& cadena) {
    for (char c : cadena) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Función para desplegar el menú de selección de estado
std::string seleccionarEstado() {
    std::vector<std::string> estados = {
        "AS - Aguascalientes", "BC - Baja California", "BS - Baja California Sur", "CC - Campeche", "CL - Coahuila",
        "CM - Colima", "CS - Chiapas", "CH - Chihuahua", "DF - Ciudad de México", "DG - Durango", "GT - Guanajuato",
        "GR - Guerrero", "HG - Hidalgo", "JC - Jalisco", "MC - Estado de México", "MN - Michoacán", "MS - Morelos",
        "NT - Nayarit", "NL - Nuevo León", "OC - Oaxaca", "PL - Puebla", "QT - Querétaro", "QR - Quintana Roo",
        "SP - San Luis Potosí", "SL - Sinaloa", "SR - Sonora", "TC - Tabasco", "TS - Tamaulipas", "TL - Tlaxcala",
        "VZ - Veracruz", "YN - Yucatán", "ZS - Zacatecas"
    };

    int opcion = 0;
    std::cout << "Seleccione su estado de nacimiento:\n";
    for (size_t i = 0; i < estados.size(); ++i) {
        std::cout << i + 1 << ". " << estados[i] << std::endl;
    }
    
    do {
        std::cout << "Ingrese el número correspondiente a su estado: ";
        std::cin >> opcion;
    } while (opcion < 1 || opcion > static_cast<int>(estados.size()));

    return estados[opcion - 1].substr(0, 2); // Retorna la clave del estado (las primeras dos letras)
}

// Función para generar la CURP utilizando los datos del usuario
std::string generarCURP(const std::string& nombres, const std::string& primerApellido, const std::string& segundoApellido,
                        const std::string& fechaNacimiento, char sexo, const std::string& estado) {
    std::string curp;
    std::string primerNombre = nombres;

    // Si hay más de un nombre, seleccionar el adecuado
    size_t espacio = nombres.find(' ');
    if (espacio != std::string::npos) {
        std::string primerNombreTemp = nombres.substr(0, espacio);
        std::string segundoNombre = nombres.substr(espacio + 1);

        // Si el primer nombre es "José" o "María", usar el segundo nombre
        if (primerNombreTemp == "José" || primerNombreTemp == "Maria") {
            primerNombre = segundoNombre;
        } else {
            primerNombre = primerNombreTemp;
        }
    }

    // Primera letra y primera vocal interna del primer apellido
    curp += primerApellido[0];
    curp += obtenerVocalInterna(primerApellido);

    // Primera letra del segundo apellido
    curp += segundoApellido[0];

    // Primera letra del primer nombre adecuado
    curp += primerNombre[0];

    // Fecha de nacimiento en formato AAMMDD
    curp += fechaNacimiento;

    // Sexo
    curp += sexo;

    // Clave del estado seleccionado por el usuario
    curp += estado;

    // Primera consonante interna del primer apellido
    curp += obtenerConsonanteInterna(primerApellido);

    // Primera consonante interna del segundo apellido
    curp += obtenerConsonanteInterna(segundoApellido);

    // Primera consonante interna del primer nombre
    curp += obtenerConsonanteInterna(primerNombre);

    // Dígito verificador generado aleatoriamente
    curp += generarDigitoVerificador();

    return curp;
}

int main() {
    srand(time(0)); // Inicializa la semilla para números aleatorios

    std::string nombres, primerApellido, segundoApellido, fechaNacimiento;
    char sexo;

    // Menú para ingresar los datos con validación
    do {
        std::cout << "Ingrese su(s) nombre(s) completo(s) (solo letras): ";
        std::getline(std::cin, nombres);
    } while (!esAlfabetico(nombres));

    do {
        std::cout << "Ingrese su apellido paterno (solo letras): ";
        std::getline(std::cin, primerApellido);
    } while (!esAlfabetico(primerApellido));

    do {
        std::cout << "Ingrese su apellido materno (solo letras): ";
        std::getline(std::cin, segundoApellido);
    } while (!esAlfabetico(segundoApellido));

    do {
        std::cout << "Ingrese su fecha de nacimiento (AAMMDD, solo números): ";
        std::getline(std::cin, fechaNacimiento);
    } while (!esNumerico(fechaNacimiento) || fechaNacimiento.length() != 6);

    do {
        std::cout << "Ingrese su sexo (H/M): ";
        std::cin >> sexo;
        sexo = std::toupper(sexo);
    } while (sexo != 'H' && sexo != 'M');

    // Seleccionar el estado de nacimiento
    std::string estado = seleccionarEstado();

    // Generar y mostrar la CURP
    std::string curp = generarCURP(nombres, primerApellido, segundoApellido, fechaNacimiento, sexo, estado);
    std::cout << "CURP generada: " << curp << std::endl;

    return 0;
}

