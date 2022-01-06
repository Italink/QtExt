#include <QPainter>
#include "FramlessWindow.h"
#include <windows.h>        //ע��ͷ�ļ�
#include <windowsx.h>
#include "QWidgetEx/Widgets/Buttons/WinMaxButton.h"
#include "QWidgetEx/Widgets/Buttons/WinCloseButton.h"
#include "QWidgetEx/Widgets/Buttons/WinMinButton.h"

class CustomHeaderBar : public QWidget {
public:
	CustomHeaderBar() {
		QHBoxLayout* h = new QHBoxLayout(this);
		h->setContentsMargins(0, 0, 0, 0);
		h->setSpacing(0);
		minButton.setFixedSize(30, 30);
		maxButton.setFixedSize(30, 30);
		closeButton.setFixedSize(30, 30);
		h->addSpacing(5);
		h->addWidget(&title, 1, Qt::AlignLeft);
		h->addWidget(&minButton, 0, Qt::AlignRight);
		h->addWidget(&maxButton, 0, Qt::AlignRight);
		h->addWidget(&closeButton, 0, Qt::AlignRight);
	}

	QLabel title;
	WinMaxButton maxButton;
	WinMinButton minButton;
	WinCloseButton closeButton;
};

typedef enum _WINDOWCOMPOSITIONATTRIB {
	WCA_UNDEFINED = 0,
	WCA_NCRENDERING_ENABLED = 1,
	WCA_NCRENDERING_POLICY = 2,
	WCA_TRANSITIONS_FORCEDISABLED = 3,
	WCA_ALLOW_NCPAINT = 4,
	WCA_CAPTION_BUTTON_BOUNDS = 5,
	WCA_NONCLIENT_RTL_LAYOUT = 6,
	WCA_FORCE_ICONIC_REPRESENTATION = 7,
	WCA_EXTENDED_FRAME_BOUNDS = 8,
	WCA_HAS_ICONIC_BITMAP = 9,
	WCA_THEME_ATTRIBUTES = 10,
	WCA_NCRENDERING_EXILED = 11,
	WCA_NCADORNMENTINFO = 12,
	WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
	WCA_VIDEO_OVERLAY_ACTIVE = 14,
	WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
	WCA_DISALLOW_PEEK = 16,
	WCA_CLOAK = 17,
	WCA_CLOAKED = 18,
	WCA_ACCENT_POLICY = 19,
	WCA_FREEZE_REPRESENTATION = 20,
	WCA_EVER_UNCLOAKED = 21,
	WCA_VISUAL_OWNER = 22,
	WCA_LAST = 23
} WINDOWCOMPOSITIONATTRIB;

typedef struct _WINDOWCOMPOSITIONATTRIBDATA {
	WINDOWCOMPOSITIONATTRIB Attrib;
	PVOID pvData;
	SIZE_T cbData;
} WINDOWCOMPOSITIONATTRIBDATA;
typedef enum _ACCENT_STATE {
	ACCENT_DISABLED = 0,
	ACCENT_ENABLE_GRADIENT = 1,
	ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
	ACCENT_ENABLE_BLURBEHIND = 3,
	ACCENT_INVALID_STATE = 4
} ACCENT_STATE;
typedef struct _ACCENT_POLICY
{
	ACCENT_STATE AccentState;
	DWORD AccentFlags;
	DWORD GradientColor;
	DWORD AnimationId;
} ACCENT_POLICY;
WINUSERAPI
BOOL
WINAPI
GetWindowCompositionAttribute(
	_In_ HWND hWnd,
	_Inout_ WINDOWCOMPOSITIONATTRIBDATA* pAttrData);
typedef BOOL(WINAPI* pfnGetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
WINUSERAPI
BOOL
WINAPI
SetWindowCompositionAttribute(
	_In_ HWND hWnd,
	_Inout_ WINDOWCOMPOSITIONATTRIBDATA* pAttrData);
typedef BOOL(WINAPI* pfnSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);

int FramelessWidget::boundaryWidth = 5;

FramelessWidget::FramelessWidget(const QString& title, QWidget* parent)
	: QWidget(parent)
	, headerBar(new CustomHeaderBar)
	, vLayout(this)
{
	headerBar->title.setText(title);
	setMinimumSize(100, 100);
	vLayout.addWidget(headerBar);
	vLayout.setAlignment(Qt::AlignTop);
	vLayout.setContentsMargins(0, 0, 0, 0);
	vLayout.setSpacing(0);

	setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
	setAttribute(Qt::WA_TranslucentBackground);

	connect(&headerBar->minButton, &QPushButton::clicked, this, [this]() {
		this->showMinimized();
	});
	connect(&headerBar->maxButton, &QPushButton::clicked, this, [this]() {
		if (isFullScreen())
			this->showNormal();
		else
			this->showFullScreen();
	});
	connect(&headerBar->closeButton, &QPushButton::clicked, this, [this]() {
		this->close();
	});
	HWND hWnd = HWND(winId());
	HMODULE hUser = GetModuleHandle(L"user32.dll");
	if (hUser)
	{
		pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
		if (setWindowCompositionAttribute)
		{
			ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
			WINDOWCOMPOSITIONATTRIBDATA data;
			data.Attrib = WCA_ACCENT_POLICY;
			data.pvData = &accent;
			data.cbData = sizeof(accent);
			setWindowCompositionAttribute(hWnd, &data);
		}
	}
}

FramelessWidget::~FramelessWidget()
{
}

bool FramelessWidget::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
	MSG* msg = (MSG*)message;
	switch (msg->message)
	{
	case WM_NCHITTEST:
		int xPos = QCursor::pos().x() - this->geometry().x();
		int yPos = QCursor::pos().y() - this->geometry().y();
		if (xPos < boundaryWidth && yPos < boundaryWidth)                    //���Ͻ�
			*result = HTTOPLEFT;
		else if (xPos >= width() - boundaryWidth && yPos < boundaryWidth)          //���Ͻ�
			*result = HTTOPRIGHT;
		else if (xPos < boundaryWidth && yPos >= height() - boundaryWidth)         //���½�
			*result = HTBOTTOMLEFT;
		else if (xPos >= width() - boundaryWidth && yPos >= height() - boundaryWidth)//���½�
			*result = HTBOTTOMRIGHT;
		else if (xPos < boundaryWidth)                                     //���
			*result = HTLEFT;
		else if (xPos >= width() - boundaryWidth)                              //�ұ�
			*result = HTRIGHT;
		else if (yPos < boundaryWidth)                                       //�ϱ�
			*result = HTTOP;
		else if (yPos >= height() - boundaryWidth)                             //�±�
			*result = HTBOTTOM;
		else              //�������ֲ�����������false�����������¼�����������
			return false;
		return true;
	}
	return false;         //�˴�����false�����������¼�����������
}

void FramelessWidget::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton && !isFullScreen())
		clickPos = e->pos();
}
void FramelessWidget::mouseMoveEvent(QMouseEvent* e)
{
	if (e->buttons() & Qt::LeftButton && !clickPos.isNull() && !isFullScreen() && e->y() < headerBar->height())
		move(e->pos() + pos() - clickPos);
}

void FramelessWidget::mouseReleaseEvent(QMouseEvent*)
{
	clickPos = { 0,0 };
}

void FramelessWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.setPen(QColor(0, 0, 0, 80));
	painter.setBrush(QColor(255, 255, 255, 200));
	painter.drawRect(rect().adjusted(1, 1, -1, -1));
}

void FramelessWidget::showEvent(QShowEvent*)
{
	clickPos = { 0,0 };
}