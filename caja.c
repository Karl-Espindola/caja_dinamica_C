#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


typedef struct{
    int anio;
    int mes;
    int dia;
    int hora;
    int min;
    int seg;
}Fecha;

typedef struct{
    int id;
    int idProducto;
    int cantidad;
    float precioTotal;
}Comprado;

struct Ventas{
    int id;
    Fecha tiempo;
    char comprador[80];
    Comprado compra[100];
    int cantidadDeProductos;    //Numero de productos diferentes agregados a la compra
    float total;
    struct Ventas *sig;

};

struct Productos{
    int id;
    char nombre[80];
    int precio;
    int cantidad;
    struct Productos *sig;
};

struct Productos *raizProducto = NULL;
struct Ventas *raizVenta = NULL;
struct Productos *fondo = NULL;
struct Ventas *fondoVenta = NULL;

int anio;
int mes;
int dia;
int hora;
int min;
int seg;



int crearProducto();
int ponerEnElcarrito();
struct Productos consultarProducto(int idProducto);
int listarProductos();
void editarProducto(int idProducto);
void eliminarProducto(int idProducto);
struct Productos restarStock(int idProducto, int cantidad);
int verificarProuctosRepetidos(char nomProducto[80]);

void tiempoActual();
void factura(int idVenta);
void listarTodasLasVentas();

void menuInventario();

void liberarProductos();
void liberarVentas();

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

                idVenta = ponerEnElcarrito();
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
    void liberarProductos();
    void liberarVentas();
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

// ##########################################################





int crearProducto(){

    char nombreProducto[80];
    int id = 0;
    int existe = 0;

    struct Productos *producto;
    
    struct Productos *bor;
    producto = malloc(sizeof(struct Productos));

    producto->sig = NULL;
    


    /* ID autoincrementable para Productos */


    struct Productos *reco = raizProducto;

    while (reco != NULL)
    {
        id = reco->id;
        reco = reco->sig;
    }
    if(id != 0){
        producto->id = id + 1;
        /* Fin de autoincrementable para Productos */

        fondo->sig = producto;
        fondo = producto;

        system("cls");
        fflush(stdin);
        printf("\nIngresa el nombre del producto: ");
        gets(nombreProducto);
        existe = verificarProuctosRepetidos(nombreProducto);
        if(existe == 1){
            printf("\nEste producto ya existe");
            return 0;
        }
        printf("\nIngresa el precio del producto: ");
        scanf("%i", &producto->precio);
        printf("\nIngresa el cantidad del producto: ");
        scanf("%i", &producto->cantidad);
        strcpy(producto->nombre, nombreProducto);

        if(producto->precio >= 0 && producto->cantidad >= 0){
            
            printf("\nProducto Registrado\n");
        }
        else{
            raizProducto = raizProducto->sig;
            bor = producto;
            free(bor);
            printf("\nNo se admiten valores negativos. Registro cancelado\n");
        }
    }
    else{
        producto->id = 1;
        raizProducto = producto;
        fondo = producto;
        system("cls");
        fflush(stdin);
        printf("\nIngresa el nombre del producto: ");
        gets(nombreProducto);
        existe = verificarProuctosRepetidos(nombreProducto);
        if(existe == 1){
            printf("\nEste producto ya existe");
            getch();
            return 0;
        }
        printf("\nIngresa el precio del producto: ");
        scanf("%i", &producto->precio);
        printf("\nIngresa el cantidad del producto: ");
        scanf("%i", &producto->cantidad);
        strcpy(producto->nombre, nombreProducto);

        if(producto->precio >= 0 && producto->cantidad >= 0){
            printf("\nProducto Registrado\n");
        }
        else{
            raizProducto = raizProducto->sig;
            bor = producto;
            free(bor);
            printf("\nNo se admiten valores negativos. Registro cancelado\n");
        }
    }

    return 0;
}



int listarProductos(){
   
    // struct Productos *producto;
    struct Productos *reco;
    reco = raizProducto;
    int existe;
   
    while (reco != NULL)
    {
        existe = 1;
        printf("\nID: %i  Producto: %s  Precio: $%i  Cantidad: %i", reco->id, reco->nombre, reco->precio, reco->cantidad);
        reco = reco->sig;
    }

    return existe;
}

struct Productos consultarProducto(int idProducto){
    struct Productos *reco = raizProducto;
    
    while(reco != NULL){
        if(reco->id == idProducto){
            
            return *reco;
        }
        reco = reco->sig;
    }
    reco->id = -1;

    return *reco;
}


void editarProducto(int idProducto){
    
    struct Productos *reco;
    reco = raizProducto;

    char nuevoNombre[80];
    int nuevaCantidad;
    float nuevoPrecio;
    int existe;
    

    while(reco != NULL){
        if(reco->id == idProducto){
            fflush(stdin);
            printf("\nIngrese el nuevo titulo: \n");
            fgets(nuevoNombre, 79, stdin);

            if(strcmp(nuevoNombre, "\n") != 0){ //Si se presiona Enter, entonces deja el nombre originar sin modificar

                strcpy(reco->nombre, nuevoNombre);
            }
            
            printf("Ingrese la nueva cantidad: \n");
            scanf("%i", &nuevaCantidad);
            printf("Ingrese el nuevo precio: \n");
            scanf("%f", &nuevoPrecio);
            
            if(nuevaCantidad > 0 && nuevoPrecio >= 0){
                    
                reco->cantidad = nuevaCantidad;
                reco->precio = nuevoPrecio;
                
                printf("\nEl producto fue editado\n");
            }
            else{
                printf("\nCantidad o Precio menor a 0. No se realizo ningun cambio");
            }
            existe = 1;
            break;
        }
        reco = reco->sig;
    }
    if(existe != 1){
        printf("\nEl producto no existe\n");
    }
}


void eliminarProducto(int idProducto){

    struct Productos *reco;
    struct Productos *prev;
    struct Productos *bor;
    reco = raizProducto;
    int existe;

    while (reco != NULL)
    {
        if(reco->id == idProducto){
            existe = 1;
            prev->sig = reco->sig;
            bor = reco;
            free(bor);
            break;
        }
        prev = reco;
        reco = reco->sig;
    }
    if(existe != 1){
        printf("\nEL producto no existe\n");
    }
    else{
        printf("\nProducto eliminado\n\n");
    }
    
}

struct Productos restarStock(int idProducto, int cantidad){ // Cada vez que se registra la venta de un producto, se resta la cantidad comprada del inventario 
    
    struct Productos *reco = raizProducto;

    while (reco != NULL){
        if(reco->id == idProducto){
            reco->cantidad = reco->cantidad - cantidad;
            break;
        }
        reco = reco->sig;
    }
    return *reco;
}

int verificarProuctosRepetidos(char nomProducto[80]){
    
    struct Productos *reco = raizProducto;
  
    while (reco != NULL)
    {
        if(strcmp(nomProducto, reco->nombre) == 0){
            
            return 1;
        }   
        reco = reco->sig;
    }

    return 0;
}

// ################################################################

int ponerEnElcarrito(){
    
    struct Ventas *venta;
    venta = malloc(sizeof(struct Ventas));
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
        venta->sig = NULL;
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
    int i = 0;
    int existe;
    int cantidad = 0;
    int acumulador;

    while(opc1 != 2){
        
        system("cls");
        existe = listarProductos();
        if(existe != 1){
            printf("\nNo hay productos\n");
            return -1;
        }
        else if(existe == 1){
            printf("\n\n----- Productos en el Carrito -----\n");
            for (int x = 0; x < i; x++){
                
                producto = consultarProducto(venta->compra[x].idProducto);
                printf("\nProducto: %s cantidad: %i total: $%.2f", 
                producto.nombre, venta->compra[x].cantidad, venta->compra[x].precioTotal);
            }
            printf("\n-------------------");
            printf("\n1: Elegir producto");
            printf("\n2: Finalizar compra");
            printf("\nOpcion: ");
            scanf("%i", &opc1);
            
            if(opc1 == 1){

                system("cls");
                listarProductos();
                printf("\n\nIngrese el ID del producto: ");
                scanf("%i", &venta->compra[i].idProducto);
                producto = consultarProducto(venta->compra[i].idProducto);

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
                do{
                    int facturado;
                    cantidadStock = producto.cantidad;
                    for(int j = 0; j < i; j++){
                        if(venta->compra[j].idProducto == producto.id){
                            
                            facturado = 1;
                            printf("\nIngrese la cantidad: ");
                            scanf("%i", &acumulador);
                            
                            if(acumulador > producto.cantidad){
                                printf("\nNo tenemos esa cantidad. Puede llevar maximo %i unidades\n", producto.cantidad);
                            }
                            else{
                                producto = restarStock(producto.id, acumulador);
                                cantidad = venta->compra[j].cantidad;
                                venta->compra[j].cantidad = (cantidad + acumulador);
                                venta->compra[j].precioTotal = (producto.precio) * (venta->compra[j].cantidad);
                            } 
                        }

                    }

                    if(facturado != 1){
                        acumulador = 0;
                        cantidad = 0;
                        
                        printf("\nIngrese la cantidad: ");
                        scanf("%i", &acumulador);
                        venta->compra[i].cantidad = cantidad + acumulador;
                        cantidad = venta->compra[i].cantidad;
                        if(acumulador > producto.cantidad){
                            printf("\nNo tenemos esa cantidad. Puede llevar maximo %i unidades\n", producto.cantidad);
                        }
                        else{
                     
                            producto = restarStock(producto.id, acumulador);
                            venta->compra[i].precioTotal = (producto.precio) * (venta->compra[i].cantidad);
 
                        }
                    }
                    facturado = 0;
                }
                while(acumulador > cantidadStock );

                venta->compra[i].precioTotal = (producto.precio) * (venta->compra[i].cantidad);
                
                int z = i;
                int repetido = 0;

                for (int x = 0; x < z; x++){
                    if(venta->compra[i].idProducto == venta->compra[x].idProducto ){
                        repetido = 1;
                        cantidad = 0;
                        acumulador = 0;
                        
                    }
                }
                
                if(repetido != 1){
                    
                    i = i + 1;
                }
                
            }
            else if(opc1 == 2){
                break;
            } 
        }
    }
    float suma = 0;
    for(int x = 0; x < i; x++){
        suma = suma + venta->compra[x].precioTotal;
    }
    venta->total = suma; // Precio total por todos los productos comprados
    venta->cantidadDeProductos = i; //Numero de productos registrados en la compra. Este numero se usa despues para recorrer la lista de compras
    int id_venta = venta->id;
    
    
    return id_venta;
    
}

void listarTodasLasVentas(){
    struct Ventas *recoV = raizVenta;
    int i = 1;
  
    if(recoV == NULL){
        system("cls");
        printf("\nNo hay ninguna\n");
        getch();
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
    
    int i = reco->cantidadDeProductos;
    for (int x = 0; x < i; x++){
        
        producto = consultarProducto(reco->compra[x].idProducto);
        printf("\nProducto: %s cantidad: %i total: $%.2f", 
        producto.nombre, reco->compra[x].cantidad, reco->compra[x].precioTotal);
    }
    printf("\nTOTAL:                             $%.2f\n", reco->total);
    printf("--------------------------------------------");

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




















