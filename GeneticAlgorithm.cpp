//
//  main.cpp
//  genetic_algorithm
//
//  Created by Bayes on 25/07/2017.

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define HEIGHT 200
#define WIDTH 150
#define COLOR_MAX 255
#define NUMBER_OF_GENES 20
#define NUMBER_OF_INDIVIDUALS 10
#define OK 1
#define ERROR 0
#define MUTATION_RATE 1
//#define MAX_GENERATION 10000

//#define SUM_OF_SQUARE(a, b, c) (a * a + b * b + c * c)

typedef int Status;

int RandomN(int N);
long long Random(long long low, long long high);
long long SumOfSquare(long long a, long long b, long long c);
Status FileToList(char file_name[], int list[WIDTH][HEIGHT][3]);
Status ListToFile(char file_name[], int list[WIDTH][HEIGHT][3]);

class Vector2
{
public:
    Vector2();
    Vector2(int x, int y);
    Status SetVector(int x, int y);
    int GetX();
    int GetY();
    Status PrintVector();
    Vector2 operator-();
    friend Vector2 operator+(Vector2 &v1, Vector2 &v2);
    friend Vector2 operator-(Vector2 &v1, Vector2 &v2);
    friend int operator*(Vector2 &v1, Vector2 &v2);//dot
    friend int operator^(Vector2 &v1, Vector2 &v2);//cross
protected:
    int xpos_, ypos_;
};

class Line
{
public:
    Line();
    Line(Vector2 start, Vector2 end);
    Status PrintLine();
    bool IsPointAtSameSideOfLine(Vector2 point1, Vector2 point2);
protected:
    Vector2 start_, end_;
};

class Triangle
{
public:
    Triangle();
    Triangle(Vector2 v1, Vector2 v2, Vector2 v3);
    Status SetTriangle(Vector2 v1, Vector2 v2, Vector2 v3);
    Status PrintTriangle();
    bool IsPointInTriangle(Vector2 p);
protected:
    Vector2 v1_, v2_, v3_;
    Line l12_, l13_, l23_;
};

class RandomTriangle: public Triangle
{
public:
    RandomTriangle();
    int GetRed();
    int GetGreen();
    int GetBlue();
protected:
    int red_, green_, blue_;
};

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
    friend bool operator>=(Individual i1, Individual i2);
    friend bool operator<=(Individual i1, Individual i2);
protected:
    RandomTriangle genes_[NUMBER_OF_GENES];
    int picture_[WIDTH][HEIGHT][3];
    long long fitness_ = -1;
};

class Individuals
{
public:
    Individuals();
    ~Individuals();
    Individuals(int list[WIDTH][HEIGHT][3]);
    Individuals(Individual *ancestors[NUMBER_OF_INDIVIDUALS], int list[WIDTH][HEIGHT][3]);
    Individual *GetFather(int i);
    long long *GetFitness();
    Status PrintIndividual();
    //Individual *GetChild(int i);
    Status Sort();
    Individual *Roulette();
    Individuals *Evolve();
protected:
    Individual *fathers[NUMBER_OF_INDIVIDUALS] = {NULL};
    Individual *children[NUMBER_OF_INDIVIDUALS] = {NULL};
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
//    //test on Ranom
    Individuals *test = new Individuals(picture);
    Individuals *tmp;
//    test->PrintIndividual();
//    //test.PrintIndividual();
//    tmp = test->Evolve();
//    test->~Individuals();
//    tmp->PrintIndividual();
//    test->GetFather(0)->OutPut(output);
    //test = test.Evolve();
    for (int i = 0; i < 50; i++) {
        tmp = test->Evolve();
        test->~Individuals();
        test = tmp;
    }
    test->GetFather(0)->OutPut(output);
    
    
    

    if (!ListToFile("output.txt", output))
        return ERROR;

    printf("finished\n");
    
    return OK;
}

Vector2::Vector2()
{
    xpos_ = 0;
    ypos_ = 0;
}

Vector2::Vector2(int x, int y)
{
    xpos_ = x;
    ypos_ = y;
}

Status Vector2::SetVector(int x, int y)
{
    xpos_ = x;
    ypos_ = y;
    return OK;
}

int Vector2::GetX()
{
    return xpos_;
}

int Vector2::GetY()
{
    return ypos_;
}

Status Vector2::PrintVector()
{
    printf("xpos = %d, ypos = %d\n", xpos_, ypos_);
    //cout<<"xpos = "<<xpos_<<" ypos = "<<ypos_<<endl;
    return OK;
}


Vector2 Vector2::operator-()
{
    return Vector2(-xpos_, -ypos_);
}


Vector2 operator+(Vector2 &v1, Vector2 &v2)
{
    int x, y;
    x = v1.xpos_ + v2.xpos_;
    y = v1.ypos_ + v2.ypos_;
    return Vector2(x, y);
}

Vector2 operator-(Vector2 &v1, Vector2 &v2)
{
    Vector2 v = -v2;
    return v + v1;
}

int operator*(Vector2 &v1, Vector2 &v2)
{
    return v1.xpos_ * v2.xpos_ + v1.ypos_ * v2.ypos_;
}

int operator^(Vector2 &v1, Vector2 &v2)
{
    return ((v1.xpos_ * v2.ypos_) - (v1.ypos_ * v2.xpos_));
}

Line::Line()
{
    start_ = Vector2(0, 0);
    end_ = Vector2(0, 0);
}

Line::Line(Vector2 start, Vector2 end)
{
    start_ = start;
    end_ = end;
}

Status Line::PrintLine()
{
    start_.PrintVector();
    end_.PrintVector();
    return OK;
}

bool Line::IsPointAtSameSideOfLine(Vector2 point1, Vector2 point2)
{
    Vector2 ab = start_ - end_;
    Vector2 am = point1 - start_;
    Vector2 an = point2 - start_;
//    ab.PrintVector();
//    am.PrintVector();
//    an.PrintVector();
//    printf("%d %d\n", ab ^ am, ab ^ an);
    return (ab ^ am) * (ab ^ an) >= 0;
}

Triangle::Triangle(){}

Triangle::Triangle(Vector2 v1, Vector2 v2, Vector2 v3)
{
    v1_ = v1;
    v2_ = v2;
    v3_ = v3;
    l12_ = Line(v1, v2);
    l13_ = Line(v1, v3);
    l23_ = Line(v2, v3);
}

Status Triangle::SetTriangle(Vector2 v1, Vector2 v2, Vector2 v3)
{
    v1_ = v1;
    v2_ = v2;
    v3_ = v3;
    return OK;
}

Status Triangle::PrintTriangle()
{
    v1_.PrintVector();
    v2_.PrintVector();
    v3_.PrintVector();
    return OK;
}

bool Triangle::IsPointInTriangle(Vector2 p)
{
    //printf("%d %d\n", v1_.GetX(), v1_.GetY());
    return l12_.IsPointAtSameSideOfLine(v3_, p) && l13_.IsPointAtSameSideOfLine(v2_, p) && l23_.IsPointAtSameSideOfLine(v1_, p);
}

RandomTriangle::RandomTriangle(): Triangle(Vector2(rand() % WIDTH, rand() % HEIGHT), Vector2(rand() % WIDTH, rand() % HEIGHT), Vector2(rand() % WIDTH, rand() % HEIGHT))
{
    red_ = rand() % COLOR_MAX;
    green_ = rand() % COLOR_MAX;
    blue_ = rand() % COLOR_MAX;
}

int RandomTriangle::GetRed()
{
    return red_;
}

int RandomTriangle::GetGreen()
{
    return green_;
}

int RandomTriangle::GetBlue()
{
    return blue_;
}

Individual::Individual()
{
    for (int i = 0; i < NUMBER_OF_GENES; i++) {
        genes_[i] = RandomTriangle();//initialize genes_
    }
}

Individual::Individual(Individual const &i)
{
    for (int j = 0; j < NUMBER_OF_GENES; j++) {
        genes_[j] = i.genes_[j];//initialize genes_
    }
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

bool operator>=(Individual i1, Individual i2)
{
    return i1.fitness_ >= i2.fitness_;
}

bool operator<=(Individual i1, Individual i2)
{
    return i1.fitness_ <= i2.fitness_;
}

Individuals::Individuals()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        fathers[i] = new Individual();
    }
    Sort();
}

Individuals::Individuals(int list[WIDTH][HEIGHT][3])
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        fathers[i] = new Individual();
    }
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int i = 0; i < 3; i++) {
                target_[x][y][i] = list[x][y][i];
            }
        }
    }
    Sort();
}

Individuals::Individuals(Individual *ancestors[NUMBER_OF_INDIVIDUALS], int list[WIDTH][HEIGHT][3])
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        fathers[i] = ancestors[i];
    }
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int i = 0; i < 3; i++) {
                target_[x][y][i] = list[x][y][i];
            }
        }
    }
    Sort();
}

Individuals::~Individuals()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        //printf("delete\n");
        delete fathers[i];
        //delete children[i];
    }
}

Individual *Individuals::GetFather(int i)
{
    return fathers[i];
}

long long *Individuals::GetFitness()
{
    return add_up_fitness_;
}

Status Individuals::PrintIndividual()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        printf("the %d individual's fittness %lld\n", i + 1, fathers[i]->Adaptability(target_));
        //fathers[i]->PrintGenes();
    }
    return OK;
}

Status Individuals::Sort()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        for (int j = i; j < NUMBER_OF_INDIVIDUALS; j++) {
            if (*fathers[j] >= *fathers[i]) {
                Individual *tmp = fathers[j];
                fathers[j] = fathers[i];
                fathers[i] = tmp;
            }
        }
    }
    add_up_fitness_[0] = fathers[0]->Adaptability(target_);
    for (int i = 1; i < NUMBER_OF_INDIVIDUALS; i++) {
        add_up_fitness_[i] += add_up_fitness_[i - 1] + fathers[i]->Adaptability(target_);
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
    return fathers[choice];
}

Individuals *Individuals::Evolve()
{
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        children[i] = new Individual(*Roulette() ^ *Roulette());
        children[i]->Mutate();
    }
    return new Individuals(children, target_);
}
int RandomN(int N)
{// N must be smaller than RAND_MAX
    int i;
    while (true) {
        i = rand();
        if (i < RAND_MAX / N * N) {
            break;
        }
    }
    return 1 + i % N;
}

long long Random(long long low, long long high)
{
    if (high - low < RAND_MAX) {
        return low + rand() % (high - low);
    }
    else
    {
        return (high - low) / RAND_MAX * rand() + low;
    }
}

long long SumOfSquare(long long a, long long b, long long c)
{
    return a * a + b * b + c * c;
}

Status FileToList(char file_name[], int list[WIDTH][HEIGHT][3])
{
    //int tmp[WIDTH][HEIGHT][3] = {0};
    FILE *fp = fopen(file_name, "r");
    int count = 0;
    if (fp == NULL) {
        printf("file not exist\n");
        return ERROR;
    }
    for (count = 0; count < WIDTH * HEIGHT; count++)
    {
        fscanf(fp, "%d %d %d\n", &list[count / HEIGHT][count % HEIGHT][0], &list[count / HEIGHT][count % HEIGHT][1], &list[count / HEIGHT][count % HEIGHT][2]);
    }
    fclose(fp);
    return count;
}

Status ListToFile(char file_name[], int list[WIDTH][HEIGHT][3])
{
    //int tmp[WIDTH][HEIGHT][3] = {0};
    FILE *fp = fopen(file_name, "w+");
    int count = 0;
    if (fp == NULL) {
        printf("file not exist\n");
        return ERROR;
    }
    for (count = 0; count < WIDTH * HEIGHT; count++)
    {
        //fscanf(fp, "%d %d %d\n", &list[count / HEIGHT][count % HEIGHT][0], &list[count / HEIGHT][count % HEIGHT][1], &list[count / HEIGHT][count % HEIGHT][2]);
        fprintf(fp, "%d %d %d\n", list[count / HEIGHT][count % HEIGHT][0], list[count / HEIGHT][count % HEIGHT][1], list[count / HEIGHT][count % HEIGHT][2]);
    }
    fclose(fp);
    return count;
}
