#pragma once

#include "Dataset.h"
#include "NestSet.h"
class NestSet;

// 定数の定義
#define GEN_MAX 1000 // 世代交代数
#define SET_SIZE 100 // 巣集合のサイズ
#define ABA_RATE 0.1 // 放棄する巣の割合
#define ALPHA 0.1    // ステップ長調整パラメータ
#define BETA 1.5     // スケーリング指数
#define PI 3.141592  // 円周率
#define COEF_MIN -1  // 標準偏回帰係数の最小値
#define COEF_MAX 1   // 標準偏回帰係数の最大値

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

// 標準正規分布に従う乱数
#define RAND_N (sqrt(-2.0 * log(RAND_01) * cos(2 * PI * RAND_01)))

// レヴィフライトのステップ長算出に使用する標準偏差
#define NUME (tgamma(1 + BETA) * sin(PI * BETA / 2))
#define DENOM (tgamma((1 + BETA) / 2) * BETA * pow(2.0, (BETA - 1) / 2))
#define SIGMA pow(NUME / DENOM, 1 / BETA)

class Nest
{
  public:
    Nest(NestSet *argNS);
    ~Nest();

    void replace(Nest *base); // 卵を置換する
    void abandon();           // 巣を放棄する

    NestSet *ns;  // 属している巣集合
    double *egg;  // 卵
    double value; // 評価値

  private:
    double evaluate(double *argEgg); // 評価値を算出する

    double *newEgg; // 新しい卵
};
