// FSM 패턴 예제.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 20193496 나용성 ( 요리 생성 및 식사 과정 예제를 만들어봄)

#include <iostream>

using namespace std;

enum
{
    Idle = 1,
    ReadRecipe,
    COOK,
    CookIdle,
    Eat,
    Exit
};

class Recipe 
{
    int count;
    int CodeOfRecipe;
    char* NameOfRecipe;
public:
    Recipe(int &Num, char* FoodName) : CodeOfRecipe(Num)
    {
        NameOfRecipe = new char[strlen(FoodName) + 1];
        strcpy_s(NameOfRecipe, (strlen(FoodName) + 1), FoodName);
    }

    Recipe(const Recipe& newRecipe) : CodeOfRecipe(newRecipe.CodeOfRecipe)
    {
        NameOfRecipe = new char[strlen(newRecipe.NameOfRecipe) + 1];
        strcpy_s(NameOfRecipe, (strlen(newRecipe.NameOfRecipe) + 1), NameOfRecipe);
    }

    ~Recipe()
    {
        delete[] NameOfRecipe;
    }

    void showRecipe() const
    {
        cout << "<< 현재 만들 수 있는 음식 >>" << endl;
        cout << "요리 코드 = " << CodeOfRecipe << endl;
        cout << "요리 이름 = " << NameOfRecipe << endl;
    }

    int getRecipeCode() const
    {
        return CodeOfRecipe;
    }

    void AddFood(int number)
    {
        count += number;
    }

    void MinusFood(int number)
    {
        if (count < number)
            count = 0;
        else
        {
            count -= number;
        }
    }

    void showFood() const
    {
        cout << "<< 현재 만들어진 음식 >>" << endl;
        cout << "요리 코드 = " << CodeOfRecipe << endl;
        cout << "개수 =" << count << endl;
    }
};


class Cooking {
    Recipe* newrecipe[100];
    int NumOfRecipe;
public:
    Cooking() : NumOfRecipe(0) {}

    ~Cooking()
    {
        for (int w = 0; w < NumOfRecipe; w++)
        {
            delete newrecipe[w];
        }
    }

    void show() const
    {
        cout << "<< 실행할 동작 선택 >>" << endl;
        cout << "1 = 현재 요리법 상태" << endl;
        cout << "2 = 새로운 요리법 배우기" << endl;
        cout << "3 = 요리 시작" << endl;
        cout << "4 = 만들어진 요리 상태" << endl;
        cout << "5 = 식사" << endl;
        cout << "6 = 종료" << endl;
    }

    void idleSituation() const
    {
        for (int i = 0; i < NumOfRecipe; i++)
        {
            newrecipe[i]->showRecipe();
            cout << endl;
        }
    }

    void  readSituation()
    {
        int CodeOfRecipe;
        char NameOfRecipe[20];

        cout << " << 새로운 요리법 추가 >>" << endl;
        cout << "요리 코드 = "; cin >> CodeOfRecipe;
        cout << "요리 이름 = "; cin >> NameOfRecipe;
        cout << endl;

        newrecipe[NumOfRecipe++] = new Recipe(CodeOfRecipe, NameOfRecipe);
    }

    void cookSituation()
    {
        int num;
        int CodeOfRecipe;

        cout << " << 어느 요리를 몇 개 만드시겠습니까?>> " << endl;
        cout << "요리 코드 = "; cin >> CodeOfRecipe;
        cout << "요리 개수 = "; cin >> num;
        cout << endl;

        for (int i = 0; i < NumOfRecipe; i++)
        {
            if (newrecipe[i]->getRecipeCode() == CodeOfRecipe)
            {
                newrecipe[i]->AddFood(num);
                cout << "요리가 생성되었습니다" << endl;
                return;
            }
        }
        cout << "레시피가 없는  요리 입니다." << endl << endl;
    }

    void cookIdleSituation() const
    {
        for (int q = 0; q < NumOfRecipe; q++)
        {
            newrecipe[q]->showFood();
            cout << endl;
        }
    }

    void  eatSituation()
    {
        int num;
        int CodeOfRecipe;

        cout << " <<만들어진 요리 중 어느 요리를 몇 개 드시겠습니까?>> " << endl;
        cout << "요리 코드 = "; cin >> CodeOfRecipe;
        cout << "개수 ="; cin >> num;
        cout << endl;

        for (int i = 0; i < NumOfRecipe; i++)
        {
            if (newrecipe[i]->getRecipeCode() == CodeOfRecipe)
            {
                newrecipe[i]->MinusFood(num);
                cout << "요리가 소모되었습니다" << endl;
                cout << "냠냠" << endl;
                return;
            }
        }
        cout << "만들어지지 않은  요리 입니다." << endl << endl;
    }
};

int main()
{
    Cooking cooking;
    int situ;

    while (1)
    {
        cooking.show();
        cout << "무엇을 하시겠습니까?";
        cin >> situ;
        cout << endl;

        switch (situ)
        {
        case Idle:
            cooking.idleSituation();
            break;
        case ReadRecipe:
            cooking.readSituation();
            break;
        case COOK:
            cooking.cookSituation();
            break;
        case CookIdle:
            cooking.cookIdleSituation();
            break;
        case Eat:
            cooking.eatSituation();
            break;
        case Exit:
            return 0;
        default:
            cout << "잘못된 명령입니다." << endl;
        }
    }
    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
