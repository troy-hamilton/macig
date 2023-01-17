int getdata(int client)
{
	
}

int putdata(int client)
{
	
}

/*this is the forking version of step out
reads and writes are done sequentially.
if a future version of this program uses
non blocking io, then it would probably read in data first, then pass it
to this function, then call further(),check for conditions,
then start some kind of non blocking read or write (unless the condition is WRITEFUL)
, then return, and be re-called when the read or write completes, but for now it is
a shell allowing portability with future versions.
*/

void step_out(int client)
{
	struct holdie request;
	request.capacity = some number of bytes
	request.start = realloc request.capacity
	request.end = request.start
	
	int retval = getdata(client, request); // in this version(1) getdata is blocking
	if(retval == -1)
		return;
	
	
	retval = further(client, request); // refer to readme to build
	if(retval == conditions)
	{
		...
	}
	else if(...)
	{
		...
	}
	...
	
}
