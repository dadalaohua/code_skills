/*----------------------------------------------------------------------------
 * Tencent is pleased to support the open source community by making TencentOS
 * available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
 * If you have downloaded a copy of the TencentOS binary from Tencent, please
 * note that the TencentOS binary is licensed under the BSD 3-Clause License.
 *
 * If you have downloaded a copy of the TencentOS source code from Tencent,
 * please note that TencentOS source code is licensed under the BSD 3-Clause
 * License, except for the third-party components listed below which are
 * subject to different license terms. Your integration of TencentOS into your
 * own projects may require compliance with the BSD 3-Clause License, as well
 * as the other licenses applicable to the third-party components included
 * within TencentOS.
 *---------------------------------------------------------------------------*/

#ifndef _TOS_K_H_
#define  _TOS_K_H_

/* CPP header guards */
#ifdef __cplusplus
#define __CDECLS_BEGIN          extern "C" {
#define __CDECLS_END            }
#else
#define __CDECLS_BEGIN
#define __CDECLS_END
#endif

#define tos_mmheap_alloc            malloc
#define tos_mmheap_free             free

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

typedef enum k_err_en {
    K_ERR_NONE                                  = 0u,

    K_ERR_BIN_HEAP_FULL                     = 15u,
    K_ERR_BIN_HEAP_EMPTY,
    K_ERR_BIN_HEAP_ITEM_SIZE_NOT_MATCH,

    K_ERR_OBJ_PTR_NULL                          = 1100u,
    K_ERR_OBJ_INVALID,
    K_ERR_OBJ_INVALID_ALLOC_TYPE,

    K_ERR_OUT_OF_MEMORY                         = 1150u,

    K_ERR_PRIO_Q_EMPTY                      = 1400u,
    K_ERR_PRIO_Q_FULL,
    K_ERR_PRIO_Q_SLOT_NOT_TAKEN,
    K_ERR_PRIO_Q_ITEM_SIZE_NOT_MATCH,
} k_err_t;

typedef uint8_t             k_prio_t;

#define K_TRUE              (1u)
#define K_FALSE             (0u)

#ifndef K_NULL
#define  K_NULL             0
#endif

typedef enum knl_obj_alloc_type_en {
    KNL_OBJ_ALLOC_TYPE_NONE,
    KNL_OBJ_ALLOC_TYPE_STATIC,
    KNL_OBJ_ALLOC_TYPE_DYNAMIC,
} knl_obj_alloc_type_t;

typedef struct knl_object_st {
    knl_obj_alloc_type_t    alloc_type; /* is dynamic allocated(using tos_mmheap) or static memory? */
} knl_obj_t;

static inline void knl_object_alloc_reset(knl_obj_t *knl_obj)
{
    knl_obj->alloc_type = KNL_OBJ_ALLOC_TYPE_NONE;
}

static inline void knl_object_alloc_set_dynamic(knl_obj_t *knl_obj)
{
    knl_obj->alloc_type = KNL_OBJ_ALLOC_TYPE_DYNAMIC;
}

static inline void knl_object_alloc_set_static(knl_obj_t *knl_obj)
{
    knl_obj->alloc_type = KNL_OBJ_ALLOC_TYPE_STATIC;
}

static inline int knl_object_alloc_is_dynamic(knl_obj_t *knl_obj)
{
    return knl_obj->alloc_type == KNL_OBJ_ALLOC_TYPE_DYNAMIC;
}

static inline int knl_object_alloc_is_static(knl_obj_t *knl_obj)
{
    return knl_obj->alloc_type == KNL_OBJ_ALLOC_TYPE_STATIC;
}

#include "tos_binary_heap.h"
#include "tos_priority_queue.h"

#endif /* _TOS_K_H_ */

