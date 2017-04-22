#ifndef _ASSEMBLY_COMMANDS_H
#define _ASSEMBLY_COMMANDS_H

namespace ava {

	enum Operation : unsigned char
	{
		push = 0,
		push_register,
		pop_register,
		add,
		div,
		multiply,
		call,
		ret,
		jmp,
		jmpe,
		jmpa,
		jmpae,
		jmpb,
		jmpbe,
		jmpne
	};

}

#endif