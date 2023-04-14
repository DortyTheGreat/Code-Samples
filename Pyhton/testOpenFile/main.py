open('result1.txt', 'w').close()

import os
with open('result2.txt', 'w'):
    os.utime('result2.txt',None)

#open('result3.txt').close()


from pathlib import Path
Path('result4.txt').touch()

import os
#os.mknod('result5.txt') только на винде не робит