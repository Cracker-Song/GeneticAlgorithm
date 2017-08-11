//
//  Header.h
//  genetic_algorithm
//
//  Created by Bayes on 11/08/2017.
//
//

#ifndef Header_h
#define Header_h

using namespace std;

#define HEIGHT 200
#define WIDTH 150
#define COLOR_MAX 255
#define NUMBER_OF_GENES 50
#define NUMBER_OF_INDIVIDUALS 20
#define OK 1
#define ERROR 0
#define MUTATION_RATE 1
#define MAX_GENERATION 1

//#define SUM_OF_SQUARE(a, b, c) (a * a + b * b + c * c)

typedef int Status;







int RandomN(int N);
long long Random(long long low, long long high);
long long SumOfSquare(long long a, long long b, long long c);
Status FileToList(char file_name[], int list[WIDTH][HEIGHT][3]);
Status ListToFile(char file_name[], int list[WIDTH][HEIGHT][3]);

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







class LinkedChar
{
public:
    LinkedChar();
protected:
    char p;
    char *next;
};
LinkedChar::LinkedChar()
{
    p = 0;
    next = NULL;
}

class String
{
public:
    String();
    String(string str);
    ~String();
    friend String operator+(String str1, String str2);
protected:
    LinkedChar *head, *tail;
};

String::String()
{
    head = new LinkedChar();
    tail = head;
}








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


#endif /* Header_h */
