#pragma once

#include "Field.h"
#include "Colony.h"
class Colony;

// 定数の定義
#define REPEAT_NUM 1000 // 繰返し数
#define ANT_NUM 100     // 蟻の数
#define PHERO_Q 10      // 1回の巡回で分泌するフェロモン量
#define EVA_R 0.05      // フェロモンの蒸発率
#define PHERO_R 0.95    // フェロモンに基づいて経路を選択する確率
#define PHERO_L 1       // フェロモンを考慮する度合い
#define HEU_L 1         // ヒューリスティック情報を考慮する度合い

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Ant
{
  public:
    Ant(Colony *argColony);
    ~Ant();
    void selectRoute();  // 経路を選択する
    void putPheromone(); // フェロモンを分泌する

    Colony *colony;  // 属しているコロニー
    int *route;      // 経路
    double totalDis; // 総移動距離

  private:
    int *candidate; // 未訪問ノード
};
