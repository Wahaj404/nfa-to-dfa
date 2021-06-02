#include "fa.hpp"

fort::char_table FA::makeTable() const {
    fort::char_table table;
    table << fort::header << "";
    table.range_write_ln(alphabet.cbegin(), alphabet.cend());
    table.set_border_style(FT_SOLID_ROUND_STYLE);
    for (int i = 0; i < table.col_count(); ++i) {
        table.set_cell_text_align(fort::text_align::center);
    }
    return table;
}

std::ostream &operator<<(std::ostream &out, FA const &machine) {
    return machine.print(out);
}