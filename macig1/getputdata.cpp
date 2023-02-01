#include <unistd.h> // read write
#include <sys/ioctl.h> // ioctl
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <cstdio>

int pending_bytes(int socket)
{
	int count;
	ioctl(socket, FIONREAD, &count);	
	
	return count;
}

int get(int peer, std::vector<std::byte> &holder)
{
	size_t index = holder.size();
	
	holder.resize(index + 4096);
	int count = read(peer, &*(holder.begin() + index), 4096);
	holder.resize(index + count);
	return count;
}

int put(int peer, std::vector<std::byte> &data)
{
	int count = write(peer, &*data.begin(), data.size());
	return count;
}

int put(int peer, std::string &data)
{
	int count = write(peer, &*data.begin(), data.length());
	return count;
}

int put(int peer, const char *data)
{
	int count = write(peer, data, strlen(data));
	return count;
}

int put(int peer, void *data, int amount)
{
	int count = write(peer, data, amount);
	return count;
}

int get_file_size(const char *filename)
{
	struct stat stat_buf;
    if(stat(filename, &stat_buf) == -1)
		return -1;
	
    return (int)stat_buf.st_size;
}

// load file into vector
int file_into_vector(const char *filename, std::vector<std::byte> &holder)
{
	// get file size
	// resize vector to file size
	// load file into vector
	// return
	
    int file_size = get_file_size(filename);
	holder.resize(file_size);
	
	FILE * fp = fopen(filename, "r");
	if(fread(&*holder.begin(), file_size, 1, fp) != 1)
		return -1;
	
	fclose(fp);
	return 0;
}

int fput(int peer, const char *filename)
{
	using std::vector;
	using std::byte;
	
	vector<byte> file_holder;
	
	if(file_into_vector(filename, file_holder) != 0)
		return -1;
	
	return(put(peer, file_holder));
}