import random
secret = random.randint(1,18)
print("i love fischc")
temp  = input("next number in your heart:")
guess = int(temp)
count = 1
while count != 10:
  count = count + 1
  if guess == secret:
     print("right,are you bug in my heart")
     print("but no prize !")
     break
  else:
     if guess > secret:
        print("too big")
     else:
        print("too small")
     temp  = input("wrong,input again:")
     guess = int(temp)
print("game over,see you next time!")
