
import re

class Calculator:

    def __init__(self):
        self.running = True
        self.variables = {}

    def evaluate(self, user_input):

        # Determine if the user wants to exit
        if user_input == ".exit":
            self.running = False
            return
        # Determine if the user wants to call a function
        elif user_input[0] == ".":
            self.evaluate_function(user_input)
        # Determine if the user wants to assign a variable
        elif user_input[0] == "=":
            self.evaluate_variable(user_input)
        # Determine if the user wants to print a variable
        else:
            self.evaluate_print(user_input)

    def evaluate_function(self, user_input):
        pass

    def evaluate_variable(self, user_input):
        
        # Parse the input
        variable_info = self.parse_variable(user_input)

        # Validate that the first character is a letter and that there are no special characters other than - and _
        if not variable_info["name"][0].isalpha():
            self.usage("variable", "Invalid variable name")
            return
        
        regex = re.compile("[^a-zA-Z0-9-_]")
        if regex.search(variable_info["name"]):
            self.usage("variable", "Invalid variable name")
            return
        
        # Determine if the value is a number or another variable
        if variable_info["value"] in self.variables.keys():
            self.variables[variable_info["name"]] = self.variables[variable_info["value"]]
        # Otherwise, try to convert the value to a number
        else:
            try:
                if "." in variable_info["value"]:
                    self.variables[variable_info["name"]] = float(variable_info["value"])
                else:
                    self.variables[variable_info["name"]] = int(variable_info["value"])
            except ValueError:
                self.usage("variable", "Invalid variable value")
                return
            
        print(f"{variable_info['name']} = {self.variables[variable_info['name']]}")

    def evaluate_print(self, user_input):
        
        variable_name = user_input[1:]
        if variable_name in self.variables.keys():
            print(f"{variable_name} = {self.variables[variable_name]}")
        else:
            self.usage("print", f"'{variable_name}' is not defined")

    def parse_function(self, user_input: str):
        print("Function called")

    def parse_variable(self, user_input) -> dict:

        # Validate that there is an open and close parenthesis
        if user_input.count("(") != 1 or user_input.count(")") != 1:
            self.usage("variable", "Invalid syntax")
            return {}
        
        # Find the first parenthesis and find the variable name
        parenthesis_index = user_input.find("(")
        variable_name = user_input[1:parenthesis_index]
        remaining_input = user_input[parenthesis_index+1:]

        # Validate that the closing parenthesis is at the end of the string
        if remaining_input[-1] != ")":
            self.usage("variable", "Invalid syntax")
            return {}
        
        # grab the value of the variable
        variable_value = remaining_input[:-1]

        return {"name": variable_name, "value": variable_value}


    def usage(self, expressions_type, error_message=None):

        if expressions_type == "function":
            usage_string = error_message + " Function calls take the following format: " \
                           "\n\n\t.function_name(arg1, arg2[; assignment var])\n"
        elif expressions_type == "variable":
            usage_string = error_message + " Variable assignment takes the following format:" \
                           "\n\n\t=variable_name(value)\n"
        elif expressions_type == "print":
            usage_string = error_message + " Expressions take the following format:" \
                           "\n\n\t#variable_name\n"
            
        print(usage_string)