### TP8 Exp1

* You must compile first and run the executable!
* Don't skip nha!
```bash
# All the files need to be linked and compiled into the executable ./tp8ex1
gcc tp8ex1.c matrix.c -o tp8ex1

# Run the executable file
./tp8ex1
```

### TP8 Exp2
* You must compile first and run the executable!
* Don't skip nha!
```bash
# All the files need to be linked and compiled into the executable ./tp8ex2
gcc tp8ex2.c image.c matrix.c -o tp8ex2

# Run the executable file
./tp8ex2
```


### Task 1 Polygon
```bash
# All the files need to be linked and compiled into the executable ./testpolygon
gcc testpolygon.c svg.c polygon.c -o testpolygon;

# Run the executable file 
./testpolygon;
```

### Task 2 Contex
```bash
# All the files need to be linked and compiled into the executable ./contex
gcc contex.c image.c polygon.c svg.c -o contex

# Run the executable file contex as many times as you want!
./contex "data/im0.pgm" "/full/data/im0.png" "full/data/contour0.ct" "full/data/im0.svg";

# for im1
./contex "data/im1.pgm" "/full/data/im1.png" "full/data/contour1.ct" "full/data/im1.svg";

# for im2
./contex "data/im2.pgm" "/full/data/im2.png" "full/data/contour2.ct" "full/data/im2.svg";
```
