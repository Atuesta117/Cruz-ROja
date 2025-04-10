
/*
		Clase: BloodDatabase
		Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
		Universidad del Valle

		Información CRC:
		
		Clase: BloodDatabase

		Responsabilidades:
				- Gestionar una base de datos de donantes de sangre, almacenando 
					un conjuto de objetos de tipo `Donor`.
				- Proveer métodos para agregar, eliminar y buscar donantes en la base de datos.
				- Facilitar el manejo de la información almacenada de forma eficiente y 
					adecuada para su consulta y modificación.

		Colaboradores:
				- Colabora directamente con la clase `Donor`, ya que administra una colección 
					de objetos `Donor`.
					
		Lista de deseos: 
				- Crear una clase utilitarista que incluya las funciones de waitForKeyPress() y 
					clearConsole() ya que son funciones que no tienen relación con la clase BloodDatabase.
					Ademas, se podria utilizar para proximos proyectos, pues seria una clase "independiente"
					a cualquier programa.

		Este es un proyecto del curso FPOO de la Universidad del Valle, 
		desarrollado con fines académicos. Puede ser utilizado con fines 
		académicos dando los créditos de la autoría.

		El código se basó en el proyecto BloodDatabase, fue traducido al español 
		y adaptado a las necesidades del curso.

		Autor: Victor Bucheli
		Correo: victor.bucheli@correounivalle.edu.co
		Fecha: Octubre 2024
*/
#ifndef BLOODDATABASE_H
#define BLOODDATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Donor.h"
using namespace std;

class BloodDatabase {
		private:
				const string fileName = "data.txt"; //abrir el archivo data.txt Contiene la base de datos
				vector<Donor> donors; // Vector para almacenar los donantes
				//funcion para ahorrar codigo
				static void displayProvinces();
				string to_upper_case(const string& str); // Convertir a mayúsculas
		public:
				static void clearConsole(); // Limpiar la consola
				static void waitForKeyPress();// Esperar a que el usuario presione una tecla

				// Función para validar la entrada del usuario y asegurarse de que sea un número entero
				static int getValidatedInput(const string& prompt); 

				// Funciones para agregar donantes a la base de datos
				void getDonorDetails(); //obtener detalles del donante
				void writeDataToFile(); //escribir datos en el archivo .txt (en la base datos)

				// Funcion para buscar donantes
				void searchAndDisplay() const; //buscar y mostrar los donantes. Es constante porque solo queremos leer los datos de los users
				
				// Función para eliminar un donante
				void deleteDonor(const string& donorName); //eliminar donante

				// Funcion para cumplir indicadores del punto #1 del laboratorio: 
				// Porcentaje de donantes por tipo de sangre y el tipo de sangre más común
				void mostrarEstadisticasSangre();

};

#endif // BLOODDATABASE_H
