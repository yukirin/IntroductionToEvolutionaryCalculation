// 8ch.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "NestSet.h"

int main()
{
	int i;
	NestSet *ns;

	srand((unsigned int)time(NULL));

	ns = new NestSet("sampledata.csv");
	for (i = 1; i <= GEN_MAX; i++)
	{
		ns->alternate();
		printf("%d times : best value%f\n", i, ns->nest[0]->value);
	}
	ns->printResult();
	delete ns;

	return 0;
}
