#include <stdio.h>

void detailleSocket(int domain, int type, int protocol)
{
	printf("domain : %d\n", domain);

	printf("type : %d\n", type);
	
	printf("protocol : %d\n", protocol);
}

int socket(int domain, int type, int protocol)
{
	detailleSocket(domain, type, protocol);
	return domain+type+protocol;
}


