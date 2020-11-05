<h1 align="center">Pryst Language</h1>
<h3 align="center">A static-typed language with beautiful syntax and a little bit of sugar :)</h3>
<p align="center">
  <a href="https://ci.appveyor.com/project/cliid/pryst/branch/master">
    <img src="https://ci.appveyor.com/api/projects/status/github/jitcijk/pryst?branch=master&svg=true" />
  </a>
  <a href="https://travis-ci.com/github/jitcijk/pryst/builds">
    <img src="https://travis-ci.org/jitcijk/pryst.svg?branch=master" />
  </a>
  <a href="https://github.com/jitcijk/pryst/blob/master/LICENSE">
    <img alt="License: MIT" src="https://img.shields.io/badge/license-MIT-blue.svg" target="_blank" />
  </a>
  <a href="https://app.codacy.com/gh/jitcijk/pryst/dashboard">
    <img src="https://app.codacy.com/project/badge/Grade/724be582a55e464d97018c11df1bebd2" />
  </a>
  <a href="https://codecov.io/gh/jitcijk/pryst">
    <img src="https://codecov.io/gh/jitcijk/pryst/branch/master/graph/badge.svg" />
  </a>
</p>

![Pryst Logo](https://raw.githubusercontent.com/cliid/pryst-logos/main/Pryst.png)

## Intro

Pryst (spoken as \[ˈpraɪst\]) is a static-typed language with a beautiful C-like syntax.

It features variables, types, conditionals, loops, arrays and more! 

Most of all, Pryst is `currently in development`, so there will be new features!

## Core Technologies

#### JIT compilation (`./pryst`)
#### AOT compilation (`./native/prystnative`)
#### Static Typing
#### Interoperability with Truffle

## Pryst's Philosophy

#### `Static` is better than `Dynamic`.

#### One's code should be readable by others. `No tricks like ol' C/C++`.

#### `Syntax` should be beautiful, no exceptions.

#### Most of all, `Code in a comfortable syntax.`

## Example Code

```
int main(str argv[])
{
  if (argv.len > 1) {
    print("Hello" + argv[1]);
  }
  else {
    print("Hello!");
  }
}
```

## Table of Contents
- [Build from Source](#build-from-source)
  - [Prerequisites](#prerequisites)
  - [Build](#build)
- [Usage](#usage)
  - [Run a Source File](#run-a-source-file)
- [Variables](#variables)
  - [Integer Variable](#integer-variable)
  - [Float Variable](#float-variable)
  - [Boolean Variable](#boolean-variable)
  - [String Variable](#string-variable)
  - [Array Variable](#array-variable)
  - [Type Conversion](#type-conversion)
- [Data Types](#data-types)
  - [Integer](#integer)
  - [Float](#float)
  - [Boolean](#boolean)
  - [String](#string)
  - [Array](#array)
- [Operators](#operators)
  - [Arithmetic Operators](#arithmetic-operators)
  - [Postfix Operators](#postfix-operators)
  - [Prefix Operators](#prefix-operators)
  - [Bitwise Operators](#bitwise-operators)
  - [Shorthand Assignment](#shorthand-assignment)
- [Functions](#functions)
  - [Return Statement](#return-statement)
  - [Recursion](#recursion)
- [Conditionals](#conditionals)
  - [If](#if)
  - [Ternary Operator](#ternary-operator)
  - [Switch](#switch)
- [Loops](#loops)
  - [For Loop](#for-loop)
  - [While Loop](#while-loop)
- [Packages](#packages)
- [Imports](#imports)
- [Comments](#comments)
- [Package Manager](#package-manager)
- [Standard Library](#standard-library)
- [TODO](#todo)

## Build from Source

### Prerequisites

In order to build Pryst properly, you need to install GraalVM and Maven.

#### Install GraalVM

Go to [GraalVM Github Package Download Link](https://github.com/graalvm/graalvm-ce-builds/releases/tag/vm-20.2.0) and install the proper GraalVM release matching your JDK version.

After you download GraalVM, follow the instructions by [GraalVM Docs](https://www.graalvm.org/docs/getting-started-with-graalvm/)

#### Install Maven

Follow the instructions made by [Baeldung](https://www.baeldung.com/install-maven-on-windows-linux-mac#:~:text=Installing%20Maven%20on%20Mac%20OS,%3A%20apache%2Dmaven%2D3.3.)

### Build

`git clone https://github.com/jitcijk/pryst.git`

`cd pryst`

`mvn package`

## Usage

### Run a source file

To run a Pryst source file on top of JVM, give it a relative/absolute path to the file.

`./pryst /path/to/your/pryst/code.pr (It's extension name is .pr)`

To run with native build:

`./native/prystnative /path/to/your/pryst/code.pr`

## Variables

Variable names have to start with an alphabetic character and continue either with alphanumeric, underscores.
For example:

```
int x; // OK
float var_whatever; // OK
bool _isClicked; // OK
str 3numbers[3]; // NO
```

### Integer Variable

Unsigned long integer variables in Pryst start with the keyword `int`.

```
int age = 40;
age = 41;
```

### Float Variable

Double precision floating-point variables in Pryst start with the keyword `float`.

```
float height = 183.82;
height = 177.13;
```

### Boolean Variable

Boolean variables in Pryst start with the keyword `bool`.

```
bool x = true;
x = false;
if (x) {
  print("x is true!");
}
else {
  print("x is false!");
}
```

In Pryst, `true | false` isn't `1 | 0`.

Instead, `true` and `false` is a singleton object.

More info: `null` uses the same philosophy.

### String Variable

String variables in Pryst start with the keyword `str`.

```
str myString = "Hello";
print(myString);
```

### Array Variable

Static size arrays in Pryst look like this: `type_name[arr_size]`.

```
str strArray[3] = {"Jack", "The", "Pillow"};
println(strArray[1][1]); // It basically means the second character of the second elem of the string array.
// It prints "h"
str[3][4] str_3by4_elems = {{"A", "B", "C", "D"}, {"E", "F", "G", "H"}, {"I", "J", "K", "L"}, {"M", "N", "O", "P"}};
print(str_4by4_elems[2][1]);
// It prints "J"
```

### Type Conversion

In Pryst, type conversion is kinda-explicit.

For example, 

```
int x = 3;
float y = x; // OK

print("Hello" + x); // NO

print("Hello" + x.toStr()); // OK

bool z = true;

int w = x + z; // NO
```

## Data Types

Pryst currently supports 5 primitive data types: `int`, `float`, `bool`, `str`, `array`.

### Integer

Integers are whole numbers that support most of the arithmetic and bitwise operators, as you'll see later. 
They can be represented also as: binary with the 0b prefix, hexadecimal with the 0x prefix and octal with the 0o prefix.

```
int dec = 27
int oct = 0o33
int hex = 0x1B
int bin = 0b11011
int arch = 2 ** 32
```

### Float

Floating point numbers are used in a very similar way to Integers. In fact, they can be mixed and matched, like `3 + 0.2` or `5.0 + 2`, where the result will always be a Float.

```
float pi = 3.14159265;
float e = 2.71828182;
```

Scientific notation is also supported via the `e` modifier:

```
float sci = 0.1e3;
float negsci = 25e-5;
```

### Boolean

It would be strange if this data type included anything else except `true` and `false`.

```
bool mad = true;
bool genius = false;
```

Expressions like the `if/else`, won't check for values that are not necessarily boolean.

### String

Strings are UTF-8 encoded, meaning that you can stuff in there anything, even emojis.

```
str weather = "Hot";
str price = "500円";
```

String concatenation is handled with the `+` operator. Concatenation between a string and another data type will throw a compile-time error.

```
str name = "Tony" + " " + "Stark";
```

Additionally, strings are treated as enumerables. They support subscripting and iteration in `for in` loops.

```
str me = "howdy"[2]; // "w"
```

Escape sequences are there too if you need them: `\"`, `\n`, `\t`, `\r`, `\a`, `\b`, `\f` and `\v`. Nothing changes from other languages, so I'm sure you can figure out by yourself what every one of them does.

```
str code = "if(name == \"ben\"){\n\tprint(10);\n};";
```

### Array

Arrays are ordered collections of a specific data type. You can't mix and match strings with integers, or floats with other arrays.

```
str names[] = ["John", "Ben"];
str john = names[0];
```

Individual array elements can be accessed via subscripting with a 0-based index:

```
str names[] = ["Kirk", "Bones", "Spock"];
str first = names[0]; // "Kirk"
str last = names[-1]; // "Spock"
```

In the same style, an index can be used to check if it exists. It will return `null` if it doesn't:

```
if(names[10].exists())
  // handle it
```

Individual elements can be reassigned on mutable arrays:

```
int numbers[] = [5, 8, 10, 15];
numbers[1] = 7;
```

Arrays can be compared with the `==` and `!=` operators, which will check the position and value of every element of both arrays. Equal arrays should have the same exact values in the same position.

They can also be combined with the `+` operator, which adds the element of the right side to the array on the left side.

```
str concat[] = ["an", "array"] + ["and", "another"]
// ["an", "array", "and", "another"]
```

## Operators

### Arithmetic Operators

`+`, `-`, `*`, `/`, `%`, `**`

### Postfix Operators

`a++` means to invoke the statement then increment `a`.

`a--` means to invoke the statement then decrement `a`.

### Prefix Operators

`++a` means to increment `a` and then invoke the statement.

`--a` means to decrement `a` and then invoke the statement.

### Bitwise Operators

`~` is the bitwise NOT operator.

`&` is the bitwise AND operator.

`|` is the bitwise OR operator.

`^` is the bitwise XOR operator.

### Shorthand Assignment

`a += b` is equivalent to `a = a + b`

`a -= b` is equivalent to `a = a - b`

`a *= b` is equivalent to `a = a * b`

`a /= b` is equivalent to `a = a / b`

`a %= b` is equivalent to `a = a % b`

`a &= b` is equivalent to `a = a & b`

`a |= b` is equivalent to `a = a | b`

`a ^= b` is equivalent to `a = a ^ b`

`a **= b` is equivalent to `a = a ** b`

## Functions

Pryst treats functions as functions, not as first class citizens.

```
int x() {
  println("Hello");
}
```

Parentheses are optional and for simple functions like the above, I'd omit them. Calling the function needs the parentheses though:

```
x();
```

### Type Hinting

Pryst is static-typing, so type hinting is its own reward.

### Default Parameters

TODO

### Return Statement

In Pryst, a return statement uses the keyword: `return`.

You already know how to use the return statement, right?

`return x;`

### Variadic

TODO

### Closures

Hmm... Should we?

### Recursion

Recursive functions calculate results by calling themselves. Although loops are probably easier to mentally visualize, 
recursion provides for some highly expressive and clean code. Technically, they build an intermediate stack and 
rewind it with the correct values in place when a finishing, non-recursive result is met. It's easier to understand them 
if you think of how they're executed. Let's see the classic factorial example:

```
int fac(int n) {
  if(n == 0)
    return 1;
  return n * fac(n - 1);
}
```

Keep in mind that Pryst doesn't provide tail call optimization. That would allow for more memory efficient recursion, especially when creating large stacks.

## Conditionals

Pryst provides two types of conditional statements. The `if/else` and the `switch` statement.

### If

An `if/else` block looks pretty familiar:

```
if(1 == 2)
  println("Not calling me.");
else
  println("1 isn't equal to 2. Duh!");
```

### Ternary Operator

The ternary operator `?:` is a short-hand `if/else`, mostly useful when declaring variables based on a condition or when passing function parameters. It's behaviour is exactly as that of an `if/else`.

```
int price = 100;
int offer = 120;
str status = offer > price ? "sold" : "bidding";
```

Although multiple ternary operators can be nested, I wouldn't say that would be the most readable code. 
Actually, except for simple checks, it generally makes for unreadable code.

### Switch

`Switch` expressions on the other hand are way more interesting. They can have multiple cases with multiple conditions 
that break automatically on each successful case, act as generic if/else, and match array elements.

```swift
int a = 5;
switch (a) {
  case 2, 3:
    println("Is it 2 or 3?");
  case 5:
    println("It is 5. Magic!");
  default:
    println("No idea, sorry.");
}
```

## Loops

### For Loop

Everybody knows what a For Loop is, right?

Without arguments, the `for` loop can behave as an infinite loop, much like a traditional `while`. 
Although there's not too many usecases, it does its job when needed. An example would be prompting the user for input 
and only breaking the infinite loop on a specific text.

```
for( ; ; ;) {
  str pass = prompt("Enter the password: ");
  if(pass == "123") {
    println("Good, strong password!");
    break;
  }
}
```

The `break` and `continue` keywords, well break or skip the iteration. They function exactly like you're used to.

### While Loop

In Pryst, a While Loop works as you expected.

```
int i = 10, j = 7;
while (i > j) {
  j++;
}
```

## Packages

## Imports

## Comments

Nothing ground breaking in here. You can write either single line or multi line comments:

```
// an inline comment
/*
  I'm spanning multiple
  lines.
*/
```

## Package Manager

Pryst's package manager name is `grape`.

TODO: For example, `grape install time`

## Standard Library

TODO: The Standard Library is fully written in Pryst.

## TODO

- Add `Object` type
- Add support for `Class`
- Inheritance, Abstraction
- Try to make a function as an object. (With static-typing)
- Implement Packages
- Implement Imports
- Create a Package Manager.
- Make a Standard Library.

And more!

## Credits

Pryst was developed by `cliid`, a Junior Developer from South Korea.

`PRYST`: `Pryst Runs Yet Stable and Translucent`.

Pryst is published in the `MIT License`.
