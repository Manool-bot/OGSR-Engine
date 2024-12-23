#include "stdafx.h"
#include "resource.h"

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CRenderDevice::Initialize()
{
    Log("Initializing Engine...");
    TimerGlobal.Start();
    TimerMM.Start();

    // Unless a substitute hWnd has been specified, create a window to render into
    if (m_hWnd == NULL)
    {
        const char* wndclass = "_XRAY_1.5";

        // Register the windows class
        HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(0);
        WNDCLASS wndClass = {0,    WndProc, 0, 0, hInstance, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)), LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH),
                             NULL, wndclass};
        RegisterClass(&wndClass);

        // Set the window's initial style
        m_dwWindowStyle = WS_BORDER | WS_DLGFRAME;

        // Set the window's initial width
        RECT rc;
        SetRect(&rc, 0, 0, 640, 480);
        AdjustWindowRect(&rc, m_dwWindowStyle, FALSE);

        // Create the render window
        m_hWnd = CreateWindow /*Ex*/ ( // WS_EX_TOPMOST,
            wndclass, "NLC OGSR", m_dwWindowStyle,
            /*rc.left, rc.top, */ CW_USEDEFAULT, CW_USEDEFAULT, (rc.right - rc.left), (rc.bottom - rc.top), 0L, 0, hInstance, 0L);
        gGameWindow = m_hWnd;
    }

    // Save window properties
    m_dwWindowStyle = u32(GetWindowLongPtr(m_hWnd, GWL_STYLE));
    GetWindowRect(m_hWnd, &m_rcWindowBounds);
    GetClientRect(m_hWnd, &m_rcWindowClient);

    /*
    if (strstr(lpCmdLine,"-gpu_sw")!=NULL)		HW.Caps.bForceGPU_SW		= TRUE;
    else										HW.Caps.bForceGPU_SW		= FALSE;
    if (strstr(lpCmdLine,"-gpu_nopure")!=NULL)	HW.Caps.bForceGPU_NonPure	= TRUE;
    else										HW.Caps.bForceGPU_NonPure	= FALSE;
    if (strstr(lpCmdLine,"-gpu_ref")!=NULL)		HW.Caps.bForceGPU_REF		= TRUE;
    else										HW.Caps.bForceGPU_REF		= FALSE;
    */
}
