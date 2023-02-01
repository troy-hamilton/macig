#include <vector>
#include <string>
#include <cstddef>
#include <iostream>

#include "parsing.cpp"

void step_out(int client)
{
	using std::vector;
	using std::byte;
	using std::cout;
	using std::endl;
	using std::string;
	
	vector<byte> holder;
	get(client, holder);
	
	// seperate the headers from the body
	string headers;
	gloss(headers, holder);
	
	// parse the headers
	if(deducer(client, headers, holder) != WRITEFUL)
	{
		cout << "bad message" << endl;
		cout << headers << endl;
	}
	
}
