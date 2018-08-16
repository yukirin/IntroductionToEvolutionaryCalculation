#pragma once

#include "Individual.h"

class Population
{
public:
	Population();
	~Population();
	void alternate();          // 世代交代をする
	void printResult();        // 結果を表示する

	Individual **ind;          // 現世代の個体群のメンバ

private:
	void evaluate();           // 個体を評価する
	int select();              // 親個体を選択する
	void sort(int lb, int ub); // 個体を良い順に並び替える

	Individual **nextInd;      // 次世代の個体群のメンバ
	 /*
	double trFit[POP_SIZE];    // 適応度を変換した値
	double denom;              // ルーレット選択の確率を求めるときの分母
	*/
};
