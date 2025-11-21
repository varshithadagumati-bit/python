class Animal:
    def make_sound(self):
        return "Some generic animal sound"
class Dog(Animal):
    def make_sound(self):
        return "Woof! Woof!"
class Cat(Animal):
    def make_sound(self):
        return "Meow!"
class Bird(Animal):
    def make_sound(self):
        return "Tweet! Tweet!"
if __name__ == "__main__":
    animals = [Dog(), Cat(), Bird()]
    for animal in animals:
        print(f"{animal.__class__.__name__} sound: {animal.make_sound()}")