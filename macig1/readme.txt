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

after the functions getdata() and putdata() are called, the caller should:

immediately return after executing if getdata() is used in the case of a partial
message being recieved.

immediately return if putdata() sends a message to a client, an no further processing
is needed on the server side.

continue if more server side processing is needed after a call to putdata().


getdata() will be called to initially read in a message, but should return immediately,
as getdata() can be non blocking.

if a message is fully read in, then processing and content manufacturing can occur, then
putdata() should send a buffer containing the "made" message, then immediately return.

getdata(struct holdie &inbuf);
putdata(struct holdie &outbuf);

struct holdie
{
	void *start;
	void *end;
	ptrdiff_t capacity;
}


please read a description of getdata and putdata.

start is where the beginning of a dynamically allocated buffer is located.
end is the position of where the last amount of actual, non random data is located.
capacity is the amount of bytes that the container can hold, e.g., end can only be
less than or equal to start + capacity. posi is used internally by putdata, and should
be set to 0 before calling putdata.

getdata will append data starting at end, and stop before it reaches start + capacity.
putdata will send/write data beginning at start, and ending at end.

note: getdata and putdata will stop sending a message upon an error being encountered

int retval = process_data(rqstholder, http_table);

if(retval == INCMPLMSG)
{
	return INCMPLMSG; // this will notify the caller that the message is incomplete, and needs to be read more
}
else if(retval == BROKENMSG)
{
	//close(client);
	//free(rqstholder.start);
	return BROKENMSG; // this will notify the caller that the message was broken and the connection needs to be closed and the message buffer freed
}

retval = content_manufacture(clientfd, content_buffer); // else manufacture a message

if(retval == FAILEDCOND)
{
	//close(client);
	//free(rqstholder.start);
	free(content_buffer.start); // frees the content buffer, (should have been freed anyway, but this catches missed frees, and usually frees a NULL
	return FAILEDCOND; // does the same as BROKENMSG
}
else if(retval == INCMPLMSG)
{
	free(content_buffer.start);
	//getdata(clientfd, rqstholder);
	return INCMPLMSG; // tells the caller to append more bytes to a message by calling getdata again, probably used if a body was not send with a message requiring one
}

putdata(clientfd, content_buffer); // putdata will free the content buffer when it is complete

return WRITEFUL; /* tells the caller the request was valid, and content has been made, and putdata has been called for the content.
NOTE: if WRITEFUL is returned, the caller may choose to reuse the connection. if the connection fails, e.g. the client send a connection-close:
the connection will fail gracefully, and not pointlessly re-call this function again.
*/