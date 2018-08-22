#include "stdafx.h"
#include "Flower.h"

// コンストラクタ
// argFSet: 属している食糧源集合
Flower::Flower(FlowerSet *argFSet)
{
  int i;

  fSet = argFSet;
  pos = new double[fSet->dataset->exVarNum];
  for (i = 0; i < fSet->dataset->exVarNum; i++)
  {
    pos[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
  }
  visitNum = 0;
  evaluate();
}

// デストラクタ
Flower::~Flower()
{
  delete[] pos;
}

// baseの近くの食糧源に変更する
// base: もとにする食糧源の添え字
void Flower::change(int base)
{
  int i, j;

  for (i = 0; i < fSet->dataset->exVarNum; i++)
  {
    pos[i] = fSet->flower[base]->pos[i];
  }
  i = rand() % fSet->dataset->exVarNum;
  j = (base + (rand() % (EBEE_NUM - 1) + 1)) % EBEE_NUM;
  pos[i] = pos[i] + (rand() / (RAND_MAX / 2.0) - 1) * (pos[i] - fSet->flower[j]->pos[i]);
  visitNum = 0;
  evaluate();
}

// 新しい食糧源に変更する
void Flower::renew()
{
  int i;

  for (i = 0; i < fSet->dataset->exVarNum; i++)
  {
    pos[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
  }
  visitNum = 0;
  evaluate();
}

// 評価値を算出する
void Flower::evaluate()
{
  int i, j;
  double diff;

  value = 0.0;
  for (i = 0; i < fSet->dataset->dataNum; i++)
  {
    diff = fSet->dataset->resSData[i];
    for (j = 0; j < fSet->dataset->exVarNum; j++)
    {
      diff -= pos[j] * fSet->dataset->exSData[i][j];
    }
    value += pow(diff, 2.0);
  }
}
