/*
 * Rados Filesystem - A filesystem library based in librados
 *
 * Copyright (C) 2014 CERN, Switzerland
 *
 * Author: Joaquim Rocha <joaquim.rocha@cern.ch>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License at http://www.gnu.org/licenses/lgpl-3.0.txt
 * for more details.
 */

#ifndef __DIR_INFO_HH__
#define __DIR_INFO_HH__

#include <pthread.h>
#include <set>
#include <map>
#include <string>
#include <rados/librados.h>

#include "radosfscommon.h"
#include "radosfsdefines.h"

RADOS_FS_BEGIN_NAMESPACE

typedef struct
{
  std::string name;
  std::map<std::string, std::string> metadata;
} DirEntry;

class DirCache
{
public:
  DirCache(const std::string &dirpath, RadosFsPoolSP pool);
  virtual ~DirCache(void);

  int update(void);
  const std::string getEntry(int index);
  rados_ioctx_t ioctx(void) const { return mPool->ioctx; }
  std::set<std::string> contents(void) const { return mEntryNames; }
  std::string path(void) const { return mPath; }
  void compactDirOpLog(void);
  float logRatio(void) const;
  bool hasEntry(const std::string &entry);
  int getMetadata(const std::string &entry,
                  const std::string &key,
                  std::string &value);
  int getContentsSize(uint64_t *size) const;

private:
  void parseContents(char *buff, int length);

  std::string mPath;
  RadosFsPoolSP mPool;
  std::map<std::string, DirEntry> mContents;
  std::set<std::string> mEntryNames;
  uint64_t mLastCachedSize;
  int mLastReadByte;
  pthread_mutex_t mContentsMutex;
  size_t mLogNrLines;
};

RADOS_FS_END_NAMESPACE

#endif /* __DIR_INFO_HH__ */
