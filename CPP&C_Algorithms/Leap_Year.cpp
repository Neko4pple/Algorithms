#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int year;
    int div4;
    int div100;
    int div400;
    
    cout << "년도를 입력하시오 : ";
    cin >> year;
    
    div4 = year % 4;
    div100 = year % 100;
    div400 = year % 400;
    
    if (div4 == 0 && div100 != 0){
        cout << year << "년은 윤년입니다." << endl;
    }
    else if (div400 == 0){
        cout << year << "년은 윤년입니다." << endl;
    }
    else{
        cout << year << "년은 윤년이 아닙니다." << endl;
    }
    
    return 0;
}
