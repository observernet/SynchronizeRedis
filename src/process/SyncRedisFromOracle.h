#ifndef _SYNC_REDIS_FROM_ORACLE_H
#define _SYNC_REDIS_FROM_ORACLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************************
 * Defines.....
 *************************************************************************************/


/*************************************************************************************
 * Global 변수 정의
 *************************************************************************************/
 
char				program_name[64];
int 				process_id;

int					epoll_fd;
struct epoll_event	events[MAX_SERVER_USER];
struct timeval		timeover;

int				    server_port;
SOCKET			    server_sockfd;

REDIS               redis;
sql_context			ctx;

/*************************************************************************************
 * 함수 정의
 *************************************************************************************/

int   add_epoll(SOCKET fd);
int   del_epoll(SOCKET fd);

int   ReceiveRequest(SOCKET sockfd);
int   ProcessUpdate(char* buff);
int   ProcessDelete(char* buff);
int   ProcessDeleteAll(char* buff);
int   ParseKeys(char* buff, REDIS_KEYS** rkeys);

int   SendResponse(int user_offset, SRI_REQRES_HEADER* reqHeader, int rcode);
char *toLower(char *str);

int   AcceptUser(SOCKET sockfd);
int   RemoveUser(SOCKET sockfd);
int   GetUserOffset(SOCKET sockfd);

void  InitServer();
void  interrupt(int);

#ifdef __cplusplus
}
#endif

#endif
