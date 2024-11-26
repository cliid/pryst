# Runtime Builtins Todo List

## Core Types and Functions
- [x] File (pryst::io)
  - [x] Constructor
  - [x] readToString
  - [x] writeAll
  - [x] close

- [x] Error (pryst::core)
  - [x] Constructor with message and code
  - [x] toString method
  - [x] getCode method
  - [x] getMessage method

- [x] String (pryst::core)
  - [x] length
  - [x] substring
  - [x] indexOf
  - [x] lastIndexOf
  - [x] replace
  - [x] split
  - [x] trim

- [x] Array (pryst::core)
  - [x] length
  - [x] push
  - [x] pop
  - [x] shift
  - [x] unshift
  - [x] indexOf
  - [x] slice
  - [x] join

- [x] Map (pryst::core)
  - [x] set
  - [x] get
  - [x] has
  - [x] delete
  - [x] clear
  - [x] keys
  - [x] values
  - [x] size

## IO Functions
- [ ] print (pryst::io)
- [ ] println (pryst::io)
- [ ] readLine (pryst::io)
- [ ] getChar (pryst::io)

## Web Framework
- [ ] Server (pryst::web)
  - [ ] Constructor
  - [ ] listen
  - [ ] get
  - [ ] post
  - [ ] put
  - [ ] delete
  - [ ] use

- [ ] Request (pryst::web)
  - [ ] getPath
  - [ ] getMethod
  - [ ] getHeaders
  - [ ] getBody
  - [ ] getQuery
  - [ ] getParams

- [ ] Response (pryst::web)
  - [ ] setStatus
  - [ ] setHeader
  - [ ] send
  - [ ] json
  - [ ] html

## Math Functions (pryst::math)
- [ ] abs
- [ ] ceil
- [ ] floor
- [ ] round
- [ ] max
- [ ] min
- [ ] pow
- [ ] sqrt
- [ ] random

## System Functions (pryst::sys)
- [ ] exit
- [ ] getEnv
- [ ] setEnv
- [ ] sleep
- [ ] time
- [ ] clock

Each builtin needs to be implemented as a proper class or function in the runtime system with:
1. LLVM IR generation
2. Extern "C" bindings
3. Registration in RuntimeRegistry
4. Proper error handling
5. Type safety
6. Memory management
7. Documentation
