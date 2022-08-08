/**

Авто-определённое сравнение для любых объектов.

ВНИМАНИЕ! ЕСЛИ ВАШ КЛАСС\\СТРУКТУРА ИСПОЛЬЗУЕТ ОПЕРАЦИИ СРАВНЕНИЯ
НЕ ТРИВИАЛЬНО (АКА НЕ ВЫПОЛНЯЮТСЯ БАНАЛЬНЫЕ ПРАВИЛА СРАВНЕНИЯ), ТО ОЧЕВИДНО, ЧТО ЛУЧШЕ ВАМ НЕ ПОЛЬЗОВАТЬСЯ ЭТИМИ АВТО-ОПРЕДЕЛЕНИЯМИ

+ Не уверен, но
ЭТО НЕ РАБОТАЕТ ЕСЛИ
bool operator<(const foo& b){
    return a < b.a;
}

РАБОТАЕТ ЕСЛИ:
friend bool operator<(const foo& a,const foo& b){
    return a.a < b.a;
}

Почему второй вариант лучше использовать?
- Дело в том, что первый вариант предполагает по сути нечто аналогичное
friend bool operator<(foo& a,const foo& b)
Это нечто знакомое тем, кто кодил на питоне, помните, как первый аргумент функции - это self,
так тут первый аргумент такой функции - это this, а this - это foo&, что предполагает, что в результате такой функции объект может быть изменён.
Поэтому знайте, как этим пользоваться и всё такое

Именно поэтому не забудьте добавить ключ. слово const куда надо

bool operator<(const foo& b) const {
    return a < b.a;
}

*/

template <typename A,typename B>
bool operator>(const A& a, const B& b){
    return b<a;
}

template <typename A,typename B>
bool operator>=(const A& a, const B& b){
    return !(a<b);
}

template <typename A,typename B>
bool operator<=(const A& a, const B& b){
    return !(b<a);
}
/// Это уже из разряда "Почему?"
template <typename A,typename B>
bool operator!=(const A& a, const B& b){
    return (a<b) || (b<a);
}

template <typename A,typename B,typename C>
bool operator!=(const A& a, const B& b){
    return !(a==b);
}

template <typename A,typename B>
bool operator==(const A& a, const B& b){
    return !(a!=b);
}
