#include "stdafx.h"
#include "HarmonyMemory.h"

// コンストラクタ
// fileName: データセットのファイル名
HarmonyMemory::HarmonyMemory(const char *fileName)
{
    int i;

    dataset = new Dataset(fileName);
    harmony = new Harmony *[HM_SIZE];
    best = 0;
    worst = 0;
    for (i = 0; i < HM_SIZE; i++)
    {
        harmony[i] = new Harmony(this);
        if (harmony[best]->value > harmony[i]->value)
        {
            best = i;
        }
        if (harmony[worst]->value < harmony[i]->value)
        {
            worst = i;
        }
    }
    newHarmony = new Harmony(this);
}

// デストラクタ
HarmonyMemory::~HarmonyMemory()
{
    int i;

    for (i = 0; i < HM_SIZE; i++)
    {
        delete harmony[i];
    }
    delete[] harmony;
    delete newHarmony;
    delete dataset;
}

// ハーモニーメモリを更新する
void HarmonyMemory::update()
{
    int i;
    Harmony *tmp;

    newHarmony->renew();
    if (harmony[worst]->value > newHarmony->value)
    {
        // ハーモニーを交換する
        tmp = newHarmony;
        newHarmony = harmony[worst];
        harmony[worst] = tmp;

        // 最良ハーモニーの添え字を更新する
        if (harmony[best]->value > harmony[worst]->value)
        {
            best = worst;
        }

        // 最悪ハーモニーの添え字を更新する
        worst = 0;
        for (i = 1; i < HM_SIZE; i++)
        {
            if (harmony[worst]->value < harmony[i]->value)
            {
                worst = i;
            }
        }
    }
}

// 結果を表示する
void HarmonyMemory::printResult()
{
    dataset->setCoef(harmony[best]->chord);
    dataset->printEquation();
}