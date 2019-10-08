
SYMBOL_TABLE_FORMAT = """\
#include \"symbol_table.h\"

static symbol_table_s symbol_table[{symbol_table_size}U] = {{
    {symbol_table_entries}
}};

const size_t symbol_table__size __attribute__((keep)) = {symbol_table_size}U;
const symbol_table_s *symbol_table__base __attribute__((used)) = symbol_table;
"""


class SymbolTableEntry(object):
    """
    Representation of C structure:
    - const char name[<N>]
    - const void *address
    """

    def __init__(self, name, address):
        self.name = name
        self.address = address

    def __str__(self):
        address_repr = "0x{}".format(hex(self.address)[2:].zfill(8))  # Assuming 32 bit address

        representation = \
        r'{"%s", %s}' % (self.name, address_repr)

        return representation


class SymbolTableGenerator(object):
    def __init__(self):
        self._symbol_table_entries = []

    def __str__(self):
        symbol_table_entries_repr = ",\n\t".join(map(str, self))

        representation = SYMBOL_TABLE_FORMAT.format(
            symbol_table_size=len(self._symbol_table_entries),
            symbol_table_entries=symbol_table_entries_repr,
        )

        return representation

    def __iter__(self):
        for symbol_table_entry in self._symbol_table_entries:
            yield symbol_table_entry

    """
    Public methods
    """
    def add_entry(self, symbol_table_entry):
        assert isinstance(symbol_table_entry, SymbolTableEntry)
        self._symbol_table_entries.append(symbol_table_entry)

    def to_file(self, output_filepath="symbol_table.c"):
        with open(output_filepath, "w") as file_obj:
            file_obj.write(str(self))


if __name__ == "__main__":  # Test
    _symbol_table_entry = SymbolTableEntry("my_var", 0x4ffc)
    print(_symbol_table_entry)

    print("")

    _symbol_table_generator = SymbolTableGenerator()
    _symbol_table_generator.add_entry(_symbol_table_entry)
    _symbol_table_generator.add_entry(_symbol_table_entry)
    print(_symbol_table_generator)
    _symbol_table_generator.to_file()
