
# Software Development Plan - Python Matrix calculator

This is a mock SDP for this Python project which will become a C++ project in the future. It will consist of the normal stages, but also will contain a planning stage of all the functionality that I want to include with it. The main goal is to get a working product, then start adding features, so it will need to be modular enough to support additional features on top of it anyway, here it be.

## Requirements - 0

To begin, the requirements are outlined entirely by myself. I want to build a working matrix calculator. This is inspired by octave, but will be SERIOUSLY reduced in capability and scale. I just want to get something that works, then maybe I can improve the features later. Below are the features I currently want to support

| IDX | FEATURE                                                                                          |
|-----|--------------------------------------------------------------------------------------------------|
| 0   | CLI Tool that can recognize function calls, variable assignment, and basic printing of variables |
| 1   | Creation of Matrix object that will be scaled based on desired functions                         |
| 2   | Creation of Scalar object, this will have notably less features, not unlike scalars              |
| 3   | For Matrix - Row Reduced Echelon Form                                                            |
| 4   | For Matrix - LU factorization                                                                    |
| 5   | For Matrix - QR factorization                                                                    |
| 6   | For Matrix - Diagonalization                                                                     |
| 7   | For Matrix - SVD                                                                                 |
| 8   | Creation of GUI model...maybe                                                                    |
| 9   | Future stuff (not yet thought of. Sue me)                                                        |

## Design - 1

To begin, lets start with the first feature, CLI tool to recognize things

### Phase 0 - CLI Framework

This initially shouldn't be too hard. Just have a prefix that denotes what's happening
* . -- this means the user is calling a function
* = -- this means the user is creating a variable
* \# -- this means the user is printing a variable

In this phase I don't want the parser to be too heavily taxed. Later down the line, maybe even at the end of this section, I want the parser to recongize more complex commands, but for now it will be very basic, and probably annoying to work with. Each output will need to assigned explicitly to a variable to be kept a hold of, otherwise it will just be printed and forgotten about. As for saving function output, there will be a postfix in the function line that determines if and where the output is saved to.

In this first implementation, there are only going to be 4 functions, and 2 data types. 

#### Functions
* Add
* Subtract
* Multiply
* Divide

#### Data Types
* int
* float

Each of the previous functions are all binary operators, so will take the following form

```
.FUNCTION(ARG1, ARG2; VAR_TO_STORE)
```

The first two args can either be variables or just inputs that can be evaluated (i.e. 4.0 or 5). The last will be the varialbe that the input is stored to. If there is no semicolon, the result won't be stored anywhere and will just be printed and forgotten about.

Variable assignment shouldn't be too different, but should put in the order, =name(value)

```
=NAME_OF_VAR(VALUE_TO_ASSIGN)
```

The value that is being assigned must be an evaluatable entry. If there is a . character it will be interpreted as a float. If not, then it will become an int.

Variable printing is very easy, it comes in the following form.

```
#NAME_OF_VAR
```
Then the variable will be printed. This is akin to just entering a variable into a REPL and getting its value

Onto actual design

#### Phase 0 design

Ideally this should be straighforward to identify what the call type is. With only 3 types and 3 prefixes, the psuedocode should just be this

```python

if first char is ".":
    evaluate a function
elif first char is "=":
    assign a variable
elif first char is "#":
    print the variable
else:
    fall through

```

This allows each portion to be covered and then parsed for their individual roles. Onto the parsers

##### Function parser

This will be looking for entries, and the proper formatting. If the formatting is not achieved, or there are insufficient parameters, then an error will be thrown. The parser will break down each function call into a dict with the following options

* function name - string
* arguments - tuple
* output variable - string

The arguements may eventually become larger, so using a tuple allows for the potential future scaling. Likely as it is read in it will be a list, but will be converted to a tuple to avoid stepping on any of the values. To accomplish this parsing, I believe the following algorithm should work

1. Check for one opening parenthesis and one closing parenthesis, if not throw an error
2. Assign the function name to the first character after the . all the way up to the open parenthesis
3. Use the substring between the parethesis to heck for a semicolon. If present, name the output variable everything after the semicolon up to the close parenthesis
4. Use the substring between the open parentesis and the semicolon if present or the close parenthesis to split into terms based off of commas.
5. Ensure that all entries in the split list and the output variable do not contain punctionation (except - and _) and do not begin with numbers
6. Return a dict with the corresponding values

##### Assignment Parser

Assignment parser should be even easier than the previous. All it needs to do is determine if the variable already exists, and if not create it. Then assign the entries between the parenthesis to the new variable. The variable name will be everything between the "=" and the "(".

##### Printing functionality

Printing should be even easier, as this is just identify the variable name and print its contents if it exists

## Implementation - 2

## Testing - 3

## Deployment - 4

## Maintenance - 5