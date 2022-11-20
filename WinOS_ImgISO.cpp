// WinOS_ImgISO.cpp : Définit le point d'entrée de l'application.
//
/*                      0x06030000
                  0x0A000000
                         0x0A000000
                     0x0A000001
                     0x0A000002
Windows 10_RS2                     0x0A000003
Windows 10_RS3                     0x0A000004
Windows 10_RS4                     0x0A000005
Windows 10_RS5                     0x0A000006
Windows 10_19H1                    0x0A000007
Windows 10_VB                      0x0A000008
Windows 10_MN                      0x0A000009
Windows 10_FE                      0x0A00000A
Windows 10_CO                      0x0A00000B
Windows 10_NI                      0x0A00000C
*/
#include "framework.h"
#include "WinOS_ImgISO.h"

#define MAX_LOADSTRING 100

CHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
CHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale
WNDCLASSEX wcex;
COLORREF Fond = RGB(0xCC, 0xE5, 0xFF);
HWND hWnd, hEvent;
LRESULT CALLBACK    ProcedurePrincipale(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ProcedureInformationsImage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK     ProcedureAPropos(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int       nCmdShow){
    RECT rc;
    GetClientRect(GetDesktopWindow(), &rc);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WINOSIMGISO, szWindowClass, MAX_LOADSTRING);
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = ProcedurePrincipale;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINOSIMGISO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(Fond);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WINOSIMGISO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm = wcex.hIcon;
    if(!RegisterClassEx(&wcex)){return false;}
    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,rc.left, rc.top,rc.right, rc.bottom-37, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd){return FALSE;}
    GetClientRect(hWnd,&rc);
    HICON ico = LoadIcon(wcex.hInstance, (LPCSTR)IDI_ICON1);
    hEvent=CreateWindow(WC_LISTBOX, "Evenemtiel", WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME| WS_DLGFRAME | WS_BORDER, 0, 0, rc.right/2, rc.bottom/2, hWnd, (HMENU)5000, hInstance, nullptr);
    SendMessage(hEvent, GCLP_HICONSM, 0, (LPARAM)ico);
    CreateStatusWindow(WS_CHILD | WS_VISIBLE, wcex.lpszClassName, hWnd, 6000);
    ShowWindow(hWnd, nCmdShow);
    DialogBox(wcex.hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ProcedureInformationsImage);
    UpdateWindow(hWnd);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINOSIMGISO));
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK ProcedurePrincipale(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {

    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyse les sélections de menu :
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(wcex.hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd,  ProcedureAPropos);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Ajoutez ici le code de dessin qui utilise hdc...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
INT_PTR CALLBACK  ProcedureAPropos(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
INT_PTR CALLBACK ProcedureInformationsImage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    char temp[80];
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SendMessage(hDlg, GCLP_HICONSM, 0, (LPARAM)LoadIcon(wcex.hInstance, (LPCSTR)IDI_ICON1));
        for (int x = 0xC8; x < 0xDE; x++) {
            LoadString(wcex.hInstance, x, temp, sizeof(temp));
            SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)temp);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            if(MessageBox(hDlg, "Etes vous sur de vouloir abandonner?", szTitle, MB_YESNO | MB_ICONQUESTION)==0x06){
                PostQuitMessage(0xAC);
            }            
        }
        break;
    }
    return (INT_PTR)FALSE;
}
