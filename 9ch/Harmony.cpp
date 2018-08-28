#include "stdafx.h"
#include "Harmony.h"

// コンストラクタ
// argHM: 属しているハーモニーメモリ
Harmony::Harmony(HarmonyMemory *argHM)
{
    int i;

    hm = argHM;
    chord = new double[hm->dataset->exVarNum];
    for (i = 0; i < hm->dataset->exVarNum; i++)
    {
        chord[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
    }
    evaluate();
}

// デストラクタ
Harmony::~Harmony()
{
    delete[] chord;
}

// 新しいハーモニーに変更する
void Harmony::renew()
{
    int i, r;

    for (i = 0; i < hm->dataset->exVarNum; i++)
    {
        if (RAND_01 < R_A)
        {
            r = rand() % HM_SIZE;
            if (RAND_01 < R_P)
            {
                chord[i] = hm->harmony[r]->chord[i] + BANDWIDTH * (rand() / (RAND_MAX / 2.0) - 1);
            }
            else
            {
                chord[i] = hm->harmony[r]->chord[i];
            }
        }
        else
        {
            chord[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
        }
    }
    evaluate();
}

// 評価値を算出する
void Harmony::evaluate()
{
    int i, j;
    double diff;

    value = 0.0;
    for (i = 0; i < hm->dataset->dataNum; i++)
    {
        diff = hm->dataset->resSData[i];
        for (j = 0; j < hm->dataset->exVarNum; j++)
        {
            diff -= chord[j] * hm->dataset->exSData[i][j];
        }
        value += pow(diff, 2.0);
    }
}