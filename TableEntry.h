#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

// Los pares clave->valor se representan mediante la siguiente clase genérica TableEntry<V>, con tipo std::string para las claves y tipo parámetrico V para los valores
template <typename V> class TableEntry {
    public:
        // miembros públicos
		
		// Atributos
		std::string key;	// Elemento clave del par
		V value;			// Elemento valor del par
		
		// Métodos
		// Sugerencia: sobrecargar los operadores == y != para determinar que los pares clave->valor se comparan solo usando la clave. Esto nos servirá para detectar 
		// colisiones de claves en la posterior implementación (la siguiente clase vaya)
    
		// Constructor 1 -> Inicializamos el par clave->valor
		TableEntry(std::string key, V value){
			this->key = key;
			this->value = value;
		}

		// Constructor 2 -> Crea una entrada solo con clave (sin valor)
		TableEntry(std::string key){
			this->key = key;
		}
		
		// Constructor 3 -> Crea una entrada con la clave "" (cadena vacía) y sin valor
		TableEntry(){
			key = "";
		}
		
		// Sobrecarga global del operador == para determinar que 2 instancias de TableEntry son iguales solo si comparten la misma clave (con independencia de valor)
		friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
			return (te1.key == te2.key);
		}

		// Sobrecarga global del operador != para determinar que 2 instancias de TableEntry son diferentes solo si sus claves son distintas (con independencia de valor)
		friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
			// Negamos el resultado del operador ==
			return !(te1 == te2);
		}

		// Sobrecarga global del operador < para determinar que una instancia de TableEntry es menor que otra si su key es menor
		friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){
			return (te1.key < te2.key);
		}
	
		// Sobrecarga global del operador > para determinar que una instancia de TableEntry es mayor que otra si su key es mayor
		friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){
			// Negamos el resultado del operador <
			return !(te1.key < te2.key);
		}

		// Sobrecarga global de operador << para imprimir el contenido de la entrada (par clave->valor) por pantalla
		friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
			out << "('" << te.key << "' => " << te.value << ")";
			return out;
		}
		
};

#endif
