#pragma once

#include "Harmony.h"
class Harmony;

class HarmonyMemory
{
  public:
    HarmonyMemory(const char *fileName);
    ~HarmonyMemory();
    void update();      // ハーモニーメモリを更新する
    void printResult(); // 結果を表示する

    Dataset *dataset;  // データセット
    Harmony **harmony; // 現在のハーモニーの集合のメンバ
    int best;          // 最良ハーモニーの添え字

  private:
    Harmony *newHarmony; // 新しいハーモニー
    int worst;           // 最悪ハーモニーの添え字
};
