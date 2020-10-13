<h1 align="center">Pryst Language</h1>
<h3 align="center">A static explicit language with beautiful syntax and a bit of sugar :)</h3>
<p align="center">
  <a href="https://ci.appveyor.com/project/cliid/pryst/branch/master">
    <img src="https://ci.appveyor.com/api/projects/status/github/pryst/pryst?branch=master&svg=true" />
  </a>
  <a href="https://travis-ci.com/github/pryst/pryst/builds">
    <img src="https://travis-ci.org/pryst/pryst.svg?branch=master" />
  </a>
  <a href="https://github.com/pryst/pryst/blob/master/LICENSE">
    <img alt="License: MIT" src="https://img.shields.io/badge/license-MIT-yellow.svg" target="_blank" />
  </a>
  <a href="https://codecov.io/gh/pryst/pryst">
    <img src="https://codecov.io/gh/pryst/pryst/branch/master/graph/badge.svg" />
  </a>
</p>

## Intro

Pryst is an explicit, strong, static typed language with a beautiful C-style syntax.

It features variables, types, if statements, switch statements, imports, classes and more! 

And most of all, Pryst is `currently in development` so there will be new features!

## Technologies

Technologies that makes Pryst happier:

<p align="center">
  <a href="https://www.graalvm.org/">
    <img src="https://www.graalvm.org/resources/img/home/logo-coloured.svg" />
  </a>
  <a href="https://www.antlr.org/">
    <img src="https://raw.githubusercontent.com/mike-lischke/vscode-antlr4/master/misc/antlr-logo.png" />
  </a>
</p>

### Technologies that Pryst can do:
#### JIT compilation (`./pryst`)
#### AOT compilation (`./native/prystnative`)
#### Debugger

## Pryst's Philosophy

#### `Static` is better than `Dynamic`.

#### `Explicit` is better than `Implicit`.

#### One's code should be readable by others. `No tricks like ol' C/C++`.

#### `Syntax` should be beautiful, no exceptions.

#### Most of all, `Code in a comfortable syntax.`

## Example Code

```
function printHello(str String)
{
  println("Hello " + String + "!");
  print("Hooray!\n");
}
function main()
{
  str myString = "cliid";
  printHello(myString);
}
```

## Table of Contents
- [Build from Source](#build-from-source)
  - [Prerequisites](#prerequisites)
  - [Build](#build)
- [Usage](#usage)
  - [Run a Source File](#run-a-source-file)
- [Constants](#constants)
  - [Compile Time Consts](#cptconst)
- [Variables](#variables)
  - [Int](#int)
  - [Float](#float)
  - [Double](#double)
  - [Boolean](#boolean)
  - [String](#string)
  - [Array](#array)
  - [Vector](#vector)
  - [Class](#class)
  - [Type Conversion](#type-conversion)
- [Data Types](#data-types)
  - [Int](#int)
  - [Float](#float)
  - [Double](#double)
  - [Boolean](#boolean)
  - [String](#string)
  - [Array](#array)
  - [Vector](#vector)
  - [Class](#class)
  - [Type Conversion](#type-conversion)
- [Operators](#operators)
  - [Shorthand Assignment](#shorthand-assignment)
- [Functions](#functions)
  - [Type Hinting](#type-hinting)
  - [Default Parameters](#default-parameters)
  - [Return Statement](#return-statement)
  - [Variadic](#variadic)
  - [Arrow Functions](#arrow-functions)
  - [Closures](#closures)
  - [Recursion](#recursion)
  - [Tricks](#tricks)
- [Conditionals](#conditionals)
  - [If](#if)
  - [Ternary Operator](#ternary-operator)
  - [Switch](#switch)
  - [Pattern Matching](#pattern-matching)
- [For Loop](#for-loop)
- [Range Operator](#range-operator)
- [Immutability](#immutability)
- [Modules](#modules)
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

After download, follow the instructions made by [GraalVM Docs](https://www.graalvm.org/docs/getting-started-with-graalvm/)

#### Install Maven

Follow the instructions made by [Baeldung](https://www.baeldung.com/install-maven-on-windows-linux-mac#:~:text=Installing%20Maven%20on%20Mac%20OS,%3A%20apache%2Dmaven%2D3.3.)

### Build

`git clone https://github.com/jitcijk/pryst.git`
`cd pryst`
`mvn package`

## Usage

### Run a source file

To run a Pryst source file on top of JVM, give it a relative/absolute path to the file.

`./pryst /path/to/your/pryst/code.pst (It's extension name is .pst)`

To run with native build:

`./native/prystnative /path/to/your/pryst/code.pst`

## Constants //TODO

Constants have the same traits as variables, except that they start with `let` and are immutable. Once declared, reassigning a constant will produce a runtime error. Even data structures are locked into immutability. Elements of an Array or Dictionary can't be added, updated or removed.

```
const string name = "Ben";
name = "John"; // runtime error
```

### Compile-time Constants //TODO

In Pryst, we have compile time constants named as const_cpt just works like C++'s constexpr.

For example,

```
const_cpt float PI = 3.141592;
print(PI.to_string());
```

And, yes, this won't work.

```
const_cpt int ANY_NUM = 13245453;
ANY_NUM = 1; // Compile Time Error
```

## Variables

Variable names have to start with an alphabetic character and continue either with alphanumeric, underscores.
For example:

```
int x; // OK
float var_whatever; // OK
double VaR_WHA332; // OK
bool _isOnClick; // OK
str[3] 3numbers; // NO
```

### Int

Unsigned integer variables in Pryst start with the keyword `int`.

```swift
int age = 40;
age = 41;
```

### Float

Double precision floating point variables in Pryst start with the keyword `float`.
No `double`.

```swift
float height = 183.82;
height = 177.13;
```

### Boolean

Boolean variables in Pryst start with the keyword `bool`.

```swift
bool x = true;
x = false;
if(x)
{
  print("x is true!");
}
else
{
  print("x is false!");
}
```

### String

String variables in Pryst start with the keyword `str`.

```swift
string str = "Hello";
print(str);
```

### Character //TODO

Characters in Pryst start with the keyword `char`.

```
char ch = 'A';
print(ch.toString()); // It prints "A"
```

### Array //TODO

Static size arrays in Pryst look like this: `type_name[array_size]`.

```swift
string[3] str_3_elems = ["Jack", "The", "Pillow"];
print(str_3_elems[1].index(1)); // It basically means the second character of the second elem of the string array.
// It prints 'h'
string[4][4] str_4by4_elems = [["A", "B", "C", "D"], ["E", "F", "G", "H"], ["I", "J", "K", "L"], ["M", "N", "O", "P"]];
print(str_4by4_elems[2][1]);
// It prints "J"
```

### Dynamic Array //TODO

Dynamic size arrays in Pryst look like this: `type_name[dynamic]`.

```swift
string str_elems[dynamic] = ["Jack", "The", "Pillow"];
print(str_elems[1].index(1)); // It basically means the second character of the second elem of the string vector.
// It prints "h"
str_elems = ["A", "B", "C", "D"];
print(str_elems[2]);
// It prints "C"
str_elems.add("E", 1); // It means 'add "E" after the second index'.
print(str_elems.toString()); // prints "["A", "B", "E", "C", "D"]"
str_elems.remove(3);
print(str_elems.toString()); // removes 4th index elem.
// prints "["A", "B", "E", "D"]"
```

### Private

The type or member can be accessed only by code in the same `class` or `struct`.

In Pryst, we call it `pv`.

### Public

The type or member can be accessed by any other code in the same assembly or another assembly that references it.

In Pryst, we call it `pb`.

### Protected

The type or member can be accessed only by code in the same `class`, or in a `class` that is derived from that `class`.

In Pryst, we call it `pt`.

### Class

Classes in Pryst look like this: `class class_name { constructor, your code }`.

```
class Complex
{
  pv int x_pv;
  pv int y_pv;
  pb Complex(int x_pb, int y_pb){ x_pv = x_pb; y_pv = y_pb; } // Constructor.
  pb real();
  pb imag();
}
pb Complex.real()
{
  return x_pv;
}
pb Complex.imag()
{
  return y_pv;
}
...and more code
```

## Data Types

Pryst currently supports 6 primitive data types: `int`, `float`, `bool`, `str`, `array`, `vector`
and 1 user defined type: `class`.

### Int

Integers are whole numbers that support most of the arithmetic and bitwise operators, as you'll see later. They can be represented also as: binary with the 0b prefix, hexadecimal with the 0x prefix and octal with the 0o prefix.

```swift
int dec = 27
int oct = 0o33
int hex = 0x1B
int bin = 0b11011
int arch = 2 ** 32
```

### Float

Floating point numbers are used in a very similar way to Integers. In fact, they can be mixed and matched, like `3 + 0.2` or `5.0 + 2`, where the result will always be a Float.

```swift
float pi = 3.14159265;
float e = 2.71828182;
```

Scientific notation is also supported via the `e` modifier:

```swift
float sci = 0.1e3;
float negsci = 25e-5;
```

### Bool

It would be strange if this data type included anything else except `true` and `false`.

```swift
bool mad = true;
bool genius = false;
```

Expressions like the `if/else`, won't check for values that aren't necessarily boolean.
You should use the built-in `.is_zero()` for integers and floats, and `.is_empty()` for lists, dictionarys.

### String

Strings are UTF-8 encoded, meaning that you can stuff in there anything, even emojis.

```
str weather = "Hot";
str price = "500円";
```

String concatenation is handled with the `+` operator. Concats between a string and another data type will result in a compile error.

```
str name = "Tony" + " " + "Stark";
```

Additionally, strings are treated as enumerables. They support subscripting and iteration in `for in` loops.

```
"howdy"[2]; // "w"
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
str names[] = ["Kirk", "Bones", "Spock"]
str first = names[0] // "Kirk"
str last = names[-1] // "Spock"
```

In the same style, an index can be used to check if it exists. It will return `null` if it doesn't:

```
if names[10]
  // handle it
end
```

Individual elements can be reassigned on mutable arrays:

```
int numbers[] = [5, 8, 10, 15]
numbers[1] = 7
```

Arrays can be compared with the `==` and `!=` operators, which will check the position and value of every element of both arrays. Equal arrays should have the same exact values in the same position.

They can also be combined with the `+` operator, which adds the element of the right side to the array on the left side.

```
let concat = ["an", "array"] + ["and", "another"]
// ["an", "array", "and", "another"]
```

### Dictionary

Dictionaries are hashes with a key and a value of any data type. They're good to hold unordered, structured data:

```swift
dict user = ["name" => "Dr. Unusual", "proffesion" => "Illusionist", "age" => 150]
```

Unlike arrays, internally their order is irrelevant, so you can't rely on index-based subscripting. They only support key-based subscripting:

```
user["name"] // "Dr. Unusual"
```

Values can be reassigned or inserted by key on mutable dictionaries:

```
var numbers = ["one" => 1, "two" => 2]
numbers["one"] = 5
numbers["three"] = 3 // new key:value
```

To check for a key's existence, you can access it as normal and check if it's `null` or truthy:

```
if user["location"] == null
  // do something
end
```

### Type Conversion


### Type Checking


## Operators


### Shorthand Assignment

## Functions

Pryst treats functions as first class, like any sane language should. It checks all the boxes: they can be passed to variables, as arguments to other functions, and as elements to data structures. They also support recursion, closures, currying, variadic parameters, you name it.

```swift
function x()
{
  println("Hello");
}
```

Parentheses are optional and for simple functions like the above, I'd omit them. Calling the function needs the parantheses though:

```swift
let sum = 1335 + 2;
```

### Type Hinting



### Default Parameters



### Return Statement


### Variadic



### Closures


### Recursion

Recursive functions calculate results by calling themselves. Although loops are probably easier to mentally visualize, recursion provides for some highly expressive and clean code. Technically, they build an intermediate stack and rewind it with the correct values in place when a finishing, non-recursive result is met. It's easier to understand them if you think of how they're executed. Let's see the classic factorial example:

```swift
let fac = func n
  if n == 0
    return 1
  end
  n * fac(n - 1)
end
```

Keep in mind that Pryst doesn't provide tail call optimization, as Go still doesn't support it. That would allow for more memory efficient recursion, especially when creating large stacks.

### Tricks

As first class, functions have their share of tricks. First, they can self-execute and return their result immediately:

```swift
let pow_2 = func x
  x ** 2
end(2)
```

Not sure how useful, but they can be passed as elements to data structures, like arrays and dictionaries:

```swift
let add = func x, y do x + y end
let list = [1, 2, add]
list[2](5, 7)
```

Finally, like you may have guessed from previous examples, they can be passed as parameters to other functions:

```swift
let add = func x, factor
  x + factor(x)
end
add(5, (x) -> x * 2)
```

## Conditionals

Pryst provides two types of conditional statements. The `if/else` is limited to just an `if` and/or `else` block, without support for multiple `else if` blocks. That's because it advocates the use of the much better looking and flexible `switch` statement.

### If

An `if/else` block looks pretty familiar:

```swift
if 1 == 2
  println("Not calling me.")
else
  println("1 isn't equal to 2. Duh!")
end
```

Sometimes it's useful to inline it for simple checks:

```swift
let married = true
let free_time = if married then 0 else 100_000_000 end
```

### Ternary Operator

The ternary operator `?:` is a short-hand `if/else`, mostly useful when declaring variables based on a condition or when passing function parameters. It's behaviour is exactly as that of an `if/else`.

```
int price = 100;
int offer = 120;
str status = offer > price ? "sold" : "bidding";
```

Although multiple ternary operators can be nested, I wouldn't say that would be the most readable code. Actually, except for simple checks, it generally makes for unreadable code.

### Switch

`Switch` expressions on the other hand are way more interesting. They can have multiple cases with multiple conditions that break automatically on each successful case, act as generic if/else, and match array elements.

```swift
int a = 5
switch (a){
  case 2, 3:
    println("Is it 2 or 3?");
  case 5:
    println("It is 5. Magic!");
  default:
    println("No idea, sorry.");
}
```

Not only that, but a `switch` can behave as a typical if/else when no control condition is provided. It basically becomes a `switch true`.

```swift
str a = "John";
switch() {
  case "John":
    println("John");
  case "Ben":
    println("Ben");
  default:
    println("Nobody");
}
```

### Pattern Matching


## For Loop

Pryst supports both the traditional, 3-parts `for` and a flexible `for in` loop that iterates arrays, dictionaries.

```
for(v in [1, 2, 3, 4]) {
  println(v);
}
```

With that power, you could build a function like `map` in no time:

```
function map(let x, let v)
  for(v in x){
    f(v);
  }
}
let plus_one = map([1, 2, 3, 4], (x) -> x + 1);
println(plus_one); // [2, 3, 4, 5]
```

Without arguments, the `for` loop can behave as an infinite loop, much like a traditional `while`. Although there's not too many usecases, it does its job when needed. An example would be prompting the user for input and only breaking the infinite loop on a specific text.

```
for( ; ; ;)
{
  str pass = prompt("Enter the password: ");
  if(pass == "123"){
    println("Good, strong password!");
    break;
  }
}
```

The `break` and `continue` keywords, well break or skip the iteration. They function exactly like you're used to.

```
for(i in 1..10){
  if(i == 5){
    continue;
  }
}
```

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

## Standard Library

The Standard Library is fully written in Pryst.

## TODO

- Make a Standard Library.

## Credits

Pryst was developed by cliid, a Junior Developer from South Korea.

Pryst is published in MIT License.
