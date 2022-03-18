#include <cmath>

double GetArmorMult(int armor){
/// Даёт множитель урона в зависимости от брони
double b = 1; // База Брони
double f = 0.06; // Фактор брони
return 1 - (f * armor) / (b + f * abs(armor));

}
