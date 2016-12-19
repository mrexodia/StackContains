# StackContains

Sample x64dbg plugin to scan the stack during tracing.

## Usage

With this plugin installed you have the `stack.contains(base, needle)` expression function.

`base` The address to start searching down from (usually `csp`).

`needle` The value with size = `sizeof(void*)` you are looking for.
