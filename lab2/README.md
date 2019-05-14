# Lab2: Bomb Lab

This is bomb 256. It belongs to me, 005181694 (zenn@ucla.edu).

My bomb is very likely different from your bomb, but hey, don't leave just
yet; I still have some tool here that could be very useful to you.

## Tools

### room

The `room` directory is created as a safe house, which can prevent you from
accidentally executing `bomb` without any protection.

Inside `room`, there is a simple shell script called `defuse`. Its whole content,
as you can see, is the following two lines:

``` bash
#!/bin/bash
gdb ../bomb -x ../commands
```

It uses `gdb` to examine `bomb`, and execute commands in `commands` file on
start. That is very handy as you will see later on.

### pass

`pass` is nothing more than a file that holds passwords that you've found, so
that you don't need to type them again and again.

### commands

As is explained above, `commands` hold all the commands you wish to execute on
start. I would suggest keeping

`break explode_bomb`

and

`run ../pass`

there all the time to make sure you stop before the bomb explodes (duh), and
also always start the bomb with the passwords.


