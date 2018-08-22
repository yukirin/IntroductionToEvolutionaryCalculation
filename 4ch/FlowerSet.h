#pragma once

#include "Flower.h"
class Flower;

class FlowerSet
{
  public:
    FlowerSet(char *fileName);
    ~FlowerSet();
    void employedBeePhase(); // 収穫バチフェーズを実行する
    void onlookerBeePhase(); // 追従バチフェーズを実行する
    void scoutBeePhase();    // 偵察バチフェーズを実行する
    void saveBestPos();      // 最良食糧源を記録する
    void printResult();      // 結果を表示する

    Dataset *dataset; // データセット
    Flower **flower;  // 食糧源の集合のメンバ
    double *bestPos;  // 最良食糧源の位置
    double bestValue; // 最良食糧源の評価値

  private:
    Flower *newFlower; // 新しい食糧源
    double *trValue;   // 各食糧源の変換後の評価値
};
