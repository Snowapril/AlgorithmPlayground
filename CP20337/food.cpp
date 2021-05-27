#include <fstream>
#include <array>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>

using namespace std;
#include <iostream>

template <typename Type>
struct Nutrient
{
    Type p{ 0 };
    Type f{ 0 };
    Type s{ 0 };
    Type v{ 0 };
    Type price{ 0 };
    int index{ 0 };
};

template <typename Type>
struct Node
{
    Nutrient<Type> nutrient;
    int depth, bound;
};

int  getInput   (Nutrient<int>* minNutrient, 
                 vector<pair<Nutrient<int>, Nutrient<float>>>* foods, 
                 vector<int>* resultRecipe);
void branchBound(const Nutrient<int>& minNutrient, 
                 const vector<pair<Nutrient<int>, Nutrient<float>>>& foods, 
                 vector<int>* resultRecipe);
void bound      ();
void printOutput(const vector<int>& resultRecipe);

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("food.inp", "r", stdin);
    freopen("food.out", "w", stdout);

    Nutrient<int> minNutrient;
    vector<pair<Nutrient<int>, Nutrient<float>>> foods;
    vector<int> resultRecipe;
    
    getInput(&minNutrient, &foods, &resultRecipe);

    //! Sort foods with nutrient ratio
    auto tuplize = [](const Nutrient<float>& nutrient) {
        return std::tie(nutrient.p, nutrient.f, nutrient.s, nutrient.v);
    };
    sort(foods.begin(), foods.end(), [tuplize](const auto& food1, const auto& food2) {
        return tuplize(food1.second) > tuplize(food2.second);
    });

    for (auto& food : foods)    
    {
        cout << food.first.index << ' ' << food.first.p << ' ' << food.first.f << ' ' << food.first.s << ' ' << food.first.v << ' ' << food.first.price << '\n';
        cout << food.second.p << ' ' << food.second.f << ' ' << food.second.s << ' ' << food.second.v << ' ' << "\n\n";
    }

    branchBound(minNutrient, foods, &resultRecipe);

    return 0;
}

int getInput(Nutrient<int>* minNutrient, vector<pair<Nutrient<int>, Nutrient<float>>>* foods, vector<int>* resultRecipe)
{
    int numInput;
    cin >> numInput;
    cin >> minNutrient->p >> minNutrient->f >> minNutrient->s >> minNutrient->v;
    //! Negates the minimum nutrient
    minNutrient->p = -minNutrient->p;
    minNutrient->f = -minNutrient->f;
    minNutrient->s = -minNutrient->s;
    minNutrient->v = -minNutrient->v;

    foods->reserve(numInput);

    for (int i = 0; i < numInput; ++i)
    {
        pair<Nutrient<int>, Nutrient<float>> food;

        food.first.index = food.second.index = i;
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

    return numInput;
}

void branchBound(const Nutrient<int>& minNutrient, const vector<pair<Nutrient<int>, Nutrient<float>>>& foods, vector<int>* resultRecipe)
{

    int localOptima = -1;

    auto cmp = [](const Node<int>& node1, const Node<int>& node2) {
        return node1.nutrient.price > node2.nutrient.price;
    };

    priority_queue<Node<int>, vector<Node<int>>, decltype(cmp)> pq(cmp);

    while (!pq.empty())
    {

    }
}

void bound()
{

}

void printOutput(const vector<int>& resultRecipe)
{
    for (int foodIdx : resultRecipe)
    {
        cout << foodIdx << ' ';
    }
}