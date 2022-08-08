/**
���� ��� ���� �������� ��� ����, ����� ������� SFML ��� Code::Blocks

��� 1. ������ ����� � ��� ����������

��������� � ����� � Code::Blocks, ����� � ..\CodeBlocks\MinGW\bin
����� ���� ������ libgcc_s_XXX-1.dll
��� XXX ����� ����
> SEH
> SJLJ
> DW2

� ����������� �� ���� ����� � ��� ��� ������ �� ������ ��������������� ����� � ����� SFML
( ����� �� ������, �� ���� � ��� ���� � SJLJ � DW2, �� ������ ���� ������ SJLJ, �� ��� �� �����)

��� 1.5 ���������� � �����

���������� ���������� ���� ��� ������, � ����� ��� ��������� ������� ����� 1 �� 2 ���������

������� 1: ����������� � ������� SFML � ����������� c++
( Settings -> Compiler... -> Linker Settings -> ...
������� 2: ����������� � ������� SFML ������ ��� �������� �������
( Project -> Buuild Options... -> Linker Settings -> ...

����� ��������� ���������� ����� ���������:
������� 1 -> "Link Libraries:" (������� ������ Add � ��������� �� ������� )
������� 2 -> "Other Linking Options:" (����� ������ �������� ���� ����� �����, ���������� ���� �������)

����� ������� ����� ����� ���������?
- ���� ������ � �� ����, ��� ������ �������� ������, ��� �� ����� ������ ����� ���������� � ������ ������� �� ������.


��� 2. �������

���� �� �� ������, ��� ����� Debug � Release, �� � ������ ��� ��� ������ ������ ������ � ��������.
� ������ "������������" � ������ "��������". ��, ��� �� ������ ������� ������� �� �������� � Build -> Select Target -> Debug\\Release (Debug �� ���������)
���� �� ������ ������� ��������� ��� "��������� �������", �� ����� ������� ����� ����������� ��� ���� ����� �����. ���������� �������� � "�������� �������" ���� �������.


� ����������� �� ���� ��� �� ������ ��������� ����� ������ ������ ��������.


����� "Other Linking Options:" (���������� ���� ������� � ���������� ������� �������)
-lsfml-graphics
-lsfml-audio
-lsfml-network
-lsfml-window
-lsfml-system

����� "Link Libraries:" (Debug)
sfml-graphics-d
sfml-audio-d
sfml-network-d
sfml-window-d
sfml-system-d

����� "Link Libraries:" (Release, "��� �������", ��� � ����� ����������)
sfml-graphics
sfml-audio
sfml-network
sfml-window
sfml-system


��� 3. ����������� ����������.

Settings -> Compiler...
��� (� ����������� �� ���� ������ �� ��������� �� ���� ��������)
Project -> Buuild Options... ( ���� �� ������� ��� ����������� �������, �� ����� �� �������� ����� � ������ � ������ ����� "��� �������"

-> Search Directories -> Compiler (������ add �����, ����� ���� �� �������� ����� SFML, ����� ������� � ����� SFML ����� include, ������ ����� ����: ..\SFML-X.X.X\include)
-> Search Directories -> Linker   (���������� ��� ����� lib, ����:..\SFML-X.X.X\lib)


��� 4. ����������� .dll.

� ����� �� ������ ����� �� �� �� ����������, � ���-�� ��������� ���������, (�������� �����),
�� ����� ������ ���������� ��� .dll �� SFML-X.X.X\bin � ����� �������.

��� 5. Profit.

�� ������, ������� "Build and Run" � �� ������ ��������

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
