// 2ch.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Population.h"

using namespace std;

int main()
{
	int i;
	Population *pop;

	srand((unsigned int)time(NULL));

	pop = new Population();
	for (i = 1; i <= GEN_MAX; i++) {
		pop->alternate();
		printf("%d generation : Best fitness %f\n", i, pop->ind[0]->fitness);
	}
	pop->printResult();
	delete pop;

	return 0;
}
