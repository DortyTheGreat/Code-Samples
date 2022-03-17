#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ///setlocale (LC_ALL, "russian");
    string name;
    cout <<"Как вас зовут? " <<endl;
    getline(cin,name);
    string age;
    cout <<"Сколько вам лет? " <<endl;
    getline(cin,age);
    string attitude;
    cout <<"Какое ваше отношение у нашему ВУЗу? " <<endl;
    getline(cin,attitude);
    string exam;
    cout <<"Какие экзамены вы сдавали на этой сессии? " <<endl;
    getline(cin,exam);
    string complexity;
    cout <<"Вам было сложно сдавать экзамены? " <<endl;
    getline(cin,complexity);
    string grade;
    cout <<"Какие оценки вы получили? " <<endl;
    getline(cin,grade);
    string satis;
    cout <<"Довольны ли вы своими оценками? " <<endl;
    getline(cin,satis);
    cout <<" Чтобы лучше сдать сессию, я предоставлю вам несколько советов:"<<endl;

    ofstream s( (name) );

    s <<"1. Расписывать план занятий на каждый день" << endl;
    s <<"2. Нарушаем золотое правило откладывать все на потом " << endl;
    s <<"3. Возьмите у преподавателя список вопросов и тем к экзамену заранее" << endl;
    s <<"4. Учи конспекты заранее, а не в последнюю ночь" << endl;
    s <<"5. Доказано, что интересную для вас информацию мозг усваивает намного быстрее" << endl;
    s <<"6. Для самоподдержки делайте себе приятности" << endl;
    s <<"7. Слушайте классическую музыку" << endl;
    s <<"8. Ешьте больше белков (мясо, рыба) и углеводов (фрукты, овощи и крупы)" << endl;
    s <<"9. Делайте перерывы между заучиванием больших объемов информации" << endl;
    s <<"10. Заучивайте определения" << endl;
    return 0;
}
