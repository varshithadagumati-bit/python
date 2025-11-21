import random
n = random.randint(1,10)
guess = int(input("Guess the number 1-10:"))
print("The generated random number",n)
if guess==n:
    print("guessed number and random number are same")
else:
    print("guessed number and random number are not same")