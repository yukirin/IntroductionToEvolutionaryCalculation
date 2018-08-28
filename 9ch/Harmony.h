#pragma once

#include "Dataset.h"
#include "HarmonyMemory.h"
class HarmonyMemory;

// 定数の定義
#define REPEAT_NUM 1000 // 繰返し数
#define HM_SIZE 100     // ハーモニーメモリのサイズ
#define R_A 0.8         // 選択比率
#define R_P 0.3         // 値調整比率
#define BANDWIDTH 0.1   // バンド幅
#define COEF_MIN -1     // 標準偏回帰係数の最小値
#define COEF_MAX 1      // 標準偏回帰係数の最大値

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Harmony
{
  public:
    Harmony(HarmonyMemory *argHM);
    ~Harmony();

    void renew(); // 新しいハーモニーに変更する

    HarmonyMemory *hm; // 属しているハーモニーメモリ
    double *chord;     // 和音列
    double value;      // 評価値

  private:
    void evaluate(); // 評価値を算出する
};
