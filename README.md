# Marji-OS

A Unix-style shell written from scratch in C — the first real step toward
a long-term goal: my own OS, my own kernel, and eventually my own desktop
environment.

## What is this?

I started this project to build toward my own OS someday. It's been a
dream since I was a kid — I used to think it was too hard to ever
happen, but I don't think that anymore. This repo is where that dream
actually starts becoming code.

## Why from scratch, why C?

Because I want to actually understand what I'm building, not just use
tools someone else made. Hitting real errors and debugging them myself
is how I actually learn — not passive tutorials. C is the language
closest to the system itself, so it's the natural starting point for
anything that eventually touches a kernel.

## Features

- Interactive shell loop (`fgets` for input)
- Command parsing (`strtok`)
- Runs any real Linux command (`fork` + `execvp` + `wait`)
- Built-in: `cd` (via `chdir`, handled in the parent process — not forked)
- Built-in: `exit`
- Pipes (`|`) — connects two commands via `pipe()` + two `fork()` +
  `dup2()`, with proper cleanup of unused pipe ends to avoid hangs
- Output redirection (`>`) — writes command output to a file via
  `open()` + `dup2()`
- Shared `komut_calistir()` function: a single fork/dup2/execvp
  implementation reused by every command path (normal, redirection,
  pipe) instead of duplicated code

## Known limitations / not yet supported

- No quoted arguments (`rm "file name.txt"` breaks — quotes aren't
  parsed specially yet)
- No input redirection (`<`)
- No command history
- No environment variable expansion (`$HOME`, etc.)
- Fixed-size buffers (100 chars input, 10 args max)

## Roadmap

**Phase 1 — Shell (current)**
- [x] Basic shell loop and parsing
- [x] Real command execution (fork/execvp/wait)
- [x] Built-ins: `cd`, `exit`
- [x] Pipes (`|`)
- [x] Output redirection (`>`)
- [x] Input redirection (`<`)
- [ ] Quoted arguments
- [ ] Command history
- [ ] Environment variables

**Phase 2 — Systems programming**
Deeper C: memory allocators, file systems, threading, IPC. Bridging from
"using Linux" to "understanding how Linux works underneath."

**Phase 3 — Linux From Scratch**
Building a working Linux distro by hand — compiling the kernel and every
core tool myself, understanding what each piece actually does.

**Phase 4 — Kernel work**
Starting small: writing a kernel module, maybe a toy kernel (OSDev-style).
Long-term goal: my own kernel, at least compatible enough with core Linux
syscalls to run simple programs.

**Phase 5 — Desktop environment**
The dream I've had since childhood: my own windowing/desktop system on
top of it all.

## Tech notes

Developed across Termux and a Debian VM (Android 15, via `crosvm`).
Compiled with `clang -Wall`.

## License
MIT License — see [LICENSE](LICENSE) for details.
