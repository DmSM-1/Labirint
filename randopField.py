from random import randint

y,x = map(int,input("Sizes: ").split(' '))

arr = []
for i in range(y):
    arr.append([])
    for j in range(x):
        arr[i].append(' ')

x1 = randint(0,x-1)
y1 = randint(0,y-1)
arr[y1][x1]='i'

while(arr[y1][x1]!=' '):
    x1 = randint(0,x-1)
    y1 = randint(0,y-1)
    if arr[y1][x1]==' ': 
        arr[y1][x1]='o'
        break

i = min(int(input("Walls: ")),x*y/2)
while i>0:
    x1 = randint(0,x-1)
    y1 = randint(0,y-1)
    if arr[y1][x1]==' ': 
        arr[y1][x1]='#'
        i-=1

f = open(input("File name: "),'w')
f.write('#'*(x+2)+'\n')
for i in range(y):
    f.write('#'+''.join(arr[i])+'#'+'\n')
f.write('#'*(x+2)+'\n')