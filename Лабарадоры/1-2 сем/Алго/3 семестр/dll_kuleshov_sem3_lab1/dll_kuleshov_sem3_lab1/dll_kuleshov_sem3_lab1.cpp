// dll_kuleshov_sem3_lab1.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "dll_kuleshov_sem3_lab1.h"


// Пример экспортированной переменной
DLLKULESHOVSEM3LAB1_API int ndllkuleshovsem3lab1=0;

// Пример экспортированной функции.
DLLKULESHOVSEM3LAB1_API int fndllkuleshovsem3lab1(void)
{
    return 0;
}

// Конструктор для экспортированного класса.
Cdllkuleshovsem3lab1::Cdllkuleshovsem3lab1()
{
    return;
}
