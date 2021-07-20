**1.Matrix & operator=(const Matrix & m);**

- **La matrix apuntada por this debe tener el mismo contenido que m.**
- **¿¿¿El puntero apunta a distintos sitios (no se realiza copia)??.**
- **Mismos Index de columnas y filas.**
- **Mismo tamaño (NxM)**
- **La matriz m sigue teniendo el valor que tenía al principio. No se elimina nada.**
- **No se realiza copia al escribir m1=m1**

**2.Matrix & operator\*=(double val);** 

- **Cada elemento de la matriz this debe ser multiplicado por val.**
- **No afecta el número de columnas ni de filas**
- **No afecta a los índices.**
- **Devuelve la posición de memoria de this.**

**3.Matrix & operator+=(double val);** 

- **Cada elemento de la matriz this debe incrementar su valor en val.**
- **No afecta el número de columnas ni de filas.**
- **Devuelve la posición de memoria de this.**

**4.Matrix operator\*(const Matrix & m) const;** 

- **La matriz resultante debe tener las filas de la matriz this y las columnas de la matriz m.**
- **NO multiplica matrices con dimensiones incorrectas. Todos los elementos a npos (3x3).**
- **Cada posición (i,j) debe ser producto escalar de la fila i de la matriz this y la columna j de la matriz m.**
- **El resultado no debe de ser igual si se cambia el orden de la multiplicación 5.Matrix operator\*(double val) const;** 
- **La matriz resultante debe tener el mismo tamaño.**
- **Mismos índices, filas y columnas que el original.**
- **Cada elemento debe ser igual al original \* val**

**6.Matrix operator+(double val) const;** 

- **La matriz resultante debe tener el mismo tamaño.** 
- **Mismos índices, filas y columnas que el original.**
- **Cada elemento de la matriz nueva debe incrementar su valor en val respecto de la matriz señalada.** 

**7.const double & at(const string & row, const string & col)** 

**const;**

- **Cuando “row” o “col” son inválidos, devuelve un número entero negativo (npos).**
- **Devuelve el valor [row][col] de la matriz, sin permisos para editarlo.**

**8.double & at(const string & row, const string & col);** 

- **Cuando “row” o “col” son inválidos, ¿assert?**
- **Devuelve el valor [row][col] de la matriz, con permisos para editarlo.**

**9.const double & operator()(const string & row, const string &** 

**col) const;**

- **Mismos que at. No debe ser modificable.**

**10.double & operator()(const string & row, const string & col);**

- **Mismos que at. Ha de ser modificable.**
