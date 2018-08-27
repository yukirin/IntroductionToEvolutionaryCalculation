#include "stdafx.h"
#include "NestSet.h"

// コンストラクタ
// fileName: データセットのファイル名
NestSet::NestSet(const char *fileName)
{
    int i;

    dataset = new Dataset(fileName);
    nest = new Nest *[SET_SIZE];
    for (i = 0; i < SET_SIZE; i++)
    {
        nest[i] = new Nest(this);
    }
    sort(0, SET_SIZE - 1);
}

// デストラクタ
NestSet::~NestSet()
{
    int i;

    for (i = 0; i < SET_SIZE; i++)
    {
        delete nest[i];
    }
    delete[] nest;
    delete dataset;
}

// 世代交代をする
void NestSet::alternate()
{
    int i, r1, r2;

    // 新しい卵を生成する
    r1 = rand() % SET_SIZE;
    r2 = (r1 + (rand() % (SET_SIZE - 1) + 1)) % SET_SIZE;
    nest[r2]->replace(nest[r1]);

    // 悪い巣を放棄する
    for (i = (int)(SET_SIZE * (1 - ABA_RATE)); i < SET_SIZE; i++)
    {
        nest[i]->abandon();
    }

    // 巣を良い順に並べ替える
    sort(0, SET_SIZE - 1);
}

// nest[lb]～next[ub]をクイックソートで並び替える
// lb: 並び替えの対象要素の添え字の下限
// ub: 並び替えの対象要素の添え字の上限
void NestSet::sort(int lb, int ub)
{
    int i, j, k;
    double pivot;
    Nest *tmp;

    if (lb < ub)
    {
        k = (lb + ub) / 2;
        pivot = nest[k]->value;
        i = lb;
        j = ub;
        do
        {
            while (nest[i]->value < pivot)
            {
                i++;
            }
            while (nest[j]->value > pivot)
            {
                j--;
            }
            if (i <= j)
            {
                tmp = nest[i];
                nest[i] = nest[j];
                nest[j] = tmp;
                i++;
                j--;
            }
        } while (i <= j);
        sort(lb, j);
        sort(i, ub);
    }
}

// 結果を表示する
void NestSet::printResult()
{
    dataset->setCoef(nest[0]->egg);
    dataset->printEquation();
}
