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

Pryst is an explicit, weak, static typed, Rust-like language with a beautiful syntax.

It features variables, types, if and elif/else, switch statements, imports, classes and more! And most of all, Pryst is currently in development so there will be new features!

## Pryst's Philosophy

### Static is better than Dynamic.

### Explicit is better than Implicit.

### One's code should be readable by others. No tricks like ol' C/C++.

### Syntax should be beautiful, no exceptions.

### Most of all, "Write once, Read forever"

## Example Code

```
use unsafe; // Just because of the char** argv part. Basically, you don't need that if you don't want console args.

import io;

int main(int argc, char** argv){
  int x = 3;
  string str = "Hello";
  string str2 = " World";
  string[] str_arr = {"Hello", "World"};
  print(x.to_string());
  print(str + str2);
  print(str_arr[0] + " " + str_arr[1]);
  return 0;
}
```

## Table of Contents

- [Usage](#usage)
  - [Run a Source File](#run-a-source-file)
  - [REPL](#repl)
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

## Usage

### Run a source file //TODO

To run an Pryst source file, give it a relative/absolute path to the file.

```
pryst /path/to/your/pryst/code.pst (It's extension name is .pst)
```

### REPL //TODO

As any serious language, Pryst provides a REPL too:

```
pryst repl
```

## Constants //TODO

Constants have the same traits as variables, except that they start with `let` and are immutable. Once declared, reassigning a constant will produce a runtime error. Even data structures are locked into immutability. Elements of an Array or Dictionary can't be added, updated or removed.

```swift
const string name = "Ben";
name = "John"; // runtime error
```

### Compile-time Constants //TODO

In Pryst, we have compile time constants named as const_cpt just works like C++'s constexpr.

For example,

```swift
const_cpt float PI = 3.141592;

print(PI.to_string());
```

And, yes, this won't work.

```swift
const_cpt int ANY_NUM = 13245453;

ANY_NUM = 1; // Compile Time Error
```

## Variables //TODO

Variable names have to start with an alphabetic character and continue either with alphanumeric, underscores.
For example:

```swift
int x; // OK
float var_whatever; // OK
double VaR_WHA332; // OK
bool _is_on_click; // OK
string[3] 3numbers; // NO
```

### Int //TODO

Unsigned integer variables in Pryst start with the keyword `int`.

```swift
int age = 40;
age = 41;
```

### Float //TODO

Double precision floating point variables in Pryst start with the keyword `float`.
No `double`.

```swift
float height = 183.82;
height = 177.13;
```

### Boolean //TODO

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

### String //TODO

String variables in Pryst start with the keyword `string`.

```swift
string str = "Hello";
print(str);
```

### Character //TODO

Characters in Pryst start with the keyword `char`.
But don't use char[] as a string, it's not recommended in Pryst.

```swift
char ch = 'A';
print(ch.to_string()); // It prints "A"
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

Pryst currently supports 6 primitive data types: `int`, `float`, `bool`, `string`, `array`
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

```swift
string weather = "Hot";
string price = "500円";
```

String concatenation is handled with the `+` operator. Concats between a string and another data type will result in a compile error.

```swift
string name = "Tony" + " " + "Stark";
```

Additionally, strings are treated as enumerables. They support subscripting and iteration in `for in` loops.

```swift
"howdy"[2]; // "w"
```

Escape sequences are there too if you need them: `\"`, `\n`, `\t`, `\r`, `\a`, `\b`, `\f` and `\v`. Nothing changes from other languages, so I'm sure you can figure out by yourself what every one of them does.

```swift
string code = "if(name == \"ben\"){\n\tprint(10);\n};";
```

### Array

Arrays are ordered collections of a specific data type. You can't mix and match strings with integers, or floats with other arrays.

```swift
string[] names = ["John", "Ben"];

string john = names[0];
```

Individual array elements can be accessed via subscripting with a 0-based index:

```swift
string[] names = ["Kirk", "Bones", "Spock"]
string first = names[0] // "Kirk"
string last = names[-1] // "Spock"
```

In the same style, an index can be used to check if it exists. It will return `nil` if it doesn't:

```swift
if names[10]
  // handle it
end
```

Individual elements can be reassigned on mutable arrays:

```swift
var numbers = [5, 8, 10, 15]
numbers[1] = 7
```

Arrays can be compared with the `==` and `!=` operators, which will check the position and value of every element of both arrays. Equal arrays should have the same exact values in the same position.

They can also be combined with the `+` operator, which adds the element of the right side to the array on the left side.

```swift
let concat = ["an", "array"] + ["and", "another"]
// ["an", "array", "and", "another"]
```

Oh and if you're that lazy, you can ommit commas too:

```swift
let nocomma = [5 7 9 "Hi"]
```

### Dictionary

Dictionaries are hashes with a key and a value of any data type. They're good to hold unordered, structured data:

```swift
let user = ["name" => "Dr. Unusual", "proffesion" => "Illusionist", "age" => 150]
```

I'd argue that using Atoms for keys would make them look cleaner:

```swift
let user = [:name => "Dr. Unusual", :proffesion => "Illusionist", :age => 150]
```

Unlike arrays, internally their order is irrelevant, so you can't rely on index-based subscripting. They only support key-based subscripting:

```swift
user["name"] // "Dr. Unusual"
```

Values can be reassigned or inserted by key on mutable dictionaries:

```swift
var numbers = ["one" => 1, "two" => 2]
numbers["one"] = 5
numbers["three"] = 3 // new key:value
```

To check for a key's existence, you can access it as normal and check if it's `nil` or truthy:

```swift
if user["location"] == nil
  // do smth
end
```

### Type Conversion

Converting between types is handled in a few ways that produce exactly the same results. The `as` operator is probably the more convenient and more expressive of the bunch. Like all type conversion methods, it can convert to `String`, `Int`, `Float` and `Array`:

```swift
let nr = 10
nr as String
nr as Int
nr as Float
nr as Array
```

Provided by the runtime are the appropriately named functions: `String()`, `Int()`, `Float()` and `Array()`.

```swift
let str = String(10)
let int = Int("10")
let fl = Float(10)
let arr = Array(10)
```

The `Type` module of the Standard Library provides interfaces to those same functions and even adds some more, like `Type.of()` and `Type.isNumber()`.

```swift
let str = Type.
(10)
let int = Type.toInt("10")
let fl = Type.toFloat(10)
let arr = Type.toArray(10)
```

Which method you choose to use is strictly preferential and depends on your background.

### Type Checking

There will be more than one occassion where you'll need to type check a variable. Pryst provides a few ways to achieve that.

The `is` operator is specialized in checking types and should be the one you'll want to use practically everywhere.

```swift
let nr = 10
if nr is Int
  println("Yes, an integer")
end
```

There's also the `typeof()` runtime function and `Type.of()` from the Standard Library. They essentially do the same thing, but not only they're longer to write, but return strings. The above would be equivalent to:

```swift
if Type.of(nr) == "Int"
  println("Yes, an integer")
end
```

## Operators

You can't expect to run some calculations without a good batch of operators, right? Well, Pryst has a range of arithmetic, boolean and bitwise operators to match your needs.

By order of precedence:

```C++
Boolean: && || (AND, OR)
Bitwise: & | ~ (Bitwise AND, OR, NOT)
Equality: == != (Equal, Not equal)
Comparison: < <= > >=
Bitshift: << >> (Bitshift left and right)
Arithmetic: + - * / % ** (addition, substraction, multiplication, division, modulo, power)
```

Arithmetic expressions can be safely used for Integers and Floats:

```C++
1 + 2 * 3 / 4.2
2 ** 8
3 % 2 * (5 - 3)
```

Addition can be used to concatenate Strings or combine Arrays and Dictionaries:

```C++
"Whoam" + " " + "I"
[1, 2] + [3, 4]
["a" => 1, "b" => 2] + ["c" => 3]
```

Comparison operators can compare Integers and Float by exact value, Strings, Arrays and Dictionaries by length:

```swift
5 > 2
3.2 <= 4.5
"one" < "three"
[1, 2] > [5]
["a" => 1] < ["b" => 2, "c" => 3]
```

Equality and inequality can be used for most data types. Integers, Floats and Booleans will be compared by exact value, Strings by comparing each index, Arrays by the value and position of the elements, and Dictionaries by the the combination of key and value.

```C++
1 != 4
1.0 != 2.5
true == true
"one" == "three"
[1, 2, 3] != [1, 2]
["a" => 1, "b" => 2] != ["a" => 5, "b" => 6]
```

Boolean operators can only be used with Boolean values, namely `true` or `false`. Other data types will not be converted to truthy values.

```C++
true == true
false != true
```

Bitwise and bitshift operator apply only to Integers. Float values can't be used, even those that "look" as Integers, like `1.0` or `5.0`.

```C++
10 >> 1
12 & 5 | 3
5 ~ 2
```

### Shorthand Assignment

Operators like `+`, `-`, `*` and `/` support shorthand assignment to variables. Basically, statements like this:

```C++
count = count + 1
```

Can be expressed as:

```C++
count += 1
```

## Functions

Pryst treats functions as first class, like any sane language should. It checks all the boxes: they can be passed to variables, as arguments to other functions, and as elements to data structures. They also support recursion, closures, currying, variadic parameters, you name it.

```swift
let add = func x, y
  x + y
end
```

Parantheses are optional and for simple functions like the above, I'd omit them. Calling the function needs the parantheses though:

```swift
let sum = add(1335, 2)
```

### Type Hinting

Like in strong typed languages, type hinting can be a very useful feature to validate function arguments and its return type. It's extra useful for library functions that have no assurance of the data types they're going to get.

This function call will produce output:

```swift
let add = func (x: Int, y: Int) -> Int
  x + y
end
println(add(5, 2))
```

This however, will cause a type missmatch runtime error:

```swift
println(add(5, "two"))
```

Pryst is not a strong typed language, so type hinting is completely optional. Generally, it's a good idea to use it as a validation measure. Once you enforce a certain type, you'll be sure of how the function executes.

### Default Parameters

Function parameters can have default values, used when the parameters are omitted from function calls.

```swift
let architecture = func bits = 6
  2 ** bits
end

architecture() // 64
architecture(4) // 16
```

They can be combined with type hinting and, obviously, need to be of the same declared type.

```swift
let architecture = func bits: Int = 6
  2 ** bits
end
```

### Return Statement

Until now we haven't seen a single `return` statement. Functions are expressions, so the last line is considered its return value. In most cases, especially with small functions, you don't have to bother. However, there are scenarios with multiple return points that need to explicitly tell the interpreter.

```swift
let even = func n
  if n % 2 == 0
    return true
  end
  false
end
```

The last statement doesn't need a `return`, as it's the last line and will be automatically inferred. With the `if` on the other hand, the interpreter can't understand the intention, as it's just another expression. It needs the explicit `return` to stop the other statements from being interpreted.

In the case of multiple return points, I'd advise to always use `return`, no matter if it's the first or last statement. It will make for clearer intentions.

### Variadic

Variadic functions take an indefinite number of parameters and merge them all into a single, Array argument. Their first use would be as a sugar:

```swift
let add = func ...nums
  var count = 0
  for n in nums
    count = count + n
  end
  count
end

add(1, 2, 3, 4, 5) // 10
```

Even better, they can be used for functions that respond differently based on the number of arguments:

```swift
let structure = func ...args
  if Enum.size(args) == 2
    let key = args[0]
    let val = args[1]
    return [key: val]
  end
  if Enum.size(args) > 2
    return args
  end
  args[0]
end

structure("name", "John") // dictionary
structure(1, 2, 3) // array
structure(5) // integer
```

Functions may have as many parameters as needed, as long the variadic argument is the last parameter:

```swift
let calc = func mult, ...nums
  mult * Enum.reduce(nums, 0, func x, acc do x + acc end)
end
calc(10, 1, 2, 3, 4) // 100
```

Variadic arguments can even have default values:

```swift
let join = func (glue: String, ...words = ["hello", "there"])
  String.join(words, glue)
end

join(" ") // "hello there"
```

### Arrow Functions

Very useful when passing short functions as arguments, arrow functions provide a very clean syntax. They're handled internally exactly like normal functions. The only difference is that they're meant as a single line of code, while normal functions can handle blocks.

This normal function:

```swift
let sub = func x
  x - 5
end
```

Is equivalent to:

```swift
let sub = (x) -> x - 5
```

They're not that useful to just spare a couple lines of code. They shine when passed as arguments:

```swift
Enum.map([1, 2, 3, 4], (x) -> x * 2)
Enum.reduce(1..10, 0, (x, acc) -> x + acc)
```

### Closures

Closures are functions inside functions that hold on to values from the parent and "close" them when executed. This allows for some interesting side effects, like currying:

```swift
let add = func x
  func y
    x + y
  end
end

add(5)(7) // 12
```

Some would prefer a more explicit way of calling:

```swift
let add_5 = add(5) // returns a function
let add_5_7 = add_5(7) // 12
```

You could nest a virtually unlimited amount of functions inside other functions, and all of them will have the scope of the parents.

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

```swift
let price = 100
let offer = 120
let status = offer > price ? "sold" : "bidding"
```

Although multiple ternary operators can be nested, I wouldn't say that would be the most readable code. Actually, except for simple checks, it generally makes for unreadable code.

### Switch

`Switch` expressions on the other hand are way more interesting. They can have multiple cases with multiple conditions that break automatically on each successful case, act as generic if/else, and match array elements.

```swift
let a = 5
switch a
case 2, 3
  println("Is it 2 or 3?")
case 5
  println("It is 5. Magic!")
default
  println("No idea, sorry.")
end
```

Not only that, but a `switch` can behave as a typical if/else when no control condition is provided. It basically becomes a `switch true`.

```swift
let a = "John"
switch
case a == "John"
  println("John")
case a == "Ben"
  println("Ben")
default
  println("Nobody")
end
```

### Pattern Matching

When fed arrays as the control condition, the `switch` can pattern match its elements. Every argument to the switch case is compared to the respective element of the array. Off course, for a match, the number of arguments should match the size of the array.

```swift
switch ["game", "of", "thrones"]
case "game", "thrones"
  println("no match")
case "game", "of", "thrones"
  println("yep!")
end
```

That's probably useful from time to time, but it's totally achievable with array cases. The `switch` can do much better than that.

```swift
switch ["John", "Lick", 2]
case "John", _, _
  println("John Something")
case _, _ 2
  println("Something 2")
default
  println("Lame movie pun not found")
end
```

The `_` is a placeholder that will match any type and value. That makes it powerful to compare arrays where you don't need to know every element. You can mix and match values with placeholders in any position, as long as they match the size of the array.

## For Loop

Pryst takes a modern approach to the `for` loop, evading from the traditional, 3-parts `for` we've been using for decades. Instead, it focuses on a flexible `for in` loop that iterates arrays, dictionaries, and as you'll see later, ranges.

```swift
for v in [1, 2, 3, 4]
  println(v)
end
```

Obviously, the result of the loop can be passed to a variable, and that's what makes them interesting to manipulate enumerables.

```swift
let plus_one = for v in [1, 2, 3, 4]
  v + 1
end
println(plus_one) // [2, 3, 4, 5]
```

Passing two arguments for arrays or strings will return the current index and value. For dictionaries, the first argument will be the key.

```swift
for i, v in "abcd"
  println(i + "=>" + v)
end
```

```swift
for k, v in ["name" => "John", "age" => 40]
  println(k)
  println(v)
end
```

With that power, you could build a function like `map` in no time:

```swift
let map = func x, f
  for v in x
    f(v)
  end
end

let plus_one = map([1, 2, 3, 4], (x) -> x + 1)

println(plus_one) // [2, 3, 4, 5]
```

Without arguments, the `for` loop can behave as an infite loop, much like a traditional `while`. Although there's not too many usecases, it does its job when needed. An example would be prompting the user for input and only breaking the infinite loop on a specific text.

```swift
for
  let pass = prompt("Enter the password: ")
  if pass == "123"
    println("Good, strong password!")
    break
  end
end
```

The `break` and `continue` keywords, well break or skip the iteration. They function exactly like you're used to.

```swift
for i in 1..10
  if i == 5
    continue
  end
end
```

_The `for` loop is currently naively parsed. It works for most cases, but still, it's not robust enough. I'm working to find a better solution._

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

Pryst was developed by cliid, a Full Stack Developer from South Korea.

Pryst is published in MIT License.
