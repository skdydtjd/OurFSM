// 작성자 : chocokart2
#include <iostream>
#include <random>
using namespace std;

#define KART_STATE_IDLE 10
#define KART_STATE_FIGHT 20
#define KART_STATE_HURT 30
#define KART_STATE_DEAD 40

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 1);
#define RAND_NUM dis(gen)

class Kart {
    int state = KART_STATE_IDLE;
public:
    Kart(int stat) : state{ stat } {}

    void SetStat(int stat) { state = stat; }
    int GetStat(void) { return state; }

    void Action();
    void CallFriend(); // 잡담 혹은
};

void Kart::Action() {
    switch (state)
    {
    case KART_STATE_IDLE:
        cout << "kart 객체 어슬렁거림." << endl;
        if (RAND_NUM == 0) return;
        else {
            state = KART_STATE_FIGHT;
            cout << "kart 객체 괴물을 만남." << endl;
        }
        break;
    case KART_STATE_FIGHT:
        cout << "kart 객체 전투 중!" << endl;
        if (RAND_NUM == 0) {
            state = KART_STATE_IDLE;
            cout << "kart 객체 전투에서 승리." << endl;
        }
        else {
            state = KART_STATE_HURT;
            cout << "kart 객체 싸우다 부상을 입음." << endl;
        }
        break;
    case KART_STATE_HURT:
        cout << "kart 객체가 치명상을 입었습니다" << endl;
        if (RAND_NUM == 0) {
            state = KART_STATE_IDLE;
            cout << "kart 객체 전투에서 승리." << endl;
        }
        else {
            state = KART_STATE_DEAD;
            cout << "kart 객체 사망함." << endl;
        }
        break;
    case KART_STATE_DEAD:
        cout << "kart 객체가 사망했습니다. 움직이지 않습니다." << endl;
        break;
    default:
        cout << "정의되지 않은 상태 : " << state << endl;
        break;
    }
}
void Kart::CallFriend() {
    switch (state)
    {
    case KART_STATE_IDLE:
        cout << "kart 객체 친구를 불러 잡담 중." << endl;
        break;
    case KART_STATE_FIGHT:
        cout << "kart 객체 친구를 불러 전투 지원 요청." << endl;
        if (RAND_NUM == 0) {
            state = KART_STATE_IDLE;
            cout << "kart 객체 전투에서 승리." << endl;
        }
        else {
            state = KART_STATE_HURT;
            cout << "kart 객체 싸우다 부상을 입음." << endl;
        }
        break;
    case KART_STATE_HURT:
        cout << "kart 객체가 치명상을 입어 구조를 요청합니다." << endl;
        if (RAND_NUM == 0) {
            state = KART_STATE_IDLE;
            cout << "kart 객체 전투에서 승리." << endl;
        }
        else {
            state = KART_STATE_DEAD;
            cout << "kart 객체 사망함." << endl;
        }
        break;
    case KART_STATE_DEAD:
        cout << "kart 객체가 사망했습니다. 움직이지 않습니다." << endl;
        break;
    default:
        cout << "정의되지 않은 상태 : " << state << endl;
        break;
    }
}

int main()
{
    Kart kart(10);
    for (int i = 0; i < 20; i++) {
        if (RAND_NUM == 0) kart.Action();
        else kart.CallFriend();
    }
    return 0;
}