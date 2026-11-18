# Emergency Dispatch Simulation

A turn-based simulation of an emergency dispatch system, written in C as the final project for the Basic Programming course.

The city is modeled as a 2D grid with fire, medical, and police departments, each operating a number of units. Incidents appear on the map with a type, priority, and location; the simulation dispatches available units, tracks response times, and reports statistics (solved vs. unsolved incidents, average resolution time). Every action is written to a timestamped log file.

## Build & Run

Requires GCC (or any C99 compiler) and Make:

```bash
make
./simulation
```

The simulation reads its initial setup from `sample_config.txt` in the working directory.

## Configuration

`sample_config.txt` defines the map size and the departments:

```
MAP_SIZE 20 10
DEPARTMENT FIRE 1 2 8 3
DEPARTMENT MEDICAL 1 5 5 5
DEPARTMENT POLICE 1 8 1 3
```

- `MAP_SIZE <width> <height>` — grid dimensions.
- `DEPARTMENT <type> <number> <x> <y> <unit_count>` — a department of the given type at position (x, y) with the given number of units.

## Using the Simulation

The simulation advances in turns. Every 10 turns it pauses and shows a menu:

1. **Enter a new incident** — choose type (`FIRE`, `MEDICAL`, `CRIME`), priority (`HIGH`, `MEDIUM`, `LOW`), and coordinates.
2. **Continue simulation** — advance turns.
3. **Exit** — print final statistics and stop.

## Project Structure

| File | Responsibility |
|---|---|
| `main.c` | Entry point |
| `simulation.c` | Main loop, turn handling, user menu |
| `config.c` | Configuration file parsing |
| `map.c` | City grid |
| `unit.c` | Dispatch units and movement |
| `incident.c` | Incident lifecycle |
| `log.c` | Timestamped event logging |
| `utils.c` | Shared helpers |

## License

MIT — see [LICENSE](LICENSE).