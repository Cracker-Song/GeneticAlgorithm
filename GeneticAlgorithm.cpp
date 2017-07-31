//
//  main.cpp
//  genetic_algorithm
//
//  Created by Bayes on 25/07/2017.
//
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define HEIGHT 200
#define WIDTH 150
#define COLOR_MAX 255
#define NUMBER_OF_GENES 10
#define NUMBER_OF_INDIVIDUALS 5
#define OK 1
#define ERROR 0
#define MUTATION_RATE 1
//#define MAX_GENERATION 10000

//#define SUM_OF_SQUARE(a, b, c) (a * a + b * b + c * c)

typedef int Status;

long SumOfSquare(long a, long b, long c);
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
    Status SetGene(int i, RandomTriangle rt);
    Status OverLay();
    Status OutPut(int list[WIDTH][HEIGHT][3]);
    Status PrintGenes();
    Status Mutate();//mutation
    long Adaptability(int list[WIDTH][HEIGHT][3]);
    friend Individual operator^(Individual i1, Individual i2);//crossover
protected:
    RandomTriangle genes_[NUMBER_OF_GENES];
    int picture_[WIDTH][HEIGHT][3];
    long fitness_ = -1;
};

class Individuals
{
public:
    Individuals();
    Individuals(int list[WIDTH][HEIGHT][3]);
    Individuals(Individual ancestors[NUMBER_OF_INDIVIDUALS], int list[WIDTH][HEIGHT][3]);
    Individual GetFather(int i);
    Individual GetChild(int i);
    Status QuickSort(int head, int tail);
//    Individual Roulette();
//    Individuals Evolve();
protected:
    Individual father_[NUMBER_OF_INDIVIDUALS];
    int add_up_fitness_[NUMBER_OF_INDIVIDUALS];
    Individual child_[NUMBER_OF_INDIVIDUALS];
    int target_[WIDTH][HEIGHT][3];
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
//    Vector2 o = Vector2(25, 21);
//    printf("%d\n", abc.IsPointInTriangle(o));
//    //test on class RandonTriangle

    
//    Individual test = Individual();
//    //test.PrintGenes();
//    test.OverLay();
//    test.OutPut(output);
//    printf("%ld\n", test.Adaptability(picture));
    
//    Individual i1, i2, i3;
//    i3 = i1 ^ i2;
//    i1.PrintGenes();
//    i1.Mutate();
//    i1.PrintGenes();
//    i2.PrintGenes();
//    i3.PrintGenes();
//    //test on class Individual
    
//    Individuals test = Individuals(picture);
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%ld\n", test.GetFather(i).Adaptability(picture));
//    }
//    test.QuickSort(0, NUMBER_OF_INDIVIDUALS);
//    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
//        printf("%ld\n", test.GetFather(i).Adaptability(picture));
//    }
    
//    printf("%d\n", sizeof(test));
    

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

Status Individual::SetGene(int i, RandomTriangle rt)
{
    genes_[i] = rt;
    return OK;
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

long Individual::Adaptability(int list[WIDTH][HEIGHT][3])
{
    //OverLay();
    if (fitness_ < 0) {
        long sum = 0;
        long r, g, b;
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

Individuals::Individuals(){}

Individuals::Individuals(int list[WIDTH][HEIGHT][3])
{
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            target_[x][y][0] = list[x][y][0];
            target_[x][y][1] = list[x][y][1];
            target_[x][y][2] = list[x][y][2];
        }
    }
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        father_[i] = Individual();
        father_[i].OverLay();
        //fitness_[i] = individuals[i].Adaptability(list);
    }
}

Individuals::Individuals(Individual ancestors[NUMBER_OF_INDIVIDUALS], int list[WIDTH][HEIGHT][3])
{
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            target_[x][y][0] = list[x][y][0];
            target_[x][y][1] = list[x][y][1];
            target_[x][y][2] = list[x][y][2];
        }
    }
    for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
        father_[i] = ancestors[i];
        father_[i].OverLay();
        //fitness_[i] = individuals[i].Adaptability(list);
    }
}

Individual Individuals::GetFather(int i)
{
    return father_[i];
}

Individual Individuals::GetChild(int i)
{
    return child_[i];
}

Status Individuals::QuickSort(int head, int tail)
{
    if (head >= tail)
        return OK;
    int i = head, j = tail;
    Individual tmp = father_[head];
    int pivot = father_[head].Adaptability(target_);
    while (i < j) {
        while (i < j and father_[j].Adaptability(target_) >= pivot) j--;
        father_[i] = father_[j];
        while (i < j and father_[i].Adaptability(target_) <= pivot) i++;
        father_[j] = father_[i];
    }
    father_[i] = tmp;
    
    QuickSort(head, i - 1);
    QuickSort(j + 1, tail);
    return OK;
}

long SumOfSquare(long a, long b, long c)
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
