// 4ch.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "FlowerSet.h"

using namespace std;

int main()
{
	int i;
	FlowerSet *fSet;

	srand((unsigned int)time(NULL));

	fSet = new FlowerSet("sampledata.csv");
	for (i = 1; i <= REPEAT_NUM; i++)
	{
		fSet->employedBeePhase();
		fSet->onlookerBeePhase();
		fSet->scoutBeePhase();
		fSet->saveBestPos();
		printf("%d times : best value%f\n", i, fSet->bestValue);
	}
	fSet->printResult();
	delete fSet;

	return 0;
}
