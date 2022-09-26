/**
 * @brief Escribe un subárbol
 * 
 * @tparam Tbase Tipo de dato que conforma el subárbol
 * @param flujo stream de saliad en el que escribir
 * @param n nodo del que cuelga el subárbol a escribir
 * 
 * Escribe los nodos del subárbol en el flujo de salida siguiendo un recorrido
 * en preorden. Si un nodo tiene dos hijos se escribe "n" seguido de un espacio
 * en blanco y la etiqueta del nodo, si solo tiene hijo a la izquierda se 
 * escribe "l" seguido de un espacio en blanco y la etiqueta del nodo, 
 * si solo tiene hijo a la derecha se escribe "r" seguido de un espacio
 * en blanco y la etiqueta del nodo y si no tiene hijos se escribe "h".
 */
template <class Tbase>
void ArbolBinario<Tbase>::escribe_arbol(ostream& flujo, Nodo n) const{
  if(n->izqda == nullptr && n->drcha == nullptr){
      flujo << "h " << n->etiqueta << " ";
  }
  else if(n->drcha == nullptr){
      flujo << "l " << n->etiqueta << " ";
      escribe_arbol(flujo, n->izqda);
  }
  else if(n->izqda == nullptr){
      flujo << "r " << n->etiqueta << " ";
      escribe_arbol(arbol, n->drcha);
  }
  else{
    flujo << "n " << n->etiqueta << " ";
    escribe_arbol(flujo, n->izqda);
    escribe_arbol(flujo, n->drcha);
    }
}

/**
 * @brief Lee un subárbol
 * 
 * @tparam Tbase Tipo de dato que conforma el subárbol
 * @param flujo stream de entrada desde el que leer
 * @param n referencia al nodo que contendrá el subárbol leido
 * 
 * Lee la entrada del contenido de un árbol en el formato descrito en la función
 * de escritura. @see ArbolBinario\<Tbase>::escribe_arbol
 */
template <class Tbase>
void ArbolBinario<Tbase>::lee_arbol(istream &flujo, Nodo &n){
  char c;
  flujo >> c;
  if (c=='n'){
    n = new nodo;
    flujo >> n->etiqueta;
    lee_arbol(flujo, n->izqda);
    lee_arbol(flujo, n->drcha);
    n->izqda->padre = n;
    n->drcha->padre = n;
  }
  else if (c == 'r'){
    n = new nodo;
    flujo >> n->etiqueta;
    lee_arbol(flujo, n->drcha);
    n->drcha->padre = n;
  }
  else if (c == 'l'){
      n = new nodo;
      flujo >> n->etiqueta;
      lee_arbol(flujo, n->izqda);
      n->izqda->padre = n;
  }
  else if (c == 'h'){
      n = new nodo;
      flujo >> n->etiqueta;
  }
}
