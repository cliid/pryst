# Pryst Programming Language

A modern systems programming language that looks like C but won't segfault. Built with LLVM and ANTLR4.

## Features

- Strong static typing with type inference
- Memory safe with garbage collection
- No pointers, only references
- Built-in web framework
- Modern syntax with C-like familiarity
- UTF-8 string support
- Dynamic arrays and hash maps
- Comprehensive error handling

## Requirements

- LLVM 14.0.6
- ANTLR 4.13.1
- CMake 3.10 or higher
- C++17 compiler
- Boehm GC library
- cpp-httplib

## Building

```bash
# Install dependencies (Ubuntu)
sudo apt-get update
sudo apt-get install -y \
    llvm-14-dev \
    clang-14 \
    libantlr4-runtime-dev \
    antlr4 \
    cmake \
    libgc-dev \
    libcpp-httplib-dev

# Build the project
mkdir build
cd build
cmake ..
make

# Run tests
make test
```

## Usage

```bash
# Compile a Pryst source file
./pryst input.pst -o output

# Run the compiled program
./output
```

## Example

```pryst
import http;
import json;

class User {
    str name;
    int[] scores;

    User(str name) {
        this.name = name;
        this.scores = {};
    }

    float average() {
        if (scores.length() == 0) {
            return 0.0;
        }
        return scores.reduce((float a, int b) -> a + b, 0.0) / scores.length();
    }
}

int main() {
    Server server(8080);
    map<str,User> users = {};

    server.post("/user", (Request req, Response res) -> {
        json data = req.json()?;
        str name = data.name;

        if (users.has(name)) {
            res.status(400).json({
                "error": "User exists"
            });
            return;
        }

        users.set(name, User(name));
        res.json({"status": "ok"});
    });

    server.get("/users", (Request req, Response res) -> {
        json result = {};
        for (str name in users.keys()) {
            result[name] = {
                "scores": users.get(name)?.scores,
                "average": users.get(name)?.average()
            };
        }
        res.json(result);
    });

    print("Listening on 8080");
    server.listen();
}
```

## Language Features

### Types
- Basic: `int`, `float`, `bool`, `str`, `void`
- Compound: arrays `T[]`, maps `map<K,V>`
- User-defined classes

### Control Flow
- If-else statements
- While loops
- For loops (C-style and range-based)
- Try-catch error handling

### Functions
- Named functions
- Lambda expressions
- Method declarations
- Error propagation with `?` operator

### Memory Management
- Automatic garbage collection
- No explicit memory management
- No raw pointers
- Safe references

### Web Framework
- Built-in HTTP server
- JSON support
- Request/Response handling
- Static file serving

## License

MIT License

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request
