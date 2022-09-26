# Sistemas Operativos

# Alumno: Javier Gómez López

# DGIIM 2º Grupo A

# Makefile para la compilacion de los programas pedidos en la sesion
# 7 de las prácticas de esta asignatura

CPPFLAGS = -Wall -g -c
BIN = bin
OBJ = obj
CXX = gcc

# Regla ALL para compilar todo
 all: clientes proxy server

 # Creamos los ejecutables en bin

 server: $(OBJ)/server.o
	-mkdir -p $(BIN)
	$(CXX) -o $(BIN)/server $(OBJ)/server.o

clientes: $(OBJ)/clientes.o
	-mkdir -p $(BIN)
	$(CXX) -o $(BIN)/clientes $(OBJ)/clientes.o

proxy: $(OBJ)/proxy.o
	-mkdir -p $(BIN)
	$(CXX) -o $(BIN)/proxy $(OBJ)/proxy.o

# Creamos los codigo objeto

$(OBJ)/server.o: server.c
	-mkdir -p $(OBJ)
	$(CXX) $(CPPFLAGS) server.c -o $(OBJ)/server.o

$(OBJ)/clientes.o: clientes.c
	-mkdir -p $(OBJ)
	$(CXX) $(CPPFLAGS) clientes.c -o $(OBJ)/clientes.o

$(OBJ)/proxy.o: proxy.c
	-mkdir -p $(OBJ)
	$(CXX) $(CPPFLAGS) proxy.c -o $(OBJ)/proxy.o


# Codigo de limpieza de los ejecutables
clean:
	-rm -r $(OBJ)/* $(BIN)/*
	-rmdir $(OBJ) $(BIN)