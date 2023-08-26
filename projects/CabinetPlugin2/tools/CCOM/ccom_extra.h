/*
* $Revision: 1.1 $
* $Date: 2008/10/30 15:25:15 $
*/

/* 
* ccom_extra.h
* Crypto-COM 3.2 extra functions 
* Copyright (C) 1997-2006 Signal-COM
*/

#ifndef _CCOM_EXTRA_H
#define _CCOM_EXTRA_H

#ifdef  __cplusplus
extern "C" {
#endif

#pragma once

int __cdecl CADB_write_file(char *fname, char *buf, long len); 
int __cdecl CADB_read_file(char *fname, char *buf, long len); 
int __cdecl CADB_erase_file(char *fname); 
long __cdecl CADB_file_size(char *path); 
int __cdecl CADB_file_exists(char *path); 
int __cdecl CADB_is_dir(char *path); 
int __cdecl CADB_mkdir(char *path); 
int __cdecl CADB_rmdir(char *path, int flags); 
int __cdecl CADB_access(char *path, int mode); 

#ifdef  __cplusplus
}
#endif
#endif	/* _CCOM_H */
