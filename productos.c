#include "estructuras.h"
#include "productos.h"
#include "ventas.h"

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

        system("cls");
        fflush(stdin);
        printf("\nIngresa el nombre del producto: ");
        gets(nombreProducto);
        
        existe = verificarProuctosRepetidos(nombreProducto);
        if(existe == 1){
            // raizProducto = raizProducto->sig;
            fondo->sig = NULL;
            bor = producto;
            free(bor);
            printf("\nEste producto ya existe");
            return 0;
        }
        printf("\nIngresa el precio del producto: ");
        scanf("%i", &producto->precio);
        printf("\nIngresa el cantidad del producto: ");
        scanf("%i", &producto->cantidad);
        strcpy(producto->nombre, nombreProducto);


        if(producto->precio >= 0 && producto->cantidad >= 0){
        
            fondo->sig = producto;
            fondo = producto;
            printf("\nProducto Registrado\n");
        }
        else{
            
            fondo->sig = NULL;
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

       
        printf("\nIngresa el precio del producto: ");
        scanf("%i", &producto->precio);
        printf("\nIngresa el cantidad del producto: ");
        scanf("%i", &producto->cantidad);
        strcpy(producto->nombre, nombreProducto);

        if(producto->precio >= 0 && producto->cantidad >= 0){
            printf("\nProducto Registrado\n");
        }
        else{
            raizProducto = NULL;
            bor = producto;
            free(bor);
            printf("\nNo se admiten valores negativos. Registro cancelado\n");
        }
            
    }


    return 0;
}

int listarProductos(){
   
    struct Productos *reco;
    reco = raizProducto;
    int existe;
   
    while (reco != NULL)
    {
        existe = 1;
        printf("\nID: %i  Producto: %s  Precio: $%i  Cantidad: %i", 
        reco->id, reco->nombre, reco->precio, reco->cantidad);
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

            char caracteres[] = "\n";
            if(strcmp(nuevoNombre, "\n") != 0){ //Si se presiona Enter, entonces deja el nombre originar sin modificar
                removerCaracteres(nuevoNombre, caracteres);
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
    struct Productos *prev = NULL;
    struct Productos *bor;
    reco = raizProducto;
    int existe;

    while (reco != NULL)
    {
        if(reco->id == idProducto){
            existe = 1;
            if(prev != NULL){
                prev->sig = reco->sig;
                if(fondo == reco){
                    fondo = prev;
                }
            }
            else{
                raizProducto = reco->sig;
            }
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

void removerCaracteres(char *cadena, char *caracteres) {
  int indiceCadena = 0, indiceCadenaLimpia = 0;
  int deberiaAgregarCaracter = 1;
  // Recorrer cadena carácter por carácter
  while (cadena[indiceCadena]) {
    // Primero suponemos que la letra sí debe permanecer
    deberiaAgregarCaracter = 1;
    int indiceCaracteres = 0;
    // Recorrer los caracteres prohibidos
    while (caracteres[indiceCaracteres]) {
      // Y si la letra actual es uno de los caracteres, ya no se agrega
      if (cadena[indiceCadena] == caracteres[indiceCaracteres]) {
        deberiaAgregarCaracter = 0;
      }
      indiceCaracteres++;
    }
    // Dependiendo de la variable de arriba, la letra se agrega a la "nueva
    // cadena"
    if (deberiaAgregarCaracter) {
      cadena[indiceCadenaLimpia] = cadena[indiceCadena];
      indiceCadenaLimpia++;
    }
    indiceCadena++;
  }
  // Al final se agrega el carácter NULL para terminar la cadena
  cadena[indiceCadenaLimpia] = 0;
}