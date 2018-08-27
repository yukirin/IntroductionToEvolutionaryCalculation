#pragma once

#include "Nest.h"
class Nest;

class NestSet
{
  public:
    NestSet(const char *fileName);
    ~NestSet();
    void alternate();   // 世代交代をする
    void printResult(); // 結果を表示する

    Dataset *dataset; // データセット
    Nest **nest;      // 巣の集合のメンバ

  private:
    void sort(int lb, int ub); // 巣を良い順に並び替える
};
