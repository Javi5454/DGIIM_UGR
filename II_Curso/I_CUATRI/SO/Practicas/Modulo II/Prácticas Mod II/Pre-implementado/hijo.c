

// Creación de un hijo con fork

    pid_t PID;

    if ((PID = fork()) < 0) {   // si hay error al crearlo
        
        perror("\nError en fork hijo");
        exit(EXIT_FAILURE);
        
    } else if (PID == 0) {  // estamos en el hijo

        // código hijo

    } else {    // estamos en el padre

        // código padre

        // recogida del hijo para que no queden procesos zombie
        if (waitpid (PID, NULL, WNOHANG) == -1) { 
                printf ("\nError al esperar al hijo\n");
                exit(EXIT_FAILURE);
        }

    }