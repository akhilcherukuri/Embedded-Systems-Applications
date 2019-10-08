"""
References:
- https://sourceware.org/binutils/docs/binutils/nm.html
"""

from collections import namedtuple
import os
import subprocess
import time


SymbolEntry = namedtuple("SymbolEntry", ["address", "size", "symbol"])  # address (int), size (int), symbol (str)


class SymbolTableParser(object):
    def __init__(self, nm_exe="nm"):
        self._nm_exe = nm_exe

    """
    Public methods
    """
    def parse(self, elf_filepath):
        assert os.path.isfile(elf_filepath)

        stdout = self._execute_nm(elf_filepath=elf_filepath)

        # Assume each line of standard out looks like:
        # "10000054 000000a4 d lpc_peripheral__isr_registrations\n"
        for line in stdout.split("\n"):
            if line.strip() == "":
                continue
            line = line.replace("\r", "")

            try:
                address, size, symbol_type, symbol = line.split(" ")
                if not self._filter(symbol_type=symbol_type):
                    continue
                else:
                    address = int(address, 16)
                    size = int(size, 16)
                    new_symbol_entry = SymbolEntry(address, size, symbol)
                    yield new_symbol_entry
            except ValueError:
                continue  # Ignore error

    """
    Private methods
    """
    def _execute_nm(self, elf_filepath):
        cmd = [
            self._nm_exe,
            elf_filepath,
            "--print-size",
        ]

        process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
        stdout, _ = process.communicate()
        return stdout.decode()


    @staticmethod
    def _filter(symbol_type):
        valid_types = [
            "d", "D",  # Symbols in .data section
            "b", "B",  # Symbols in .bss section
            "r", "R",  # Symbols in .rodata section
        ]

        return symbol_type in valid_types


if __name__ == "__main__":  # Test
    _symbol_table_parser = SymbolTableParser(nm_exe="arm-none-eabi-nm")
    for _symbol_entry in _symbol_table_parser.parse(r"C:\git\sjtwo-c\_build_lpc40xx_freertos\lpc40xx_freertos.elf"):
        print(_symbol_entry)
