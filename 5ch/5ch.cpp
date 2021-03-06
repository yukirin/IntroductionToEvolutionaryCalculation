// 5ch.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Swarm.h"

int main()
{
	int t;
	Swarm *swarm;

	srand((unsigned int)time(NULL));

	swarm = new Swarm("sampledata.csv");
	for (t = 1; t <= TIME_MAX; t++)
	{
		swarm->move();
		printf("time %d : best value%f\n", t, swarm->gBestValue);
	}
	swarm->printResult();
	delete swarm;

	return 0;
}
