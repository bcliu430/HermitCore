/* Copyright (c) 2015, IBM
 * Author(s): Dan Williams <djwillia@us.ibm.com>
 *            Ricardo Koller <kollerr@us.ibm.com>
 * Copyright (c) 2017, RWTH Aachen University
 * Author(s): Stefan Lankes <slankes@eonerc.rwth-aachen.de>
 *            Tim van de Kamp <tim.van.de.kamp@rwth-aachen.de>
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* We used several existing projects as guides
 * kvmtest.c: http://lwn.net/Articles/658512/
 * lkvm: http://github.com/clearlinux/kvmtool
 */

/*
 * 15.1.2017: extend original version (https://github.com/Solo5/solo5)
 *            for HermitCore
 */

#include "uhyve-blk.h"

static uhyve_blkinfo_t blkinfo;

//-------------------------------------- SETUP NETWORK ---------------------------------------------//
static int uhyve_blk_init(char *hermit_blk)
{
	size_t (blk_size);
	char* str_blk_bs = getenv("HERMIT_BLK_BS");
	if (str_blk_bs) {
		blk_size = (size_t) atoi(str_blk_bs);
		if (blk_size < 255) {
			err(1, "ERROR: Blocksize must be greater then 255");
			return -3;
		}
	} else {
		blk_size = HERMIT_BLK_BS;
	}

	// useful if? setup network is only called if HERMTI_BLK is set
	if (hermit_blk == NULL) {
		err(1, "ERROR: no blk device defined\n");
		return -1;
	}
	diskfd = open(hermit_blk, O_RDWR);
	if (diskfd == -1) {
		err(1, "Could not open disk: %s", hermit_blk);
		return -2;
	}

	blkinfo.sector_size = blk_size;
	blkinfo.num_sectors = lseek(diskfd, 0, SEEK_END) / 512;
	blkinfo.rw = 1;
	printf("BLK device attached with %i sectors and sector_size %i bytes\n", blkinfo.num_sectors, blkinfo.sector_size);

	return diskfd;
}