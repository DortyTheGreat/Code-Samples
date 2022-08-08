/**

����-����������� ��������� ��� ����� ��������.

��������! ���� ��� �����\\��������� ���������� �������� ���������
�� ���������� (��� �� ����������� ��������� ������� ���������), �� ��������, ��� ����� ��� �� ������������ ����� ����-�������������

+ �� ������, ��
��� �� �������� ����
bool operator<(const foo& b){
    return a < b.a;
}

�������� ����:
friend bool operator<(const foo& a,const foo& b){
    return a.a < b.a;
}

������ ������ ������� ����� ������������?
- ���� � ���, ��� ������ ������� ������������ �� ���� ����� �����������
friend bool operator<(foo& a,const foo& b)
��� ����� �������� ���, ��� ����� �� ������, �������, ��� ������ �������� ������� - ��� self,
��� ��� ������ �������� ����� ������� - ��� this, � this - ��� foo&, ��� ������������, ��� � ���������� ����� ������� ������ ����� ���� ������.
������� ������, ��� ���� ������������ � �� �����

������ ������� �� �������� �������� ����. ����� const ���� ����

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
/// ��� ��� �� ������� "������?"
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
