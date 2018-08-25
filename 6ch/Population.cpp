#include "stdafx.h"
#include "Population.h"

// コンストラクタ
// fileName: データセットのファイル名
Population::Population(const char *fileName)
{
    int i, best;

    dataset = new Dataset(fileName);
    firefly = new Firefly *[POP_SIZE];
    best = 0;
    for (i = 0; i < POP_SIZE; i++)
    {
        firefly[i] = new Firefly(this);
        if (firefly[best]->intensity > firefly[i]->intensity)
        {
            best = i;
        }
    }
    bestPos = new double[dataset->exVarNum];
    for (i = 0; i < dataset->exVarNum; i++)
    {
        bestPos[i] = firefly[best]->pos[i];
    }
    bestInt = firefly[best]->intensity;
}

// デストラクタ
Population::~Population()
{
    int i;

    for (i = 0; i < POP_SIZE; i++)
    {
        delete firefly[i];
    }
    delete[] firefly;
    delete[] bestPos;
    delete dataset;
}

// ホタルを移動する
void Population::move()
{
    int i, j, k;

    // すべての蛍のペアについて繰り返す
    for (i = 0; i < POP_SIZE; i++)
    {
        for (j = 0; j < POP_SIZE; j++)
        {
            // ホタルを移動する
            firefly[i]->move(firefly[j]);
            // 最も明るいホタルの位置を更新する
            if (bestInt > firefly[i]->intensity)
            {
                for (k = 0; k < dataset->exVarNum; k++)
                {
                    bestPos[k] = firefly[i]->pos[k];
                }
                bestInt = firefly[i]->intensity;
            }
        }
    }
}

// 結果を表示する
void Population::printResult()
{
    dataset->setCoef(bestPos);
    dataset->printEquation();
}
