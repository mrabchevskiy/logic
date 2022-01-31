Three-value (Łukasiewicz version) logic

 See `https://en.wikipedia.org/wiki/Three-valued_logic` for details

 Implemented as wrapper over `std::strong_ordering` that represents results
 of the three-way comparison operator `<=>`.

 Implication operator represented by the pseudo-operator `-->` that actually
 is a conbination of postfix `--` and `>`
