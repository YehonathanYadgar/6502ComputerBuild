#!/usr/bin/env python3
"""Create a deterministic starter ROM image for the 6502 project."""

from argparse import ArgumentParser
from pathlib import Path

ROM_SIZE = 32 * 1024
NOP = 0xEA


def make_rom(output: Path) -> None:
    """Write a 32 KiB ROM filled with 6502 NOP instructions."""
    output.write_bytes(bytes([NOP]) * ROM_SIZE)


def main() -> None:
    parser = ArgumentParser(description=__doc__)
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=Path(__file__).with_name("rom.bin"),
        help="output path (default: rom/rom.bin)",
    )
    args = parser.parse_args()
    make_rom(args.output)
    print(f"Wrote {ROM_SIZE} bytes to {args.output}")


if __name__ == "__main__":
    main()
