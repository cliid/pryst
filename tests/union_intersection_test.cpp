#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include "../src/type_checker.hpp"
#include "../src/type_registry.hpp"
#include "../src/error.hpp"
#include "../src/PrystLexer.h"
#include "../src/PrystParser.h"

using namespace pryst::core;
using namespace antlr4;

class UnionIntersectionTypeTest : public ::testing::Test {
protected:
    llvm::LLVMContext context;
    TypeRegistry typeRegistry;
    TypeChecker typeChecker;

    UnionIntersectionTypeTest()
        : typeRegistry(context),
          typeChecker(typeRegistry) {
        // Register basic types
        auto intType = std::make_shared<BasicType>(TypeKind::Int);
        auto strType = std::make_shared<BasicType>(TypeKind::String);
        auto printableType = std::make_shared<InterfaceType>("Printable");

        typeRegistry.cacheType("int", intType);
        typeRegistry.cacheType("str", strType);
        typeRegistry.registerInterfaceType(printableType);
    }

    std::shared_ptr<PrystParser::ProgramContext> parseCode(const std::string& code) {
        ANTLRInputStream input(code);
        PrystLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        PrystParser parser(&tokens);
        return std::make_shared<PrystParser::ProgramContext>(parser.program());
    }
};

TEST_F(UnionIntersectionTypeTest, BasicUnionType) {
    auto intType = typeRegistry.getCachedType("int");
    auto strType = typeRegistry.getCachedType("str");

    std::vector<std::shared_ptr<Type>> types = {intType, strType};
    auto unionType = std::make_shared<UnionType>(types);

    EXPECT_TRUE(unionType->satisfiesConstraint(intType));
    EXPECT_TRUE(unionType->satisfiesConstraint(strType));
    EXPECT_FALSE(unionType->satisfiesConstraint(std::make_shared<BasicType>(TypeKind::Float)));
}

TEST_F(UnionIntersectionTypeTest, BasicIntersectionType) {
    auto intType = typeRegistry.getCachedType("int");
    auto printableType = std::make_shared<InterfaceType>("Printable");

    std::vector<std::shared_ptr<Type>> types = {intType, printableType};
    auto intersectionType = std::make_shared<IntersectionType>(types);

    auto testType = std::make_shared<ClassType>("PrintableInt");
    typeRegistry.registerInterfaceImplementation("PrintableInt", "Printable");

    EXPECT_TRUE(intersectionType->satisfiesConstraint(testType));
    EXPECT_FALSE(intersectionType->satisfiesConstraint(intType));
}

TEST_F(UnionIntersectionTypeTest, NullableUnionType) {
    auto intType = typeRegistry.getCachedType("int");
    auto strType = typeRegistry.getCachedType("str");

    std::vector<std::shared_ptr<Type>> types = {intType, strType};
    auto unionType = std::make_shared<UnionType>(types);
    auto nullableUnionType = std::make_shared<NullableType>(unionType);

    EXPECT_TRUE(nullableUnionType->isNullable());
    EXPECT_TRUE(nullableUnionType->getBaseType()->isUnion());
    EXPECT_TRUE(nullableUnionType->satisfiesConstraint(intType));
    EXPECT_TRUE(nullableUnionType->satisfiesConstraint(strType));
}

TEST_F(UnionIntersectionTypeTest, MixinTypes) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }
        interface Comparable { int compare(T other); }

        // Using intersection types as mixins
        class Data : Printable & Serializable & Comparable {
            void print() {}
            str serialize() { return "data"; }
            int compare(T other) { return 0; }
        }

        // Type inference with mixins
        fn process<T : Printable & Comparable>(obj: T) {
            obj.print();
            obj.compare(obj);
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, DiscriminatedUnions) {
    const char* code = R"(
        class Success {
            str kind = "success";
            int value;
        }

        class Error {
            str kind = "error";
            str message;
        }

        // Using discriminated unions
        fn process(result: Success | Error) {
            match (result.kind) {
                case "success": {
                    let x: Success = result;  // Type narrowed to Success
                    let value: int = x.value;
                }
                case "error": {
                    let x: Error = result;  // Type narrowed to Error
                    let msg: str = x.message;
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, VariadicTemplates) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        // Variadic template with union types
        class Tuple<...T> {
            void forEach(fn(T) -> void... handlers) {
                // Implementation
            }
        }

        // Using variadic template with union and intersection types
        let t = new Tuple<int | str, Printable & Serializable>();
        t.forEach(
            (int | str x) -> { /* handle first */ },
            (Printable & Serializable x) -> { x.print(); }
        );
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, ParseIntersectionType) {
    const char* code = R"(
        interface Printable {
            void print();
        }

        class Number : Printable {
            void print() {}
        }

        let x: int & Printable = new Number();
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, ComplexTypeNarrowing) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        class Data : Printable & Serializable {
            void print() {}
            str serialize() { return "data"; }
        }

        let value: (int | str) & Printable = new Data();

        if (typeof(value) == int) {
            let x: int & Printable = value;  // Valid after narrowing
        } else if (typeof(value) == str) {
            let y: str & Printable = value;  // Valid after narrowing
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, ComplexErrorHandling) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        // Error: Cannot create intersection of incompatible types
        let x: int & str = 42;

        // Error: Cannot assign incompatible union type
        let y: int | Printable = "hello";

        // Error: Cannot satisfy multiple interface constraints
        class Invalid : Printable & int {
            void print() {}
        }
    )";

    auto ast = parseCode(code);
    EXPECT_THROW(typeChecker.visit(ast), TypeError);
}

TEST_F(UnionIntersectionTypeTest, ComplexTypeInference) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        class A : Printable & Serializable {
            void print() {}
            str serialize() { return "A"; }
        }

        class B : Printable {
            void print() {}
        }

        // Complex type inference scenarios
        let x = condition ? new A() : new B();  // Should infer Printable
        let y = [new A(), new B()];  // Should infer Printable[]
        let z = condition ? 42 : (condition ? "str" : new A());  // Should infer int | str | A
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, GenericTypeConstraints) {
    const char* code = R"(
        interface Printable {
            void print();
        }
        interface Serializable {
            str serialize();
        }

        // Generic class with intersection type constraint
        class Container<T : Printable & Serializable> {
            T value;
            void process() {
                value.print();
                value.serialize();
            }
        }

        // Generic function with union type constraint
        fn process<T : int | str>(value: T) {
            match (value) {
                case int i: { /* handle int */ }
                case str s: { /* handle str */ }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, PatternMatching) {
    const char* code = R"(
        let value: int | str = 42;

        match (value) {
            case int i: {
                let x: int = i;  // Type narrowing in pattern match
            }
            case str s: {
                let y: str = s;  // Type narrowing in pattern match
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, TypeAliases) {
    const char* code = R"(
        interface Printable {
            void print();
        }
        interface Serializable {
            str serialize();
        }

        // Type alias for union type
        type StringOrInt = str | int;

        // Type alias for intersection type
        type PrintableSerializable = Printable & Serializable;

        // Using type aliases
        let x: StringOrInt = 42;
        let y: PrintableSerializable = new (class : Printable & Serializable {
            void print() {}
            str serialize() { return "data"; }
        });
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, FunctionTypes) {
    const char* code = R"(
        interface Printable {
            void print();
        }

        // Function accepting union type
        fn process(x: int | str) -> void {}

        // Function returning union type
        fn getValue() -> int | str { return 42; }

        // Function with intersection type parameter
        fn printValue(x: int & Printable) {
            x.print();
        }

        // Function type as union member
        type Handler = fn(int) -> void | fn(str) -> void;
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, ArrayTypes) {
    const char* code = R"(
        interface Printable {
            void print();
        }

        class PrintableInt : Printable {
            void print() {}
        }

        // Array of union types
        let arr1: (int | str)[] = [42, "hello"];

        // Array of intersection types
        let arr2: (int & Printable)[] = [new PrintableInt()];

        // Union of array types
        let arr3: int[] | str[] = [1, 2, 3];
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, MethodOverloading) {
    const char* code = R"(
        interface Printable {
            void print();
        }

        class Processor {
            void process(int x) {}
            void process(str x) {}
            void process(Printable x) { x.print(); }

            void handleValue(int | str value) {
                process(value);  // Should resolve to correct overload based on runtime type
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, TypeConversionAndAssignability) {
    const char* code = R"(
        interface Printable {
            void print();
        }
        interface Serializable {
            str serialize();
        }

        class Data : Printable & Serializable {
            void print() {}
            str serialize() { return "data"; }
        }

        // Test assignability
        let x: Printable = new Data();  // Intersection type assignable to component
        let y: Printable | Serializable = x;  // Component type assignable to union
        let z: Data = new Data();
        let w: Printable & Serializable = z;  // Class type assignable to intersection
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, TypeInference) {
    const char* code = R"(
        interface Printable {
            void print();
        }
        class PrintableInt : Printable {
            void print() {}
        }

        // Type inference with union types
        let x = condition ? 42 : "hello";  // Should infer int | str

        // Type inference with intersection types
        let y = new PrintableInt();  // Should infer PrintableInt & Printable
        y.print();
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, RecursiveTypes) {
    const char* code = R"(
        class Node {
            int value;
            Node? | null next;  // Recursive type definition
        }

        let head: Node | null = new Node();
        head.next = null;
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, GenericConstraints) {
    const char* code = R"(
        interface Comparable {
            int compare(T other);
        }

        class Box<T : Comparable & Printable> {
            T value;
            void sort(Box<T> other) {
                value.compare(other.value);
                value.print();
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, IntersectionMethodAccess) {
    const char* code = R"(
        interface Printable {
            void print();
        }
        interface Serializable {
            str serialize();
        }

        class Data : Printable & Serializable {
            void print() {}
            str serialize() { return "data"; }
        }

        let x: Printable & Serializable = new Data();
        x.print();
        x.serialize();
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, InvalidTypeCompositions) {
    const char* invalidUnion = R"(
        // Cannot union with void type
        let x: int | void = 42;
    )";

    const char* invalidIntersection = R"(
        // Cannot intersect incompatible types
        let x: int & str = 42;
    )";

    auto ast1 = parseCode(invalidUnion);
    EXPECT_THROW(typeChecker.visit(ast1), Error);

    auto ast2 = parseCode(invalidIntersection);
    EXPECT_THROW(typeChecker.visit(ast2), Error);
}

TEST_F(UnionIntersectionTypeTest, TypeNarrowing) {
    const char* code = R"(
        let x: int | str = 42;
        if (typeof(x) == int) {
            let y: int = x;  // Should work after type narrowing
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, PerformanceStressTest) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        // Complex nested type combinations
        type ComplexType = ((int & Printable) | (str & Serializable)) &
                         Container<(float & Printable) | (bool & Serializable)>;

        // Stress test type resolution
        fn process<T : ComplexType>(x: T) {
            match (typeof(x)) {
                case int & Printable: { x.print(); }
                case str & Serializable: { x.serialize(); }
            }
        }

        // Test deep type nesting
        class DeepNested<T : Container<U & (Printable | Serializable)>,
                        U : Container<V & Printable>,
                        V : int | str> {
            T container;
            void processContents() {
                let val = container.get();
                match (typeof(val)) {
                    case int: { val.print(); }
                    case str: { val.print(); }
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, EdgeCases) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        // Edge case: Empty intersection with union
        type EmptyIntersection = (int & str) | Printable;

        // Edge case: Self-referential type with union
        class Node<T : Printable | Serializable> {
            T value;
            Node<T>? next;
        }

        // Edge case: Constraint satisfaction with complex bounds
        fn validate<T : (int & Printable) | (str & Serializable)>(x: T) {
            match (typeof(x)) {
                case int & Printable: { x.print(); }
                case str & Serializable: { x.serialize(); }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, TypeOperators) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        // Type operator examples
        type KeyOf<T> = { key in T : typeof(T[key]) };
        type ValueOf<T> = { value in T : T[value] };

        class Data {
            int x;
            str y;
        }

        // Using type operators with unions and intersections
        type DataKeys = KeyOf<Data>;  // Should be "x" | "y"
        type DataValues = ValueOf<Data>;  // Should be int | str

        // Type operators with constraints
        type PrintableProps<T> = {
            key in T : T[key] : Printable
        };

        type SerializableValues<T> = {
            value in T : value : Serializable
        };
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, HigherKindedTypes) {
    const char* code = R"(
        interface Container<T> {
            T get();
            void set(T value);
        }

        // Higher-kinded type parameter
        class Box<T> : Container<T> {
            T value;
            T get() { return value; }
            void set(T v) { value = v; }
        }

        // Using higher-kinded types with unions and intersections
        class DataProcessor<C : Container<int | str>> {
            C container;
            void process() {
                let value = container.get();  // Should infer int | str
                match (value) {
                    case int i: { /* handle int */ }
                    case str s: { /* handle str */ }
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, ExistentialTypes) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        // Existential type with bounds
        class Any<exists T : Printable & Serializable> {
            T value;
            void process() {
                value.print();
                value.serialize();
            }
        }

        // Using existential types with union bounds
        class Handler<exists T : int | str> {
            T value;
            void handle() {
                match (value) {
                    case int i: { /* handle int */ }
                    case str s: { /* handle str */ }
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, BoundedQuantification) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Comparable { int compare(T other); }

        // Bounded quantification with intersection type bounds
        class SortedList<T : Comparable & Printable> {
            T[] items;

            void add(T item) {
                item.print();  // Can use Printable methods
                // Sort using compare from Comparable
                for (let i = 0; i < items.length; i++) {
                    items[i].compare(item);
                }
            }
        }

        // Bounded quantification with union type bounds
        class Processor<T : (int & Comparable) | (str & Printable)> {
            T value;
            void process() {
                match (typeof(value)) {
                    case int & Comparable: { value.compare(value); }
                    case str & Printable: { value.print(); }
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, HigherKindedTypes) {
    const char* code = R"(
        interface Container<T> {
            T get();
            void set(T value);
        }

        // Higher-kinded type parameter
        class Box<T> : Container<T> {
            T value;
            T get() { return value; }
            void set(T v) { value = v; }
        }

        // Using higher-kinded types with unions and intersections
        class DataProcessor<C : Container<int | str>> {
            C container;
            void process() {
                let value = container.get();  // Should infer int | str
                match (value) {
                    case int i: { /* handle int */ }
                    case str s: { /* handle str */ }
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, ExistentialTypes) {
    const char* code = R"(
        interface Printable { void print(); }
        interface Serializable { str serialize(); }

        // Existential type with bounds
        class Any<exists T : Printable & Serializable> {
            T value;
            void process() {
                value.print();
                value.serialize();
            }
        }

        // Using existential types with union bounds
        class Handler<exists T : int | str> {
            T value;
            void handle() {
                match (value) {
                    case int i: { /* handle int */ }
                    case str s: { /* handle str */ }
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, HigherKindedTypes) {
    const char* code = R"(
        interface Container<T> {
            T get();
            void set(T value);
        }

        // Higher-kinded type parameter
        class Box<T> : Container<T> {
            T value;
            T get() { return value; }
            void set(T v) { value = v; }
        }

        // Using higher-kinded types with unions and intersections
        class DataProcessor<C : Container<int | str>> {
            C container;
            void process() {
                let value = container.get();  // Should infer int | str
                match (value) {
                    case int i: { /* handle int */ }
                    case str s: { /* handle str */ }
                }
            }
        }
    )";

    auto ast = parseCode(code);
    EXPECT_NO_THROW(typeChecker.visit(ast));
}

TEST_F(UnionIntersectionTypeTest, InvalidTypeCompositions) {
    const char* invalidUnion = R"(
        // Cannot union with void type
        let x: int | void = 42;
    )";

    const char* invalidIntersection = R"(
        // Cannot intersect incompatible types
        let x: int & str = 42;
    )";

    auto ast1 = parseCode(invalidUnion);
    EXPECT_THROW(typeChecker.visit(ast1), Error);

    auto ast2 = parseCode(invalidIntersection);
    EXPECT_THROW(typeChecker.visit(ast2), Error);
}
