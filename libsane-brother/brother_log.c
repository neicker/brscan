/*

 This file is part of the Brother MFC/DCP backend for SANE.

 This program is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the Free
 Software Foundation; either version 2 of the License, or (at your option)
 any later version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 Place, Suite 330, Boston, MA  02111-1307  USA

*/
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//	Source filename: brother_log.c
//
//	Copyright(c) 1997-2000 Brother Industries, Ltd.  All Rights Reserved.
//
//
//	Abstract:
//			ログファイル処理モジュール
//
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include "brother_devaccs.h"
#include "brother_misc.h"

#include "brother_log.h"

//
// ログファイル・モジュールの制御用変数
//
static int  nLogFile = 1;
static int  nNewLog  = 1;

static HANDLE  hLogFile = 0;

#define BROTHER_SANE_DIR "/usr/share/sane/brother/"


//-----------------------------------------------------------------------------
//
//	Function name:	WriteLogFileString
//
//
//	Abstract:
//		ログ文字列をログファイルに出力する
//
//
//	Parameters:
//		lpszLogStr
//			ログ文字列へのポインタ
//
//
//	Return values:
//		なし
//
//-----------------------------------------------------------------------------
//	WriteLogFileString（旧LogString_file）
void
WriteLogFileString(LPSTR lpszLogStr)
{
    if (hLogFile == 0) {
	char  szLogFile[ MAX_PATH ];

	strcpy( szLogFile, BROTHER_SANE_DIR );

	strcat( szLogFile, LOGFILENAME );
	if (nNewLog == 0){
	    hLogFile = fopen(szLogFile,"a");
	} else {
	    hLogFile = fopen(szLogFile,"w");
	}
    }

    if (hLogFile != NULL) {
	char   szStrBuff[ LOGSTRMAXLEN ];
	DWORD  dwStrLen = 0;

	time_t ltime;
	struct tm *sysTime;
	void *b_sysTime;
	if (NULL != (sysTime = malloc(sizeof(struct tm)))) {
	    b_sysTime = sysTime;
	    if (lpszLogStr != NULL) {
		time(&ltime);
		sysTime = localtime(&ltime);

		dwStrLen = sprintf(szStrBuff, "%02d:%02d:%02d.%03ld  %s\n",
				   sysTime->tm_hour, sysTime->tm_min,
				   sysTime->tm_sec, (ltime%1000), lpszLogStr);
	    } else {
		strcpy( szStrBuff, "\n" );
		dwStrLen = 2;
	    }
	    free(b_sysTime);
	}
	fwrite( szStrBuff, sizeof(char), dwStrLen, hLogFile);
    }

    CloseLogFile();
}


//-----------------------------------------------------------------------------
//
//	Function name:	WriteLog
//
//
//	Abstract:
//		ログ文字列を出力する
//
//
//	Parameters:
//		ログ文字列（書式付）
//
//
//	Return values:
//		なし
//
//-----------------------------------------------------------------------------
//	OutputLogString（旧LogString）
void WriteLog( LPSTR first, ... )
{
    if (nLogFile) {
	va_list  marker;
	char  szStrBuff[ LOGSTRMAXLEN ];

	va_start(marker, first);
	vsprintf((LPSTR)szStrBuff, first, marker);
	va_end(marker);

	WriteLogFileString( (LPSTR)szStrBuff );
    }

    return;
}


//-----------------------------------------------------------------------------
//
//	Function name:	WriteLogScanCmd
//
//
//	Abstract:
//		スキャナコマンドをログに出力
//
//
//	Parameters:
//		lpszId
//			付加文字列へのポインタ
//
//		lpszCmd
//			コマンド文字列へのポインタ
//
//
//	Return values:
//		なし
//
//-----------------------------------------------------------------------------
//	WriteLogScanCmd（旧WriteLogBidiCmd）
void
WriteLogScanCmd( LPSTR lpszId, LPSTR lpszCmd )
{
    if(nLogFile){
	int   nCmdLen, i;
	char  szStrBuff[ LOGSTRMAXLEN ];
	LPSTR lpCmdStr;

	nCmdLen = strlen(lpszCmd);

	lpCmdStr = szStrBuff;

	strcpy(szStrBuff, "[");
	lpCmdStr++;

	if (nCmdLen > 0 && *lpszCmd == 0x1B) {
	    //
	    // ESCコードを文字列に変換
	    //

	    strcat( szStrBuff, "ESC+" );
	    nCmdLen--;
	    lpszCmd++;
	    lpCmdStr += 4;
	}
	for (i = 0 ; i < nCmdLen ; i++, lpszCmd++) {
	    if (*lpszCmd == '\n') {
		//
		// LFコードをスペースに変換
		//
		*lpCmdStr++ = ' ';
	    }else if ((BYTE)*lpszCmd == (BYTE)0x80){
		//
		// Scanner Command Terminatorならループ終了
		//
		break;
	    } else if (' ' <= *lpszCmd && (BYTE)*lpszCmd < 0x80) {
		//
		// Printableコード
		//
		*lpCmdStr++ = *lpszCmd;
	    } else {
		//
		// その他のコード
		//
		*lpszCmd++ = '.';
	    }
	}
	*lpCmdStr++ = ']';
	*lpCmdStr   = '\0';

	//
	// ログ文字列を出力
	//
	WriteLog( "%s %s", lpszId, szStrBuff );
    }
}

//-----------------------------------------------------------------------------
//
//	Function name:	CloseLogFile
//
//
//	Abstract:
//		ログファイルをクローズ
//
//
//	Parameters:
//		なし
//
//
//	Return values:
//		なし
//
//-----------------------------------------------------------------------------
//
void CloseLogFile( void )
{
    if(hLogFile) {
	fclose(hLogFile);
	hLogFile = NULL;
    }
}


//-----------------------------------------------------------------------------
//
//	Function name:	GetLogSwitch
//
//
//	Abstract:
//		ログ有効／無効情報をINIファイルから取得する
//
//
//	Parameters:
//		なし
//
//
//	Return values:
//		なし
//
//-----------------------------------------------------------------------------
//
void
GetLogSwitch( Brother_Scanner *this )
{
    nLogFile = this->modelConfig.bLogFile;
    nNewLog  = 1;
}


//////// end of brother_log.c ////////
