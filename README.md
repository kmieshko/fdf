# fdf

This is UNIT factory (school 42) studying graphical project that takes map of area (2d array of ints, see example) as agument (plain text file) and converts it to 3d image - wire frame, which uses x and y pos of map numbers as X and Y coordinates and it's value as z, for example:
```
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  10 10 0  0  10 10 0  0  0  10 10 10 10 10 0  0  0
0  0  10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
0  0  10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
0  0  10 10 10 10 10 10 0  0  0  0  10 10 10 10 0  0  0
0  0  0  10 10 10 10 10 0  0  0  10 10 0  0  0  0  0  0
0  0  0  0  0  0  10 10 0  0  0  10 10 0  0  0  0  0  0
0  0  0  0  0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

produces:

![42](https://github.com/kmieshko/fdf/blob/master/examples/Screen%20Shot%202019-03-19%20at%2011.43.10%20AM.png)

Also there can be added colors in map in hex, using comma like: `20,0xFF0000` `15,0xFF00FF` `13,0x00FF00` etc...

Also you can rotate, zoom, change colors etc...(All controls are displayed on output screen)

# Some examples

![plane](https://github.com/kmieshko/fdf/blob/master/examples/Screen%20Shot%202019-03-19%20at%2011.45.15%20AM.png)

![mountain1](https://github.com/kmieshko/fdf/blob/master/examples/Screen%20Shot%202019-03-19%20at%2011.49.42%20AM.png)

![mountain2](https://github.com/kmieshko/fdf/blob/master/examples/Screen%20Shot%202019-03-19%20at%2011.49.49%20AM.png)

![mountain3](https://github.com/kmieshko/fdf/blob/master/examples/Screen%20Shot%202019-03-19%20at%2011.50.00%20AM.png)

![julia1](https://github.com/kmieshko/fdf/blob/master/examples/Screen%20Shot%202019-03-19%20at%2011.50.34%20AM.png)

![julia2](https://github.com/kmieshko/fdf/blob/master/examples/Screen%20Shot%202019-03-19%20at%2011.50.47%20AM.png)

# Project Details

This project is written for macOS (OS X High Sierra) using *MinilibX* graphic library (https://github.com/abouvier/minilibx) and it is needed to run this project

# Disclaimer

This project is written according to 42's "The Norm" which specifies special rules for code like less then 25 lines in each function, 85 symbols in line, forbidden most of libraries and functions that wasn't written by you, also "for", "switch case" and others are forbidden (you can read more at https://ncoden.fr/datas/42/norm.pdf)
