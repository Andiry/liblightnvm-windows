/*
 * geo - Geometry functions
 *
 * Copyright (C) 2015-2017 Javier Gonzáles <javier@cnexlabs.com>
 * Copyright (C) 2015-2017 Matias Bjørling <matias@cnexlabs.com>
 * Copyright (C) 2015-2017 Simon A. F. Lund <slund@cnexlabs.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include "../include/liblightnvm.h"

void nvm_geo_pr(const struct nvm_geo *geo)
{
	printf("geo:\n");
	printf("  nchannels: %I64u\n", geo->nchannels);
	printf("  nluns: %I64u\n", geo->nluns);
	printf("  nplanes: %I64u\n", geo->nplanes);
	printf("  nblocks: %I64u\n", geo->nblocks);
	printf("  npages: %I64u\n", geo->npages);
	printf("  nsectors: %I64u\n", geo->nsectors);
	printf("  page_nbytes: %I64u\n", geo->page_nbytes);
	printf("  sector_nbytes: %I64u\n", geo->sector_nbytes);
	printf("  meta_nbytes: %I64u\n", geo->meta_nbytes);	
	printf("  tbytes: %I64u\n", geo->tbytes);
	printf("  tmbytes: %I64u\n", geo->tbytes >> 20);
}
