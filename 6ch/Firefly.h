#pragma once

#include "Dataset.h"
#include "Population.h"
class Population;

// 定数の定義
#define TIME_MAX 100  // 最終時刻
#define POP_SIZE 100  // ホタル群のサイズ
#define ABSORB 0.5    // 吸収係数
#define RANDOMIZE 0.5 // ランダム性パラメータ
#define ATTRACT 1     // 発光地点における誘引度
#define COEF_MIN -1   // 標準偏回帰係数の最小値
#define COEF_MAX 1    // 標準偏回帰係数の最大値

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Firefly
{
  public:
    Firefly(Population *argPop);
    ~Firefly();
    void move(Firefly *base); // ホタルを移動する

    Population *pop;  // 属しているホタル群
    double *pos;      // 位置
    double intensity; // 光の強度

  private:
    void evaluate(); // 光の強度を算出する
};
