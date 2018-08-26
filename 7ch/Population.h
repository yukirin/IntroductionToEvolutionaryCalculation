#pragma once

#include "Bat.h"
class Bat;

class Population
{
  public:
    Population(const char *fileName);
    ~Population();
    void move(int t);   // コウモリを移動する
    void printResult(); // 結果を表示する

    Dataset *dataset; // データセット
    Bat **bat;        // コウモリ群のメンバ
    double *bestPos;  // 最良コウモリの位置
    double bestValue; // 最良コウモリの評価値

  private:
    void sort(int lb, int ub); // コウモリを良い順に並び替える
};
