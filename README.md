# Dijkstra Algorithm Visualizer

### Compiling locally

1- Clone the repository  
2- Install SDL2 and SDL2_ttf  
3- Run `make`  
4- Run `./pdriver`

### Usage

```
Usage: pdriver [-hd] [-xylSB <number>] [-etswvcp <hex-color>]
 h              Prints this message
 d              Enable diagonal paths
 x <number>     width of canvas
 y <number>     height of canvas
 l <number>     cell lines width
 S <number>     path finder sleep time
 B <number>     back tracking sleep time
 e <hex-color>  empty cell color
 s <hex-color>  start cell color
 t <hex-color>  target cell color
 w <hex-color>  wall cell color
 v <hex-color>  visited cell color
 c <hex-color>  seen cell color
 p <hex-color>  path color
```

Hex colors are formed by combining the rgb values.  
rgb color 235, 64, 52 (red), converted to hex is eb, 40, 34  
After the hex digits are combined, the hex color formed is eb4034.

### Screenshot

<img width="600" src="https://github.com/dferndz/path-finder-visualizer/blob/main/assets/screenshot.png?raw=true" />
