#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Food
{
    int p;
    int f;
    int s;
    int v;
    int index;
    int price;
};

#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX_NUM_FOODS 50

struct Food minFood;
struct Food foods[MAX_NUM_FOODS + 1];
int recipe[MAX_NUM_FOODS + 1], recipeLength;
int answer[MAX_NUM_FOODS + 1], answerLength;
int visit[MAX_NUM_FOODS + 1];
int lowerBound = INT_MAX;
int nutrientSum = 0;
int numInput;

void branchBound(int depth, struct Food food);
int initialCmp(const void* pfood1, const void* pfood2);
int answerCmp(const void* p1, const void* p2);
int recipeCmp(const int* recipe1, int recipe1Length, const int* recipe2, int recipe2Length);

int main()
{
    freopen("food.inp", "r", stdin);
    freopen("food.out", "w", stdout);

    scanf("%d %d %d %d %d", &numInput, &minFood.p, &minFood.f, &minFood.s, &minFood.v);
    minFood.p = -minFood.p;
    minFood.f = -minFood.f;
    minFood.s = -minFood.s;
    minFood.v = -minFood.v;

    for (int i = 0; i < numInput; ++i)
    {
        struct Food* food = &foods[i];
        scanf("%d %d %d %d %d", &food->p, &food->f, &food->s, &food->v, &food->price);
        food->index = i;
    }
    qsort(foods, numInput, sizeof(struct Food), initialCmp);

    branchBound(0, minFood);

    if (answerLength == 0)
    {
        printf("0");
    }
    else
    {
        qsort(answer, answerLength, sizeof(int), answerCmp);
        for (int i = 0; i < answerLength; ++i)
            printf("%d ", answer[i]);
    }

    return 0;
}

void branchBound(int depth, struct Food food)
{
    struct Food newFood = food;
    newFood.f += foods[depth].f;
    newFood.p += foods[depth].p;
    newFood.s += foods[depth].s;
    newFood.v += foods[depth].v;
    newFood.price += foods[depth].price;

    if (newFood.f >= 0 && newFood.p >= 0 && newFood.s >= 0 && newFood.v >= 0)
    {
        recipe[recipeLength++] = foods[depth].index + 1;

        const int newBound = newFood.price;
        const int newNutrientSum = newFood.p + newFood.f + newFood.s + newFood.v;

        if (lowerBound > newBound || (lowerBound == newBound && ((newNutrientSum > nutrientSum) ||
            (newNutrientSum == nutrientSum && recipeCmp(answer, answerLength, recipe, recipeLength)))))
        {
            memcpy(answer, recipe, sizeof(int) * recipeLength);
            answerLength = recipeLength;
            lowerBound = newBound;
            nutrientSum = newNutrientSum;
        }

        --recipeLength;
    }

    if (depth == numInput - 1)
        return;

    if (newFood.price <= lowerBound)
    {
        recipe[recipeLength++] = foods[depth].index + 1;
        branchBound(depth + 1, newFood);
        --recipeLength;
    }

    branchBound(depth + 1, food);
}

int initialCmp(const void* pfood1, const void* pfood2)
{
    struct Food food1 = *(struct Food*)pfood1;
    struct Food food2 = *(struct Food*)pfood2;

    double ratio1 = (food1.p * 1000000000LL + food1.f * 1000000LL + food1.s * 1000LL + food1.v) / (double)(food1.price + 1);
    double ratio2 = (food2.p * 1000000000LL + food2.f * 1000000LL + food2.s * 1000LL + food2.v) / (double)(food2.price + 1);

    if (ratio1 < ratio2)
        return 1;

    if (ratio1 > ratio2)
        return -1;

    return 0;
}

int answerCmp(const void* p1, const void* p2)
{
    int n1 = *(int*)p1;
    int n2 = *(int*)p2;

    if (n1 < n2)
        return -1;

    if (n1 > n2)
        return 1;

    return 0;
}

int recipeCmp(const int* recipe1, int recipe1Length, const int* recipe2, int recipe2Length)
{
    const int minLength = MIN(recipe1Length, recipe2Length);

    for (int i = 0; i < minLength; ++i)
    {
        if (recipe1[i] < recipe2[i])
            return 1;
        if (recipe1[i] > recipe2[i])
            return -1;
    }

    if (recipe1Length < recipe2Length)
        return 1;
    if (recipe1Length > recipe2Length)
        return -1;
    return 0;
}