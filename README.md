# cicalc: C Interactive CALCulator
cicalc is an interactive calculator written in C. It can handle decimals due to it using `double`s.
## Motivation
GNU bc is the common tool used for calculations. Unfortunately, it is thousands of lines of code and includes a whole scripting language.
## Running
Run `make` to compile it and `make install` to install it.
## Syntax
The syntax is `OPERATOR [NUMBERS...]`.
You can use the following operators.
### add
Add the numbers following this operator.
### sub
Substract the numbers following this operator.
### mul
Multiply the numbers following this operator.
### div
Divide the numbers following this operator
### sqr
Calculate the root of the number following this operator. For example, `sqr 4 2` to get the square root of 4, where 2 is the index.
Limitation: May not work with negative index
### pow
Same as `sqr`, but it calculates the exponentiation of the number. For example, `pow 2 2` to get 2 to the power of 2.
## Scripting
cicalc can be scripted using basic shell functionality. Rather than giving a script as an argument, you'd input it like this:
```bash
cicalc < script.cicalc
```
