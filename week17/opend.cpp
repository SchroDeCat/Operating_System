#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
using namespace std;

int main()
{
    // char * directory = new char[100];
    char directory[1000];
    struct dirent *info = new struct dirent;
    struct stat * detail = new struct stat;
    getcwd(directory, 1000);
    DIR * direct = opendir(directory);
    
    char * name = new char[100];
    // cout << "file name : " << endl;
    // cin >> name; 
    // if( mkdir(name, 0775) == -1)
    // {
    //     if(errno == 14)  cout << "Bad address! Please try again later!" << endl;
    //     cout << "mkdir error, please try it later" << endl;
    // }
    // cout << "Delete file name: " << endl;
    // cin >> name;
    // if(remove(name) == -1)
    // {
    //     cout << "Delete file error, please try it later" << endl;
    // }

    delete name;


    while(info = readdir(direct))
    {
        cout << endl << "----------------------------------------" << endl;
        cout << "filename: " << info->d_name << endl;
        cout << "inode: " << info->d_ino << endl;
        cout << "offset to next dirent: " << info->d_off << endl;
        cout << "length of this record: " << info->d_reclen << endl;
        //cout << "type of file: " << info->d_type << endl;

        /* judge the type of the file */
        stat(info->d_name, detail);
        cout << "Type of the file: ";
        if(S_ISDIR(detail->st_mode)) cout << "Directory" << endl;
        if(S_ISREG(detail->st_mode)) cout << "File" << endl;
        if(S_ISBLK(detail->st_mode)) cout << "Block" << endl;
        if(S_ISFIFO(detail->st_mode)) cout << "Pipeline or FIFO" << endl;
        if(S_ISLNK(detail->st_mode)) cout << "Link" << endl;
        if(S_ISSOCK(detail->st_mode)) cout << "Socket" << endl;
        if(S_ISCHR(detail->st_mode)) cout << "Character" << endl;
        
    }


    closedir(direct);
    // delete directory;
    return 0;
}

    //    struct dirent { 
    //          ino_t          d_ino;       /* inode number */ 
    //          off_t          d_off;       /* offset to the next dirent */ 
    //          unsigned short d_reclen;    /* length of this record */ 
    //          unsigned char  d_type;      /* type of file */ 
    //          char           d_name[256]; /* filename */ 
    //      };

/*
struct stat {
    dev_t         st_dev;       //文件的设备编号
    ino_t         st_ino;       //节点
    mode_t        st_mode;      //文件的类型和存取的权限
    nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
    uid_t         st_uid;       //用户ID
    gid_t         st_gid;       //组ID
    dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
    off_t         st_size;      //文件字节数(文件大小)
    unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
    unsigned long st_blocks;    //块数
    time_t        st_atime;     //最后一次访问时间
    time_t        st_mtime;     //最后一次修改时间
    time_t        st_ctime;     //最后一次改变时间(指属性)
};
*/