#pragma once

#include "Dataset.h"
#include "FlowerSet.h"
class FlowerSet;

// 定数の定義
#define REPEAT_NUM 1000 // 繰返し数
#define EBEE_NUM 100    // 収穫バチの数
#define OBEE_NUM 10     // 追従バチの数
#define VISIT_MAX 10    // 蜜の採取可能回数
#define COEF_MIN -1     // 標準偏回帰係数の最小値
#define COEF_MAX 1      // 標準偏回帰係数の最大値

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Flower
{
  public:
    Flower(FlowerSet *argFSet);
    ~Flower();
    void change(int base); // 近くの食糧源に変更する
    void renew();          // 新しい食糧源に変更する

    FlowerSet *fSet; // 属している食糧源集合
    double *pos;     // 位置
    double value;    // 評価値
    int visitNum;    // 蜜の採取回数

  private:
    void evaluate(); // 評価値を算出する
};
