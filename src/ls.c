/*
 * The code in this file is derived from the source for the R project, and is
 * licensed under the GPL version 2.
 *
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1999-2012  The R Core Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 */

#include <R.h>
#include <Rdefines.h>

static int FrameSize(SEXP frame, int all)
{
    int count = 0;
    while (frame != R_NilValue) {
        if ((all || CHAR(PRINTNAME(TAG(frame)))[0] != '.') &&
                                      CAR(frame) != R_UnboundValue)
            count += 1;
        frame = CDR(frame);
    }
    return count;
}

static void FrameNames(SEXP frame, int all, SEXP names, int *indx)
{
    while (frame != R_NilValue) {
        if ((all || CHAR(PRINTNAME(TAG(frame)))[0] != '.') &&
                                      CAR(frame) != R_UnboundValue) {
            SET_STRING_ELT(names, *indx, PRINTNAME(TAG(frame)));
            (*indx)++;
        }
        frame = CDR(frame);
    }
}

static int HashTableSize(SEXP table, int all)
{
    int count = 0;
    int n = length(table);
    int i;
    for (i = 0; i < n; i++)
        count += FrameSize(VECTOR_ELT(table, i), all);
    return count;
}

static void HashTableNames(SEXP table, int all, SEXP names, int *indx)
{
    int n = length(table);
    int i;
    for (i = 0; i < n; i++)
        FrameNames(VECTOR_ELT(table, i), all, names, indx);
}


// Fast replacement for R_lsInternal (called by ls()).
// This version doesn't sort the results (sorting is the slowest part of
// R_lsInternal), and it always returns all objects.
SEXP C_ls(SEXP env) {
    int  k;
    SEXP ans;

    if (env == R_BaseEnv || env == R_BaseNamespace)
        return R_lsInternal(env, TRUE);

    /* Step 1 : Compute the Vector Size */
    k = 0;

    if (isEnvironment(env)) {
        if (HASHTAB(env) != R_NilValue)
            k += HashTableSize(HASHTAB(env), TRUE);
        else
            k += FrameSize(FRAME(env), TRUE);
    }
    else
        error("invalid 'envir' argument");

    /* Step 2 : Allocate and Fill the Result */
    PROTECT(ans = allocVector(STRSXP, k));
    k = 0;
    if (isEnvironment(env)) {
        if (HASHTAB(env) != R_NilValue)
            HashTableNames(HASHTAB(env), TRUE, ans, &k);
        else
            FrameNames(FRAME(env), TRUE, ans, &k);
    }

    UNPROTECT(1);
    return ans;
}
