a = int(input("Enter a number"))
n = 0
n1 = 1
count = 0
while count <= a:
    print(n)
    n,n1 = n1, n+n1
    count +=1