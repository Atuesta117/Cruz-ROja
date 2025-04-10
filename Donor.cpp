#include "Donor.h" 
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;



//esta funcion elimina los espacios en blanco al principio y al final de una cadena
//el trim se pone primero que el parseLine porque lo usa el parseLine
string Donor::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

//Validacion del tipo de sangre
bool Donor::validBlood(const string& type) 
{
    int contador = 0;
    for (size_t i = 0; i < validBloodTypes.size(); i++)
    {
        if (validBloodTypes[i] == type) 
        {
            return true;
        }
        
        
    }
    
    return false;
}

//esto es el original
void Donor::donorDetails() const
{
    cout << "Nombre del donante: " << name << endl;
    cout << "Distrito del donante: " << district << endl;
    cout << "Tipo de sangre del donante: " << bloodType << endl;
}

//esta funcion se encarga de parsear una linea de texto y crear un objeto Donor a partir de ella
//la idea es que la linea de texto tenga el formato: id, nombre, direccion, distrito, tipo de sangre, numero
//por ejemplo: 1, Juan Perez, Calle Falsa 123, 2, A+, 987654321
//la funcion separa la linea en partes usando la coma como delimitador y asigna cada parte a un atributo del objeto Donor
//Luego de todo este proceso, devuelve el objeto Donor creado
//la funcion se llama parseLine porque es una convencion en C++ para funciones que crean objetos a partir de texto
//Y ademas, es estatica porque no necesita acceder a ningun atributo de la clase Donor para hacer su trabajo
Donor Donor::parseLine(const string& line) 
{
    Donor d;
    stringstream ss(line);
    string token;

    //leemos el id, y lo asignamos a donorId
    getline(ss, token, ','); 
    d.donorId = stoi(trim(token));

    //leemos el nombre, y lo asignamos a name
    getline(ss, token, ','); 
    d.name = trim(token);
    
    //leemos la direccion, y lo asignamos a address
    getline(ss, token, ','); 
    d.address = trim(token);
    
    //leemos el departamento (distrito), y lo asignamos a district
    getline(ss, token, ','); 
    d.district = stoi(trim(token));
    
    //leemos el tipo de sangre, y lo asignamos a bloodType
    getline(ss, token, ','); 
    d.bloodType = trim(token);
    
    //leemos el numero, y lo asignamos a number
    getline(ss, token, ','); 
    d.number = trim(token);// dado que number no es un entero sino un string, se cambio esto d.number = stoi(trim(token));

    //finalmente, devolvemos el objeto Donor creado
    return d;
}

//las validaciones de cada setter

void Donor::setDonorId(int id)
{
    if(id <= 0)
    {
        throw invalid_argument("ID deber ser positivo");
    }
    donorId = id; 
}

void Donor::setDistrict(int dist) 
{
    if (dist < 0 || dist > 7) 
    { 
        throw invalid_argument("Departamento inválido. Ingrese uno de la lista de departamentos.");
    }
    district = dist;
}

void Donor::setNumber(const string& num) 
{
//validar el numero de telefono, de 7 a 15 digitos
    if (num.empty() || num.length() > 15 || num.length() < 7) 
    {
        throw invalid_argument("Número de teléfono inválido");
    }
    number = num;
}

void Donor::setName(const string& nam) 
{
    if (nam.empty()) 
    {
        throw invalid_argument("Nombre no puede estar vacio.");
    }
    name = nam;
}

void Donor::setAddress(const string& addr) 
{
    if (addr.empty()) 
    {
        throw invalid_argument("Dirección no puede estar vacía");
    }
    address = addr;
}    

void Donor::setBloodType(const string& type) 
{
    if (!validBlood(type))  // Negamos la condición
    {
        throw invalid_argument("Tipo de sangre inválido");
    }
    bloodType = type;
}





