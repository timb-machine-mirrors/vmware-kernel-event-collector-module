/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright 2021 VMware Inc.  All rights reserved. */

#pragma once

#include "hash-table-generic.h"
#include "process-context.h"

typedef struct PATH_KEY {
    uint64_t            ns_id;
    uint64_t            device;
    uint64_t            inode;
} PathKey;

typedef struct PATH_DATA {
    HashTableNode       node;
    PathKey             key;
    char               *path;
    bool                path_found;
    bool                is_special_file;
    uint64_t            file_id;
    uint64_t            fs_magic;
    atomic64_t          reference_count;
} PathData;

bool ec_path_cache_init(ProcessContext *context);
void ec_path_cache_shutdown(ProcessContext *context);

PathData *ec_path_cache_find(
    uint64_t            ns_id,
    uint64_t            device,
    uint64_t            inode,
    ProcessContext     *context);
PathData *ec_path_cache_add(
    uint64_t            ns_id,
    uint64_t            device,
    uint64_t            inode,
    char               *path,
    uint64_t            fs_magic,
    ProcessContext     *context);
void ec_path_cache_delete(
    PathData           *value,
    ProcessContext     *context);
PathData *ec_path_cache_get(
    PathData           *path_data,
    ProcessContext     *context);
void ec_path_cache_put(
    PathData           *path_data,
    ProcessContext     *context);