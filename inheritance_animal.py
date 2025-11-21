class Animal:
    def __init__(self, name):
        self.name = name
    def speak(self):
        return "Some generic animal sound"
    def move(self):
        return "The animal moves around"
class Dog(Animal):
    def speak(self):
        return f"{self.name} says: Woof! Woof!"
    def move(self):
        return f"{self.name} runs happily."
class Cat(Animal):
    def speak(self):
        print(f"{self.name} says: Meow! meow!..")
    def move(self):
        print(f"{self.name} walks excitedly")
class Snake(Animal):
    def speak(self):
        print(f"{self.name} says: Hisss! Hisss!..")
    def move(self):
        print(f"{self.name} Moving Curiously")
dog = Dog("Shiro")
cat = Cat("Leo")
snake = Snake("Hasini")
animals = [dog,cat,snake]
for animal in animals:
    print(animal.speak())
    print(animal.move())
