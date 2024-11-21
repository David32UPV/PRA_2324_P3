#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        // miembros públicos
		// Atributos
		T elem;					// Elemento de tipo T (genérico) almacenado en el nodo
		BSNode<T>* left;		// Puntero al nodo sucesor izquierdo
		BSNode<T>* right;		// Puntero al nodo sucesor derecho

		// Métodos
		
		// Constructor -> Crea un BSNode con el elemento elem y los punteros a los nodos sucesores left y right proporcionados (que apuntan por defecto a nullptr)
		BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr){
			this->elem = elem;
			this->left = left;
			this->right = right;
		}

		// Sobrecarga global del operador << para imprimir el nodo por pantalla. Por simplicidad, imprimir solo el atributo elem
		friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
			out << bsn.elem;
			return out;
		}
};

#endif
