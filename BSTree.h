#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        //miembros privados
		// Atributos privados
		int n_elem;				// Nº de elementos almacenados en el ABB (Arbol Binario de Búsqueda). Esta variable es en sí un contador (incrementarla y decrementarla)
		BSNode<T>* root;		// Nodo raíz del ABB
		
		// Métodos privados
		// Método recursivo para la búsqueda de elementos en el ABB. Busca y devuelve el elemento e si se encuentra en el subárbol cuya raíz es n
		// De lo contrario (si no encuentra e en dicho subárbol) lanza un std::runtime_error
		BSNode<T>* search(BSNode<T>* n, T e) const{
			// El caso base es cuando hemos recorrido el árbol y no hemos encontrado e
			if(n == nullptr)
				throw std::runtime_error("No se ha encontrado el elemento");
			// Casos recursivos
			else if(n->elem < e)
				 return search(n->right, e);
			else if(n->elem > e)
				return search(n->left, e);
			else
				// Devolvemos el nodo raíz
				return n;
		}

		// Método recursivo para la inserción ordenada de elementos -> Inserta el elemento e de manera ordenada en el subárbol cuya raíz es n.
		// Devuelve el nodo que encabeza dicho subárbol modificado. Si el elemento e ya existe, lanza un std::runtime_error()
		BSNode<T>* insert(BSNode<T>* n, T e){
			// Casos base
			// Si mi raíz apunta a nullptr, debo crear un nuevo nodo al que apunte la raíz
			if(n == nullptr){
				n = new BSNode<T>(e);
				// Incrementamos el contador de elementos del ABB justo cuando nos creamos el nodo
				n_elem++;
			}
			// Si el elemento e a insertar ya existe en el árbol, lanzamos excepción
			else if(n->elem == e){
				throw std::runtime_error("El elemento ya existe en el árbol");
			}

			// Casos recursivos
			// Si el elemento de la raíz es < e, inserto e en el subárbol derecho
			else if(n->elem < e){
				n->right = insert(n->right, e);
			}
			// Si el elemento de la raíz es > e, inserto e en el subárbol izquierdo
			else{
				n->left = insert(n->left, e);
			}
			// Incrementamos el contador del número de elementos en el ABB
			// Al final, devolvemos el nodo que encabeza el subárbol modificado
			return n;
		}
		
		// Reorrido en inorden del subárbol cuya raíz es n para mostrar a través de out los elementos ordenados de menor a mayor
		void print_inorder(std::ostream &out, BSNode<T>* n) const{
			if(n != nullptr){
				print_inorder(out, n->left);
				out << n->elem << " ";
				print_inorder(out, n->right);
			}
		}
		
		// Método recursivo que elimina el elemento e del subárbol cuya raíz es n. Devuelve el nodo que encabeza dicho subárbol modificado (i.e. n).
		// En caso de eliminar un nodo con 2 sucesores (izquierdo y derecho), aplicará la política de reeemplazo por el elemento máximo del subárbol izquierdo. Para ello
		// se apoyará en los métodos privados auxiliares max() y remove_max(). Si el elemento e NO existe, lanza un std::runtime_error()
		BSNode<T>* remove(BSNode<T>* n, T e){
			// Caso base (si el elemento no existe)
			if(n == nullptr){
				throw std::runtime_error("No existe el elemento en el árbol");
			}
			// Casos recursivos
			else if(n->elem < e){
				n->right = remove(n->right, e);
			}
			else if(n->elem > e){
				n->left = remove(n->left, e);
			}
			else{
				// Decrementamos el contador del número de elementos en el ABB en el punto donde se identifica que el nodo actual n contiene el elemento a eliminar.
				// Es en este momento cuando sabemos que el ABB perderá un elemento (decrementamos el contador antes de llamar a reove_max())
				n_elem--;
				// Si eliminamos un nodo con 2 sucesores, i.e. tanto izquierda como derecha apuntan a algo
				if(n->left != nullptr && n->right != nullptr){
					// Reemplazo por el elemento máximo del subárbol izquierdo (y lo eliminas)
					n->elem = max(n->left);
					n->left = remove_max(n->left);
				}
				// Si hay 1 o 0 descendientes
				else{
					// Si la izquierda apunta a algo, que nuestra raíz apunte a eso
					if(n->left != nullptr){
						n = n->left;
					}
					// Si la derecha apunta a algo, que nuestra ráiz apunte a eso
					else{
						n = n->right;
					}
				}

			}
			// Devolvemos el nodo que encabeza el subárbol en el que hemos eliminado el nodo
			return n;
		}
		
		// Método recursivo que devuelve el elemento de máximo valor (n->elem) contenido en el subárbol cuya raíz es n
		// Si la raíz apunta a nullptr lanzamos un std::runtime_error
		T max(BSNode<T>* n) const{
			// Caso base
			if(n == nullptr){
				throw std::runtime_error("No hay ningún elemento en el árbol");
			}
			// Casos recursivos
			if(n->right != nullptr){
				return max(n->right);
			}
			else{
				return n->elem;
			}

		}
		
		// Método recursivo que elimina el elemento de máximo valor (n->elem) contenido en el subárbol cuya raíz es n
		BSNode<T>* remove_max(BSNode<T> *n){
			// Caso base 
			if(n->right == nullptr){
				return n->left;
			}
			// Caso recursivo
			else{
				n->right = remove_max(n->right);
				return n;
			}
		}
		
		// Método recursivo para la liberación de la memoria dinámica ocupada por los objetos de tipo BSNode<T> que conforman el subárbol cuya raíz es n
		void delete_cascade(BSNode<T>* n){
			// Caso base -> Si no hay más nodos que procesar
			if(n == nullptr)
				return;
			// Casos recursivos
			// Antes de liberar el nodo actual n usando delete, primero debemos liberar los subárboles izquierdo y derecho, para que así los nodos descendientes sean
			// liberados antes que el actual
			delete_cascade(n->left);
			delete_cascade(n->right);
			// Liberamos la memoria dinámica del nodo actual usando delete
			delete n;
		}

    public:
        // miembros públicos
		// Los métodos públicos invocan las funciones recursivas correspondientes sobre el nodo raíz root
		// Métodos públicos

		// Constructor -> Crea un ABB vacío (como está vacío NO hay root)
		BSTree(){
			n_elem = 0;
			root = nullptr;
		}
		
		// Devuelve el nº de elementos n_elem del ABB (la llamamos tras haner incrementado o decrementado n_elem)
		int size() const{
			return n_elem;
		}
		
		// Busca y devuelve el elemento e de tipo T en el ABB. Actúa como método lanzadera del método privado recursivo search(BSNode<T>* n, T e)
		// Deberá devolver el elemento contenido por el nodo devuelto por el método privado (i.e. llamar a la función usando una variable de tipo genérica)
		T search(T e) const{
			return search(root, e)->elem;
		}
		
		// Sobrecarga del operador []. Actúa como interfaz al método search(T e).
		T operator[](T e) const{
			return search(e);
		}

		// Inserta el elemento e de manera ordenada en el ABB. Actúa como método lanzadera del método privado recursivo insert(BSNode<T>* n, T e)
		void insert(T e){
			root = insert(root, e);
		}
		
		// Sobrecarga global del operador << para mostrar a través de out los contenidos del ABB bst, realizando un recorrido en inorden para mostrar los elementos
		// ordenados de menor a mayor. Esta función delega en el método privado recursivo print_inorder().
		friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
			bst.print_inorder(out, bst.root);
			return out;
		}

		// Elimina el elemento e del ABB. Actúa como método lanzadera del método privado recursivo remove(BSNode<T>* n, T e)
		void remove(T e){
			root = remove(root, e);
		}

		// Método destructor. Delega en el método privado recursivo delete_cascade()
		~BSTree(){
			delete_cascade(root);	
		}
	 
};

#endif
