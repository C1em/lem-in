# lem-in

lem-in is graph theory project.

the program take a anteater and a number of ants and output the most optimal way to make all the ants go from start to end.  
Each node can containe only one ant (unless for start and end). 

for example : 

  [start]  
  /  |        For one or two ants, the most optimal path is the middle one.  
[3] [1]--[5]  
 |   |    |   For more than two ants, the best way is to send half of the ants on the left path  
 |   |    |   and the other half on the right way.  
[4]--[2] [6]  Sending all the ants on the middle way will cause them to wait for the node to be left  
      | /     by the ant actually on it, so only one ant by turn will reach the end.  
    [end]     Whereas by sending on the wings ways, you can send 2 ants by turn and make 2 others reach the end.  

         
The input file need to be formted like follow :  

ants_nb  
##start  
start coord1 coord2  
1 coord1 coord2  
2 coord1 coord2  
3 coord1 coord2  
4 coord1 coord2  
5 coord1 coord2  
6 coord1 coord2  
##end  
end coord1 coord2  
start-3  
start-1  
3-4  
1-2  
1-5  
4-2  
5-6  
2-end  
6-end  

This is the input for the anteater of the example. 

The program output the operation, each line is a turn.

program output for 1 ant :  
L1-1  
L1-2  
L1-end  

L1 is the ant number 1.

program output for 4 ants :  
L1-3 L2-1  
L1-4 L2-5 L3-3 L4-1  
L1-2 L2-6 L3-4 L4-5  
L1-end L2-end L3-2 L4-6  
L3-end L4-end  


You can make your own anteater or use the generator.

# How to use it

$make

if you have you own anteater:  
$./lem-in < anteater

if you want to use the generator:  
$./generator [--flow-one | --flow-ten | --flow-thousand | --big | --big-superposition] > anteater && ./lem-in < anteater
