# Technoatom-CPP
Project with:
- assembler, which convert source code of script in bynary file,
- processor, which execute this bynary file.


Source code supports commands:
- push $i
- push_reg $i
- pop $i
- add
- div
- mul
- call :$i
- ret
- jmp :$i
- jmpe :$i
- jmpa :$i
- jmpae :$i
- jmpb :$i
- jmpbe :$i
- jmpne :$i
where: $i - integer value of number, register number or tag number.
