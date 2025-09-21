# Repository Guidelines

## Project Structure & Module Organization
QMK firmware centers around reusable keyboard modules. Core behavior lives in `quantum/`, hardware drivers in `drivers/` and `platforms/`, and shared libraries in `lib/` and `modules/`. Keyboard-specific sources and keymaps sit under `keyboards/<board>/`, with per-user overrides in `users/` and community layouts in `layouts/`. Firmware build metadata is stored in `data/`, while documentation belongs in `docs/`. Host-side utilities, including the CLI entry point, are under `lib/python/qmk/`, and end-to-end tests reside in `tests/`.

## Build, Test, and Development Commands
- `./util/qmk_install.sh` installs compiler toolchains, Python dependencies, and udev rules.
- `qmk compile -kb <keyboard> -km <keymap>` runs the standard build using the selected keyboard and keymap.
- `make <keyboard>:<keymap>` is available for legacy build scripts and CI automation.
- `qmk flash -kb <keyboard> -km <keymap>` builds and flashes in one step (requires bootloader ready hardware).
- `qmk lint -kb <vendor>/<keyboard>` checks metadata and rules for a specific keyboard tree before review.
- `qmk format-c --core-only -a` and `qmk format-python -a` apply the repo’s clang-format and yapf profiles.

## Coding Style & Naming Conventions
Core C code uses four-space indentation, modified OTBS braces, and mandatory optional braces (see `docs/coding_conventions_c.md`). Prefer descriptive snake_case for functions and variables, and uppercase for macros and enums. Python modules follow PEP 8 with yapf formatting; import order is maintained by isort when available. Keyboard directories use the pattern `keyboards/<vendor>/<board>/`, with keymaps in `keymaps/<name>/` and configuration files named `rules.mk`, `config.h`, and `keymap.c`.

## Testing Guidelines
CLI and Python changes must pass `qmk pytest`, which wraps nose2 tests inside `lib/python`. Firmware changes should at minimum compile the affected keyboard(s); include `qmk compile -kb <board> -km <map>` output in PR discussions when adding features. Place new Python tests alongside existing modules using the `test_<feature>.py` naming convention, and consider `qmk lint --keyboard <board>` to spot metadata regressions before pushing.

## Commit & Pull Request Guidelines
Keep commits scoped to a single logical change and follow the historical prefix style: `keyboards/<board>: short summary` or `quantum: short summary`. Reference related GitHub issues when applicable and provide context in the commit body for hardware-impacting changes. Pull requests should include a concise summary, a list of tested build targets or scripts, and any screenshots or logs that help reviewers. Run formatting, linting, and the relevant compile/test commands before requesting review.
