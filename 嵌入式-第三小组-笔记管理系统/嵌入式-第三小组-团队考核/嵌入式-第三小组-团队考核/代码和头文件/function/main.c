#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "../head/NoteManagementSystem.h"
#include "../head/chenyu.h" 
#include "../head/linwenchen.h"
#include "../head/moveFOF.h"

char rootpath[200];//�洢�û�·��  
char currentpath[200];//�洢��ǰ·��

int main()
{
	All_User L;
	getcwd(rootpath,sizeof(rootpath));
	L = InitSystem();
	MenuAdmin(&L);
	return 0;
}

