#include "stdafx.h"
#include "Bat.h"

// コンストラクタ
// argPop: 属しているコウモリ群
Bat::Bat(Population *argPop)
{
    int i;

    pop = argPop;
    pos = new double[pop->dataset->exVarNum];
    newPos1 = new double[pop->dataset->exVarNum];
    newPos2 = new double[pop->dataset->exVarNum];
    velocity = new double[pop->dataset->exVarNum];
    for (i = 0; i < pop->dataset->exVarNum; i++)
    {
        pos[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
        velocity[i] = 0.0;
    }
    value = evaluate(pos);
    freq = 0.0;
    pulse = 0.0;
    loudness = LOUD_0;
}

// デストラクタ
Bat::~Bat()
{
    delete[] pos;
    delete[] newPos1;
    delete[] newPos2;
    delete[] velocity;
}

// コウモリを移動する
// t: 時刻
void Bat::move(int t)
{
    int i, r;
    double newValue1, newValue2, aveLoud, *tmp;

    // 最良コウモリの方向に移動する
    freq = FREQ_MIN + (FREQ_MAX - FREQ_MIN) * RAND_01;
    for (i = 0; i < pop->dataset->exVarNum; i++)
    {
        velocity[i] += (pop->bestPos[i] - pos[i]) * freq;
        pos[i] += velocity[i];
    }
    value = evaluate(pos);

    // 良いコウモリの近傍に新しい移動先を生成する
    if (RAND_01 > pulse)
    {
        r = rand() % (int)(POP_SIZE * BEST_RATE);
        aveLoud = 0.0;
        for (i = 0; i < POP_SIZE; i++)
        {
            aveLoud += pop->bat[i]->loudness;
        }
        aveLoud /= POP_SIZE;
        for (i = 0; i < pop->dataset->exVarNum; i++)
        {
            newPos1[i] = pop->bat[r]->pos[i] + (rand() / (RAND_MAX / 2.0) - 1) * aveLoud;
        }
        newValue1 = evaluate(newPos1);
    }
    else
    {
        newValue1 = DBL_MAX;
    }

    // ランダムに新しい移動先を生成する
    for (i = 0; i < pop->dataset->exVarNum; i++)
    {
        newPos2[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
    }
    newValue2 = evaluate(newPos2);

    // 新しい移動先のほうが良かったら置換し，パルス率と音量を更新する
    if (((newValue1 < value) || (newValue2 < value)) && (RAND_01 < loudness))
    {
        if (newValue1 < newValue2)
        {
            tmp = pos;
            pos = newPos1;
            newPos1 = tmp;
            value = newValue1;
        }
        else
        {
            tmp = pos;
            pos = newPos2;
            newPos2 = tmp;
            value = newValue2;
        }
        pulse = PULSE_0 * (1 - exp(-PULSE_R * (double)t));
        loudness *= LOUD_R;
    }
}

// 評価値を算出する
// argPos: 評価対象のコウモリの位置
// 戻り値: 評価値
double Bat::evaluate(double *argPos)
{
    int i, j;
    double diff, retValue;

    retValue = 0.0;
    for (i = 0; i < pop->dataset->dataNum; i++)
    {
        diff = pop->dataset->resSData[i];
        for (j = 0; j < pop->dataset->exVarNum; j++)
        {
            diff -= argPos[j] * pop->dataset->exSData[i][j];
        }
        retValue += pow(diff, 2.0);
    }
    return retValue;
}