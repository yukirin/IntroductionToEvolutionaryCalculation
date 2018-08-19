#include "stdafx.h"
#include "Ant.h"

// コンストラクタ
// argColony: 属しているコロニー
Ant::Ant(Colony *argColony)
{
    colony = argColony;
    route = new int[colony->field->nodeNum];
    candidate = new int[colony->field->nodeNum];
    route[0] = 0;
    candidate[0] = 0;
    totalDis = 0.0;
}

// デストラクタ
Ant::~Ant()
{
    delete[] route;
    delete[] candidate;
}

// 経路を選択する
void Ant::selectRoute()
{
    int i, j, next, next2;
    double denom, r, prob;

    // 未訪問ノードを初期化する
    for (i = 1; i < colony->field->nodeNum; i++)
    {
        candidate[i] = 1;
    }

    // 経路を選択する
    totalDis = 0.0;
    for (i = 0; i < colony->field->nodeNum - 2; i++)
    {
        // 確率の分母を算出する
        denom = 0.0;
        for (j = 1; j < colony->field->nodeNum; j++)
        {
            if (candidate[j] == 1)
            {
                denom += colony->nume[route[i]][j];
            }
        }
        // 次のノードを選択する
        next = -1;
        if ((denom != 0.0) && (RAND_01 <= PHERO_R))
        {
            // フェロモン量に基づいて選択する
            r = RAND_01;
            for (next = 1; next < colony->field->nodeNum; next++)
            {
                if (candidate[next] == 1)
                {
                    prob = colony->nume[route[i]][next] / denom;
                    if (r <= prob)
                    {
                        break;
                    }
                    r -= prob;
                }
            }
            if (next == colony->field->nodeNum)
            {
                next = -1;
            }
        }
        if (next == -1)
        {
            // ランダムに選択する
            next2 = rand() % (colony->field->nodeNum - i - 1);
            for (next = 1; next < colony->field->nodeNum - 1; next++)
            {
                if (candidate[next] == 1)
                {
                    if (next2 == 0)
                    {
                        break;
                    }
                    else
                    {
                        next2--;
                    }
                }
            }
        }
        route[i + 1] = next;
        candidate[next] = 0;
        totalDis += colony->field->distance[route[i]][next];
    }

    // 最後の1ノードを探索する
    for (next = 1; next < colony->field->nodeNum; next++)
    {
        if (candidate[next] == 1)
        {
            break;
        }
    }
    route[colony->field->nodeNum - 1] = next;
    totalDis += colony->field->distance[route[colony->field->nodeNum - 2]][next];

    // 出発地点への距離を加算する
    totalDis += colony->field->distance[next][0];
}

// フェロモンを分泌する
void Ant::putPheromone()
{
    int i;
    double p;

    p = PHERO_Q / totalDis;
    for (i = 0; i < colony->field->nodeNum - 1; i++)
    {
        if (route[i] < route[i + 1])
        {
            colony->field->pheromone[route[i]][route[i + 1]] += p;
        }
        else
        {
            colony->field->pheromone[route[i + 1]][route[i]] += p;
        }
    }
    colony->field->pheromone[0][route[colony->field->nodeNum - 1]] += p;
}
