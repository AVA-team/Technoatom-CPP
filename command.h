#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>

namespace ava {

	//! Codes of commands for CPU.
	enum Command_code : unsigned char {
		PUSH,
		PUSH_REG,
		POP,
		ADD,
		DIV,
		MUL,
		RET,
		CALL,
		JMP,
		JMPE,
		JMPA,
		JMPAE,
		JMPB,
		JMPBE,
		JMPNE,
		END
	};

	struct Command {
		//! Name of command in source file.
		const std::string name_;
		//! Code of command in binary file.
		Command_code code_;
		//! Existing of one argument of command.
		const bool argument_existing_;
	};

	//! Vector of availible in source code commands.
	const std::vector<Command> availible_commands = {
														{"push",     PUSH,     true },
														{"push_reg", PUSH_REG, true },
														{"pop",      POP,      true },
														{"add",      ADD,      false},
														{"div",      DIV,      false},
														{"mul",      MUL,      false},
														{"ret",      RET,      false},
														{"call",     CALL,     true },
														{"jmp",      JMP,      true },
														{"jmpe",     JMPE,     true },
														{"jmpa",     JMPA,     true },
														{"jmpae",    JMPAE,    true },
														{"jmpb",     JMPB,     true },
														{"jmpbe",    JMPBE,    true },
														{"jmpne",    JMPNE,    true },
														{"end",      END,      false }
	};

}

#endif //COMMAND_H_
