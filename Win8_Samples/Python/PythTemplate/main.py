class Rectangle:
    def __init__(self,H,W):
        self.height = H
        self.width = W

    def GetArea(self):
        return self.width*self.height

    def GetPerimeter(self):
        return (self.width+self.height)*2

class Fraction:
    def __init__(self,A,B):
        self.UP=A
        self.DOWN=B
    def equal(self,second):
        if self.UP/second.UP == self.DOWN/second.DOWN:
            return "YES"
        else:
            return "NO"




a = input()
if a == "1":
    print("#1 prog")
    a, b = input().split()
    a = int(a)
    b = int(b)
    MyRect = Rectangle(a, b)


    print(MyRect.GetArea(), end=" ")
    print(MyRect.GetPerimeter())
else:
    print("#2 prog")

    a,b = input().split("/")
    a=int(a)
    b=int(b)
    MyVar = Fraction(a,b)

    c,d = input().split("/")
    c=int(c)
    d=int(d)
    MyVar2 = Fraction(c,d)



    print(MyVar.equal(MyVar2))