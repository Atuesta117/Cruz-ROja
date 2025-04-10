
    /*
        Proyecto: BloodDatabase (Adaptado)
        Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
        Universidad del Valle

        Descripción:
        Este proyecto gestiona una base de datos de donantes de sangre, proporcionando 
        funcionalidades para registrar, buscar y analizar la información de los donantes.

        El código se basó en el proyecto BloodDatabase, fue traducido al español 
        y adaptado a las necesidades del curso.

        g++ main.cpp BloodDatabase.cpp Donor.cpp -o prog
        

        Autor: Victor Bucheli
        Correo: victor.bucheli@correounivalle.edu.co
        Fecha: Octubre 2024
    */
    #include "BloodDatabase.h"
    #include "Donor.h"
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include <limits>
    #include <stdexcept>
    #include <cctype>
    #include <algorithm>
    #include "PhoneValidator.h"
    #include <curl/curl.h>


    using namespace std;
    inline std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");
        size_t end = str.find_last_not_of(" \t\r\n");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    void BloodDatabase::displayProvinces() {
        std::cout << "Elige el departamento:\n";
        std::cout << "1. Putumayo\n";
        std::cout << "2. Cauca\n";
        std::cout << "3. Valle del Cauca\n";
        std::cout << "4. Amazonas\n";
        std::cout << "5. Risaralda\n";
        std::cout << "6. Antioquia\n";
        std::cout << "7. Norte de Santander\n";
    }

    void BloodDatabase::clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        //   system("clear");
    #endif
    }
    std::string toUpperCase(const std::string& str) {
        std::string result = str;
        for (char& c : result)
            c = std::toupper(static_cast<unsigned char>(c));
        return result;
    }


    void BloodDatabase::waitForKeyPress() {
        std::cout << "Presiona cualquier tecla para continuar...";
        std::cin.ignore();
        std::cin.get();
    }

    int BloodDatabase::getValidatedInput(const std::string& prompt) {
        int value;
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            try
            {
                if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
                    throw std::invalid_argument("La entrada contiene caracteres no numéricos");
                }
                value = std::stoi(input);
                break; // si la conversión es exitosa, salir del bucle
            } 
            catch (const std::invalid_argument& e) 
            {
                std::cout << "Entrada no válida: " << e.what() << ". Por favor ingrese un número válido." << std::endl;
            } 
            catch (const std::out_of_range&) 
            {
                std::cout << "Entrada fuera de rango. Por favor ingrese un número válido." << std::endl;
            }
        }
        return value;
    }

    void BloodDatabase::getDonorDetails() {
        clearConsole();
        std::string nombreDonante;
        std::string direccionDonante;
        std::string tipoSangreDonante;
        std::string numeroDonante;

        std::cout << "Ingrese los detalles del donante\n";

        //estoy cambiendo cosas en get donorDetails
        //en caso de qye fucnione, getvalidatedInput() es la funcion que he podido reutilizar en elc odigo, solo cambiando de si es int o str
        Donor newDonor;
        newDonor.setDonorId(getValidatedInput("Id: " ));

        std::cout << "Nombre: ";
        getline(std::cin, nombreDonante);
        newDonor.setName(nombreDonante);


        //std::getline(std::cin, newDonor.getName());
        std::cout << "Dirección: ";
        getline(std::cin, direccionDonante);
        newDonor.setAddress(direccionDonante);

        //std::getline(std::cin, newDonor.address);

        displayProvinces();
        //newDonor.district = getValidatedInput("Departamento (ingrese el número correspondiente): ");
        newDonor.setDistrict((getValidatedInput("Departamento (ingrese el número correspondiente): " )));


        while (true) {
            std::cout << "Tipo de sangre (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
            getline(std::cin, tipoSangreDonante);
        
            tipoSangreDonante = Donor::trim(toUpperCase(tipoSangreDonante));
        
            if (newDonor.validBlood(tipoSangreDonante)) {
                newDonor.setBloodType(tipoSangreDonante);
                break; // tipo válido
            } else {
                std::cout << "Tipo de sangre no válido. Intente de nuevo.\n";
            }
        }
        
        
        //newDonor.number = getValidatedInput("Número: ");
        while(true){
        PhoneValidator validador ("4B836698810C4FF6B7C56C4431318D80");
        std::cout << "Número de móvil: ";
        getline(std::cin, numeroDonante);
        if (validador.esNumeroValido(numeroDonante)) {
            std::cout << "Número de móvil válido.\n";
            newDonor.setNumber(numeroDonante);
            break; // Salir del bucle si es válido
        } else {
            std::cout << "Número de móvil no válido. Intente de nuevo.\n";
        }

        
    }

    donors.push_back(newDonor);
    }

    void BloodDatabase::writeDataToFile() {
        std::ofstream outfile(fileName, std::ios::app);

        if (!outfile) {
            std::cout << "Error al abrir el archivo para escribir." << std::endl;
            return;
        }

        Donor newDonor = donors.back();
        //cambiamos cada uno de los atributos por su respectivo getter, para leer los datos
        outfile << newDonor.getDonorId() << ",    " << newDonor.getName() << ",    " << newDonor.getAddress() << ",    " << newDonor.getDistrict() << ",    " << newDonor.getBloodType() << ",    " << newDonor.getNumber() << std::endl;

        outfile.close();
    }

    void BloodDatabase::searchAndDisplay() const {
        clearConsole();
        displayProvinces();
        int provinceName = getValidatedInput("Ingrese el número del departamento: ");

        std::cout << "Ingrese la dirección (dejar en blanco para omitir): ";
        std::string addressFilter;
        std::getline(std::cin, addressFilter);

        std::cout << "Ingrese el tipo de sangre (dejar en blanco para omitir): ";
        std::string bloodTypeFilter;
        std::getline(std::cin, bloodTypeFilter);

        std::ifstream inFile(fileName);

        if (!inFile) {
            std::cout << "Error al abrir el archivo para leer." << std::endl;
            return;
        }

        std::vector<Donor> donors;
        std::string line;
        bool found = false;

        while (std::getline(inFile, line)) {
            Donor d = Donor::parseLine(line);
            bool match = d.getDistrict() == provinceName &&
                (addressFilter.empty() || d.getAddress().find(addressFilter) != std::string::npos) &&
                (bloodTypeFilter.empty() || d.getBloodType() == bloodTypeFilter);

            if (match) {
                donors.push_back(d);
                found = true;
            }
        }

        if (!found) 
        {
            std::cout << "No se encontraron personas del departamento " << provinceName;
            if (!addressFilter.empty()) 
            {
                std::cout << " con dirección que contiene '" << addressFilter << "'";
            }
            if (!bloodTypeFilter.empty()) {
                std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
            }
            std::cout << "." << std::endl;
        } 

        else 
        {
            std::cout << "Personas del departamento " << provinceName;
            if (!addressFilter.empty()) 
            {
                std::cout << " con dirección que contiene '" << addressFilter << "'";
            }
            if (!bloodTypeFilter.empty()) 
            {
                std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
            }
            std::cout << ":" << std::endl;
            
            //aca tambien cambie los atributos por sus respectivos getters (mejor dicho, en todas las partes del codigo que tenga getters. Alli estuve cambiando atributos por getters)
            for (const auto& d : donors) {
                std::cout << "Id: " << d.getDonorId() << std::endl;
                std::cout << "Nombre: " << d.getName() << std::endl;
                std::cout << "Dirección: " << d.getAddress() << std::endl;
                std::cout << "departamento: " << d.getDistrict() << std::endl;
                std::cout << "Tipo de sangre: " << d.getBloodType() << std::endl;
                std::cout << "Número de móvil: " << d.getNumber() << std::endl;
                std::cout << std::endl;
            }
        }

        inFile.close();
        waitForKeyPress();
    }

    void BloodDatabase::deleteDonor(const std::string& donorName) {
        std::ifstream inFile(fileName);
        std::ofstream tempFile("temp.txt");

        if (!inFile) {
            std::cerr << "Error al abrir el archivo " << fileName << std::endl;
            return;
        }

        if (!tempFile) {
            std::cerr << "Error al crear el archivo temporal" << std::endl;
            return;
        }

        std::string line;
        bool found = false;

        while (std::getline(inFile, line)) {
            Donor d = Donor::parseLine(line);
            if (d.getName() == donorName) {
                found = true;
                std::cout << "Nombre: " << d.getName() << std::endl;
                std::cout << "Dirección: " << d.getAddress() << std::endl;
                std::cout << "Tipo de sangre: " << d.getBloodType() << std::endl;
                std::cout << "Número de móvil: " << d.getNumber() << std::endl;
                std::cout << std::endl;
                std::cout << "¿Está seguro de que desea eliminar al donante? [s/n]: ";
                char sureChoice;
                std::cin >> sureChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descartar cualquier entrada extra

                if (sureChoice == 's' || sureChoice == 'S') {
                    continue;
                }
            }

            tempFile << d.getDonorId() << ",    " << d.getName() << ",    " << d.getAddress() << ",    " << d.getDistrict() << ",    " << d.getBloodType() << ",    " << d.getNumber() << std::endl;
        }

        inFile.close();
        tempFile.close();

        if (std::remove(fileName.c_str()) != 0) {
            std::cerr << "Error al eliminar el archivo original" << std::endl;
            return;
        }

        if (std::rename("temp.txt", fileName.c_str()) != 0) {
            std::cerr << "Error al renombrar el archivo temporal" << std::endl;
            return;
        }

        if (!found) {
            std::cout << "No se encontró ningún donante con el nombre " << donorName << std::endl;
        }
    }

    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <map>
    #include <iomanip>
    #include <limits> // Para limpiar cin

    void BloodDatabase::mostrarEstadisticasSangre() {
        std::ifstream file("data.txt"); // Abrimos el archivo que contiene los donantes
        if (!file) {
            std::cerr << "No se pudo abrir el archivo.\n";
            return;
        }

        std::map<std::string, int> conteoTipos; // Mapa para contar cada tipo de sangre
        int totalDonantes = 0;
        std::string linea;

        // Leemos cada línea del archivo
        while (std::getline(file, linea)) {
            std::stringstream ss(linea);
            std::string campo;
            int campoIndex = 0;
            std::string tipoSangre;

            // Separamos los campos por comas
            while (std::getline(ss, campo, ',')) {
                campoIndex++;

                // El campo 5 es el tipo de sangre
                if (campoIndex == 5) {
                    tipoSangre = campo;

                    // Limpiamos espacios al inicio y final
                    tipoSangre.erase(0, tipoSangre.find_first_not_of(" \t"));
                    tipoSangre.erase(tipoSangre.find_last_not_of(" \t") + 1);

                    // Convertimos a mayúsculas por consistencia
                    for (auto& c : tipoSangre) c = toupper(c);

                    // Contamos ese tipo de sangre
                    conteoTipos[tipoSangre]++;
                    totalDonantes++;
                    break;
                }
            }
        }

        // Si no hay donantes registrados, avisamos
        if (totalDonantes == 0) {
            std::cout << "No hay donantes registrados aún.\n";
            return;
        }

        int opcion;
        // Menú para el usuario
        std::cout << "\n¿Qué deseas ver?\n";
        std::cout << "1. Porcentajes de cada tipo de sangre\n";
        std::cout << "2. Tipo de sangre más común\n";
        std::cout << "Ingrese su elección: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiamos el buffer

        switch (opcion) {
            case 1:
                std::cout << "\nPorcentaje por tipo de sangre:\n";
                for (const auto& par : conteoTipos) {
                    double porcentaje = (par.second * 100.0) / totalDonantes;
                    std::cout << " - " << par.first << ": " << std::fixed << std::setprecision(2)
                            << porcentaje << "% (" << par.second << " donantes)\n";
                }
                break;

            case 2: {
                std::string tipoDominante;
                int maxCantidad = 0;

                // Primero encontramos la cantidad máxima
                for (const auto& par : conteoTipos) {
                    if (par.second > maxCantidad) {
                        maxCantidad = par.second;
                    }
                }

                // Luego revisamos cuántos tipos tienen esa cantidad
                std::vector<std::string> tiposMaximos;
                for (const auto& par : conteoTipos) {
                    if (par.second == maxCantidad) {
                        tiposMaximos.push_back(par.first);
                    }
                }

                // Si hay más de un tipo con la misma cantidad máxima → empate
                if (tiposMaximos.size() > 1) {
                    std::cout << "\nNo hay un tipo de sangre dominante. Hay un empate entre:\n";
                    for (const auto& tipo : tiposMaximos) {
                        std::cout << " - " << tipo << " (" << conteoTipos[tipo] << " donantes)\n";
                    }
                } else {
                    // Si solo hay uno, es el dominante
                    tipoDominante = tiposMaximos[0];
                    std::cout << "\nTipo de sangre más común: " << tipoDominante
                            << " (" << conteoTipos[tipoDominante] << " donantes)\n";
                }
                break;
            }

            default:
                std::cout << "Opción no válida.\n";
        }
    }
