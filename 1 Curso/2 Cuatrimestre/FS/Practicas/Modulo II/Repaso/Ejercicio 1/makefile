# Nombre archivo: makefile
# Uso: make 
# Descripción: Mantiene todas las dependencias entre los módulos y la biblioteca
#              que utiliza el Practica7.

LIB_DIR=./
INCLUDE_DIR=./includes
CC=g++

Practica7: main2.o factorial.o hello.o libmath.a
	$(CC) -L$(LIB_DIR) -o $@ $^ -lmath

main2.o: main2.cpp $(INCLUDE_DIR)/functions.h $(INCLUDE_DIR)/mates.h
	$(CC) -I$(INCLUDE_DIR)/ -c $^

libmath.a: cos.o sin.o tan.o
	ar -rvs libmath.a $^

cos.o: cos.cpp $(INCLUDE_DIR)/mates.h
	$(CC) -I $(INCLUDE_DIR) -c $^

sin.o: sin.cpp $(INCLUDE_DIR)/mates.h
	$(CC) -I $(INCLUDE_DIR) -c $^

tan.o: tan.cpp $(INCLUDE_DIR)/mates.h
	$(CC) -I$(INCLUDE_DIR) -c $^

hello.o: hello.cpp $(INCLUDE_DIR)/functions.h
	$(CC) -I $(INCLUDE_DIR) -c $^

factorial.o: factorial.cpp $(INCLUDE_DIR)/functions.h
	$(CC) -I $(INCLUDE_DIR) -c $^

cleanObj:
	rm main2.o factorial.o hello.o sin.o cos.o tan.o 
