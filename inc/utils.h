#pragma once

typedef struct {
    const char * name;
    struct stat stat;
    void * data;
} tmpfs_inode_t;

/**
 * Initializes a file struct with the given name and stat.
 * @return 0 iff successful, -ENOMEM otherwise.
 * @note name is copied to a buffer owned by the inode.
 */
int init_file(tmpfs_inode_t *file, const char *name, const struct stat *stat);

/**
 * Performs a lookup for the file struct corresponding to the given path, starting from the given root dir.
 * Stores the result in the out parameter `file`.
 * Returns -ENOMEM or -ENOENT if some error occured, or 0 if successful.
 */
int lookup(const char * path, tmpfs_inode_t * root_dir, tmpfs_inode_t ** file);

/**
 * Looks for an entry with the given name inside the dir.
 * Returns the inode if found, else returns NULL.
 */
tmpfs_inode_t * dir_lookup(tmpfs_inode_t * dir, const char * name);

/**
 * Puts the given inode in the dir.
 * Returns 0 iff successful, -ENOMEM or -EEXIST otherwise.
 */
int add_inode_to_dir(tmpfs_inode_t * dir, const tmpfs_inode_t * inode);

/**
 * Splits the given path into the dirname and filename.
 * @return 0 iff successful, -ENOMEM otherwise.
 * @note filename must NOT be freed, it's a pointer inside the given path.
 */
int split(const char *path, const tmpfs_inode_t * root_dir, tmpfs_inode_t ** dirname, char **filename);
