# Dijkstra Algorithm Visualizer

### Compiling locally

1- Clone the repository  
2- Install SDL2 and SDL2_ttf  
3- Run ```make```  
4- Run ```./pdriver``` 

### Usage
```
Usage: pdriver [-h] [-xylSB number] [-etswvcp hex color]
 h              Prints this message
 x number       Set width of canvas
 y number       Set height of canvas
 l number       Set cell lines width
 S number       Set path finder sleep time
 B number       Set back tracking sleep time
 e hex color    Set empty cell color
 s hex color    Set start cell color
 t hex color    Set target cell color
 w hex color    Set wall cell color
 v hex color    Set visited cell color
 c hex color    Set seen cell color
 p hex color    Set path color
```  
Hex colors are formed by combining

<img width="600" src="https://github.com/dferndz/path-finder-visualizer/blob/main/assets/screenshot.png?raw=true" />

