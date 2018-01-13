#AWA LWM2M Práctica 4
##Alumnos 
Sergio Semedi Barranco

Lucas Segarra Fernandez

##Memoria


__Utiliza la herramienta awa-client-get para leer el recurso recién creado__

    user-iot@VM-IOT:~/AwaLWM2M/build/tools$ ./awa-client-get /1000
    Heater[/1000/0]:
         Manufacturer[/1000/0/101]: HotAir Systems Inc

__Actualiza el código con las anteriores modificaciones y, además, añade una nueva
función UpdateTemperature() que acepte un valor de temperatura en punto flo-
tante y lo escriba en el nuevo recurso. Añade también un bucle while en la función
main que acepte valores de temperatura proporcionados por consola (para simular
valores reales de un dispositivo, por ejemplo), y use la función creada para actuali-
zar el recurso.__


Añadimos primero mediante código el nuevo recurso del que dispondra el objeto
(temperature):

    user-iot@VM-IOT:~/AwaLWM2M/build/tools$ ./awa-client-get /1000
    Heater[/1000/0]:
         Manufacturer[/1000/0/101]: HotAir Systems Inc
        Temperature[/1000/0/104]: 0

