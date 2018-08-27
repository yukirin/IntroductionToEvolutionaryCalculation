#include "stdafx.h"
#include "Nest.h"

// コンストラクタ
// argNS: 属している巣の集合
Nest::Nest(NestSet *argNS)
{
    int i;

    ns = argNS;
    egg = new double[ns->dataset->exVarNum];
    newEgg = new double[ns->dataset->exVarNum];
    for (i = 0; i < ns->dataset->exVarNum; i++)
    {
        egg[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
    }
    value = evaluate(egg);
}

// デストラクタ
Nest::~Nest()
{
    delete[] egg;
    delete[] newEgg;
}

// 卵を置換する
// base: もとにする卵の巣
void Nest::replace(Nest *base)
{
    int i;
    double u, v, s, newValue;
    double *tmp;

    for (i = 0; i < ns->dataset->exVarNum; i++)
    {
        u = RAND_N * SIGMA;
        v = RAND_N;
        s = u / pow(fabs(v), 1 / BETA);
        newEgg[i] = base->egg[i] + ALPHA * s;
    }
    newValue = evaluate(newEgg);
    if (newValue < value)
    {
        tmp = egg;
        egg = newEgg;
        newEgg = tmp;
        value = newValue;
    }
}

// 巣を放棄する
void Nest::abandon()
{
    int i;

    for (i = 0; i < ns->dataset->exVarNum; i++)
    {
        egg[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
    }
    value = evaluate(egg);
}

// 評価値を算出する
// argEgg: 評価対象の卵
// 戻り値: 評価値
double Nest::evaluate(double *argEgg)
{
    int i, j;
    double diff;
    double retValue;

    retValue = 0.0;
    for (i = 0; i < ns->dataset->dataNum; i++)
    {
        diff = ns->dataset->resSData[i];
        for (j = 0; j < ns->dataset->exVarNum; j++)
        {
            diff -= argEgg[j] * ns->dataset->exSData[i][j];
        }
        retValue += pow(diff, 2.0);
    }
    return retValue;
}
