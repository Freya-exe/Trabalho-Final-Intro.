#include <raylib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <string.h>

int comp(const void *a, const void*b)
{
	const RankingItem *ra = a;
	const RankingItem *rb = b;

	if (ra->time > rb->time) {
		return 1;
	} else if (ra->time < rb->time) {
		return -1;
	} else {
		return 0;
	}
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
	qsort(r, n, sizeof(RankingItem), comp);
}

void updateRanking(RankingItem *r, int n, int index, char *name, double time)
{
	strcpy(r[index].name, name);
	r[index].time = time;
}

void writeRanking(RankingItem *r, int n) 
{
	FILE *fd = fopen("ranking.bin", "wb");
	if (!fd) {
		TraceLog(LOG_ERROR, "Error: could not write ranking");
		return;
	}

	fwrite(r, n, sizeof(RankingItem), fd);
	fclose(fd);
}

void readRanking(RankingItem *r, int n)
{
	FILE *fd = fopen("ranking.bin", "rb");
	if (!fd) {
		TraceLog(LOG_ERROR, "Error: could not read ranking");
		return;
	}
	fread(r, n, sizeof(RankingItem), fd);
	fclose(fd);
}
