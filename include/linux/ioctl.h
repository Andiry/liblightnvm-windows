#ifndef _UAPI_ASM_GENERIC_IOCTL_H
#define _UAPI_ASM_GENERIC_IOCTL_H

/* ioctl command encoding: 32 bits total, command in lower 16 bits,
 *  * size of the parameter structure in the lower 14 bits of the
 *   * upper 16 bits.
 *    * Encoding the size of the parameter structure in the ioctl request
 *     * is useful for catching programs compiled with old versions
 *      * and to avoid overwriting user space outside the user buffer area.
 *       * The highest 2 bits are reserved for indicating the ``access mode''.
 *        * NOTE: This limits the max parameter size to 16kB -1 !
 *         */

/*
 *  * The following is for compatibility across the various Linux
 *   * platforms.  The generic ioctl numbering scheme doesn't really enforce
 *    * a type field.  De facto, however, the top 8 bits of the lower 16
 *     * bits are indeed used as a type field, so we might just as well make
 *      * this explicit here.  Please be sure to use the decoding macros
 *       * below from now on.
 *        */
#define __IOC_NRBITS	8
#define __IOC_TYPEBITS	8

/*
 *  * Let any architecture override either of the following before
 *   * including this file.
 *    */

#ifndef __IOC_SIZEBITS
# define __IOC_SIZEBITS	14
#endif

#ifndef __IOC_DIRBITS
# define __IOC_DIRBITS	2
#endif

#define __IOC_NRMASK	((1 << __IOC_NRBITS)-1)
#define __IOC_TYPEMASK	((1 << __IOC_TYPEBITS)-1)
#define __IOC_SIZEMASK	((1 << __IOC_SIZEBITS)-1)
#define __IOC_DIRMASK	((1 << __IOC_DIRBITS)-1)

#define __IOC_NRSHIFT	0
#define __IOC_TYPESHIFT	(__IOC_NRSHIFT+__IOC_NRBITS)
#define __IOC_SIZESHIFT	(__IOC_TYPESHIFT+__IOC_TYPEBITS)
#define __IOC_DIRSHIFT	(__IOC_SIZESHIFT+__IOC_SIZEBITS)

/*
 *  * Direction bits, which any architecture can choose to override
 *   * before including this file.
 *    */

#ifndef __IOC_NONE
# define __IOC_NONE	0U
#endif

#ifndef __IOC_WRITE
# define __IOC_WRITE	1U
#endif

#ifndef __IOC_READ
# define __IOC_READ	2U
#endif

#define __IOC(dir,type,nr,size) \
		(((dir)  << __IOC_DIRSHIFT) | \
		 	 ((type) << __IOC_TYPESHIFT) | \
		 	 ((nr)   << __IOC_NRSHIFT) | \
		 	 ((size) << __IOC_SIZESHIFT))

#ifndef __KERNEL__
#define __IOC_TYPECHECK(t) (sizeof(t))
#endif

/* used to create numbers */
#define __IO(type,nr)		__IOC(__IOC_NONE,(type),(nr),0)
#define __IOR(type,nr,size)	__IOC(__IOC_READ,(type),(nr),(__IOC_TYPECHECK(size)))
#define __IOW(type,nr,size)	__IOC(__IOC_WRITE,(type),(nr),(__IOC_TYPECHECK(size)))
#define __IOWR(type,nr,size)	__IOC(__IOC_READ|__IOC_WRITE,(type),(nr),(__IOC_TYPECHECK(size)))
#define __IOR_BAD(type,nr,size)	__IOC(__IOC_READ,(type),(nr),sizeof(size))
#define __IOW_BAD(type,nr,size)	__IOC(__IOC_WRITE,(type),(nr),sizeof(size))
#define __IOWR_BAD(type,nr,size)	__IOC(__IOC_READ|__IOC_WRITE,(type),(nr),sizeof(size))

/* used to decode ioctl numbers.. */
#define __IOC_DIR(nr)		(((nr) >> __IOC_DIRSHIFT) & __IOC_DIRMASK)
#define __IOC_TYPE(nr)		(((nr) >> __IOC_TYPESHIFT) & __IOC_TYPEMASK)
#define __IOC_NR(nr)		(((nr) >> __IOC_NRSHIFT) & __IOC_NRMASK)
#define __IOC_SIZE(nr)		(((nr) >> __IOC_SIZESHIFT) & __IOC_SIZEMASK)

/* ...and for the drivers/sound files... */

#define __IOC_IN		(__IOC_WRITE << __IOC_DIRSHIFT)
#define __IOC_OUT		(__IOC_READ << __IOC_DIRSHIFT)
#define __IOC_INOUT	((__IOC_WRITE|__IOC_READ) << __IOC_DIRSHIFT)
#define __IOCSIZE_MASK	(__IOC_SIZEMASK << __IOC_SIZESHIFT)
#define __IOCSIZE_SHIFT	(__IOC_SIZESHIFT)

#endif /* _UAPI_ASM_GENERIC_IOCTL_H */
