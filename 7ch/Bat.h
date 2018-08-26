#pragma once

#include "Dataset.h"
#include "Population.h"
class Population;

// 定数の定義
#define TIME_MAX 500  // 最終時刻
#define POP_SIZE 20   // コウモリ群のサイズ
#define PULSE_0 0.5   // パルス率の収束値
#define PULSE_R 0.9   // パルス率の更新パラメータ
#define LOUD_0 1.0    // 音量の初期値
#define LOUD_R 0.9    // 音量の変化率
#define FREQ_MIN 0    // 周波数の最小値
#define FREQ_MAX 1    // 周波数の最大値
#define BEST_RATE 0.2 // 良いコウモリと判断する割合
#define COEF_MIN -1   // 標準偏回帰係数の最小値
#define COEF_MAX 1    // 標準偏回帰係数の最大値

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Bat
{
  public:
    Bat(Population *argPop);
    ~Bat();
    void move(int t); // コウモリを移動する

    Population *pop;  // 属しているコウモリ群
    double *pos;      // 位置
    double *velocity; // 速度
    double freq;      // 周波数
    double pulse;     // パルス率
    double loudness;  // 音量
    double value;     // 評価値

  private:
    double evaluate(double *argPos); // 評価値を算出する

    double *newPos1; // 新しい位置（良いコウモリの近く）
    double *newPos2; // 新しい位置（ランダム）
};
