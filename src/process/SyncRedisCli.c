/*****************************************************
 * 프로그램ID	: SyncRedisCli.c
 * 프로그램명	: Argument를 받아 SyncRedisFromOracle에 전송한다
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

#include <network.h>
#include <profile.h>
#include <ft_common.h>
#include <SyncRedis_interface.h>

/*************************************************************************************
 * Global 변수 정의
 *************************************************************************************/
 
char				program_name[64];

/*************************************************************************************
 * 구현 시작..
 *************************************************************************************/

SOCKET ConnectServer()
{
    SOCKET sockfd;
    int server_port;

    char conf_file_name[256];
		
	/* 설정파일을 연다. */
	sprintf(conf_file_name, "%s/%s/%s", mdb->program_home, CONF_PATH, SERVER_CONFIG_FILE);
	if ( !OpenProfile(conf_file_name) )
	{
		printf("설정파일을 여는 도중 에러가 발생하였습니다. file[%s] errno[%d]\n", conf_file_name, errno);
		return (-1);
	}
	
	/* 설정파일의 값을 가져온다. */
	server_port = GetProfileInt("SERVER_INFO", "SYNC_REDIS_ORACLE_PORT", 0);
	if ( server_port == 0 )
	{
		printf("서버 접속 정보가 없습니다.\n");
		return (-1);
	}
	
	/* 설정파일을 닫는다. */
	CloseProfile();

    // 서버연결
    if ( (sockfd = GetConnectSocket("127.0.0.1", server_port)) == -1 )
    {
        printf("서버 접속에 실패하였습니다!! host[%s:%d] errno[%d]\n", "127.0.0.1", server_port, errno);
        return (-1);
    }

    return (sockfd);
}

int main(int argc, char** argv)
{
    SOCKET sockfd;
    char trid, keylist[MAX_BUFFER];
    char sndbuf[MAX_BUFFER], rcvbuf[MAX_BUFFER];
    int length;

    SetProgramName(argv[0]);

    if ( argc != 3 )
    {
        printf("useage: %s TRID 'key_list'\n", program_name);
        printf("  - TRID '%c': Update Value of key_list\n", SRI_TRID_UPDATE);
        printf("  - TRID '%c': Delete Value of key_list\n", SRI_TRID_DELETE);
        printf("  - TRID '%c': Delete All Value of key_list\n", SRI_TRID_DELETE_ALL);
        exit(EXIT_FAILURE);
    }
    trid = argv[1][0];
    strcpy(keylist, argv[2]);

    /* 공유메모리를 초기화 한다. */
	InitCommonMemory();

    /* 서버에 연결한다 */
    if ( (sockfd = ConnectServer()) == -1 )
        exit(EXIT_FAILURE);
    
    /* 보낼데이타를 세팅한다 */
    sprintf(sndbuf, "%0*ld%c%s", SRI_LENGTH_SIZE, strlen(keylist) + 1, trid, keylist);

    /* 데이타를 전송한다 */
    if ( SendTCP(sockfd, sndbuf, strlen(sndbuf), 0) == -1 )
    {
        printf("데이타 전송에 실패하였습니다. errno[%d]\n", errno);
        exit(EXIT_FAILURE);
    }
    printf("요청 데이타 전송 [%ld:%s]\n", strlen(sndbuf), sndbuf);

    /* 응답데이타를 읽어온다 */
    memset(rcvbuf, 0x00, MAX_BUFFER);
    if ( ReceiveTCP(sockfd, rcvbuf, SRI_LENGTH_SIZE, 0) <= 0 )
    {
        printf("응답 사이즈 수신에 실패하였습니다. errno[%d]\n", errno);
        exit(EXIT_FAILURE);
    }
    if ( (length = atoi(rcvbuf)) > 0 )
    {
        if ( ReceiveTCP(sockfd, rcvbuf + SRI_LENGTH_SIZE, length, 0) <= 0 )
        {
            printf("응답 데이타 수신에 실패하였습니다. errno[%d]\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    printf("응답 데이타 수신 [%ld:%s]\n", strlen(rcvbuf), rcvbuf);

    CloseSocket(sockfd);
    exit(EXIT_SUCCESS);
}
