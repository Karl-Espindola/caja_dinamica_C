#ifndef _ESTRUCTURAS_
#define _ESTRUCTURAS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

// #ifndef _FECHA_
// #define _FECHA_
typedef struct{
    int anio;
    int mes;
    int dia;
    int hora;
    int min;
    int seg;
}Fecha;
// #endif //fin de fecha

// #ifndef _COMPRADO_
// #define _COMPRADO_
struct Comprado{
    int id;
    int idVenta;
    int idProducto;
    int cantidad;
    float precioTotal;
    struct Comprado *sig;
};
// #endif //fin de comprado

// #ifndef _VENTAS_
// #define _VENTAS_
struct Ventas{
    int id;
    Fecha tiempo;
    char comprador[80];
    struct Comprado *listaCompra;
    int cantidadDeProductos;    //Numero de productos diferentes agregados a la compra
    float total;
    struct Ventas *sig;

};
// #endif // fin de comprado

// #ifndef _PRODUCTOS_
// #define _PRODUCTOS_
struct Productos{
    int id;
    char nombre[80];
    int precio;
    int cantidad;
    struct Productos *sig;
};

// #ifndef _PUNTEROS_
// #define _PUNTEROS_ 
extern struct Productos *raizProducto;
extern struct Ventas *raizVenta;
extern struct Comprado *raizComprado;
extern struct Productos *fondo;
extern struct Ventas *fondoVenta;
extern struct Comprado *fondoComprado;
// #endif

int anio;
int mes;
int dia;
int hora;
int min;
int seg;

#endif