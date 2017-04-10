#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>

struct Command {
    //! Name of command in source file.
    const std::string name_;
    //! Code of command in binary file.
    const unsigned char code_;
    //! Existing of one argument of command.
    const bool argument_existing_;
};

//! Vector of availible in source code commands.
const std::vector<Command> availible_commands = {
													{"push",     0,  true },
													{"push_reg", 1,  true },
													{"pop",      2,  true },
													{"add",      3,  false},
													{"div",      4,  false},
													{"mul",      5,  false},
													{"call",     6,  true },
													{"ret",      7,  false},
													{"jmp",      8,  true },
													{"jmpe",     9,  true },
													{"jmpa",     10, true },
													{"jmpae",    11, true },
													{"jmpb",     12, true },
													{"jmpbe",    12, true },
													{"jmpne",    12, true }
												};

#endif //COMMAND_H_
