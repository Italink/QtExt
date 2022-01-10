#include "WallpaperWindow.h"
#include <QDebug>

WallpaperWindow::WallpaperWindow(){
	setWindowLevel(WindowLevel::Wallpaper);
}

void WallpaperWindow::setWindowLevel(WindowLevel level, bool toolWindow)
{
	if (windowLevel_ == level)
		return;
	close();

	Qt::WindowType toolWindowType = toolWindow ? Qt::Tool : Qt::Widget;

	switch (level) {
	case WindowLevel::Top: {
		setAttribute(Qt::WA_TransparentForMouseEvents, true);
		LONG l = GetWindowLongA((HWND)winId(), GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLongA((HWND)winId(), GWL_EXSTYLE, l);
		SetParent((HWND)winId(), NULL);
		SetWindowLongA((HWND)winId(), GWL_STYLE, (WS_POPUP | WS_VISIBLE));
		SetWindowLongA((HWND)winId(), GWL_EXSTYLE, 0);
		setWindowFlags(Qt::Window | toolWindowType | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		break;
	}
	case WindowLevel::Normal: {
		setAttribute(Qt::WA_TransparentForMouseEvents, true);
		LONG l = GetWindowLongA((HWND)winId(), GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLongA((HWND)winId(), GWL_EXSTYLE, l);
		SetParent((HWND)winId(), NULL);
		SetWindowLongA((HWND)winId(), GWL_STYLE, (WS_POPUP | WS_VISIBLE));
		SetWindowLongA((HWND)winId(), GWL_EXSTYLE, 0);
		setWindowFlags(Qt::Window | toolWindowType | Qt::FramelessWindowHint);
		break;
	}
	case WindowLevel::Bottom: {
		setAttribute(Qt::WA_TransparentForMouseEvents, true);
		LONG l = GetWindowLongA((HWND)winId(), GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLongA((HWND)winId(), GWL_EXSTYLE, l);
		SetParent((HWND)winId(), NULL);
		SetWindowLongA((HWND)winId(), GWL_STYLE, (WS_POPUP | WS_VISIBLE));
		SetWindowLongA((HWND)winId(), GWL_EXSTYLE, 0);
		setWindowFlags(Qt::Window | toolWindowType | Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
		break;
	}
	case WindowLevel::Wallpaper: {
		setAttribute(Qt::WA_TransparentForMouseEvents, false);
		HWND Parent = getDesktopHWND();
		SetParent((HWND)winId(), Parent);
		SetWindowLongA((HWND)winId(), GWL_STYLE, (WS_POPUP | WS_VISIBLE));
		SetWindowLongA((HWND)winId(), GWL_EXSTYLE, (WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TRANSPARENT | WS_EX_TOPMOST));
		setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint);
		break;
	}
	default:
		break;
	}
	show();
	if (windowLevel_ == Wallpaper) {
		HWND desktop = getDesktopHWND();
		ShowWindow(desktop, SW_HIDE);
		RedrawWindow(desktop, nullptr, nullptr, RDW_ERASE | RDW_INTERNALPAINT | RDW_ERASENOW | RDW_UPDATENOW | RDW_ALLCHILDREN);
		ShowWindow(desktop, SW_SHOW);
	}
	windowLevel_ = level;
}

HWND WallpaperWindow::getDesktopHWND()
{
	HWND hWnd = ::FindWindow(L"Progman", L"Program Manager");
	SendMessage(hWnd, 0x052c, 0, 0);;
	HWND hwndWorkW = NULL;
	while (true){
		hwndWorkW = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
		if (NULL == hwndWorkW)
			continue;
		HWND hView = ::FindWindowEx(hwndWorkW, NULL, L"SHELLDLL_DefView", NULL);
		if (NULL == hView)
			continue;
		hwndWorkW = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
		break;
	};
	return  hwndWorkW;
}

void WallpaperWindow::closeEvent(QCloseEvent* event){
	if (windowLevel_ == Wallpaper) {
		HWND desktop = getDesktopHWND();
		ShowWindow(desktop, SW_HIDE);
		RedrawWindow(desktop, nullptr, nullptr, RDW_ERASE | RDW_INTERNALPAINT | RDW_ERASENOW | RDW_UPDATENOW | RDW_ALLCHILDREN);
		ShowWindow(desktop, SW_SHOW);
	}
}