/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Sample Application for eMMC (Embedded Multi Media Card) driver.
 * This example demonstrates how to use eMMC with the Zephyr File System for
 * the following APIs:
 *    • fs_open
 *    • fs_write
 *    • fs_sync
 *    • fs_read
 * @{
 */

/* Local Includes */
#include <device.h>
#include <ff.h>
#include <fs/fs.h>
#include <intel/hal_emmc.h>
#include <logging/log.h>
#include <stdio.h>
#include <storage/disk_access.h>
#include <zephyr.h>

LOG_MODULE_REGISTER(main);

/* Mount Point */
#define FATFS_MNTP      "/SD:"

/* File Name to be created */
#define FILE_NAME       FATFS_MNTP "/testfile.txt"

/* Read/Write Buffer size */
#define BUFF_SIZE       512

/* Buffer to be written to the storage device. */
static const char write_buff[BUFF_SIZE] = "sample app for emmc!";

static FATFS fat_fs;
/* mounting info */
static struct fs_mount_t mp = {
	.type = FS_FATFS,
	.fs_data = &fat_fs,
};

/*
 *  Note the fatfs library is able to mount only strings inside _VOLUME_STRS
 *  in ffconf.h
 */
static const char *disk_mount_pt = FATFS_MNTP;

struct fs_file_t filep;

/* @brief check_file_dir_exists
 * Checks if the file or directory exists on the device.
 */
static int check_file_dir_exists(const char *path)
{
	int res;
	struct fs_dirent entry;

	/* Verify fs_stat() */
	res = fs_stat(path, &entry);

	return !res;
}

/* @brief file_open
 * Creates a new file if the file_name does not exits,
 * else it opens the existing file.
 */
static int file_open(void)
{
	int res;

	if (check_file_dir_exists(FILE_NAME)) {
		printk("Opening existing file %s\n", FILE_NAME);
	} else {
		printk("Creating new file %s\n", FILE_NAME);
	}

	/* Verify fs_open() */
	res = fs_open(&filep, FILE_NAME, FS_O_CREATE | FS_O_RDWR);
	if (res) {
		printk("Failed opening file [%d]\n", res);
		return -EIO;
	}

	printk("Opened file %s\n", FILE_NAME);

	if (check_file_dir_exists(FILE_NAME)) {
		printk("File now exists %s\n", FILE_NAME);
	}
	return 0;
}

/* @brief file_write
 * Moves the file position to the beginning of the file and
 * writes the data from the write_buff to the file.
 */
static int file_write(void)
{
	ssize_t brw;
	int res;

	/* Verify fs_seek() */
	res = fs_seek(&filep, 0, FS_SEEK_SET);
	if (res) {
		printk("fs_seek failed [%d]\n", res);
		fs_close(&filep);
		return -EIO;
	}

	printk("Data written:\"%s\"\n\n", write_buff);

	/* Verify fs_write() */
	brw = fs_write(&filep, (char *)write_buff, strlen(write_buff));
	if (brw < 0) {
		printk("Failed writing to file [%zd]\n", brw);
		fs_close(&filep);
		return -EIO;
	}
	if (brw < strlen(write_buff)) {
		printk("Unable to complete write. Volume full.\n");
		printk("Number of bytes written: [%zd]\n", brw);
		fs_close(&filep);
		return -EIO;
	}

	printk("Data successfully written!\n");
	return 0;
}

/* @brief file_sync
 * Flushes the cached write buffers of an open file and
 * ensures data gets written to the storage media immediately
 */
static int file_sync(void)
{
	int res;

	/* Verify fs_sync() */
	res = fs_sync(&filep);
	if (res) {
		printk("Error syncing file [%d]\n", res);
		return -EIO;
	}

	return 0;
}

/* @brief file_read
 * Moves the file position to the beginning of the file and
 * reads the data from the file and stores it in read_buff.
 */
static int file_read(void)
{
	ssize_t brw;
	int res;
	char read_buff[BUFF_SIZE];
	size_t sz = strlen(write_buff);

	res = fs_seek(&filep, 0, FS_SEEK_SET);
	if (res) {
		printk("fs_seek failed [%d]\n", res);
		fs_close(&filep);
		return -EIO;
	}

	/* Verify fs_read() */
	brw = fs_read(&filep, read_buff, sz);
	if (brw < 0) {
		printk("Failed reading file [%zd]\n", brw);
		fs_close(&filep);
		return -EIO;
	}

	read_buff[brw] = 0;

	printk("Data read:\"%s\"\n\n", read_buff);

	if (strcmp(write_buff, read_buff)) {
		printk("Error - Data read does not match data written\n");
		printk("Data read:\"%s\"\n\n", read_buff);
		return -EIO;
	}

	printk("Data read matches data written\n");

	return 0;
}

/* @brief lsdir
 * Reads and lists entries of an open directory.
 */
static int lsdir(const char *path)
{
	int res;
	struct fs_dir_t dirp;
	static struct fs_dirent entry;

	fs_dir_t_init(&dirp);

	/* Verify fs_opendir() */
	res = fs_opendir(&dirp, path);
	if (res) {
		printk("Error opening dir %s [%d]\n", path, res);
		return -EIO;
	}

	printk("\nListing dir %s ...\n", path);
	for (;;) {
		/* Verify fs_readdir() */
		res = fs_readdir(&dirp, &entry);

		/* entry.name[0] == 0 means end-of-dir */
		if (res || entry.name[0] == 0) {
			break;
		}

		if (entry.type == FS_DIR_ENTRY_DIR) {
			printk("[DIR ] %s\n", entry.name);
		} else {
			printk("[FILE] %s (size = %zu)\n",
			       entry.name, entry.size);
		}
	}

	/* Verify fs_closedir() */
	fs_closedir(&dirp);

	return 0;
}

/* @brief main function
 * The eMMC application demonstrates file open, write and
 * and read operations.
 */
void main(void)
{
	/* raw disk i/o */
	static const char *disk_pdrv = "SD";
	uint64_t memory_size_mb;
	uint32_t block_count;
	uint32_t block_size;
	uint8_t bus_width = CONFIG_EMMC_BUS_WIDTH;

	if (disk_access_init(disk_pdrv) != 0) {
		printk("Storage init ERROR!");
		return;
	}

	if (disk_access_ioctl(disk_pdrv,
			      DISK_IOCTL_GET_SECTOR_COUNT, &block_count)) {
		printk("Unable to get sector count");
		return;
	}
	LOG_INF("Block count %u", block_count);

	if (disk_access_ioctl(disk_pdrv,
			      DISK_IOCTL_GET_SECTOR_SIZE, &block_size)) {
		printk("Unable to get sector size");
		return;
	}
	printk("Sector size %u\n", block_size);

	memory_size_mb = (uint64_t)block_count * block_size;
	printk("Memory Size(MB) %u\n", (uint32_t)(memory_size_mb >> 20));

	if (disk_access_ioctl(disk_pdrv,
			  DISK_IOCTL_LINE_CTRL, &bus_width)) {
		printk("Unable to set bus width");
		return;
	}

	mp.mnt_point = disk_mount_pt;

	/* If FAT32 file system is not found, it will format the disk to FAT32
	 * which will take some time.
	 */
	int res = fs_mount(&mp);

	if (res == FR_OK) {
		printk("Disk mounted.\n");
	} else {
		printk("Error mounting disk.\n");
		return;
	}

	/* Initialize file object */
	fs_file_t_init(&filep);

	res = file_open();
	if (res) {
		printk("Failed to open file.\n");
		return;
	}

	res = file_write();
	if (res) {
		printk("Failed to write to file.\n");
		return;
	}

	res = file_sync();
	if (res) {
		printk("Failed to sync file.\n");
		return;
	}

	res = lsdir(disk_mount_pt);
	if (res) {
		printk("Failed to list contents of directory.\n");
		return;
	}

	res = file_read();
	if (res) {
		printk("Failed to read file.\n");
		return;
	}

	printk("Exiting eMMM sample app.\n");
}

/**
 * @}
 */
