# Marji-OS

## What is this?

I started this project to build toward my own OS someday — my own kernel, 
and eventually my own desktop environment. It's been a dream since I was 
a kid, and this repo is the first real step toward making it happen.

## Why from scratch, why C?

Because I want to actually understand what I'm building, not just use 
tools someone else made. Doing it from scratch — hitting real errors, 
debugging them myself — is how I actually learn. C is the language 
closest to the system itself, so it's the natural starting point for 
anything that eventually touches a kernel.

## Progress so far

- [x] Basic shell loop (reading input with `fgets`)
- [x] Command parsing (`strtok`)
- [x] Running real Linux commands (`fork` + `execvp` + `wait`)
- [x] Built-in command: `cd`
- [x] Built-in command: `exit`
- [ ] Pipes (`|`)
- [ ] I/O redirection (`>`, `<`)
- [ ] Command history
- [ ] Environment variables

## Roadmap

**Phase 1 — Shell (current)**
A working Unix-style shell in C: parsing, process management, built-ins, 
eventually pipes and redirection. This is where process management, 
memory handling, and reading system errors get learned hands-on.

**Phase 2 — Systems programming**
Deeper C: memory allocators, file systems, threading, IPC. Bridging from 
"using Linux" to "understanding how Linux works underneath."

**Phase 3 — Linux From Scratch**
Building a working Linux distro by hand — compiling the kernel and every 
core tool myself, understanding what each piece actually does.

**Phase 4 — Kernel work**
Starting with small things: writing a kernel module, maybe experimenting 
with a toy kernel (OSDev-style). Long-term goal: my own kernel, at least 
compatible enough with core Linux syscalls to run simple programs.

**Phase 5 — Desktop environment**
The dream I've had since childhood: my own windowing/desktop system on 
top of it all.

## Tech notes

Developed across Termux and a Debian VM (Android 15, via crosvm).
