//
//  main.cpp
//  genetic_algorithm
//
//  Created by Bayes on 25/07/2017.

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Header.h"

using namespace std;

class Individual
{
public:
    Individual();
    Individual(Individual const &i);
    Status SetGene(int i, RandomTriangle rt);
    RandomTriangle *GetGenes();
    Status OverLay();
    Status OutPut(int list[WIDTH][HEIGHT][3]);
    Status PrintGenes();
    Status Mutate();//mutation
    long long Adaptability(int list[WIDTH][HEIGHT][3]);
    friend Individual operator^(Individual i1, Individual i2);//crossover
protected:
    RandomTriangle genes_[NUMBER_OF_GENES];
    int picture_[WIDTH][HEIGHT][3];
    long long fitness_ = -1;
};

class Individuals
{
public:
    //Individuals();
    ~Individuals();
    Individuals(int list[WIDTH][HEIGHT][3]);
    //Individuals(Individual *ancestors[NUMBER_OF_INDIVIDUALS], int list[WIDTH][HEIGHT][3]);
    Individual *GetFather(int i);
    long long *GetFitness();
    Status PrintIndividual();
    //Individual *GetChild(int i);
    Status Sort();
    Individual *Roulette();
    Status Evolve();
protected:
    Individual *individuals[NUMBER_OF_INDIVIDUALS] = {NULL};
    Individual *tmp[NUMBER_OF_INDIVIDUALS] = {NULL};
    long long add_up_fitness_[NUMBER_OF_INDIVIDUALS] = {0};
    int target_[WIDTH][HEIGHT][3] = {0};
};

int main(int argc, const char * argv[]) {
    
    srand((unsigned)time(NULL));
    
    int picture[WIDTH][HEIGHT][3] = {0};
    int output[WIDTH][HEIGHT][3] = {0};
    if (!FileToList("test.txt", picture))
        return ERROR;
//    for (int x = 0; x < WIDTH; x++) {
//        for (int y = 0; y < HEIGHT; y++) {
//            printf("%d %d %d\n", list[x][y][0], list[x][y][1], list[x][y][2]);
//        }
//    }
//    //show rgb of the image test of function file to list
    

//    Vector2 a, b, c;
//    a.SetVector(5, -5);
//    b.SetVector(-5, 0);
//    c.SetVector(5, 10);
//    printf("%d\n", a^c);
//    //test on operator^ of class Vector2
    
//    Vector2 a, b, m, n, o;
//    a.SetVector(0, 0);
//    b.SetVector(1, 0);
//    m.SetVector(1, 2);
//    n.SetVector(3, 4);
//    o.SetVector(3, -4);
//    Line ab = Line(a, b);
//    cout<<ab.IsPointAtSameSideOfLine(m, n)<<endl<<ab.IsPointAtSameSideOfLine(m, o)<<endl;
//    Triangle ano = Triangle(a, n, o);
//    cout<<ano.IsPointInTriangle(b)<<endl;
//    ano.PrintTriangle();
    //test on class Triangle and line
    
//    RandomTriangle abc = RandomTriangle();
//    abc.PrintTriangle();
//    //abc.l12_.PrintLine();
//    //abc.l13_.PrintLine();
//    //abc.l23_.PrintLine();
//    Vector2 o = Vector2(75, 100);
//    printf("%d\n", abc.IsPointInTriangle(o));
//    //test on class RandonTriangle

    
//    Individual test = Individual();
//    //test.PrintGenes();
//    test.OverLay();
//    //test.OutPut(output);
//    printf("%lld\n", test.Adaptability(picture));
    
//    Individual i1, i2, i3;
//    i3 = i1 ^ i2;
//    i1.PrintGenes();
//    i1.Mutate();
//    i1.PrintGenes();
//    i2.PrintGenes();
//    i3.PrintGenes();
//    Individual i1;
//    printf("%lld\n", i1.Adaptability(picture));
//    printf("%lld\n", i1.Adaptability(picture));
    //printf("%d\n", i1 > i1);
//    //test on class Individual
    
//    Individuals test = Individuals();
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%lld\n", (test.GetFather(i))->Adaptability(picture));
//    }
//    printf("\n");
//    test.Sort();
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%lld\n", (test.GetFather(i))->Adaptability(picture));
//    }
//    printf("\n");
//    long long *fitness = test.GetFitness();
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%lld\n", fitness[i]);
//    }
//    printf("%d\n", sizeof(test));
    
//    int count[30] = {0};
//    printf("%lld\n", (long long) (RAND_MAX) + 30);
//    for (int i = 0; i < 10000000; i++) {
//        count[Random((long long) RAND_MAX, (long long) RAND_MAX + 30) - (long long) RAND_MAX]++;
//    }
//    for (int i = 0; i < 30; i++) {
//        printf("%lf\n", count[i] / 10000000.0);
//    }
//    //test on Random
    Individuals *test = new Individuals(picture);
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%lld\n", (test->GetFather(i))->Adaptability(picture));
//    }
//    printf("\n");
//    test->Sort();
//    //test->PrintIndividual();
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%lld\n", (test->GetFather(i))->Adaptability(picture));
//    }
//    printf("\n");
//    long long *fitness = test->GetFitness();
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%lld\n", fitness[i]);
//    }
//    //test on Sort
    for (int i = 0; i < MAX_GENERATION; i++) {
        printf("%d   %lld\n", i, test->GetFather(0)->Adaptability(picture));
        test->Evolve();
    }
    test->GetFather(0)->OutPut(output);
    //test->~Individuals();
    
    

    if (!ListToFile("output.txt", output))
        return ERROR;

    printf("finished\n");
    
    return OK;
}


Individual::Individual()
{
    for (int i = 0; i < NUMBER_OF_GENES; i++) {
        genes_[i] = RandomTriangle();//initialize genes_
    }
    //fitness_ = -1;
}

Individual::Individual(Individual const &i)
{
    for (int j = 0; j < NUMBER_OF_GENES; j++) {
        genes_[j] = i.genes_[j];//initialize genes_
    }
    fitness_ = -1;
}

Status Individual::SetGene(int i, RandomTriangle rt)
{
    genes_[i] = rt;
    return OK;
}

RandomTriangle *Individual::GetGenes()
{
    return genes_;
}

Status Individual::OverLay()
{
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            int tmp = 0;
            for (int i = 0; i < NUMBER_OF_GENES; i++) {
                if (genes_[i].IsPointInTriangle(Vector2(x, y))) {
                    picture_[x][y][0] += genes_[i].GetRed();
                    picture_[x][y][1] += genes_[i].GetGreen();
                    picture_[x][y][2] += genes_[i].GetBlue();
                    tmp++;
                }
                
            }
            if (tmp) {
                picture_[x][y][0] /= tmp;
                picture_[x][y][1] /= tmp;
                picture_[x][y][2] /= tmp;
            }
            //printf("%d %d %d\n", picture[x][y][0], picture[x][y][1], picture[x][y][2]);
        }
    }
    return OK;
}

int Individual::OutPut(int list[WIDTH][HEIGHT][3])
{
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            //printf("%d %d %d\n", picture[x][y][0], picture[x][y][1], picture[x][y][2]);
            list[x][y][0] = picture_[x][y][0];
            list[x][y][1] = picture_[x][y][1];
            list[x][y][2] = picture_[x][y][2];
        }
    }
    return OK;
}

Status Individual::PrintGenes()
{
    for (int i = 0; i < NUMBER_OF_GENES; i++) {
        genes_[i].PrintTriangle();
        printf("r = %d, g = %d, b = %d\n\n", genes_[i].GetRed(), genes_[i].GetGreen(), genes_[i].GetBlue());
    }
    return OK;
}

Status Individual::Mutate()
{
    for (int i = 0; i < MUTATION_RATE; i++) {
        int tmp = rand() % NUMBER_OF_GENES;
        genes_[tmp] = RandomTriangle();
    }
    return OK;
}

long long Individual::Adaptability(int list[WIDTH][HEIGHT][3])
{
    if (fitness_ < 0) {
        OverLay();
        long long sum = 0;
        long long r, g, b;
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                r = list[x][y][0] - picture_[x][y][0];
                g = list[x][y][1] - picture_[x][y][1];
                b = list[x][y][2] - picture_[x][y][2];
                sum += SumOfSquare(r, g, b);
            }
        }
        fitness_ = (WIDTH * HEIGHT * SumOfSquare(COLOR_MAX, COLOR_MAX, COLOR_MAX) - sum);
        //printf("fitness %lld\n", fitness_);
    }
    //printf("%lf\n", sum);
    return fitness_;
}

Individual operator^(Individual i1, Individual i2)
{
    Individual new_individual;
    for (int i = 0; i < NUMBER_OF_GENES; i++) {
        if (rand() % 2) {
            //new_individual.genes_[i] = i1.genes_[i];
            new_individual.SetGene(i, i1.genes_[i]);
        }
        else
        {
            //new_individual.genes_[i] = i2.genes_[i];
            new_individual.SetGene(i, i2.genes_[i]);
        }
    }
    return new_individual;
}

//Individuals::Individuals()
//{
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        individuals[i] = new Individual();
//        individuals[i]->Adaptability(target_);
//    }
//}

Individuals::Individuals(int list[WIDTH][HEIGHT][3])
{

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int i = 0; i < 3; i++) {
                target_[x][y][i] = list[x][y][i];
            }
        }
    }
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        individuals[i] = new Individual();
        individuals[i]->Adaptability(target_);
    }
    Sort();
}

//Individuals::Individuals(Individual *ancestors[NUMBER_OF_INDIVIDUALS], int list[WIDTH][HEIGHT][3])
//{
//    for (int x = 0; x < WIDTH; x++) {
//        for (int y = 0; y < HEIGHT; y++) {
//            for (int i = 0; i < 3; i++) {
//                target_[x][y][i] = list[x][y][i];
//            }
//        }
//    }
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        individuals[i] = ancestors[i];
//        individuals[i]->Adaptability(target_);
//    }
//    Sort();
//}

Individuals::~Individuals()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        //printf("delete\n");
        delete individuals[i];
    }
}

Individual *Individuals::GetFather(int i)
{
    return individuals[i];
}

long long *Individuals::GetFitness()
{
    return add_up_fitness_;
}

Status Individuals::PrintIndividual()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        printf("the %d individual's fittness %lld\n", i + 1, individuals[i]->Adaptability(target_));
        //individuals[i]->PrintGenes();
    }
    return OK;
}

Status Individuals::Sort()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        for (int j = i; j < NUMBER_OF_INDIVIDUALS; j++) {
            if (individuals[j]->Adaptability(target_) > individuals[i]->Adaptability(target_)) {
                Individual *tmp = individuals[j];
                individuals[j] = individuals[i];
                individuals[i] = tmp;
            }
        }
    }
    add_up_fitness_[0] = individuals[0]->Adaptability(target_);
    for (int i = 1; i < NUMBER_OF_INDIVIDUALS; i++) {
        add_up_fitness_[i] = add_up_fitness_[i - 1] + individuals[i]->Adaptability(target_);
    }
    return OK;
}

Individual *Individuals::Roulette()
{
    long long random_number = Random(0, add_up_fitness_[NUMBER_OF_INDIVIDUALS - 1]);
    int choice = 0;
    while (add_up_fitness_[choice] < random_number) {
        choice++;
    }
    return individuals[choice];
}

Status Individuals::Evolve()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        if (i == 0) {
            continue;
        }
        tmp[i] = individuals[i];
        individuals[i] = new Individual(*Roulette() ^ *Roulette());
        individuals[i]->Mutate();
        tmp[i]->~Individual();
    }
    Sort();
    return OK;;
}
