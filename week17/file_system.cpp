#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <dirent.h>
using namespace std;

const int BLANK = 40;
const int BLANK2 = 10;

int main()
{
    char directory[1000];
    struct stat *  file_stat;
    
    cout << "File System is running!" << endl
    << ">----------------------------------------------------------------------<" << endl;
    if(getcwd(directory, 1000) == NULL)
    /* get the directory */
    {
        cout << "Finding directory error!" << endl;
    }
    else
    {
        cout << directory << endl;
    }
        
    if(stat("/home/schrodecat/Documents/OS/week17/实验十四+文件和目录.pdf", file_stat) == -1)
    /* get the state of the file */
    {
        cout << "Reading file stat2 error!" << endl;
        cout << "Errno: " << errno << endl;
        if(errno == 14)
        cout << "Bad address! Please try again later!" << endl;
    }
    else
    {
        cout << left;
        cout << setw(BLANK)<< "Inode:" << setw(BLANK2) << file_stat->st_ino << endl
            << setw(BLANK) << "Mode:" << setw(BLANK2) << oct << file_stat->st_mode << endl
            << setw(BLANK) << "Links:" << setw(BLANK2) << dec << file_stat->st_nlink << endl
            << setw(BLANK) << "User ID:" << setw(BLANK2) << dec << file_stat->st_uid << endl
            << setw(BLANK) << "Group ID:" << setw(BLANK2) << dec << file_stat->st_gid << endl
            << setw(BLANK) << "Device:" << setw(0) << hex << file_stat->st_rdev << " / " << hex << file_stat->st_dev << "(hex) / " << dec << file_stat->st_dev << "(dec)" << endl 
            << setw(BLANK) << "Size:" << setw(BLANK2) << dec << file_stat->st_size << endl
            << setw(BLANK) << "IO Block Size:" << setw(BLANK2) << file_stat->st_blksize << endl
            << setw(BLANK) << "blocks:" << setw(BLANK2) << file_stat->st_blocks << endl 
            << setw(BLANK) << "Last access:" << setw(BLANK2) << ctime(&(file_stat->st_atime))
            << setw(BLANK) << "Last modify:" << setw(BLANK2) << ctime(&(file_stat->st_mtime))
            << setw(BLANK) << "Last change:" << setw(BLANK2) << ctime(&(file_stat->st_ctime)) << endl;
    }
    return 0;
}

// string GT(ctime input)
// {
//     string result;
//     result.Format("%d-%d-%d-%d",input.getyear(),input.getmonth(),input.getday());
//     return result;
// }

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

//
//        struct dirent { 
//              ino_t          d_ino;       /* inode number */
//              off_t          d_off;       /* offset to the next dirent */ 
//              unsigned short d_reclen;    /* length of this record */ 
//              unsigned char  d_type;      /* type of file */ 
//              char           d_name[256]; /* filename */ 
//          };
