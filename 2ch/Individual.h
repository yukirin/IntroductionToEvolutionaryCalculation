#pragma once

// 標準ヘッダのインクルード
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

// 定数の定義
#define GEN_MAX     1000   // 世代交代数
#define POP_SIZE    1000   // 個体群のサイズ
#define ELITE       1      // エリート保存戦略で残す個体の数
#define MUTATE_PROB 0.01   // 突然変異確率
#define N           64     // 集合の要素となる最大数の平方値
/*
#define TOURNAMENT_SIZE 30 // トーナメントサイズ
*/

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Individual
{
public:
	Individual();
	~Individual();
	void evaluate();                                // 適応度を算出する
	void crossover(Individual *p1, Individual *p2); // 交叉による子にする
	void mutate();                                  // 突然変異を起こす

	int chrom[N];                                   // 染色体
	double fitness;                                 // 適応度
};
