Option Strict On
Option Explicit On
Imports System.Math
Public Class Form1
    'Процедура решения задачи
    Sub massiv(ByRef a(,) As Integer)
        Dim i, j As Integer
        Dim q As Boolean
        Dim p As Boolean
        Dim f As Integer
        f = 0
        If f = 0 Then
            TextBox1.Text = "Таких чисел нет"
        End If
        Randomize()
        For i = 0 To 7
            For j = 0 To 2
                a(i, j) = CInt(Rnd() * 100 - 50)
            Next
        Next
        For i = 0 To 7
            For j = 0 To 2
                p = MaxColum(a, a(i, j), i, j)
                q = MinRow(a, a(i, j), i, j)
                If q And p Then
                    vivod(i, j, a(i, j), TextBox1)
                    f = 1
                End If
            Next
        Next
    End Sub
    'Функция ввода данных из TextBox            
    Function vvod(ByRef T As TextBox) As Integer
        Return CInt(Val(T.Text))
    End Function
    'Функция вывода данных в TextBox
    Public Sub vivod(ByVal i As Integer, ByVal j As Integer, ByVal el As Integer, ByVal T As TextBox)
        T.Text = CStr(el)
    End Sub
    'Процедура вывода массивов в ListBox
    Public Sub PrintMatr(ByRef a(,) As Integer, ByRef LB As ListBox)
        Dim i, j, m, n As Integer
        Dim z, z1 As String
        m = a.GetLength(0) - 1
        n = a.GetLength(1) - 1
        LB.Items.Clear()
        For i = 0 To m
            z = " "
            For j = 0 To n
                z1 = Format(a(i, j), "00")
                If a(i, j) < 0 Then
                    z1 = Space(2) + z1
                Else
                    z1 = Space(3) + z1
                End If
                z = z + z1
            Next j
            LB.Items.Add(z)
        Next i
    End Sub
    'Процедура нахождения минимального значения элемента массива в строке
    Function MinRow(ByRef a(,) As Integer, ByVal el As Integer, ByVal k As Integer, ByVal l As Integer) As Boolean
        Dim i, m, n As Integer
        m = a.GetLength(0) - 1
        n = a.GetLength(1) - 1
        For i = 0 To n
            If (Not l = i) Then
                If (el >= a(k, i)) Then Return False
            End If
        Next
        Return True
    End Function
    'Процедура нахождения максимального значения элемента массива в столбце
    Function MaxColum(ByRef a(,) As Integer, ByVal el As Integer, ByVal k As Integer, ByVal l As Integer) As Boolean
        Dim i, m, n As Integer
        m = a.GetLength(0) - 1
        n = a.GetLength(1) - 1
        For i = 0 To m
            If (Not k = i) Then
                If (el <= a(i, l)) Then Return False
            End If
        Next
        Return True
    End Function
    'Процедура обработки нажатия на кнопку
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim a(7, 2) As Integer
        massiv(a)
        PrintMatr(a, ListBox1)
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub TextBox3_TextChanged(sender As Object, e As EventArgs) Handles TextBox3.TextChanged

    End Sub
    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Application.Exit()
    End Sub

End Class











