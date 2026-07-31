# cicalc: C Interactive CALCulator
cicalc is an interactive calculator written in C. It can handle decimals due to it using `double`s.
## Motivation
GNU bc is the common tool used for calculations. Unfortunately, it is thousands of lines of code and includes a whole scripting language.
Other alternatives like GNOME Calculator require running a heavy graphical interface. Calculators don't have to be this complex, so I decided I could make better software than these people.
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
### nrt
Calculate the Nth root of the number following this operator. For example, `nrt 4 2` to get the square root of 4, where 2 is N.
Limitation: May not work with negative index
### pow
Same as `nrt`, but it calculates the exponentiation of the number. For example, `pow 2 2` to get 2 to the power of 2.
### quit
Will quit cicalc.
## Scripting
cicalc can be scripted using basic shell functionality. Rather than giving a script as an argument, you'd input it like this:
```bash
cicalc < script.cicalc
```
IMPORTANT: The script must end with `quit`. Otherwise, cicalc will print zeroes forever!
