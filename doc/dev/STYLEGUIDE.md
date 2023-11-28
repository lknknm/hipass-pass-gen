## Hipass Code Style Guide
Since this is a student project, I am very flexible about Code Style improvements and suggestions. Here are the basic rules to follow in order to style the code and make it readable.


### For the C library:
- Functions/"Methods" should be named all in lowercase with words separated with `_`.
- Variables should also be named all in lowercase with words separated with `_`.

Example:
```c
void name_your_function(char* argument_name) {}
```
- "Disposable" variables such `i, j` inside `for loops` always in lowercase.
- Indentation (Tab) with 4 spaces.
- Allman indentation style convention.
- One-line `if/for/foreach` statements can be left without brackets following the example:
```c
if (char_type == 0)
    password[i] = digits[prng48_rand(0, 0xABCDE) % NUM_DIGITS];
```
- Functions/"Methods" must have a dashed-line separator before them, followed by a simple description if possible:
```c
//----------------------------------------------------------------------------
// Recursive function will generate a random number between 
// the 4 available character types. 
// If a character type was not selected within arguments, generate random number again. 
int generate_type(bool CH_TYPE[])
{
    // Function
}
```
- Color output directives should be prefixed with `C_` and be included after the header files, with a dashed-line separator before them, such as follows:
```C
//----------------------------------------------------------------------------
// Output constants to color values:
#define C_CLEAR  "\033[2J\033[1;1H"
#define C_RESET  "\e[m"
#define C_GREEN  "\e[32m"
#define C_YELLOW "\e[33m"
```