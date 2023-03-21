#include "estructuras.h"
#include "productos.h"
#include "ventas.h"


struct Productos *raizProducto = NULL;
struct Ventas *raizVenta = NULL;
struct Comprado *raizComprado = NULL;
struct Productos *fondo = NULL;
struct Ventas *fondoVenta = NULL;
struct Comprado *fondoComprado = NULL;

void tiempoActual();

void liberarProductos();
void liberarVentas();
void liberarComprado();


int main(){
    int opc = -1;
    
    while (opc != 0)
    {
        int existeProducto;
        int idVenta;
        tiempoActual();

        
        if(raizProducto != NULL){
            existeProducto = 1;
        }
        else{
            existeProducto = -1;
        }
        

        system("cls");
        printf("\n******* MENU PRINCIPAL *******\n");
        printf("\n1: Registrar venta");
        printf("\n2: Inventario");
        printf("\n3: Listar ventas");
        printf("\n0: Salir");
        printf("\n\nOpcion: ");
        scanf("%i", &opc);

        switch (opc)
        {
        case 1:
            if(existeProducto == 1){

                idVenta = ponerEnElCarrito();
                factura(idVenta);
            }
            else if(existeProducto == -1){
                system("cls");
                printf("\nNo hay productos. Registre algun producto\n");
            }
            getch();
            break;
        case 2:
            menuInventario();
            break;
        case 3:
            if(existeProducto == 1){
                listarTodasLasVentas();
            }
            else if(existeProducto == -1){
                system("cls");
                printf("\nNo hay productos. Registre algun producto\n");
            }
            getch();
            break;
        case 0:
            break;
        default:
            printf("\n\nOpcion no valida");
            getch();
        }

    
    }
    liberarProductos();
    liberarVentas();
    liberarComprado();
    return 0;
}

void menuInventario(){
    int opc;
    while (opc != 0)
    {
        int existe;
        int idProducto;

        system("cls");
        printf("\n******* Menu inventario *******\n");
        printf("\n1: Crear producto");
        printf("\n2: Listar productos");
        printf("\n3: Editar");
        printf("\n4: Borrar");
        printf("\n0: regresar");
        printf("\n\nOpcion: ");
        scanf("%i", &opc);

        switch (opc)
        {
        case 1:
            crearProducto();
            getch();
            break;
        case 2:
            system("cls");
            existe = listarProductos();
            if(existe != 1){
                printf("\nNo hay productos\n");
            }
            getch();
            break;
        case 3:
            system("cls");
            listarProductos();
            printf("\n\nIngrese el ID del producto: ");
            scanf("%i", &idProducto);
            editarProducto(idProducto);
            getch();
            break;
        case 4:
            system("cls");
            listarProductos();
            printf("\n\nIngrese el ID del producto: ");
            scanf("%i", &idProducto);
            eliminarProducto(idProducto);
            getch();
            break;
        case 0:
            break;
        default:
            printf("\n\nOpcion no valida");
        }

    }
}


void tiempoActual(){ // Obtenemos la hora y fecha actuales //
    
    time_t actual = time(NULL); 
    struct tm *tm = localtime(&actual);
    anio= tm->tm_year+1900;
    mes = tm->tm_mon+1;
    dia = tm->tm_mday;
    hora = tm->tm_hour;
    min = tm->tm_min;
    seg = tm->tm_sec;
}


void liberarProductos(){
    struct Productos *reco = raizProducto;
    struct Productos *bor;

    while (reco != NULL)
    {
        bor = reco;
        reco = reco->sig;
        free(bor);
    }
    
}
void liberarVentas(){
    struct Ventas *reco = raizVenta;
    struct Ventas *bor;

    while (reco != NULL)
    {
        bor = reco;
        reco = reco->sig;
        free(bor);
    }
    
}
void liberarComprado(){
    struct Comprado *reco = raizComprado;
    struct Comprado *bor;

    while (reco != NULL)
    {
        bor = reco;
        reco = reco->sig;
        free(bor);
    }
    
}


















