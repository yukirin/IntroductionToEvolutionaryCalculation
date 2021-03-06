// 6ch.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Population.h"

int main()
{
	int i;
	Population *pop;

	srand((unsigned int)time(NULL));

	pop = new Population("sampledata.csv");
	for (i = 1; i <= TIME_MAX; i++)
	{
		pop->move();
		printf("time %d : light best strength %f\n", i, pop->bestInt);
	}
	pop->printResult();
	delete pop;

	return 0;
}

