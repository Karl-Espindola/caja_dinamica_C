#ifndef _PRODUCTOS_
#define _PRODUCTOS_

int crearProducto();

struct Productos consultarProducto(int idProducto);
int listarProductos();
void editarProducto(int idProducto);
void eliminarProducto(int idProducto);
struct Productos restarStock(int idProducto, int cantidad);
int verificarProuctosRepetidos(char nomProducto[80]);

void removerCaracteres(char *cadena, char *caracteres);

#endif
