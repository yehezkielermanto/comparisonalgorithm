#include <iostream>

using namespace std;

const int MAX = 14;
int n = 14;
int color[MAX];
int degree[MAX];
int NN[MAX];
int NNCount;
int unprocessed;
int a[MAX][MAX] = { //adj. matrix
 	  0,0,0,0,0,0,0,0,0,0,1,0,0,0,
  	0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  	0,0,0,0,0,0,0,0,0,0,0,0,1,0,
  	0,0,0,0,0,0,0,0,0,1,0,0,0,0,
  	0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 	  0,0,0,0,0,0,0,1,0,0,0,0,0,0,
  	0,0,0,0,0,0,0,0,1,0,0,0,0,0,
  	0,0,0,0,0,1,0,0,0,0,0,0,0,0,
  	0,0,0,0,0,0,1,0,0,0,0,0,0,0,
  	0,0,0,1,0,0,0,0,0,0,0,0,0,0,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,
  	0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  	0,0,1,0,0,0,0,0,0,0,0,0,0,0,
  	0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void Init()
{
    for (int i=0; i < n; i++)
    {
        color[i] = 0;
        degree[i] = 0;
        for (int j = 0; j < n; j++)
            if (a[i][j] == 1)
                degree[i] ++;
    }
    NNCount = 0;
    unprocessed = n;
}

int MaxDegreeVertex()
{
    int max = -1;
    int max_i;
    for (int i =0; i < n; i++)
        if (color[i] == 0)
            if (degree[i]>max)
            {
                max = degree[i];
                max_i = i;
            }
    return max_i;
}

void scannedInit(int scanned[MAX])
{
    for (int i=0; i < n; i++)
        scanned[i] = 0;
}

void UpdateNN(int ColorNumber)
{
    NNCount = 0;
    for (int i=0; i < n; i++)
        if (color[i] == 0)
        {
            NN[NNCount] = i;
            NNCount ++;
        }
    for (int i=0; i < n; i++)
        if (color[i] == ColorNumber)
            for (int j=0; j < NNCount; j++)
                while (a[i][NN[j]] == 1)
                {
                    NN[j] = NN[NNCount - 1];
                    NNCount --;
                }
}

int FindSuitableY(int ColorNumber, int& VerticesInCommon)
{
    int temp,tmp_y,y;
    int scanned[MAX];
    VerticesInCommon = 0;
    for (int i=0; i < NNCount; i++)
    {
        tmp_y = NN[i];
        temp = 0;
        scannedInit(scanned);
        for (int x=0; x < n; x++)
            if (color[x] == ColorNumber)
                for (int k=0; k < n; k++)
                    if (color[k] == 0 && scanned[k] == 0)
                        if (a[x][k] == 1 && a[tmp_y][k] == 1)
                        {
                            temp ++;
                            scanned[k] = 1;
                        }
        if (temp > VerticesInCommon)
        {
            VerticesInCommon = temp;
            y = tmp_y;
        }
    }
    return y;
}

int MaxDegreeInNN()
{
    int tmp_y;
    int temp, max = 0;
    for (int i=0; i < NNCount; i++)
    {
        temp = 0;
        for (int j=0; j < n; j++)
            if (color[j] == 0 && a[NN[i]][j] == 1)
                temp ++;
        if (temp>max)
        {
            max = temp;
            tmp_y = NN[i];
        }
    }
    if (max == 0)
        return NN[0];
    else
        return tmp_y;
}

void Coloring()
{
    int x,y;
    int ColorNumber = 0;
    int VerticesInCommon = 0;
    while (unprocessed>0)
    {
        x = MaxDegreeVertex();
        ColorNumber ++;
        color[x] = ColorNumber;
        unprocessed --;
        UpdateNN(ColorNumber);
        while (NNCount>0)
        {
            y = FindSuitableY(ColorNumber, VerticesInCommon);
            if (VerticesInCommon == 0)
                y = MaxDegreeInNN();
            color[y] = ColorNumber;
            unprocessed --;
            UpdateNN(ColorNumber);
        }
    }
}

void PrintOutput()
{
    for (int i=0; i < n; i++)
        cout << "Vertex " << i+1
             << " is colored " << color[i] << endl;
}

int main() {
    Init();
    Coloring();
    PrintOutput();
    return 0;
}
