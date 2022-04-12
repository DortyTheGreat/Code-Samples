#define CLASS_NAME BigInt

// сравнивает два числа на неравенство
bool operator !=(const CLASS_NAME& left, const CLASS_NAME& right) {
	return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator <=(const CLASS_NAME& left, const CLASS_NAME& right) {
	return !(right < left);
}

// проверяет, является ли левый операнд больше правого
bool operator >(const CLASS_NAME& left, const CLASS_NAME& right) {
	return (right < left);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator >=(const CLASS_NAME& left, const CLASS_NAME& right) {
	return !(left < right);
}
