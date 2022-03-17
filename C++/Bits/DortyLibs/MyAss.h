

class Character {
private:
  string name;
  int max_hp, hp;
public:
  void setname(string s);
  void setmaxhp(int h);
  void sethp(int h);
  string getname();
  int getmaxhp();
  int gethp();
};


void Character::setname(string s)
{
    name = s;
}

void Character::sethp(int s)
{
    hp = min(max(0,s),max_hp);
}

void Character::setmaxhp(int s)
{
    max_hp = max(1,s);
}

string Character::getname()
{
    return name;
}

int Character::gethp()
{
    return hp;
}

int Character::getmaxhp()
{
    return max_hp;
}

