#include "stdafx.h"
#include "Field.h"

#pragma warning(disable:4996)

// コンストラクタ
// fileName: データセットのファイル名
Field::Field(const char *fileName)
{
    int i, j, columnNum, dataNum;
    char line[1024];
    FILE *fp;
    char *pos1;
    char *pos2;

    // ノード数の取得
    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("not open %s\n", fileName);
        exit(1);
    }
    nodeNum = -1;
    dataNum = 0;
    while (fgets(line, 1024, fp))
    {
        if (strcmp(line, "\n"))
        {
            columnNum = 1;
            pos1 = line;
            do
            {
                pos2 = strchr(pos1, ',');
                if (pos2)
                {
                    if (pos2 == pos1)
                    {
                        printf("include empty data");
                        exit(1);
                    }
                    columnNum++;
                    pos1 = pos2 + 1;
                }
            } while (pos2);
            if (*pos1 == '\n')
            {
                printf("include empty data");
                exit(1);
            }
            if (nodeNum == -1)
            {
                nodeNum = columnNum;
            }
            else if (nodeNum != columnNum)
            {
                printf("different line colum");
                exit(1);
            }
            dataNum++;
        }
    }
    fclose(fp);
    if (nodeNum != dataNum)
    {
        printf("not match line or colum");
        exit(1);
    }

    // 領域を確保して初期化する
    distance = new double *[nodeNum];
    pheromone = new double *[nodeNum];
    for (i = 0; i < nodeNum; i++)
    {
        pheromone[i] = new double[nodeNum];
        for (j = 0; j < nodeNum; j++)
        {
            pheromone[i][j] = 0.0;
        }
    }

    // データを読込む
    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("not open %s\n", fileName);
        exit(1);
    }
    for (i = 0; i < nodeNum; i++)
    {
        distance[i] = new double[nodeNum];
        fgets(line, 1024, fp);
        pos1 = line;
        for (j = 0; j < nodeNum - 1; j++)
        {
            pos2 = strchr(pos1, ',');
            *pos2 = '\0';
            distance[i][j] = atof(pos1);
            if ((i != j) && (distance[i][j] == 0.0))
            {
                printf("is exist length 0.0 data\n");
                exit(1);
            }
            pos1 = pos2 + 1;
        }
        pos2 = strchr(pos1, '\n');
        *pos2 = '\0';
        distance[i][j] = atof(pos1);
        if ((i != j) && (distance[i][j] == 0.0))
        {
            printf("is exist length 0.0 data\n");
            exit(1);
        }
    }
    fclose(fp);
}

// デストラクタ
Field::~Field()
{
    int i;

    for (i = 0; i < nodeNum; i++)
    {
        delete[] distance[i];
        delete[] pheromone[i];
    }
    delete[] distance;
    delete[] pheromone;
}
