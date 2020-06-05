def func():
    with open('kya.txt','w') as f:
        f.write(str(300000))
        f.write('\n')
        for i in range(300000):
            f.write(str(i+1))
            f.write(' ')

func()
