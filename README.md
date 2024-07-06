# UNIX Shell in C

Hi! This is a project I am developing to strenghten my grasp over systems programming in C, so I am building my own UNIX shell to handle many commonly used terminal commands, from which I hope to learn a lot about how these commands behave and are executed. 

I am currently trying to write up to 20 terminal commands in C available from UNIX, to mirror a UNIX Shell. I am hoping to add the ability to handling piping as well, which will be available in a later iteration.

My Shell currently supports the following commands:

cd
ls
pwd
mkdir
rmdir
mvdir (A custom command that moves entire directory)
cp (FILES ONLY, ONE AT A TIME)
rm (FILES ONLY, ONE AT A TIME)
mv (FILES ONLY, ONE AT A TIME)
cat
head
tail
kill
whoami
history
clear
exit

Compilation and Execution via Terminal:

gcc main.c shell.c -lreadline

./a.out

