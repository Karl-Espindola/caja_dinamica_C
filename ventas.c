#include "estructuras.h"
#include "productos.h"
#include "ventas.h"



int ponerEnElCarrito(){

    struct Ventas *venta;
    venta = malloc(sizeof(struct Ventas));
    venta->sig = NULL;
    struct Ventas *recoVenta;

    struct Productos producto;
    int opc1;
    int id = 0;
    char nombreComprador[80];
    

    /* ID autoincrementable para las ventas */

    recoVenta = raizVenta;

    while (recoVenta != NULL)
    {
        id = recoVenta->id;
        recoVenta = recoVenta->sig;
    }

    if(id == 0){
        venta->id = 1;
        raizVenta = venta;
        fondoVenta = venta;
    }
    /* Fin autoincrementable para las ventas */
    else{

        fondoVenta->sig = venta;
        fondoVenta = venta;  
    }

    /* Asignación de la fecha a la venta */
    venta->id = id + 1;
    venta->tiempo.anio = anio;
    venta->tiempo.mes = mes;
    venta->tiempo.dia= dia;
    venta->tiempo.hora = hora;
    venta->tiempo.min = min;
    venta->tiempo.seg = seg;

    system("cls");
    fflush(stdin);
    printf("\nIngrese el nombre del comprador: ");
    gets(nombreComprador);
    strcpy(venta->comprador, nombreComprador);
    
    int existe;
    int cantidadAnterior = 0;
    struct Comprado *prev = NULL;
    while(opc1 != 2){
        
        system("cls");
        existe = listarProductos();
        if(existe != 1){
            printf("\nNo hay productos\n");
            return -1;
        }
        else if(existe == 1){
            printf("\n\n----- Productos en el Carrito -----\n");

            if(raizComprado != NULL){

                struct Comprado *reco = raizComprado;
                while(reco != NULL){
                    if(reco->idVenta == venta->id){

                        producto = consultarProducto(reco->idProducto);
                        printf("\nProducto: %s cantidad: %i total: $%.2f", 
                        producto.nombre, reco->cantidad, reco->precioTotal);
                    }
                    reco = reco->sig;
                }
                
            }
           

            printf("\n-------------------");
            printf("\n1: Elegir producto");
            printf("\n2: Finalizar compra");
            printf("\nOpcion: ");
            scanf("%i", &opc1);
                
            if(opc1 == 1){

                
                struct Comprado *productoComprado;
                int codProducto;
                system("cls");
                listarProductos();
                printf("\n\nIngrese el ID del producto: ");
                scanf("%i", &codProducto);

                int facturado = 0;
                
                if(raizComprado != NULL){

                    struct Comprado *reco = raizComprado;
                    while(reco != NULL){
                        if(reco->idProducto == codProducto && reco->idVenta == venta->id){
                            productoComprado = reco;
                            facturado = 1;
                            break;
                        }
                        reco = reco->sig;
                    }
                }
                if(facturado != 1){
                    nodoProductoComprado();
                    productoComprado = fondoComprado;
                    productoComprado->idVenta = venta->id;
                    productoComprado->idProducto = codProducto;
                    productoComprado->cantidad = 0;
                    
                }
                if(prev != productoComprado && prev != NULL){
                    cantidadAnterior = productoComprado->cantidad;
                }

                producto = consultarProducto(productoComprado->idProducto);

                if(producto.id != -1 ){ //Producto existe
                    if(producto.cantidad <= 0){
                        system("cls");
                        printf("\nNo hay existencias disponibles");
                        getch();
                        continue;
                    }
                }
                else if(producto.id == -1){
                    system("cls");
                    printf("\nEste producto No existe");
                    getch();
                    continue;
                }

                
                int cantidadStock = producto.cantidad;
                int cantidad = 0;
                do{
                    printf("\nIngrese la cantidad: ");
                    scanf("%i", &cantidad);

                    if(cantidad > cantidadStock){
                        printf("\nNo tenemos esa cantidad. Puede llevar maximo %i unidades\n", producto.cantidad);
                    }
                }while(cantidad > producto.cantidad);
                
                restarStock(producto.id, cantidad);
                productoComprado->cantidad = cantidadAnterior + cantidad;
                cantidadAnterior = productoComprado->cantidad;
                productoComprado->precioTotal = productoComprado->cantidad * producto.precio;
                prev = productoComprado;
            }
        } 
    }
    float suma = 0;
    if(raizComprado != NULL){

        struct Comprado *reco = raizComprado;
        while(reco != NULL){
            if(reco->idVenta == venta->id){

                suma = suma + reco->precioTotal;
            }
            reco = reco->sig;
        }
    }

    venta->total = suma; // Precio total por todos los productos comprados
    int id_venta = venta->id;
    
    
    return id_venta;

}


void nodoProductoComprado(){

    struct Comprado *nodo;
    nodo = malloc(sizeof(struct Comprado));
    nodo->sig = NULL;

    if(raizComprado == NULL){
        raizComprado = nodo;
        fondoComprado = nodo;
    }
    else{
        fondoComprado->sig = nodo;
        fondoComprado = nodo;
    }
}







void listarTodasLasVentas(){
    struct Ventas *recoV = raizVenta;
    int i = 1;
  
    if(recoV == NULL){
        system("cls");
        printf("\nNo hay ninguna\n");
    }
    system("cls");
    while(recoV != NULL){
        factura(i);
        printf("\n");
        i++;
        recoV = recoV->sig;
    }
}

void factura(int idVenta){ //Imprime la factura 
   
    struct Productos producto;

    struct Ventas *reco = raizVenta;
    
    while(reco != NULL){
        if(reco->id == idVenta){
            break;
        }
        reco = reco->sig;
    }

    printf("\n------------------ FACTURA ----------------\n");
    printf("\nID: %i  Nombre: %s Fecha %.2d/%.2d/%.2d  %.2d:%.2d:%.2d\n", reco->id, reco->comprador, 
    reco->tiempo.dia, reco->tiempo.mes, reco->tiempo.anio, reco->tiempo.hora, reco->tiempo.min, reco->tiempo.seg);
    
   
    if(raizComprado != NULL){

        struct Comprado *reco2 = raizComprado;
        while(reco2 != NULL){
            if(reco2->idVenta == idVenta){

                producto = consultarProducto(reco2->idProducto);
                printf("\nProducto: %s cantidad: %i total: $%.2f", 
                producto.nombre, reco2->cantidad, reco2->precioTotal);
            }
            reco2 = reco2->sig;
        }
    }
 
    printf("\nTOTAL:                             $%.2f\n", reco->total);
    printf("--------------------------------------------");

}