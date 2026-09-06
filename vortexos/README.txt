======================================================================
               Manual de VORTEXOS v2.0              
======================================================================

VortexOS es un sistema operativo interactivo de 16 bits que se ejecuta
directamente sobre el hardware a bajo nivel mediante un emulador.

----------------------------------------------------------------------
1. REQUISITOS PREVIOS
----------------------------------------------------------------------
* Tener instaladas las herramientas de MSYS2 y QEMU en Windows.
* Tener la carpeta del proyecto en el Escritorio llamada: vortexos
* Asegurarse de que el archivo "vortexos.bin" este dentro de esa carpeta.

----------------------------------------------------------------------
2. PASOS PARA ARRANCAR EL SISTEMA OPERATIVO
----------------------------------------------------------------------
Paso 1: Abre el menu de inicio de Windows y busca la consola "MSYS2".
Paso 2: Entra a la carpeta del sistema escribiendo este comando:

   cd /c/Users/TU_USUARIO/Desktop/vortexos

   (IMPORTANTE: Cambia TU_USUARIO por tu nombre de usuario de Windows)

Paso 3: Enciende la computadora virtual ejecutando este comando:

   /c/msys64/ucrt64/bin/qemu-system-i386 -fda vortexos.bin

----------------------------------------------------------------------
3. MANUAL DE USO DE LA CONSOLA (SHELL DE VORTEXOS)
----------------------------------------------------------------------
Una vez que se abra la ventana de QEMU, HAZ CLIC CON EL RATON ADENTRO
para que el sistema operativo capture tu teclado.

Veras el indicador "> " en la pantalla. Escribe cualquiera de los 
siguientes comandos en minusculas y presiona ENTER para ejecutarlo:

   blue     -> Cambia el fondo de la pantalla a AZUL.
   red      -> Cambia el fondo de la pantalla a ROJO.
   green    -> Cambia el fondo de la pantalla a VERDE.
   dark     -> Vuelve la pantalla al fondo NEGRO clasico.
   clear    -> Borra todo el texto y limpia la pantalla.
   shutdown -> Apaga la computadora virtual por completo.

* Nota: El sistema detecta la tecla "Backspace" para borrar letras. 
  Si escribes un comando desconocido, el sistema mostrara "Err".

======================================================================
                  Gracias por leer <3                   
======================================================================
