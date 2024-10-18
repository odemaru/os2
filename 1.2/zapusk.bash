#!/bin/bash
#!/bin/bash
for var in pointA.c pointB.c pointC.c
do
  echo "!pynkt $var"
  gcc $var -o sss && ./sss && rm sss
done

gcc pointD.c -o D
gcc pointE.c -o E
gcc pointF.c -o F

