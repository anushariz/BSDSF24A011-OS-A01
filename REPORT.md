# REPORT.md

## Feature 2

**Q: Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from linking against a library?**

This rule tells make that the target executable depends on all the object
files listed in $(OBJECTS), and the recipe links them together directly
with `gcc $(OBJECTS) -o $(TARGET)`. Every function's machine code, already
compiled into each .o file, is combined into one binary at link time. This
differs from linking against a library, where instead of listing every
.o file, you link against a single archive (-lmyutils) using -L to tell
the linker where to find it and -l to name it; the linker then only pulls
in the specific object code it needs to resolve symbols, rather than
being handed every object file explicitly.

**Q: What is a git tag and why is it useful? Difference between simple and annotated tags?**

A git tag is a named pointer to a specific commit, typically used to mark
release points (v1.0, v2.0, etc.) in a project's history. It's useful
because it gives a stable, human-readable name to a commit that won't
move (unlike a branch), so you can always come back to exactly that state
of the code. A simple tag (`git tag v1.0`) is just a name pointing at a
commit. An annotated tag (`git tag -a v1.0 -m "message"`) is a full Git
object with its own author, date, message, and (optionally) GPG
signature — it's the recommended type for actual releases since it
carries metadata.

**Q: What is the purpose of a GitHub "Release"? Why attach binaries?**

A Release packages a specific tag with release notes and, optionally,
downloadable files (binary assets). It gives users a clean way to grab
a ready-to-run version of the software without cloning the repo and
building it themselves. Attaching the compiled `client` executable means
someone on a compatible system can download and run the program
immediately — this is how most software is actually distributed to
end users.
## Feature 3

**Q: Key differences between Part 2 and Part 3 Makefiles?**
Part 2 compiled every .c file (library + main) into objects and linked
them all directly into one executable — there's no separate library
artifact. Part 3 splits the library source files out, archives their
object files into lib/libmyutils.a using `ar rcs`, and then links only
main.o against that archive using -L (library search path) and -l
(library name) flags, instead of listing the library object files
directly on the link line.

**Q: Purpose of `ar`? Why is `ranlib` often used after it?**
`ar` creates and manages archive files (.a) — essentially a bundle of
.o files packaged into one file. `ranlib` builds/updates an index inside
the archive that maps symbol names to the object file that defines them,
so the linker can resolve symbols quickly without scanning every object
file in the archive sequentially. Using the `s` flag with `ar rcs`
performs this indexing automatically, which is why a separate `ranlib`
call isn't strictly needed here.

**Q: Are mystrlen's symbols present in client_static via nm? What does that tell you?**
Yes — running `nm bin/client_static | grep mystrlen` shows the symbol
with type T (defined in the text/code section). This confirms that
static linking physically copies the compiled code for every function
actually used from the library into the final executable at link time,
so the resulting binary is fully self-contained and doesn't need the
.a file (or any library) to run.
## Feature 4

**Q: What is Position-Independent Code (-fPIC) and why is it required for shared libraries?**
Position-Independent Code is machine code generated so it can execute
correctly regardless of the absolute memory address it's loaded at.
Shared libraries are mapped into different programs' address spaces —
and potentially at different addresses in each process, or shared across
processes at a common offset — so their code cannot rely on hard-coded
absolute addresses. -fPIC makes the compiler use relative addressing
(instruction-pointer-relative jumps, a global offset table for data),
so the same physical .so file can be loaded anywhere in memory for any
process without modification.

**Q: Why is client_dynamic smaller than client_static?**
client_static contains a full copy of the compiled library code baked
directly into the executable, so its size grows with however many
library functions it uses. client_dynamic contains no library code at
all — only a reference/stub telling the dynamic loader which shared
library and which symbols to resolve at runtime — so it stays small
regardless of how large the library is. The actual code lives in
libmyutils.so and is loaded (and can be shared across processes) at
runtime instead of being duplicated into every executable that uses it.

**Q: What is LD_LIBRARY_PATH and why was it necessary?**
LD_LIBRARY_PATH is an environment variable that tells the dynamic loader
(ld.so) additional directories to search for shared libraries at
runtime, before falling back to the system's default search paths
(like /lib, /usr/lib) and the system cache. Since libmyutils.so lives
in our own project's lib/ folder rather than a standard system library
path, the loader had no way to find it by default, causing the "cannot
open shared object file" error. Setting LD_LIBRARY_PATH tells the OS's
loader to also check our project directory. This shows that, unlike
static linking (resolved once at compile time), dynamic linking is
resolved every time the program starts, and it's the operating system's
responsibility — via the dynamic loader — to locate and map the needed
shared libraries into the process before execution can begin.
## Feature 5

(No specific report questions were given for this part in the assignment,
but you should still document: what man sections you used and why,
what the install target does, and any issues you hit with `mandb`.)
