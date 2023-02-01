int find_subseq(std::byte *outer, std::byte *inner, int outersize, int innersize)
{
	using std::byte;
	
	for(int i = 0; i < outersize - innersize + 1; i++)
	{
		if(outer[i] == inner[0])
		{
			for(int j = 0; j < innersize; j++)
			{
				if(outer[i + j] != inner[j])
					break;
				if(j == innersize - 1)
					return i;
			}
		}
	}
	
	return -1;
}

// fills a string with the headers
int strheaders(std::string &headers, std::vector<std::byte> &raw)
{
	using std::byte;
	int body_offset = find_subseq(&*raw.begin(), (byte*)"\r\n\r\n", raw.size(), 4);
	headers.assign((char*)&*raw.begin(), body_offset);
	
	return body_offset;
}

// seperates headers into string, and body into vector
int gloss(std::string &headers, std::vector<std::byte> &raw)
{
	int retval = strheaders(headers, raw);
	retval += 4;
	
	raw.erase(raw.begin(), raw.begin() + retval);
	
	return 0;
}

int deducer(int peer, std::string &headers, std::vector<std::byte> &body)
{
	using std::string;
	
	// sl status line
	// ct content type
	// rl request line
	
	const size_t npos = string::npos;
	
	const string index_rl = "GET /index.html ";
	const string index_rl2 = "GET / ";
	if(headers.find(index_rl) != npos || headers.find(index_rl2) != npos)
	{
		put(peer, "HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n\r\n");
		fput(peer, "resources/index.html");
		return WRITEFUL;
	}
	
	const string favicon_rl = "GET /favicon.ico ";
	if(headers.find(favicon_rl) != npos)
	{
		put(peer, "HTTP/1.1 200 OK\r\nContent-Type: image/png;\r\n\r\n");
		fput(peer, "resources/favicon.png");
		return WRITEFUL;
	}
	
	return BAD;
}