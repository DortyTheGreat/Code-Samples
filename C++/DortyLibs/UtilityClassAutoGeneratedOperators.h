#define CLASS_NAME BigInt

// ���������� ��� ����� �� �����������
bool operator !=(const CLASS_NAME& left, const CLASS_NAME& right) {
	return !(left == right);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������
bool operator <=(const CLASS_NAME& left, const CLASS_NAME& right) {
	return !(right < left);
}

// ���������, �������� �� ����� ������� ������ �������
bool operator >(const CLASS_NAME& left, const CLASS_NAME& right) {
	return (right < left);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������
bool operator >=(const CLASS_NAME& left, const CLASS_NAME& right) {
	return !(left < right);
}
