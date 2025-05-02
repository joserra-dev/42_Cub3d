# ** GAME.C **

### **🔎 Explicación de `cub_keyup(int k, t_game *g)`**
Esta función se ejecuta cuando **se suelta** una tecla.  

📌 **Objetivo:**  
- **Actualizar el estado del jugador** cuando deja de presionar teclas de movimiento (`WASD`, `←/→`).  
- **Realizar acciones especiales** cuando se suelta `R` o `E`.  

---

### **📝 Explicación Línea por Línea**
```c
if (k == KEY_R)
    g->neg *= -1;
```
- **Si se suelta `R`**, se cambia el signo de `g->neg`.  
- Esto podría estar relacionado con una mecánica especial del juego, como **invertir colores o cambiar de modo**.  

```c
else if (k == KEY_E)
    action_door(g);
```
- **Si se suelta `E`**, llama a `action_door(g)`.  
- Esto probablemente **abre o cierra una puerta** en el juego.  

```c
else if (k == KEY_LEFT)
    g->pl.keys.left_pressed = 0;
else if (k == KEY_RIGHT)
    g->pl.keys.right_pressed = 0;
```
- **Si se suelta `←` o `→`**, se desactiva la rotación.  

```c
else if (k == KEY_W)
    g->pl.keys.w_pressed = 0;
else if (k == KEY_A)
    g->pl.keys.a_pressed = 0;
else if (k == KEY_S)
    g->pl.keys.s_pressed = 0;
else if (k == KEY_D)
    g->pl.keys.d_pressed = 0;
```
- **Si se suelta `WASD`**, se detiene el movimiento del jugador en esa dirección.  
- Evita que el personaje siga moviéndose si no se está presionando la tecla.  

---

### **📌 Resumen**
✅ **`R` → Cambia el valor de `g->neg` (¿modo alternativo?)**  
✅ **`E` → Activa `action_door()`, posiblemente abre/cierra una puerta**  
✅ **Detiene el movimiento** cuando se sueltan `WASD` o `←/→`  

📌 **Combinada con `cub_keydown()`, esta función permite controlar al personaje de forma fluida.** 🚀

Estas dos funciones **manejan las entradas del teclado y el ratón** para el juego.  

---

## **🎮 `cub_keydown(int k, t_game *g)`**
- **Detecta qué tecla se ha presionado** y actualiza el estado del jugador.  
- Modifica variables dentro de `g->pl.keys`, que se usan para el movimiento.  

### **📝 Explicación Línea por Línea**
```c
if (k == KEY_Q || k == KEY_ESC)
    cub_perror(end, g, NULL, 1);
```
- **Si se presiona `Q` o `Esc`**, se llama a `cub_perror(end, g, NULL, 1)`, que probablemente **cierra el juego**.  

```c
else if (k == KEY_LEFT)
    g->pl.keys.left_pressed = 1;
else if (k == KEY_RIGHT)
    g->pl.keys.right_pressed = 1;
```
- **Si se presiona la flecha izquierda o derecha**, activa las variables de rotación (`left_pressed` o `right_pressed`).  

```c
else if (k == KEY_W)
    g->pl.keys.w_pressed = 1;
else if (k == KEY_A)
    g->pl.keys.a_pressed = 1;
else if (k == KEY_S)
    g->pl.keys.s_pressed = 1;
else if (k == KEY_D)
    g->pl.keys.d_pressed = 1;
```
- **Si se presiona `WASD`**, actualiza las variables que controlan el movimiento del jugador.  
- Estas variables probablemente se usen en `cub_update` para mover la cámara o al personaje.  

🔹 **Retorna `0` porque MiniLibX requiere que las funciones de eventos devuelvan un entero**.  

---

## **🖱️ `cub_mouse(int x, int y, t_game *g)`**
- **Maneja el movimiento del ratón**, probablemente para rotar la vista del jugador.  

### **📝 Explicación Línea por Línea**
```c
if (y != -1)
    g->ray.angle += (x - g->mouse_x) / 3;
```
- **Si `y != -1` (es decir, el mouse está dentro de la ventana)**:  
  - Ajusta el **ángulo de visión** (`g->ray.angle`).  
  - La cantidad de rotación es proporcional al **desplazamiento horizontal del ratón** `(x - g->mouse_x) / 3`.  

```c
g->mouse_x = x;
```
- **Guarda la nueva posición `x` del ratón**, para comparar en el próximo frame.  

🔹 **Esto permite que mover el ratón hacia la izquierda/derecha haga que el jugador gire en esa dirección**.  

---

## **🔎 Resumen**
✅ **`cub_keydown`** → Maneja el teclado (`WASD` para moverse, `←/→` para girar, `Q/Esc` para salir).  
✅ **`cub_mouse`** → Usa el ratón para **rotar la vista del jugador**.  

Estas funciones permiten controlar el juego de forma intuitiva, combinando **teclado y ratón** para el movimiento. 🚀

Te explico paso a paso lo que hace esta función `init_attr` en tu código de **Cub3D**.  

---

## **📌 Propósito de la Función**
Esta función inicializa las estructuras y las imágenes necesarias para la representación gráfica del juego, utilizando la **MiniLibX (MLX)**. Se encarga de:  
1. Crear la ventana del juego.  
2. Crear y configurar varias imágenes en memoria.  
3. Inicializar el minimapa y la vista en miniatura del juego.  

---

## **🔍 Explicación Línea por Línea**
```c
g->win_ptr = mlx_new_window(g->mlx_ptr, WIN_W, WIN_H, "Cub3D");
```
- **Crea la ventana del juego** con dimensiones `WIN_W` x `WIN_H`.  
- `"Cub3D"` es el título de la ventana.  
- `g->mlx_ptr` es el puntero principal de MLX (se inicializa antes en otro lugar).  

---

### **🖼️ Creación de imágenes**
```c
g->win_img.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp, \
    &g->win_img.line_len, &g->win_img.endian);
```
- **Crea una imagen en memoria** con `mlx_new_image`.  
- Luego, obtiene su dirección de memoria (`addr`) con `mlx_get_data_addr`, lo que permite manipular los píxeles directamente.  
- `bpp`, `line_len` y `endian` son parámetros técnicos que definen cómo se almacenan los datos de imagen.  

Este mismo proceso se repite para **tres imágenes** más (`win_g`, `win_r` y `minimap`), usadas para diferentes capas gráficas del juego.  

---

### **🎨 Coloreado de Imágenes**
```c
my_mlx_area_put(&g->win_g, ft_newvector(0, 0), \
    ft_newvector(WIN_W, WIN_H), 0x0000FF00);
```
- **Colorea la imagen `win_g`** (posiblemente una capa de fondo) con color **verde (`0x0000FF00`)**.  
- `ft_newvector(0, 0)` y `ft_newvector(WIN_W, WIN_H)` definen el área a colorear (toda la imagen).  

```c
my_mlx_area_put(&g->win_r, ft_newvector(0, 0), \
    ft_newvector(WIN_W, WIN_H), 0x00FF0000);
```
- **Colorea la imagen `win_r`** con color **rojo (`0x00FF0000`)**.  

Estas imágenes pueden ser usadas para aplicar efectos de color en la pantalla.  

---

### **🗺️ Creación del Minimap**
```c
g->minimap.i = mlx_new_image(g->mlx_ptr, g->width * SIZE, g->height * SIZE);
g->minimap.addr = mlx_get_data_addr(g->minimap.i, &g->minimap.bpp, \
    &g->minimap.line_len, &g->minimap.endian);
```
- **Crea una imagen para el minimapa** con dimensiones proporcionales a `g->width * SIZE` y `g->height * SIZE`.  

---

### **👀 Creación de la Mini-Vista**
```c
g->miniview.i = mlx_new_image(g->mlx_ptr, 30 * SIZE, 15 * SIZE);
g->miniview.addr = mlx_get_data_addr(g->miniview.i, &g->miniview.bpp, \
    &g->miniview.line_len, &g->miniview.endian);
g->miniview.width = 30 * SIZE;
g->miniview.height = 15 * SIZE;
```
- **Crea una imagen más pequeña**, que probablemente sea una vista reducida del juego.  
- Sus dimensiones son `30 * SIZE` x `15 * SIZE`.  

---

## **📝 Resumen Final**
Esta función **configura y prepara las imágenes** que se usarán en la ventana del juego:  
✅ **Crea la ventana del juego** con `mlx_new_window`.  
✅ **Genera imágenes en memoria** con `mlx_new_image`.  
✅ **Obtiene direcciones de memoria** con `mlx_get_data_addr`.  
✅ **Colorea imágenes de fondo** (`win_g` y `win_r`).  
✅ **Crea un minimapa y una vista en miniatura**.  

En resumen, **`init_attr` es la función que prepara la parte gráfica del juego antes de que se dibuje en la pantalla**. 🚀


Esta función `game_init` es la encargada de **inicializar el juego y configurar los eventos de entrada**.  

---

## **📌 Explicación Línea por Línea**
```c
init_attr(g);
```
- **Llama a `init_attr`** para inicializar la ventana e imágenes del juego.  

```c
init_ray(g);
```
- **Inicializa los rayos** para el algoritmo de **Raycasting** (necesario para renderizar la escena en 3D).  

---

### **🎮 Configuración de Eventos con `mlx_hook`**
Esta parte configura las interacciones del usuario con la ventana:  

```c
mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
```
- **Detecta cuando una tecla es presionada** (`02` es el código del evento de "key press").  
- Llama a la función `cub_keydown(g, keycode)`, que manejará las acciones cuando el jugador presione teclas.  

```c
mlx_hook(g->win_ptr, 03, 1L << 1, cub_keyup, g);
```
- **Detecta cuando una tecla es soltada** (`03` es el código del evento "key release").  
- Llama a `cub_keyup(g, keycode)` para manejar cuando el jugador deja de presionar una tecla.  

```c
mlx_hook(g->win_ptr, 17, 0, cub_exit, g);
```
- **Detecta cuando la ventana se cierra** (`17` es el evento de cierre de ventana).  
- Llama a `cub_exit(g)`, que cerrará el juego correctamente.  

```c
mlx_hook(g->win_ptr, 06, 1L << 6, cub_mouse, g);
```
- **Detecta movimientos del mouse** (`06` es el evento "mouse move").  
- Llama a `cub_mouse(g, x, y)`, que puede usarse para mover la vista con el ratón.  

---

### **🔄 Bucle Principal del Juego**
```c
mlx_loop_hook(g->mlx_ptr, cub_update, g);
```
- **Registra la función `cub_update` para ejecutarse en cada frame**.  
- `cub_update` actualizará la pantalla, controlará la física y manejará los eventos del juego.  

```c
mlx_loop(g->mlx_ptr);
```
- **Inicia el bucle infinito de MiniLibX**.  
- Mantiene el programa en ejecución y escucha eventos como teclas y ratón.  

---

## **📝 Resumen**
✅ **Inicializa el juego (`init_attr`, `init_ray`)**.  
✅ **Configura eventos de teclado (`cub_keydown`, `cub_keyup`)**.  
✅ **Detecta cuando se cierra la ventana (`cub_exit`)**.  
✅ **Configura el movimiento del mouse (`cub_mouse`)**.  
✅ **Ejecuta el bucle del juego (`cub_update`, `mlx_loop`)**.  

En otras palabras, **`game_init` prepara todo para que el juego comience a funcionar y responde a las acciones del usuario**. 🚀