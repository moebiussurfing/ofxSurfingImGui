#include "ofxMyUtilMedia.h"

//--------------------------------------------------------------
// ofxMyUtil Media
//--------------------------------------------------------------
using namespace ofxMyUtil;

#if defined( __WIN32__ ) || defined( _WIN32 )
#define WIN32
#endif

#ifdef WIN32

	#include <winsock2.h>

#else
	#include <sys/types.h>
	#include <semaphore.h>
#endif

//--------------------------------------------------------------
std::string Media::GetIpAddress() 
{
#ifdef WIN32
	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];

	gethostname(szBuf, (int)sizeof(szBuf));
	//printf("HOST Name : %s\n", szBuf);

	lpHost = gethostbyname(szBuf);

	for (i = 0; lpHost->h_addr_list[i]; i++) {

		memcpy(&inaddr, lpHost->h_addr_list[i], 4);

		strcpy(szIP, inet_ntoa(inaddr));

	}

	return std::string(szIP);
#else
	//mac or linux
	return std::string();
#endif
}

//--------------------------------------------------------------
void Media::ShowIpHost() 
{
#ifdef WIN32

	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];

	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	lpHost = gethostbyname(szBuf);

	for (i = 0; lpHost->h_addr_list[i]; i++) {
		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		strcpy(szIP, inet_ntoa(inaddr));
		printf("IP Adress : %s\n", szIP);
	}

#else

#endif
}
