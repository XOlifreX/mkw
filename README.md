# mkw

![build badge](https://github.com/em-eight/mkw/actions/workflows/build.yml/badge.svg?branch=master)
[![dol progress badge](https://em-eight.github.io/mkw/dol.svg)](https://em-eight.github.io/mkw)
[![rel progress badge](https://em-eight.github.io/mkw/rel.svg)](https://em-eight.github.io/mkw)
[![total progress badge](https://em-eight.github.io/mkw/total.svg)](https://em-eight.github.io/mkw)

A matching decompilation of Mario Kart Wii. All code in this repository will compile 1:1 to the original game.
It produces the following files:
mkw_pal.dol: `sha1: ac7d72448630ade7655fc8bc5fd7a6543cb53a49`
StaticR.rel: `sha1: 887bcc076781f5b005cc317a6e3cc8fd5f911300`


## Accuracy
The primary priority is to maintain absolute code accuracy. To automate verification of this, a special linker setup is used to emplace compiled code back into the original executable, forming a new executable. This new executable is hashed to ensure it matches the original. Once all code is decompiled, this setup will build a new executable from scratch, sampling none of the original.

## Code Quality
I have written code to be as readable and maintainable as possible. While the original access modifiers and trivial encapsulations have been lost to the optimizer, I have reconstructed both to minimize unsafe data exposure. Common sense debug assertions have been added, enforcing unchecked preconditions.

### Modern C++isms
While the original game was written and compiled as C++03, several modern C++ features have been used to aid readability and increase code quality. All are define'd out when compiling for C++03. For example: strongly typed null pointers with `nullptr` and the `override` specifier.

## Documentation
Every fully understood piece of reverse engineered data has been documented in a consistent doxygen style, [here](https://em-eight.github.io/mkw/docs/html/index.html).

## Dependencies
- DevKitPro (for the ppc-eabi assembler, and gcc dependency files)
- CodeWarrior compilers (in `tools`)
- Ninja
- Python 3
- Place a copy of Mario Kart Wii's PAL binaries:
  - `artifacts/orig/pal/main.dol`
  - `artifacts/orig/pal/StaticR.rel`

## Python Workspace
This build system assumes that a `python` command is available that points to a compatibly python 3 interpreter

### venv
It is recommended to setup a Python virtual environment to simplify workspace setup.
A venv saves you from installing dependencies system- or user-wide.

Run the setup steps once:

```ps1
# Initialize your venv in the ./env dir.
python3 -m venv env
# (Windows only) Allow executing the Activate script.
powershell -ExecutionPolicy Bypass -File ".\env\Scripts\Activate.ps1"
```

Then, each time you open a terminal, enter the venv:
* Windows: `.\env\Scripts\Activate.ps1`
* Good OSes: `source ./env/bin/activate`

### Install dependencies

```shell
pip install -r requirements.txt
```

## Building
If you're building the repository for the first time or any changes were made to the slice definitions, run `configure.py --regen_asm` to generate the build system. Otherwise, just run `ninja`. Final results:
  - `artifacts/target/pal/main.dol`
  - `artifacts/target/pal/StaticR.rel`

### Unit testing
We use [pytest](https://pytest.org).

### Symbol dead-stripping

By default, the CodeWarrior linker wants to remove any symbols (e.g. functions) that it considers unused.
Due to the unique nature of this build system, this would fail and result in all functions being removed.

To fix this, the `gen_lcf.py` script places all objects into the `FORCEFILES` linker directive.
This prevents any content from being dead-stripped.

In edge cases require carefully controlled use of the dead-stripping feature.
For example: Symbols that were stripped in the initial build retain all string literals.
This is very hard to replicate without dead-stripping:
Simply commenting out the stripped function would result the string literals from vanishing too.

The dead-stripping feature can be re-enabled by:
- Setting `strip` to 1 in the slices CSV
- Listing all symbols that will _not_ be stripped in the `FORCEACTIVE` directive in `dol.base.lcf` (all other symbols get thrown out)

## Contributing
Read CONTRIBUTING.md for an in-depth guide for a guide on how this decompilation project works and how to contribute.

### pre-commit

This project uses [pre-commit](https://pre-commit.com/) ensure code adheres to formatting rules.

To enable, run:

```
pre-commit install
pre-commit run --all-files
```

## .rel support
Most of Mario Kart Wii's game code is located inside a relocatable module (StaticR.rel for release builds). The decompilation builds this.
