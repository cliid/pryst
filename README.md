# Pryst Programming Language

A statically-typed, object-oriented language inspired by TypeScript and C++, designed to work *with* developers, emphasizing simplicity, clarity, and efficiency.

## Philosophy

Pryst is a no-ego language where every feature exists to empower users to focus on *what* they're building, not *how* they're building it.

## Features

### Basic Types and Variables
- Basic types: `int`, `float`, `bool`, `str`, `void`
- Arrays and generics for collections
- Custom types and structs
- Declaration keywords:
  - `let`: Standard variable with type inference
  - `const`: Immutable variable with type inference
  - `const!`: Compile-time constant
- Automatic type inference wherever possible

### Functions
Functions are first-class citizens with three declaration styles:
```pryst
// Standard function with parameter types
fn function(int x, float y) {
    return x + y;
}

// Anonymous functions with type parameters
let f = fn<int> (int x, float y) {
    return x * y;
};

// Classic C-style with explicit return type
int function() {
    return 42;
}

// Async functions
async fn fetchData() -> json {
    return await http.get("api/data");
}
```

### Control Structures
- `if-else` statements
- `while` loops
- `for` loops
- Built-in `async`/`await`

### Object-Oriented Features
- Classes and inheritance
- Method overriding
- Encapsulation
- Polymorphism

### Memory Management
- Scope-based management
- Optional garbage collection
- `embed` keyword for raw C code
- Automatic cleanup at scope end

### String and Character Handling
```pryst
// Half-open range slicing
str s = "Hello, World!";
str slice = s[0:5];  // "Hello"

// Character conversion
str ch = char(65);   // "A"
if (ch == 'A') {     // Single and double quotes are interchangeable
    print("Match!");
}
```

### Package Management
```pryst
// Simple imports
import pryst::server;
import pryst::web;
import jwt;

// CLI package management
// pryst grab package
// pryst grab package --exact
```

### Web and Networking
```pryst
// Static site generation
import pryst::web;

fn main() {
    web::create("output/");
    web::page("index.md", "output/index.html");
    web::build();
}

// Backend server
import pryst::server;

fn main() {
    let server = server::create(8080);

    server.route("/", fn() -> str {
        return "Hello, Pryst!";
    });

    server.route("/data", async fn() -> json {
        return fetch_data();
    });

    server.listen();
}

// JWT Authentication
import jwt;

fn main() {
    let token = jwt::sign({"user_id": 1234}, "secret_key");
    let decoded = jwt::verify(token, "secret_key");
}
```

## Tech Stack

- Developed in C/C++
- ANTLR4 for lexing/parsing
- LLVM 20.0.0 for code generation and optimization
- CMake >= 3.13 for build management

## Key Components

- `Pryst.g4`: ANTLR4 grammar
- `semantic_analyzer.cpp`: AST analysis
- `llvm_codegen.cpp`: LLVM IR generation
- `jit_compiler.cpp`: JIT compilation
- `aot_compiler.cpp`: AOT compilation

## Build Instructions

### Prerequisites Installation

#### Ubuntu/Debian

1. Install LLVM 20.0.0 and related packages:
```bash
# Add LLVM repository
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 20

# Install LLVM packages
sudo apt-get install -y \
    llvm-20 \
    llvm-20-dev \
    clang-20 \
    lld-20 \
    libllvm-20-ocaml-dev \
    libllvm20 \
    llvm-20-doc \
    llvm-20-examples \
    llvm-20-runtime

# Add LLVM to PATH
echo 'export PATH="/usr/lib/llvm-20/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

2. Install ANTLR4 4.13.2:
```bash
# Install Java (required for ANTLR)
sudo apt-get install -y default-jdk maven

# Download and install ANTLR
cd /usr/local/lib
sudo curl -O https://www.antlr.org/download/antlr-4.13.2-complete.jar

# Set up environment variables
echo 'export CLASSPATH=".:/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH"' >> ~/.bashrc
echo 'alias antlr4="java -jar /usr/local/lib/antlr-4.13.2-complete.jar"' >> ~/.bashrc
echo 'alias grun="java org.antlr.v4.gui.TestRig"' >> ~/.bashrc
source ~/.bashrc

# Install ANTLR4 C++ runtime
git clone --depth 1 --branch 4.13.2 https://github.com/antlr/antlr4.git
cd antlr4/runtime/Cpp
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

3. Install CMake and build tools:
```bash
sudo apt-get install -y cmake build-essential
```

#### macOS

1. Install LLVM and dependencies using Homebrew:
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install LLVM and other dependencies
brew install \
    llvm@20 \
    cmake \
    antlr4-cpp-runtime \
    java

# Add LLVM to PATH
echo 'export PATH="/usr/local/opt/llvm@20/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

2. Set up ANTLR4:
```bash
# Download ANTLR
sudo mkdir -p /usr/local/lib
cd /usr/local/lib
sudo curl -O https://www.antlr.org/download/antlr-4.13.2-complete.jar

# Set up environment variables
echo 'export CLASSPATH=".:/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH"' >> ~/.zshrc
echo 'alias antlr4="java -jar /usr/local/lib/antlr-4.13.2-complete.jar"' >> ~/.zshrc
echo 'alias grun="java org.antlr.v4.gui.TestRig"' >> ~/.zshrc
source ~/.zshrc
```

### Verify Installation
```bash
# Verify LLVM
clang --version  # Should show version 20.0.0
llvm-config --version  # Should show 20.0.0

# Verify CMake
cmake --version  # Should be >= 3.13

# Verify ANTLR
java -jar /usr/local/lib/antlr-4.13.2-complete.jar  # Should show ANTLR version
```

### Building Pryst
```bash
# Clone the repository
git clone https://github.com/cliid/pryst.git
cd pryst

# Create build directory and build
mkdir build && cd build
cmake ..
make -j$(nproc)  # Use number of available CPU cores
```

## Usage

```bash
./pryst path/to/program.pst
```

## Development Tools

### Code Formatting
```bash
pryst fmt                # Format current directory
pryst fmt file.pst      # Format specific file
```

### Language Server
- Real-time error checking
- Type information
- Diagnostics
- VSCode extension support

## Development Status

Work in progress:
- Standard library expansion
- Advanced OOP features
- Optimization improvements
- Module system enhancements
- WASM support implementation

## Contributing

Contributions welcome! Feel free to open issues or submit PRs.

## Acknowledgments

Built with ANTLR4 and LLVM.
