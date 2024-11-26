# Pryst Type System Documentation

## Type Registration and Storage

### Storage Mechanisms
1. `typeCache`: Primary storage for Type objects
   - Maps type names to shared_ptr<Type>
   - Stores both full qualified names and short names
   - Handles nullable types with '?' suffix

2. `classTypes`: LLVM type storage
   - Maps class names to llvm::StructType*
   - Used for code generation
   - Synchronized with typeCache

3. `registeredNamespaces`: Namespace tracking
   - Set of registered namespace strings
   - Includes parent namespaces automatically
   - Used for type resolution

### Type Lookup Strategy
1. Exact Match:
   - First attempts exact match in typeCache
   - Most efficient path for fully qualified names

2. Namespace Resolution:
   - For names with "::", attempts namespace resolution
   - Checks registered namespaces first
   - Resolves through namespace aliases

3. Short Name Fallback:
   - Falls back to short name lookup
   - Used when namespace resolution fails

4. Namespace Iteration:
   - Last resort: checks all registered namespaces
   - Attempts to find type in each namespace

### Potential Circular Dependencies
1. Namespace Aliases:
   - Risk: Alias A -> B -> A
   - Current Implementation: No cycle detection
   - Recommendation: Add cycle detection in resolveNamespace

2. Type Dependencies:
   - Handled via forward declarations
   - No circular dependencies in type registration
   - Member types registered after containing type

### Data Flow
1. Type Registration:
   ```
   registerClass
   ├── Register in classTypes
   ├── Convert to Type object
   └── Cache in typeCache
       ├── Full name (ns::type)
       └── Short name (type)
   ```

2. Namespace Registration:
   ```
   registerNamespace
   ├── Add to registeredNamespaces
   └── Recursive parent registration
       └── Split on "::" and register parents
   ```

3. Type Resolution:
   ```
   getCachedType
   ├── Exact match lookup
   ├── Namespace resolution
   │   ├── Check registered namespaces
   │   └── Resolve aliases
   ├── Short name fallback
   └── Namespace iteration
   ```

## Recommendations
1. Add cycle detection in namespace resolution
2. Consider caching resolved namespace paths
3. Implement namespace scope tracking
4. Add validation for namespace aliases
