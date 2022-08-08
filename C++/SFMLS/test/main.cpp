/**
Степ бай степ туториал для того, чтобы скачать SFML для Code::Blocks

Шаг 1. Узнать какой у вас компилятор

Переходим в папку в Code::Blocks, затем в ..\CodeBlocks\MinGW\bin
Затем ищем файлик libgcc_s_XXX-1.dll
под XXX может быть
> SEH
> SJLJ
> DW2

в зависимости от того какой у вас там файлик то качаем соответственную опцию с сайта SFML
( точно не уверен, но если у вас есть и SJLJ и DW2, то качать надо именно SJLJ, но это не точно)

Шаг 1.5 Распаковка и Выбор

Распакуйте библиотеку куда вам угодно, а затем вам предстоит сделать выбор 1 из 2 вариантов

Вариант 1: Залинковать и связать SFML к компилятору c++
( Settings -> Compiler... -> Linker Settings -> ...
Вариант 2: Залинковать и связать SFML только для текущего проекта
( Project -> Buuild Options... -> Linker Settings -> ...

Можно линкануть библиотеку двумя способами:
Вариант 1 -> "Link Libraries:" (Придётся тыкать Add и вставлять по файлику )
Вариант 2 -> "Other Linking Options:" (можно просто вставить весь текст сразу, рекомендую этот вариант)

Какая разница между этими способами?
- Если честно я не знаю, мне больше нравится второй, ибо не нужно делать много добавлений и прочих нажатий на кнопки.


Шаг 2. Линкинг

Если Вы не знаете, что такое Debug и Release, то в кратце это два разных метода работы с проектом.
В режиме "разработчика" и режиме "релизной". То, как Вы будете билдить зависит от настроек в Build -> Select Target -> Debug\\Release (Debug по умолчанию)
Если Вы будете вносить изменения под "названием проекта", то тогда линкинг будет происходить для двух веток сразу. Рекомендую заносить в "название проекта" весь линкинг.


В зависимости от того как Вы будете линковать нужно писать разные словечки.


Через "Other Linking Options:" (рекомендую этот вариант в глобальный линкинг занести)
-lsfml-graphics
-lsfml-audio
-lsfml-network
-lsfml-window
-lsfml-system

Через "Link Libraries:" (Debug)
sfml-graphics-d
sfml-audio-d
sfml-network-d
sfml-window-d
sfml-system-d

Через "Link Libraries:" (Release, "имя проекта", или в общих настройках)
sfml-graphics
sfml-audio
sfml-network
sfml-window
sfml-system


Шаг 3. Подключение директории.

Settings -> Compiler...
ИЛИ (в зависимости от того хотите ли привязать ко всем проектам)
Project -> Buuild Options... ( если уж делаете для конкретного проекта, то опять же линкуйте сразу к релизу и дебагу через "имя проекта"

-> Search Directories -> Compiler (Нажать add внизу, Найти куда вы засунули папку SFML, затем выбрать в папке SFML папку include, должен выйти путь: ..\SFML-X.X.X\include)
-> Search Directories -> Linker   (аналогично для папки lib, путь:..\SFML-X.X.X\lib)


Шаг 4. Скопировать .dll.

Я точно не уверен можно ли их не копировать, а как-то перенести нормально, (наверное можно),
но проще просто скопровать все .dll из SFML-X.X.X\bin в папку проекта.

Шаг 5. Profit.

Всё готово, тыкайте "Build and Run" и всё должно работать

*/

class Man{

    void Hit(Enemy& e){

    }

};

class Enemy{

    void Hit(Man& e){

    }

};

#include <SFML/Graphics.hpp>

int main()
{






    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setPosition(sf::Vector2f(100,200));
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(Color(255,120,255,0));
        window.draw(shape);
        window.display();
    }

    return 0;
}
