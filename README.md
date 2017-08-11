# GeneticAlgorithm
C++ Genetic Algorithm.  
Try to use 50 triangle to paint Mona Lisa.  
But the problem now is the program is too slow to check whether it's correct.  
This is my first c++ program so there may be some mistake.    
This is a demo of the output.  
![](/OutPut.jpg)
--------  
## Header.h  
### marco definition  
* WEITH
* HEIGHT
* and so on
### Function definition  
* long long Random  
(Generates a specified range of random numbers which can be bigger than RAND_MAX)
* Status FileToList
* Status ListToFile
### class Vector2  
* Constructor Vector2()
* Constructor Vector2(int x, int y)
* Set and Get
* operator-  
(Member function means negative)
* friend operator+
* friend operator-
* friend operator*  (dot)
* friend operator^  (cross)
### class Triangle  
* Constructor Triangle()
* Constructor Triangle(Vector2 a, Vector2 b, Vector2 c)
* Set and Get
* bool IsPointInTriangle(Vector2 p)  
(judge whether a point is in this triangle)
### class RandomTriangle  
inherit from Triangle
* Constructor RandomTriangle()  
(Generates a random Triangle with color RGB)
-------
## main.cpp  
### Individual  
* Constructor Individual()
* Constructor Individual(Individual const &i)
* SetGenes and GetGenes
* OverLay
* OutPut
* Mutate
* Adaptability  
(calc the Adaptability of an Individual)
* operator^  
(crossover)
### Generation  
* Destructor ~Generation()
* Constructor Generation(int target[WIDTH][HEIGHT][3])
* Sort
* Roulette  
(choose a Individual by their Adaptability)
* Evolve  
(number of individuals in each Generation are all the same, Roulette choose two Individuals to crossover and mutate)
