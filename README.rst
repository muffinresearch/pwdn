pwdn
====

Small utility program to display n dirs from current working directory


To compile C version:: 

  gcc pwdn.c -o <path-to-bin>


Copy to your bin directory and then use it in your bash prompt like so::

  export PS1="\[\033[0;32m\]\u@\h \[\033[33m\]\$(pwdn 3)\[\033[0m\] \$ ";

  

