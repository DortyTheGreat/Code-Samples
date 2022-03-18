#include <iostream>
#include <istream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <cwchar>
#include <conio.h>

using namespace std;
/*
Оригинальный MvW -
Mage Vs Warriors
Финальная Стадия проекта для 2018-2020 гг.
Оригинальный сурс был найден на старой флешке
Дата Оригинального Кода - 22.12.2018
*/
    string PPP;
    string Name, OpName;
     int a=9, Charra, Shoppe, ItemBuy=1, ShopBuy, ItemID[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
     int MItemBuy=1, MItemID[] = {0,0,0,0,0,0,0,0,0,0,0,0,0}, MShopAccept, MShoppe, MBonusShopAccept, MTotalShopAccept, MShopBuy;
     int Class, ClassChoose, Classo, SettingsChose, Diff, Cheat;
     float DiffM=1;
     int Boots=0, Sword=0, ManaO=0, HPO=0, Shield=0, BuyItems=0, TotalShopAccept=0;
     int ArenaChoose, Gold=0, GoldDropped, Counter, ArenaMM;
     int HodSdelan = 0, CheatChose;
     float OpDamageCoef, DamageCoef;
     int Winne, RandomTurn;
     int DP=10, TP=10, OpTP, OpDP, BDP, BTP, BOpDP, BOpTP, BaseTP=10, PlusTP=0, BaseDP=10, PlusDP=0, CoefTP=1, CoefDP=1, BPlusDP, BPlusTP, BCoefTP, BCoefDP,BOpPlusDP, BOpPlusTP, BOpCoefTP, BOpCoefDP;
     float AP=100, ManaP=200, ManaReg=10, HP=1000, OpAP, OpHP, BAP, BManaP, BManaReg, BHP, BOpAP, BOpManaP, BOpManaReg, BOpHP;
     float BaseAP=100, BaseManaP=200, BaseManaReg=10, BaseHP=1000, PlusAP=0, PlusManaP=0, PlusHP=0, CoefAP=1, PlusManaReg=0, CoefManaP=1, CoefManaReg=1, CoefHP=1, BPlusAP=0, BPlusManaP, BPlusManaReg, BPlusHP;
     float BCoefAP, BCoefManaP, BCoefManaReg, BCoefHP, BOpCoefAP, BOpCoefManaP, BOpCoefManaReg, BOpCoefHP;
     int OpCounter = 1;
     int ShopAccept, BonusShopAccept=0;
     int ClassCD[] = {0,0,0,0,0,0,0,0};





    void cls()
    {



     system("cls");
    }
    void PDMG() //ФИЗ УРОН ЕСЛИ ЧТО НУЖНО СДЕЛАТЬ HodSdelan = 1;
    {
         OpDamageCoef = pow(0.95, OpDP);

     BOpHP =  BOpHP -(BAP * OpDamageCoef);
     cls();
     cout << "Ваш Ход:" << endl;
         cout << "Ваше Здоровье: " << BHP << endl;
    cout << "Ваша Мана: " << BManaP << endl;
    cout << "Здоровье Оппонента: " << BOpHP << endl;
    cout << "_______________________" << endl;
    }
    void StKo() {
    HP = (BaseHP + PlusHP ) * CoefHP ;
    AP = (BaseAP + PlusAP ) * CoefAP ;
    DP = (BaseDP + PlusDP ) * CoefDP ;
    TP = (BaseTP + PlusTP ) * CoefTP ;
    ManaP =(BaseManaP + PlusManaP ) * CoefManaP ;
    ManaReg = (BaseManaReg + PlusManaReg ) * CoefManaReg ;
    }
int main()
{
    setlocale(0, "");

    setlocale(0, "");
    cout << "### - Наше Будущее сокращение слов: Введите любой символ, чтобы продолжить ### " << endl;
    getch();
    cls();
    cout << "Введите Ваше имя" << endl;
    cout << "P.S. БЕЗ ПРОБЕЛОВ! И Желательно на Латинице или с Помощью Цифр " <<endl;
    cin >> Name;
    Class = 0;
    cls();
    do {
    cout << "Выберите Ваш Класс" << endl;
    cout << "1 - Всратый Чиллиакс" << endl;
    cout << "2 - Папа Григорий" << endl;
    cout << "3 - Петя" << endl;
    cout << "4 - Близнец" << endl;
    cout << "5 - Травояднвый" << endl;
    cout << "6 - Еврей Эльяу" << endl;
    cout << "7 - Грустный Лёха" << endl;
    Classo = getch();
    cls();
    switch(Classo - 48){
    case 1 :
        cout << "Герой: Всратый Чиллиакс" << endl;
      cout << "Заклинание: Чилл" << endl;
    cout << "Тип Заклинания: Активная" << endl;
    cout << "_______________________" << endl;
    cout << "Лечение: 150% от Урона" <<endl;
    cout << "Защита+5(1 Раз На Всю Битву) " <<endl;
    cout << "Оглушение: 1 Атака" << endl;
    cout << "Затраты Маны: 100" <<endl;
    cout << "Перезарядка: 10" <<endl;
    cout << "НЕ Тратит Ход" << endl;
    cout << "Введите 1 Для Выбора Данного героя" << endl;
    ClassChoose = getch();
    cls();
    if (ClassChoose == 49){
        Class = 1;
    }
    break;
    case 2 :
        cout << "Герой: Папа Гриша" << endl;
      cout << "Заклинание: Найти Баг" << endl;
    cout << "Тип Заклинания: Активная" << endl;
    cout << "_______________________" << endl;
    cout << "Враг Получает 1000% Физ. Урона" <<endl;
    cout << "Защита Врага-5(1 Раз На Всю Битву) " <<endl;
    cout << "Затраты Маны: 100" <<endl;
    cout << "Перезарядка: 10" <<endl;
    cout << "Тратит Ход" << endl;
    cout << "Введите 1 Для Выбора Данного героя" << endl;
    ClassChoose = getch();
    cls();
    if (ClassChoose == 49){
        Class = 2;
    }
    break;
    case 3 :
            cout << "Герой: Петя" << endl;
      cout << "Заклинание: Ой!" << endl;
    cout << "Тип Заклинания: Активная" << endl;
    cout << "_______________________" << endl;
    cout << "Лечение: 20% от Урона" <<endl;
    cout << "Враг Получает 200% Физ. Урона" <<endl;

    cout << "Затраты Маны: 30" <<endl;
    cout << "Перезарядка: 1" <<endl;
    cout << "Тратит Ход" << endl;
    cout << "Введите 1 Для Выбора Данного героя" << endl;
    ClassChoose = getch();
    cls();
    if (ClassChoose == 49){
        Class = 3;
    }
    break;


    }
    }while (Class == 0);
    do {
    cls();
    cout << "Главное Меню"<<endl;
    cout << "1 - Начать Игру"<<endl;
    cout << "2 - Информация"<<endl;
    cout << "3 - Настройки" << endl;
    int MainMenuChoose;
    MainMenuChoose = getch() - 48;
    cls();
    switch (MainMenuChoose) {
case 1:
    int GameMapChoose;                  // CКРИПТ игры
do{
    cls();
    cout << "1 - Арена"<< endl;
cout << "2 - Работа"<< endl;
cout << "3 - Башня Магии"<< endl ;
cout << "4 - Мой Персонаж"<< endl ;
cout << "5 - Магазин"<< endl ;
cout << "6 - В Главное Меню"<< endl ;
GameMapChoose = getch() - 48;

cls();
switch (GameMapChoose) {
case 1 : //Арена
       /*
          case 1 :
        OpHP=  ;
        OpAP=  ;
        OpDP=  ;
        OpTP=  ;
        GoldDropped=  ;
        OpName="";
        break;
        */
    switch (OpCounter) {
    case 1 :
        OpHP=1000  ;
        OpAP=50  ;
        OpDP=3  ;
        OpTP=5  ;
        GoldDropped= 100;
        OpName="Моргл";
        break;
        case 2 :
        OpHP=400  ;
        OpAP=70  ;
        OpDP=2  ;
        OpTP=4  ;
        GoldDropped= 500;
        OpName="Рыба";
        break;
        case 3 :
        OpHP=500  ;
        OpAP=90 ;
        OpDP=4  ;
        OpTP=6  ;
        GoldDropped= 1000;
        OpName="Повидло";
        break;
        case 4 :
        OpHP=10000  ;
        OpAP=0  ;
        OpDP=0  ;
        OpTP=5  ;
        GoldDropped= 10000;
        OpName="СуНДУК";
        break;
           case 5 :
        OpHP=1000  ;
        OpAP=150  ;
        OpDP=0  ;
        OpTP=5  ;
        GoldDropped= 1000;
        OpName="Жадный Вор";
        break;

   case 6 :
        OpHP=10000  ;
        OpAP=300  ;
        OpDP=0  ;
        OpTP=5  ;
        GoldDropped= 12000;
        OpName="Мимик";
        break;
  case 7 :
        OpHP=1200  ;
        OpAP=150  ;
        OpDP=0  ;
        OpTP=5  ;
        GoldDropped= 2000;
        OpName="Еврей";
        break;
  case 8 :
        OpHP=3000  ;
        OpAP=70  ;
        OpDP=0  ;
        OpTP=5  ;
        GoldDropped= 1500;
        OpName="ПуДж";
        break;
  case 9 :
        OpHP=1000  ;
        OpAP=200  ;
        OpDP=0  ;
        OpTP=5  ;
        GoldDropped= 1500;
        OpName="Жиравчик";
        break;
case 10 :
        OpHP=500  ;
        OpAP=300  ;
        OpDP=0  ;
        OpTP=5  ;
        GoldDropped= 1000;
        OpName="Павук";
        break;





    break;
    }
OpHP *= DiffM;
 OpAP *= DiffM;
 OpDP *= DiffM;
 OpTP *= DiffM;

    cout << "Ваши Характеристики: " <<endl;
    cout << "Имя: " <<Name <<endl;
    cout << "Здоровье: " <<HP <<endl;
    cout << "Атака: " <<AP <<endl;
    cout << "Защита: " <<DP <<endl;
    cout << "ШансХода: " <<TP <<endl;
    cout << "Мана: " <<ManaP <<endl;
    cout << "Регенерация Маны: " <<ManaReg <<endl;
    cout << "________" <<endl;
     cout << "Характеристики Оппонента: " <<endl;
     cout << "Имя: " <<OpName <<endl;
    cout << "Здоровье: " <<OpHP <<endl;
    cout << "Атака: " <<OpAP <<endl;
    cout << "Защита: " <<OpDP <<endl;
    cout << "ШансХода: " <<OpTP <<endl;
    cout << "Порядок врага: " <<OpCounter <<endl;
    cout << "###" <<endl;

    getch();
    cls();
    BAP= AP;
    BHP=HP;
    BDP=DP;
    BTP=TP;
    BManaP=ManaP;
    BManaReg=ManaReg;

      BOpAP= OpAP;
    BOpHP= OpHP;
    BOpDP= OpDP;
    BOpTP= OpTP;
    Winne = 0;
    HodSdelan = 0;
    do{
            cls();
    RandomTurn= (1 + (rand() % (BTP+BOpTP)));
    if (RandomTurn <= OpTP) {
           cls();
     cout << "Ход Оппонента:" <<endl;
     DamageCoef = pow(0.95, DP);
     BHP =  BHP -(BOpAP * DamageCoef);
      cout << "Ваше Здоровье: " << BHP <<endl;
    cout << "Ваша Мана: " << BManaP << endl;
    cout << "Здоровье Оппонента: " << BOpHP << endl;
    cout << "_______________________" << endl;
     cout << "Вы получили ранение! ###"<< endl;
    getch();
    }
     //мой ход
     if (RandomTurn > BOpTP) {
    do {
            HodSdelan = 0;
        cls();
        cout << "Ваш Ход:" << endl;
         cout << "Ваше Здоровье: " << BHP << endl;
    cout << "Ваша Мана: " << BManaP << endl;
    cout << "Здоровье Оппонента: " << BOpHP << endl;
    cout << "_______________________" << endl;
        cout << "1 - Атака" <<endl;
        cout << "2 - Заклинания" <<endl;
        cout << "3 - Предметы" <<endl;

        ArenaChoose = getch() - 48;
        cls();
        switch (ArenaChoose) {
    case 1 :
         OpDamageCoef = pow(0.95, OpDP);

     BOpHP =  BOpHP -(BAP * OpDamageCoef);
     cls();


     HodSdelan = 1;
        break;
    case 2 :
      switch(Class){

case 1:
    cout << "0 - Чилл" << endl;
    break;

case 2 :
    cout << "0 - Найти баг" << endl;
    break;
case 3 :
    cout <<  "0 - Ой!" << endl;
    break;
      }
     Counter = 0;
      if (MItemID[1] == 1){
        Counter++;
        cout << Counter << " - Всплеск Энергии" << endl;
      }
      if (MItemID[2] == 1){
        Counter++;
        cout << Counter << " - Слабая Коррозия" << endl;
      }
      if (MItemID[3] == 1){
        Counter++;
        cout << Counter << " - Всплеск Энергии" << endl;
      }
        cin >> MShoppe;
        cls();
        MShopAccept = MShoppe; //nn
MBonusShopAccept = 0;
MTotalShopAccept = 0;
cls();
for (int i = 1; i<=MShopAccept; i++) {
    if (MItemID[i] == 0) {
        MBonusShopAccept++;
        MShopAccept++;

    }

}
MTotalShopAccept = MBonusShopAccept + MShoppe;
switch(MTotalShopAccept){

case 0 :
    cout << "0";
    cin >> PPP;
    break;
    case 1 :
    cout << "1";
    cin >> PPP;
    break;
    case 2 :
    cout << "2";
    cin >> PPP;
    break;
}
        break;
        }


    }while (HodSdelan == 0);
     }
     if  (BHP <= 0) {
        Winne = 2;
     }
     if  (BOpHP <= 0) {
        Winne = 1;
     }
    }while (Winne <= 0);

    if  (Winne == 2) {
        cout << "Поражение((( ###";
         getch();
     }
     if  (Winne == 1) {
        cout << "Победа! ###" << endl;
         getch();
        OpCounter = OpCounter + 1;
        Gold= Gold + GoldDropped;
     }
    break;
case 2: //РАБОТА
    Gold = 100000;
   cout << "adas";
   break;
case 3: //МАГИЯ

 MItemBuy = 0;
cls();
cout << "Золото: " << Gold << endl;
if (MItemID[1] == 0) {  //Boots=0, Sword=0, ManaO=0, HPO=0, Shield=0;
        MItemBuy++;
cout << MItemBuy << " - Всплеск Энергии 1000" << endl;

}
if (MItemID[2] == 0) {  //Boots=0, Sword=0, ManaO=0, HPO=0, Shield=0;
    MItemBuy++;
cout << MItemBuy << " - Слабая Коррозия 2500" << endl;
}
if (MItemID[3] == 0) {  //Boots=0, Sword=0, ManaO=0, HPO=0, Shield=0;
    MItemBuy++;
cout << MItemBuy << " - Огненный Шар 3500" << endl;
}
MShopAccept = getch() - 48;
MShoppe =MShopAccept;
MBonusShopAccept = 0;
MTotalShopAccept = 0;
cls();
for (int i = 1; i<=MShopAccept; i++) {
    if (MItemID[i] != 0) {
        MBonusShopAccept++;
        MShopAccept++;

    }

}
MTotalShopAccept = MBonusShopAccept + MShoppe;
switch (MTotalShopAccept) {
case 1 :
        cls();
    cout <<"Золото: " << Gold << endl;
    cout << "Заклинание: Всплеск Энергии" << endl;
    cout << "Тип Заклинания: Бафф" << endl;
    cout << "_______________________" << endl;
    cout << "Увеличивает Атаку на 100" <<endl;
    cout << "Длительность: 3 Атаки" <<endl;
    cout << "Затраты Маны: 100" <<endl;
    cout << "Перезарядка: 6" <<endl;
    cout << "_______________________" << endl;
    cout << "Cтоимость : 1000" << endl;
    cout << "Введите 1, чтобы купить" << endl;
    MShopBuy = getch() - 48;
    cls();
    if (MShopBuy == 1) {
            if (Gold >= 200) {
              MItemID[1] = 1;


              Gold = Gold - 1000;
              cls();
              cout << "Покупка  Успешна ###" << endl;
               getch();

            }
            else {
              cout << "Недостаточно Золота ###" << endl;
               getch();


            }

    }
    break;
}




    break;
case 4: //Персонаж
    cls();
     cout << "Золото: " << Gold << endl;
     cout << "Здоровье: " << HP << endl;
     cout << "Атака: " << AP << endl;
     cout << "Защита: " << DP << endl;
     cout << "Шанс Хода: " << TP << endl;
     cout << "Мана: " << ManaP << endl;
     cout << "Регенерация Маны: " << ManaReg << endl;
     cout << "1 - Подробные Характеристики(Не входите, если не знаете :-) )" << endl;
     Charra = getch() - 48;
     switch (Charra) {
     case 1 :

         cls();
    cout << "BaseHP: " << BaseHP << endl << "PlusHP: " << PlusHP << endl << "CoefHP: " << CoefHP << endl;
    cout << "BaseAP: " << BaseAP << endl << "PlusAP: " << PlusAP << endl << "CoefAP: " << CoefAP << endl;
    cout << "BaseDP: " << BaseDP << endl << "PlusDP: " << PlusDP << endl << "CoefDP: " << CoefDP << endl;
    cout << "BaseTP: " << BaseTP << endl << "PlusTP: " << PlusTP << endl << "CoefTP: " << CoefTP << endl;
    cout << "BaseManaP: " << BaseManaP << endl << "PlusManaP: " << PlusManaP << endl << "CoefManaP: " << CoefManaP << endl;
    cout << "BaseManaReg: " << BaseManaReg << endl << "PlusManaReg: " << PlusManaReg << endl << "CoefManaReg: " << CoefManaReg << endl;
    cout << "###" << endl;
     getch();

     }

    break;
case 5: //Магазин
    ItemBuy = 0;
cls();
cout << "Золото: " << Gold << endl;
if (ItemID[1] == 0) {  //Boots=0, Sword=0, ManaO=0, HPO=0, Shield=0;
        ItemBuy++;
cout << ItemBuy << " - Топорик 200" << endl;

}
if (ItemID[2] == 0) {  //Boots=0, Sword=0, ManaO=0, HPO=0, Shield=0;
    ItemBuy++;
cout << ItemBuy << " - Щиток 250" << endl;

}
if (ItemID[3] == 0) {
    ItemBuy++;
cout << ItemBuy << " - Кольцо Защиты 600" << endl;
}
if (ItemID[4] == 0) {
    ItemBuy++;
cout << ItemBuy << " - Маска Регенерации Маны 600" << endl;
}
if (ItemID[5] == 0) {
    ItemBuy++;
cout << ItemBuy << " - Сапоги Гномов 700" << endl;
}
ItemBuy++;
ItemBuy++;
ItemBuy++;
ItemBuy++;
ItemBuy++;
ItemBuy++;
ItemBuy++;
ItemBuy++;
ItemBuy++;
cin >> ShopAccept;
Shoppe =ShopAccept;
BonusShopAccept = 0;
TotalShopAccept = 0;
cls();
for (int i = 1; i<=ShopAccept; i++) {
    if (ItemID[i] != 0) {
        BonusShopAccept++;
        ShopAccept++;

    }

}
TotalShopAccept = BonusShopAccept + Shoppe;
switch (TotalShopAccept) {
case 1 :
        cls();
    cout <<"Золото: " << Gold << endl;
    cout << "Предмет: Топорик" << endl;
    cout << "Тип Предмета: Пассивное" << endl;
    cout << "_______________________" << endl;
    cout << "Характеристики:" << endl;
    cout << "Увеличивает Атаку на 5" <<endl;
    cout << "_______________________" << endl;
    cout << "Активная Способность:" << endl;
    cout << "Отсутствует" << endl;
    cout << "_______________________" << endl;
    cout << "Cтоимость : 200" << endl;
    cout << "Введите 1, чтобы купить" << endl;
    cin >> ShopBuy;
    cls();
    if (ShopBuy == 1) {
            if (Gold >= 200) {
              ItemID[1] = 1;
              PlusAP = PlusAP + 5;
              BuyItems = BuyItems + 1;
              Gold = Gold - 200;
              cls();
              cout << "Покупка  Успешна ###" << endl;
              cin >> PPP;

            }
            else {
              cout << "Недостаточно Золота ###" << endl;
              cin >> PPP;


            }

    }
    break;
     case 2 :
        cls();
    cout <<"Золото: " << Gold << endl;
    cout << "Предмет: Щиток " << endl;
    cout << "Тип Предмета: Пассивное" << endl;
    cout << "_______________________" << endl;
    cout << "Характеристики:" << endl;
    cout << "Увеличивает Защиту на 1" <<endl;
    cout << "_______________________" << endl;
    cout << "Активная Способность:" << endl;
    cout << "Отсутствует" << endl;
cout << "_______________________" << endl;
    cout << "Cтоимость : 250" << endl;
    cout << "Введите 1, чтобы купить" << endl;
    cin >> ShopBuy;
    cls();
    if (ShopBuy == 1) {
            if (Gold >= 250) {
              ItemID[2] = 1;
              PlusDP = PlusDP + 1;
              BuyItems = BuyItems + 1;
              Gold = Gold - 250;
              cls();
              cout << "Покупка  Успешна ###" << endl;
              cin >> PPP;

            }
            else {
              cout << "Недостаточно Золота ###" << endl;
              cin >> PPP;


            }

    }
    break;
     case 3 :
        cls();
    cout <<"Золото: " << Gold << endl;
    cout << "Предмет: Кольцо Защиты" << endl;
    cout << "Тип Предмета: Пассивное" << endl;
    cout << "_______________________" << endl;
    cout << "Характеристики:" << endl;
    cout << "Увеличивает Защиту на 2" <<endl;
    cout << "_______________________" << endl;
    cout << "Активная Способность:" << endl;
    cout << "Отсутствует" << endl;
cout << "_______________________" << endl;
    cout << "Cтоимость : 600" << endl;
    cout << "Введите 1, чтобы купить" << endl;
    cin >> ShopBuy;
    cls();
    if (ShopBuy == 1) {
            if (Gold >= 600) {
              ItemID[3] = 1;
              PlusDP = PlusDP + 2;
              BuyItems = BuyItems + 1;
              Gold = Gold - 600;
              cls();
              cout << "Покупка  Успешна ###" << endl;
              cin >> PPP;

            }
            else {
              cout << "Недостаточно Золота ###" << endl;
              cin >> PPP;


            }

    }
    break;
     case 4 :
        cls();
    cout <<"Золото: " << Gold << endl;
    cout << "Предмет: Маска Регенерации Маны" << endl;
    cout << "Тип Предмета: Пассивное" << endl;
    cout << "_______________________" << endl;
    cout << "Характеристики:" << endl;
    cout << "Увеличивает РегМаны на 2" <<endl;
    cout << "_______________________" << endl;
    cout << "Активная Способность:" << endl;
    cout << "Отсутствует" << endl;
cout << "_______________________" << endl;
    cout << "Cтоимость : 600" << endl;
    cout << "Введите 1, чтобы купить" << endl;
    cin >> ShopBuy;
    cls();
    if (ShopBuy == 1) {
            if (Gold >= 600) {
              ItemID[4] = 1;
              PlusManaReg = PlusManaReg + 2;
              BuyItems = BuyItems + 1;
              Gold = Gold - 600;
              cls();
              cout << "Покупка  Успешна ###" << endl;
              cin >> PPP;

            }
            else {
              cout << "Недостаточно Золота ###" << endl;
              cin >> PPP;


            }

    }
    break;
     case 5 :
        cls();
    cout <<"Золото: " << Gold << endl;
    cout << "Предмет: Сапоги Гномов" << endl;
    cout << "Тип Предмета: Пассивное" << endl;
    cout << "_______________________" << endl;
    cout << "Характеристики:" << endl;
    cout << "Увеличивает Шансы Хода на 1" <<endl;
    cout << "Увеличивает Атаку на 3" <<endl;
    cout << "_______________________" << endl;
    cout << "Активная Способность:" << endl;
    cout << "Отсутствует" << endl;
cout << "_______________________" << endl;
    cout << "Cтоимость : 700" << endl;
    cout << "Введите 1, чтобы купить" << endl;
    cin >> ShopBuy;
    cls();
    if (ShopBuy == 1) {
            if (Gold >= 700) {
              ItemID[5] = 1;
              PlusAP = PlusAP + 3;
              PlusTP = PlusTP + 1;
              BuyItems = BuyItems + 1;
              Gold = Gold - 1000;
              cls();
              cout << "Покупка  Успешна ###" << endl;
              cin >> PPP;

            }
            else {
              cout << "Недостаточно Золота ###" << endl;
              cin >> PPP;


            }

    }
    break;

}











StKo();
    break;





}

}while (GameMapChoose < 6);

    break;
case 2:
    int infochoosee;
    do{
    cls();
cout << "1 - Кратко о Кнопках и Обозначениях" <<endl;
cout << "2 - Механики"<<endl;
cout << "3 - Авторы"<<endl;
cout << "4 - В Главное Меню"<<endl;
infochoosee= getch() - 48;
cls();
switch (infochoosee) {
case 1:
    cout << "Арена - Место, где вы можете сражаться в врагами, на арене вы можете или победить или проиграть, в случаи победы вы получаете золото и переходите на следующего врага, а в случае поражения ничего не теряете" <<endl
    << "Работа - Место, где вы можете получить Золото выполняя некоторые задачи(В магазине есть отдельная вкладка для улучшения заработка)" <<endl <<
    "Башня Магии - Место, где вы можете за Золото купить заклинания помогающие выиграть в сражение на арене"<< endl <<
    "Мой Персонаж - Место, где вы можете увидеть ваши характеристики, и другой статистики" << endl<<
    "Магазин - Место, где вы можете за Золото получить предметы, которые помогут выиграть в сражение" << endl;



    cout << "###";
    getch();
    break;
case 2:
    cout << "ВНИМАНИЕ! СЛЕДУЮЩАЮ ИНФОРМАЦИЯ ДЛЯ ТЕХ КОМУ ИНТЕРЕСНА МЕХАНИКА СЧЕТА ИГРЫ!" << endl<< "Всего два типа характеристик : Основные и Боевые"<< endl <<
    "Основные(Их нельзя изменить во время боя, только до него): Получаются следующим образом - " <<endl << "(Базовая(зависит от уровня) + Увеличение(приходит от предметов))* Коэфицент(приходит от предметов) "
    <<endl<< "Боевые(Их можно изменить только во время боя и они никак не влияют на Основные): Получаются следующим образом - "<<endl<<"(Основные + Увелечение(Заклинания и Активация предметов))* Коэфицент(Заклинантя и Активация предметов)" <<endl;
    cout << "###";
    getch();
    break;
case 3:
    cls();
cout << "Автор идеи: Mr.Snic" << endl << "Код : Mr.Snic" << endl<< "Бета-Тестирование: Папа Григорий" <<endl << "Отдельное Спасибо: " <<endl << "Вы тоже можете помочь игре в развитии, и попасть в Отдельное спасибо))"<< endl;
    cout << "###" <<endl;
    getch();
    break;
}

    }while (infochoosee < 4);
    break;
case 3 :
    do{
    cout << "1 - Уровень Сложности" << endl;
    cout << "2 - Моды(В разработке)" << endl;
    cout << "3 - Читы" << endl;
    SettingsChose = getch() - 48;
    cls();
    switch(SettingsChose){
case 1 :
    cout << "ВНИМАНИЕ!!! Сложность влияет ТОЛЬКО на Характеристики оппонентов на арене! (Рядом со сложностью написан Множитель для каждой характеристики врага)" << endl;
     cout << "1 - Простейшая 0.7" << endl;
     cout << "2 - Легкая 0.8" << endl;
     cout << "3 - Стандартная(по умолчанию) 1" << endl;
     cout << "4 - Сложная 1.2" << endl;
     cout << "5 - Хардкорная 1.4" << endl;
     Diff = getch() - 48;
     cls();
     switch(Diff){
     case 1 : DiffM = 0.7;
     break;
      case 2 : DiffM = 0.8;
     break;
      case 3 : DiffM = 1;
     break;
      case 4 : DiffM = 1.2;
     break;
      case 5 : DiffM = 1.4;
     break;

     }
    break;
case 2 :

    break;

case 3 :
cout << "1 - Чит на золото" << endl;
cout << "2 - Чит на Последовательность Врага" << endl;
cout << "3 - Чит на Улучшение Характеристик" << endl;
cout << "4 - Чит на Героя" << endl;
CheatChose = getch() - 48;
cls();
switch(CheatChose){
case 1 :
    cout << "Введите кол-во золото, которое вы хотите получить" << endl;
    cin >> Cheat;
    cls();
    Gold = Cheat;
    break;
    case 2 :
    cout << "Введите порядок врага, которое вы хотите получить" << endl;
    cin >> Cheat;
    cls();
    OpCounter = Cheat;
    break;
    case 3 :
    cout << "Введите кол-во характеристик, которое вы хотите получить(получите все)" << endl;
    cin >> Cheat;
    cls();

    HP += Cheat ;
    AP += Cheat ;
    DP += Cheat;
    TP += Cheat;
    ManaP +=Cheat;
    ManaReg += Cheat;

    break;
    case 4 :
    cout << "Введите номер героя, которое вы хотите получить(список героев смотреть ниже)" << endl;

        cout << "1 - Всратый Чиллиакс" << endl;
    cout << "2 - Папа Григорий" << endl;
    cout << "3 - Петя" << endl;
    cout << "4 - Близнец" << endl;
    cout << "5 - Травояднвый" << endl;
    cout << "6 - Еврей Эльяу" << endl;
    cout << "7 - Грустный Лёха" << endl;
    cin >> Cheat;
    cls();
    Class = Cheat;
    break;


}

    break;
default :
    SettingsChose = 99;
    }
    }while (SettingsChose != 99);
    break;

    }

    }while (a == 9);









    return 0;
}
