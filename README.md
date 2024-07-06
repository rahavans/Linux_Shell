# UNIX Shell in C

Hi! This is a project I am developing to strenghten my grasp over systems programming in C, so I am building my own UNIX shell to handle many commonly used terminal commands, from which I hope to learn a lot about how these commands behave and are executed. 

I am currently trying to write up to 20 terminal commands in C available from UNIX, to mirror a UNIX Shell. I am hoping to add the ability to handling piping as well, which will be available in a later iteration.

My Shell currently supports the following commands:

cd <br />
ls <br />
pwd <br />
mkdir <br />
rmdir <br />
mvdir (A custom command that moves entire directory) <br />
cp (FILES ONLY, ONE AT A TIME) <br />
rm (FILES ONLY, ONE AT A TIME) <br />
mv (FILES ONLY, ONE AT A TIME) <br />
cat <br />
head <br />
tail <br />
kill <br />
whoami <br />
history <br />
clear <br />
exit <br />

Compilation and Execution via Terminal:

Since this is a C program, it can be compiled and executed through the terminal. Be sure to link the readline library using -lreadline. The terminal command is as follows:

gcc main.c shell.c -lreadline

Since I am running on macOS, the default executable file is a.out, and to run the executable is as follows:

./a.out

