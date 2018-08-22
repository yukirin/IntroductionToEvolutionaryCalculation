#include "stdafx.h"
#include "Colony.h"

// コンストラクタ
// fileName: データセットのファイル名
Colony::Colony(const char *fileName)
{
  int i;

  field = new Field(fileName);
  ant = new Ant *[ANT_NUM];
  for (i = 0; i < ANT_NUM; i++)
  {
    ant[i] = new Ant(this);
  }
  nume = new double *[field->nodeNum];
  for (i = 0; i < field->nodeNum; i++)
  {
    nume[i] = new double[field->nodeNum];
  }
}

// デストラクタ
Colony::~Colony()
{
  int i;

  for (i = 0; i < ANT_NUM; i++)
  {
    delete ant[i];
  }
  delete[] ant;
  for (i = 0; i < field->nodeNum; i++)
  {
    delete[] nume[i];
  }
  delete[] nume;
  delete field;
}

// 経路を選択する
void Colony::selectRoute()
{
  int i, j;

  // 確率の分子を算出する
  for (i = 0; i < field->nodeNum; i++)
  {
    for (j = 1; j < i; j++)
    {
      nume[i][j] = pow(field->pheromone[j][i], PHERO_L) * pow(1 / field->distance[i][j], HEU_L);
    }
    for (j = i + 1; j < field->nodeNum; j++)
    {
      nume[i][j] = pow(field->pheromone[i][j], PHERO_L) * pow(1 / field->distance[i][j], HEU_L);
    }
  }

  // 経路を選択する
  for (i = 0; i < ANT_NUM; i++)
  {
    ant[i]->selectRoute();
  }
}

// フェロモン量を更新する
void Colony::renewPheromone()
{
  int i, j;

  // 蒸発させる
  for (i = 0; i < field->nodeNum; i++)
  {
    for (j = i + 1; j < field->nodeNum; j++)
    {
      field->pheromone[i][j] *= 1 - EVA_R;
    }
  }

  // アリによる追加分を加算する
  for (i = 0; i < ANT_NUM; i++)
  {
    ant[i]->putPheromone();
  }
}

// フェロモン量を表示する
void Colony::printPheromone()
{
  int i, j;

  using namespace std;

  for (i = 0; i < field->nodeNum; i++)
  {
    for (j = 0; j < field->nodeNum; j++)
    {
      printf("%8.3f", field->pheromone[i][j]);
    }
    printf("\n");
  }
}
