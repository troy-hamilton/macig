this server program is gonna cover the basic groundwork
for a future program. this should be able to handle a few
hundred clients, and be able to avoid any generic slow lorris
attacks, whether they are nefarious or accidental.

it will simply accept a connection, then fork any processing
on that connection to a new process.

in order for the content manufacturing functions to be "portable"
in the way that they can be used on a future server which uses
the proper layout of <main will call accept(), then add the fd to a
non blocking read pool which uses epoll() to add work to a thread pool>
, it will allow the future reading and writing procedures to be implemented,
and the content manufacturing functions can be used without any changes.

the reading and writing will be seperated from the content manufacturing.
obviousley there will be things that need to be used in the conmac process,
like checking if there are bytes available, such as in the event of a partial
send. this will be available as a function called pendata();
that is just an example of a function that has to be "portable".

a list of functions that can be considered portable will be made, and
will have their own "man page" which describes their behavior.

getdata
putdata
