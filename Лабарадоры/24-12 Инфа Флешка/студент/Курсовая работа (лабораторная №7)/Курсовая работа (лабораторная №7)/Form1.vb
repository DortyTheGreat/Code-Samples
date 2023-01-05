
Option Strict On
Option Explicit On
Imports System.Math
Public Class Form1
    Sub vivod(ByVal Z As Double, ByVal T As TextBox) 'Процедура вывода массивов в TextBox'
        T.Text = CStr(Z)
    End Sub
    Sub vvod(ByRef a() As Double, ByVal n As Single) 'Процедура ввода массива
        Dim i As Integer
        ReDim a(CInt(n))
        For i = 1 To CInt(n)
            a(i) = CDbl(InputBox("Введите" & i & "-й элемент"))
        Next i
    End Sub

    Sub vivodmas(ByRef a() As Double, ByVal n As Integer, ByVal L As ListBox) 'Процедура вывода массивов в ListBox'
        Dim i As Integer
        Dim m As String = ""
        For i = 1 To UBound(a)
            m = (m) + (CStr(a(i)) + (Space(3)))
        Next i
        L.Items.Add(m)
    End Sub


    Public Sub osnova(ByVal z() As Double, ByVal a() As Double, ByVal n As Integer, ByVal n1 As Integer, ByRef i As Integer, ByRef j As Integer) 'Процедура нахождения и вывода значения одинаковых элементов  и его индексов в TextBox 
        Dim min As Integer
        Dim min1 As Integer
        Dim k As Double
        min = n
        min1 = n1
        For i = 1 To n
            For j = 1 To n1
                If (z(i) = a(j)) And (j < min1) And (i < min) Then
                    k = z(i)
                    vivod(k, TextBox4) 'Вывод значения искомого элемента
                    vivod(CDbl(i), TextBox5) 'Вывод индекса из массива Z
                    vivod(CDbl(j), TextBox6) 'Вывод индекса из массива A
                    min = i
                    min1 = j
                End If
            Next
        Next


    End Sub


    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim i, j, n, n1 As Integer
        Dim a(3) As Double
        Dim z(6) As Double
        n = CInt(CSng(TextBox1.Text))
        n1 = CInt(CSng(TextBox3.Text))
        vvod(z, n)
        vvod(a, n1)
        vivodmas(z, n, ListBox1)
        vivodmas(a, n1, ListBox2)
        osnova(z, a, n, n1, i, j)
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Application.Exit()
    End Sub

End Class
