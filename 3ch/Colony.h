#pragma once

#include "Ant.h"
class Ant;

class Colony
{
  public:
    Colony(const char *fileName);
    ~Colony();
    void selectRoute();    // 経路を選択する
    void renewPheromone(); // フェロモン量を更新する
    void printPheromone(); // フェロモン量を表示する

    Field *field;  // 採餌行動の場
    Ant **ant;     // コロニーのメンバ
    double **nume; // 経路選択確率の分子
};
