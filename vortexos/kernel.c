void _kernel_main(void) {
    // Apuntamos directamente a la memoria de la pantalla de la computadora
    char *pantalla = (char*)0xB8000;
    
    // Texto que queremos mostrar
    char *texto = "Bienvenido a VortexOS!";
    
    // Limpiamos la pantalla (escribiendo espacios vacios)
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        pantalla[i] = ' ';
        pantalla[i+1] = 0x0F;
    }

    // Escribimos nuestro mensaje en la esquina superior izquierda
    int i = 0;
    int j = 0;
    while (texto[i] != '\0') {
        pantalla[j] = texto[i];     // Ponemos la letra
        pantalla[j+1] = 0x0F;       // Ponemos el color (Blanco)
        i++;
        j += 2;                     // Saltamos al siguiente espacio
    }
}
