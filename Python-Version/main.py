
from Calculator import Calculator


if __name__ == '__main__':

    instance = Calculator()

    # Run the main loop until exit is called
    while instance.running:
        user_input = input(">> ")
        instance.evaluate(user_input)