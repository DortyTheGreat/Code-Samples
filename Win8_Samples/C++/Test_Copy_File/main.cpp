#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	char oldname[] = "Old Folder";
	char newname[] = "New Folder\\Really New Folder";

	/*	Deletes the file if exists */
	if (rename(oldname, newname) != 0)
		perror("Error moving file");
	else
		cout << "File moved successfully";

	return 0;
}
