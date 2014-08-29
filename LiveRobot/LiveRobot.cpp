// LiveRobot.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

#include "Robot.h"
#include "Douyu/DouyuRobot.h"


bool g_exit = false;

using namespace std;

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc < 4)
    {
        cout << "����˵��:" << endl;
        cout << "    LiveRobot ƽ̨ID(douyu) ����ID ģ������" << endl;
        return 0;
    }

    CString platform_id = argv[1];
    CString room_url = argv[2];
    UINT robot_total = _ttoi(argv[3]);
    Robot* robot = nullptr;

    if (platform_id == _T("douyu"))
    {
        robot = new DouyuRobot;
    }
    
    if (nullptr != robot && !room_url.IsEmpty() && robot_total > 0)
    {
        SetConsoleCtrlHandler(HandlerRoutine, TRUE);
        cout << "��Ctrl + C������ִֹ��" << endl;

        if (robot->Login(room_url, robot_total))
        {
            DWORD last_output_time = 0, now = 0;
            while (false == g_exit)
            {
                Sleep(100);
                now = GetTickCount();
                if (now - last_output_time > 3000)
                {
                    last_output_time = now;
                    cout << "��ǰ�ѵ�¼����������" << robot->GetLoggedTotal() << endl;
                }
            }
            cout << "�û���ֹ..." << endl;
            robot->Logout();
        }
        else
        {
            cout << "��¼ʧ�ܣ�" << endl;
        }
        delete robot;
    }
    else
    {
        cout << "��������." << endl;
    }

    system("pause");
	return 0;
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
    g_exit = true;
    return TRUE;
}