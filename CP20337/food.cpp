#include <algorithm>
#include <vector>
#include <numeric>
#include <queue>
#include <iostream>
#include <tuple>

using namespace std;

template <typename Type>
struct Nutrient
{
    Type p      { 0 };
    Type f      { 0 };
    Type s      { 0 };
    Type v      { 0 };
    Type price  { 0 };
    int  index  { 0 };
};

template <typename Type>
struct Node
{
    Nutrient<Type> nutrient;
    vector<int>     recipe;
    int     depth   {  0  };
    double  bound   { 0.0 };
};

using nutrient_t        = Nutrient<int>;
using nutrient_ratio_t  = Nutrient<float>;
using food_t            = pair<nutrient_t, nutrient_ratio_t>;
using recipe_t          = vector<int>;

int getInput(nutrient_t* minNutrient, vector<food_t>* foods, recipe_t* resultRecipe);
void branchBound(const nutrient_t& minNutrient, const vector<food_t>& foods, recipe_t* resultRecipe);
double bound(nutrient_t nutrient, const vector<food_t>& foods, int depth, int N);
void printOutput(recipe_t resultRecipe);

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("food.inp", "r", stdin);
    freopen("food.out", "w", stdout);

    nutrient_t minNutrient;
    vector<food_t> foods;
    recipe_t resultRecipe;
    
    getInput(&minNutrient, &foods, &resultRecipe);

    branchBound(minNutrient, foods, &resultRecipe);

    printOutput(resultRecipe);

    return 0;
}

int  getInput(nutrient_t* minNutrient, vector<food_t>* foods, recipe_t* resultRecipe)
{
    int numInput;
    cin >> numInput;
    cin >> minNutrient->p >> minNutrient->f >> minNutrient->s >> minNutrient->v;
    minNutrient->p = -minNutrient->p;
    minNutrient->f = -minNutrient->f;
    minNutrient->s = -minNutrient->s;
    minNutrient->v = -minNutrient->v;

    foods->reserve(numInput);

    for (int i = 0; i < numInput; ++i)
    {
        pair<Nutrient<int>, Nutrient<float>> food;

        food.first.index = food.second.index = i + 1;
        cin >> food.first.p >> food.first.f >> food.first.s >> food.first.v >> food.first.price;

        if (food.first.price == 0)
        {
            minNutrient->p += food.first.p;
            minNutrient->f += food.first.f;
            minNutrient->s += food.first.s;
            minNutrient->v += food.first.v;
            resultRecipe->push_back(i + 1);
        }
        else
        {
            food.second.p = food.first.p / static_cast<float>(food.first.price);
            food.second.f = food.first.f / static_cast<float>(food.first.price);
            food.second.s = food.first.s / static_cast<float>(food.first.price);
            food.second.v = food.first.v / static_cast<float>(food.first.price);
            foods->emplace_back(std::move(food));
        }
    }

    auto tuplize = [](const Nutrient<float>& nutrient) {
        return std::tie(nutrient.p, nutrient.f, nutrient.s, nutrient.v);
    };
    sort(foods->begin(), foods->end(), [tuplize](const food_t& food1, const food_t& food2) {
        return tuplize(food1.second) > tuplize(food2.second);
    });

    return numInput;
}

void branchBound(const nutrient_t& minNutrient, const vector<food_t>& foods, recipe_t* resultRecipe)
{
    const int N = static_cast<int>(foods.size());
    double lowerBound = numeric_limits<double>::max();
    int nutrientSum = minNutrient.f + minNutrient.p + minNutrient.s + minNutrient.v;
    auto cmp = [](const Node<int>& node1, const Node<int>& node2) {
        return node1.nutrient.price > node2.nutrient.price;
    };

    priority_queue<Node<int>, vector<Node<int>>, decltype(cmp)> pq(cmp);
    
    Node<int> firstNode;
    firstNode.nutrient = minNutrient;
    firstNode.depth = 0;
    firstNode.bound = bound(firstNode.nutrient, foods, firstNode.depth, N);
    firstNode.recipe = *resultRecipe;
    pq.emplace(move(firstNode));
    
    while (!pq.empty())
    {
        auto node = pq.top();
        pq.pop();

        if (node.depth == N - 1)
            continue;

        auto node0 = node, node1 = node; 
        node0.depth = node1.depth = node.depth + 1;

        node0.bound = node0.nutrient.price + bound(node0.nutrient, foods, node0.depth, N);

        if (node0.bound <= lowerBound)
            pq.push(node0);

        node1.nutrient.p     += foods[node.depth].first.p;
        node1.nutrient.f     += foods[node.depth].first.f;
        node1.nutrient.s     += foods[node.depth].first.s;
        node1.nutrient.v     += foods[node.depth].first.v;
        node1.nutrient.price += foods[node.depth].first.price;
        node1.recipe.push_back(foods[node.depth].first.index);

        if (node1.nutrient.f >= 0 && node1.nutrient.p >= 0 && node1.nutrient.s >= 0 && node1.nutrient.v >= 0)
        {
            const int newNutrientSum = node1.nutrient.f + node1.nutrient.p + node1.nutrient.s + node1.nutrient.v;

            if (lowerBound > node1.nutrient.price ||
                (lowerBound == node1.nutrient.price && ((newNutrientSum > nutrientSum) ||
                    (newNutrientSum == nutrientSum && node1.recipe < *resultRecipe))))
            {
                lowerBound = node1.nutrient.price;
                nutrientSum = newNutrientSum;
                resultRecipe->swap(node1.recipe);
            }
        }
        else
        {
            node1.bound = node1.nutrient.price + bound(node1.nutrient, foods, node1.depth, N);
            if (node1.bound <= lowerBound)
                pq.push(node1);
        }
    }
}

double bound(nutrient_t nutrient, const vector<food_t>& foods, int depth, int N)
{
    for (int i = depth; i < N; ++i)
    {
        const auto& food = foods[i].first;
        auto temp = nutrient;
        nutrient.p     += food.p;
        nutrient.f     += food.f;
        nutrient.s     += food.s;
        nutrient.v     += food.v;
        nutrient.price += food.price;

        if (nutrient.f >= 0 && nutrient.p >= 0 && nutrient.s >= 0 && nutrient.v >= 0)
        {
            double minRatio = 1.0f;
            if (temp.f < 0) minRatio = min(minRatio, (-temp.f) / static_cast<double>(food.f));
            if (temp.p < 0) minRatio = min(minRatio, (-temp.p) / static_cast<double>(food.p));
            if (temp.s < 0) minRatio = min(minRatio, (-temp.s) / static_cast<double>(food.s));
            if (temp.v < 0) minRatio = min(minRatio, (-temp.v) / static_cast<double>(food.v));
            return temp.price + minRatio * food.price;
        }
    }

    return 1e6;
}

void printOutput(recipe_t resultRecipe)
{
    if (resultRecipe.empty())
    {
        cout << '0';
        return;
    }

    sort(resultRecipe.begin(), resultRecipe.end());

    for (int foodIdx : resultRecipe)
    {
        cout << foodIdx << ' ';
    }
}