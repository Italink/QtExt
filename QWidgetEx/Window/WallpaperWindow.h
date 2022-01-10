#ifndef WallpaperWindow_h__
#define WallpaperWindow_h__

#include <QWidget>
#include <Windows.h>

class WallpaperWindow :public QWidget {
public:
	WallpaperWindow();
	enum WindowLevel{
		Top,
		Normal,
		Bottom,
		Wallpaper
	}windowLevel_;
	Q_ENUM(WindowLevel);
	void setWindowLevel(WindowLevel level,bool toolWindow = false);
protected:
	HWND getDesktopHWND();
	void closeEvent(QCloseEvent* event) override;
};


#endif // WallpaperWindow_h__
