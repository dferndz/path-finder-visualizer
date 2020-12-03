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
Hex colors are formed by combining the rgb values.  
rgb color 235, 64, 52 (red), converted to hex is eb, 40, 34  
After the hex digits are combined, the hex color formed is 0xeb4034  
Then attach hex digit ff at the end, forming the colorr 0x0xeb4034ff  

<img width="600" src="https://github.com/dferndz/path-finder-visualizer/blob/main/assets/screenshot.png?raw=true" />

