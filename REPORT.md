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
