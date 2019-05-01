#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "../head/NoteManagementSystem.h"
#include "../head/chenyu.h" 
#include "../head/linwenchen.h"
#include "../head/moveFOF.h"

char rootpath[200];//存储用户路径  
char currentpath[200];//存储当前路径

int main()
{
	All_User L;
	getcwd(rootpath,sizeof(rootpath));
	L = InitSystem();
	MenuAdmin(&L);
	return 0;
}

