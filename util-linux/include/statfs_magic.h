#ifndef UTIL_LINUX_STATFS_MAGIC_H
#define UTIL_LINUX_STATFS_MAGIC_H

#include <sys/statfs.h>

/*
 * If possible then don't depend on internal libc __SWORD_TYPE type.
 */
#ifdef __GNUC__
#define F_TYPE_EQUAL(a, b) (a == (__typeof__(a)) b)
#else
#define F_TYPE_EQUAL(a, b) (a == (__SWORD_TYPE) b)
#endif

/*
 *  Unfortunately, Linux kernel hedeader file <linux/magic.h> is incomplete
 *  mess and kernel returns by statfs f_type many numbers that are nowhere
 *  specified (in API).
 *
 *  This is collection of the magic numbers.
 */
#define STATFS_ADFS_MAGIC	0xadf5
#define STATFS_AFFS_MAGIC	0xadff
#define STATFS_AFS_MAGIC	0x5346414F
#define STATFS_AUTOFS_MAGIC	0x0187
#define STATFS_BDEVFS_MAGIC	0x62646576
#define STATFS_BEFS_MAGIC	0x42465331
#define STATFS_BFS_MAGIC	0x1BADFACE
#define STATFS_BINFMTFS_MAGIC	0x42494e4d
#define STATFS_BTRFS_MAGIC	0x9123683E
#define STATFS_CEPH_MAGIC	0x00c36400
#define STATFS_CGROUP_MAGIC	0x27e0eb
#define STATFS_CGROUP2_MAGIC	0x63677270
#define STATFS_CIFS_MAGIC	0xff534d42
#define STATFS_CODA_MAGIC	0x73757245
#define STATFS_CONFIGFS_MAGIC	0x62656570
#define STATFS_CRAMFS_MAGIC	0x28cd3d45
#define STATFS_DEBUGFS_MAGIC	0x64626720
#define STATFS_DEVPTS_MAGIC	0x1cd1
#define STATFS_ECRYPTFS_MAGIC	0xf15f
#define STATFS_EFIVARFS_MAGIC	0xde5e81e4
#define STATFS_EFS_MAGIC	0x414A53
#define STATFS_EXOFS_MAGIC	0x5DF5
#define STATFS_EXT2_MAGIC	0xEF53
#define STATFS_EXT3_MAGIC	0xEF53
#define STATFS_EXT4_MAGIC	0xEF53
#define STATFS_F2FS_MAGIC	0xF2F52010
#define STATFS_FUSE_MAGIC	0x65735546
#define STATFS_FUTEXFS_MAGIC	0xBAD1DEA
#define STATFS_GFS2_MAGIC	0x01161970
#define STATFS_HFSPLUS_MAGIC	0x482b
#define STATFS_HOSTFS_MAGIC	0x00c0ffee
#define STATFS_HPFS_MAGIC	0xf995e849
#define STATFS_HPPFS_MAGIC	0xb00000ee
#define STATFS_HUGETLBFS_MAGIC	0x958458f6
#define STATFS_ISOFS_MAGIC	0x9660
#define STATFS_JFFS2_MAGIC	0x72b6
#define STATFS_JFS_MAGIC	0x3153464a
#define STATFS_LOGFS_MAGIC	0xc97e8168
#define STATFS_MINIX2_MAGIC	0x2468
#define STATFS_MINIX2_MAGIC2	0x2478
#define STATFS_MINIX3_MAGIC	0x4d5a
#define STATFS_MINIX_MAGIC	0x137F
#define STATFS_MINIX_MAGIC2	0x138F
#define STATFS_MQUEUE_MAGIC	0x19800202
#define STATFS_MSDOS_MAGIC	0x4d44
#define STATFS_NCP_MAGIC	0x564c
#define STATFS_NFS_MAGIC	0x6969
#define STATFS_NILFS_MAGIC	0x3434
#define STATFS_NTFS_MAGIC	0x5346544e
#define STATFS_OCFS2_MAGIC	0x7461636f
#define STATFS_OMFS_MAGIC	0xC2993D87
#define STATFS_OPENPROMFS_MAGIC	0x9fa1
#define STATFS_PIPEFS_MAGIC	0x50495045
#define STATFS_PROC_MAGIC	0x9fa0
#define STATFS_PSTOREFS_MAGIC	0x6165676C
#define STATFS_QNX4_MAGIC	0x002f
#define STATFS_QNX6_MAGIC	0x68191122
#define STATFS_RAMFS_MAGIC	0x858458f6
#define STATFS_REISERFS_MAGIC	0x52654973
#define STATFS_ROMFS_MAGIC	0x7275
#define STATFS_SECURITYFS_MAGIC	0x73636673
#define STATFS_SELINUXFS_MAGIC	0xf97cff8c
#define STATFS_SMACKFS_MAGIC	0x43415d53
#define STATFS_SMB_MAGIC	0x517B
#define STATFS_SOCKFS_MAGIC	0x534F434B
#define STATFS_SQUASHFS_MAGIC	0x73717368
#define STATFS_SYSFS_MAGIC	0x62656572
#define STATFS_TMPFS_MAGIC	0x01021994
#define STATFS_UBIFS_MAGIC	0x24051905
#define STATFS_UDF_MAGIC	0x15013346
#define STATFS_UFS2_MAGIC	0x19540119
#define STATFS_UFS_MAGIC	0x00011954
#define STATFS_V9FS_MAGIC	0x01021997
#define STATFS_VXFS_MAGIC	0xa501FCF5
#define STATFS_XENFS_MAGIC	0xabba1974
#define STATFS_XFS_MAGIC	0x58465342

#endif /* UTIL_LINUX_STATFS_MAGIC_H */

