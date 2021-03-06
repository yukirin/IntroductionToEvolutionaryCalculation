// 7ch.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Population.h"

int main()
{
	int t;
	Population *pop;

	srand((unsigned int)time(NULL));

	pop = new Population("sampledata.csv");
	for (t = 1; t <= TIME_MAX; t++)
	{
		pop->move(t);
		printf("time%d : best value%f\n", t, pop->bestValue);
	}
	pop->printResult();
	delete pop;

	return 0;
}
