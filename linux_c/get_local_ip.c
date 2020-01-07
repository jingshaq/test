#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int get_local_ip(char *ip)
{
	int fd, intrface, retn = 0;
	struct ifreq buf[INET_ADDRSTRLEN];
	struct ifconf ifc;
	char *p;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
	{
		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = (caddr_t)buf;
		if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
		{
			intrface = ifc.ifc_len/sizeof(struct ifreq);
			while (intrface-- > 0)
			{
				if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))
				{
					p=(inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));
					if(strcmp("127.0.0.1", p)==0){
						continue;
					}
					strcpy(ip, p);
				}
			}
		}
		close(fd);
		return 0;
	}

	return -1;
}

int main()
{
	char ip[64];
	memset(ip, 0, sizeof(ip));
	get_local_ip(ip);
	printf("ip=%s\n", ip);
	return 0;
}
