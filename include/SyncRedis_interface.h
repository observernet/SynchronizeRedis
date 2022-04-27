/*****************************************************
 * 프로그램ID	: SyncRedis_interface.h
 * 프로그램명	: 통신 스펙을 정의한다.
 *****************************************************/
 
#ifndef _SYNC_REDIS_INTERFACE_H
#define _SYNC_REDIS_INTERFACE_H

/******************************************************************************
 * DEFINES
 ******************************************************************************/

#define SRI_LENGTH_SIZE					4
#define SRI_DATA_SEPERATOR				'|'

/******************************************************************************
 * INTERFACE Header Info (stream)
 ******************************************************************************/

/* REQUEST/RESPONSE HEADER */
typedef struct
{
	char				length[SRI_LENGTH_SIZE];					/* SRI_LENGTH_SIZE를 제외한 전체 패킷 사이즈 */
	char				trid;										/* 요청구분 */
 } SRI_REQRES_HEADER;

/******************************************************************************
 * INTERFACE Body Info (stream, 구분자로 분리)
 ******************************************************************************/

/* Update Value Event */
#define SRI_TRID_UPDATE					'U'
// Request
//  - Redis Key 1
//  - Redis Key 2
//  - Redis Key n
// Response
//  - return Code (dl_common.h에 정의)

/* Delete Value Event */
#define SRI_TRID_DELETE					'D'
// Request
//  - Redis Key 1
//  - Redis Key 2
//  - Redis Key n
// Response
//  - return Code (dl_common.h에 정의)

/* Delete All Event */
#define SRI_TRID_DELETE_ALL				'L'
// Request
//  - Redis Key
// Response
//  - return Code (dl_common.h에 정의)

#endif
