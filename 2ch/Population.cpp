#include "stdafx.h"
#include "Population.h"

// コンストラクタ
Population::Population()
{
	int i;

	ind = new Individual*[POP_SIZE];
	nextInd = new Individual*[POP_SIZE];
	for (i = 0; i < POP_SIZE; i++) {
		ind[i] = new Individual();
		nextInd[i] = new Individual();
	}
	evaluate();
}

// デストラクタ
Population::~Population()
{
	int i;

	for (i = 0; i < POP_SIZE; i++) {
		delete ind[i];
		delete nextInd[i];
	}
	delete[] ind;
	delete[] nextInd;
}

// すべての個体を評価して，適応度順に並び替える
void Population::evaluate()
{
	int i;

	for (i = 0; i < POP_SIZE; i++) {
		ind[i]->evaluate();
	}
	sort(0, POP_SIZE - 1);
}

// ind[lb]～ind[ub]をクイックソートで並び替える
// lb: 並び替えの対象要素の添え字の下限
// ub: 並び替えの対象要素の添え字の上限
void Population::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	Individual *tmp;

	if (lb < ub) {
		k = (lb + ub) / 2;
		pivot = ind[k]->fitness;
		i = lb;
		j = ub;
		do {
			while (ind[i]->fitness < pivot) {
				i++;
			}
			while (ind[j]->fitness > pivot) {
				j--;
			}
			if (i <= j) {
				tmp = ind[i];
				ind[i] = ind[j];
				ind[j] = tmp;
				i++;
				j--;
			}
		} while (i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

// 世代交代をする
void Population::alternate()
{
	int i, j, p1, p2;
	Individual **tmp;

	// ルーレット選択のための処理
	/*
	denom = 0.0;
	for(i = 0; i < POP_SIZE; i++) {
		trFit[i] = (ind[POP_SIZE - 1]->fitness - ind[i]->fitness) / (ind[POP_SIZE - 1]->fitness - ind[0]->fitness);
		denom += trFit[i];
	}
	*/

	// エリート保存戦略で子個体を作る
	for (i = 0; i < ELITE; i++) {
		for (j = 0; j < N; j++) {
			nextInd[i]->chrom[j] = ind[i]->chrom[j];
		}
	}

	// 親を選択し交叉する
	for (; i < POP_SIZE; i++) {
		p1 = select();
		p2 = select();
		nextInd[i]->crossover(ind[p1], ind[p2]);
	}

	// 突然変異を起こす
	for (i = 1; i < POP_SIZE; i++) {
		nextInd[i]->mutate();
	}

	// 次世代を現世代に変更する
	tmp = ind;
	ind = nextInd;
	nextInd = tmp;

	// 評価する
	evaluate();
}

// 順位に基づくランキング選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
int Population::select()
{
	int num, denom, r;

	denom = POP_SIZE * (POP_SIZE + 1) / 2;
	r = ((rand() << 16) + (rand() << 1) + (rand() % 2)) % denom + 1;
	for (num = POP_SIZE; 0 < num; num--) {
		if (r <= num) {
			break;
		}
		r -= num;
	}
	return POP_SIZE - num;
}

// 確率に基づくランキング選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
/*
int Population::select()
{
	int rank, denom;
	double prob, r;

	denom = POP_SIZE * (POP_SIZE + 1) / 2;
	r = RAND_01;
	for(rank = 1; rank < POP_SIZE; rank++) {
		prob = (double)(POP_SIZE - rank + 1) / denom;
		if(r <= prob) {
			break;
		}
		r -= prob;
	}
	return rank - 1;
}
*/

// ルーレット選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
/*
int Population::select()
{
	int rank;
	double prob, r;

	r = RAND_01;
	for(rank = 1; rank < POP_SIZE; rank++) {
		prob = trFit[rank - 1] / denom;
		if(r <= prob) {
			break;
		}
		r -= prob;
	}
	return rank - 1;
}
*/

// トーナメント選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
/*
int Population::select()
{
	int i, ret, num, r;
	double bestFit;
	int tmp[N];

	for(i = 0; i < N; i++) {
		tmp[i] = 0;
	}
	ret = -1;
	bestFit = DBL_MAX;
	num = 0;
	while(1) {
		r = rand() % N;
		if(tmp[r] == 0) {
			tmp[r] = 1;
			if(ind[r]->fitness < bestFit) {
				ret = r;
				bestFit = ind[r]->fitness;
			}
			if(++num == TOURNAMENT_SIZE) {
				break;
			}
		}
	}
	return ret;
}
*/

// 結果を表示する
void Population::printResult()
{
	int i;

	printf("set A : ");
	for (i = 0; i < N; i++) {
		if (ind[0]->chrom[i] == 1) {
			printf("√%d ", i + 1);
		}
	}
	printf("\nset B : ");
	for (i = 0; i < N; i++) {
		if (ind[0]->chrom[i] == 0) {
			printf("√%d ", i + 1);
		}
	}
	printf("\ndiff : %f\n", ind[0]->fitness);
}

