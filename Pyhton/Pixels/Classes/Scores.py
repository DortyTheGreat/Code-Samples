class Scores:
    def __init__(self, path):
        #'Data/highscores.txt'
        self.path=path
        self.DATA = list(map(lambda x: x.strip(), open(path,'r').readlines()))

    def sort(self):

        self.DATA.sort(key=lambda x: float(x),reverse=True)
        f = open(self.path, 'w')
        for i in range(0, len(self.DATA)):
            f.write(self.DATA[i])
            f.write('\n')
        f.close()
    def AddScore(self,score):

        f = open(self.path,'w')
        f.write(score)
        f.write('\n')
        for i in range(0,len(self.DATA)):
            f.write(self.DATA[i])
            f.write('\n')
        self.DATA.insert(0,score)

    def GetStr(self,n):
        return self.DATA[int(n)]
