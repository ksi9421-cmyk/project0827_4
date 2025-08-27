#include <iostream>
#include <vector>
#include <string>
using namespace std;

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    string potionName;
    vector<string> ingredients; // 단일 재료에서 재료 '목록'으로 변경
    int stock;

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const string& name, const vector<string>& ingredients)
        : potionName(name), ingredients(ingredients), stock(3) {}
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop 
{
private:
    vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const string& name, const vector<string>& ingredients) 
    {
        recipes.push_back(PotionRecipe(name, ingredients));
        cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다. (재고 3개)" << endl;
    }

    int getStock(const string& potionName)
    {
        for (auto& r : recipes)
        {
            if (r.potionName == potionName)
            {
                return r.stock;
            }
        }
        return -1;
    }

  
    // 모든 레시피 출력 메서드
    void displayAllRecipes() const 
    {
        if (recipes.empty()) 
        {
            cout << "아직 등록된 레시피가 없습니다." << endl;
            return;
        }

        cout << "\n--- [ 전체 레시피 목록 ] ---" << endl;
        for (size_t i = 0; i < recipes.size(); ++i) 
        {
            cout << "- 물약 이름: " << recipes[i].potionName << " (재고: " << recipes[i].stock << ")" << endl;           
            cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) 
            {
                cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) 
                {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "---------------------------\n";
    }

    // 이름으로 검색
    PotionRecipe* searchRecipeByName(const string& name)
    {
        for (size_t i = 0; i < recipes.size(); ++i)
        {
            if (recipes[i].potionName == name)
            {
                return &recipes[i];
            }
        }
        return nullptr;
    }

    // 재료 포함 검색
    vector<PotionRecipe*> searchRecipesByIngredient(const string& ingredient)
    {
        vector<PotionRecipe*> result;
        for (size_t i = 0; i < recipes.size(); ++i) 
        {
            for (const auto& ing : recipes[i].ingredients) 
            {
                if (ing.find(ingredient) != string::npos)
                {
                    result.push_back(&recipes[i]);
                    break;
                }
            }
        }
        return result;
    }
        
};

int main() 
{
    AlchemyWorkshop myWorkshop;

    while (true) 
    {
        cout << "연금술 공방 관리 시스템" << endl;
        cout << "1. 레시피 추가" << endl;
        cout << "2. 모든 레시피 출력" << endl;
        cout << "3. 이름 검색" << endl;
        cout << "4. 재료 검색" << endl;
        cout << "5. 종료" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;

        if (cin.fail()) 
        {
            cout << "잘못된 입력입니다. 숫자를 입력해주세요." <<endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            string name;
            cout << "물약 이름: ";
            cin.ignore(10000, '\n');
            getline(cin, name);

            // 여러 재료를 입력받기 위한 로직
            vector<string> ingredients_input;
            string ingredient;
            cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << endl;

            while (true)
            {
                cout << "재료 입력: ";
                getline(cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝")
                {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty())
            {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else
            {
                cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << endl;
            }

        }
        else if (choice == 2)
        {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3)
        {
            string searchName;
            cin.ignore(10000, '\n');
            cout << "검색할 물약 이름: ";
            getline(cin, searchName);

            PotionRecipe* recipe = myWorkshop.searchRecipeByName(searchName);
            if (recipe)
            {
                cout << "찾은 레시피: " << recipe->potionName << "\n재료: ";
                for (auto& ing : recipe->ingredients)
                    cout << ing << " ";
                cout << endl;
            }
            else
            {
                cout << "해당 이름의 레시피가 없습니다.\n";
            }
        }
        else if (choice == 4)
        {
            string searchIngredient;
            cin.ignore(10000, '\n');
            cout << "검색할 재료: ";
            getline(cin, searchIngredient);

            auto recipes = myWorkshop.searchRecipesByIngredient(searchIngredient);
            if (recipes.empty())
            {
                cout << "해당 재료가 포함된 레시피가 없습니다.\n";
            }
            else
            {
                cout << "검색 결과:\n";
                for (auto r : recipes)
                {
                    cout << "- " << r->potionName << " (";
                    for (auto& ing : r->ingredients)
                        cout << ing << " ";
                    cout << ")\n";
                }
            }
        }

        else if (choice == 5) 
        {
            cout << "공방 문을 닫습니다..." << endl;
            break;

        }
        else 
        {
            cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}