#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <string.h>

int comp(const void *a, const void*b)
{
	return (*(int*)a-*(int*)b);
}

RankingItem *makeRanking(int n)
{
	RankingItem *ranking = malloc(sizeof(RankingItem) * n);
	for (int i = 0; i < n; i++) {
		strcpy(ranking[i].name, "[VAZIO]");
		ranking[i].time = 0;
	}
	return ranking;
}

void sortRanking(RankingItem *r, int n)
{
	int times[n];
	for (int i = 0; i < n; i++) {
		times[i] = r[i].time;
	}
	qsort(times, n, sizeof(int), comp);
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (r[i].time == times[i]) {
			r[j++] = r[i];
		}
	}
}

void updateRanking(RankingItem *r, int n, int index, char *name, double time)
{
	strcpy(r[index].name, name);
	r[index].time = time;
	//sortRanking(r, n);
}
