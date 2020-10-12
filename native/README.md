# Pryst Language native image

Truffle language implementations can be AOT compiled using the GraalVM
[native-image](https://www.graalvm.org/docs/reference-manual/aot-compilation/)
tool.  Running `mvn package` in the pryst folder also builds a
`prystnative` executable This executable is the full Pryst Language
implementation as a native application, and has no need for a JVM to run.
