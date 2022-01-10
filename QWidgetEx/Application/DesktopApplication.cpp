#include "DesktopApplication.h"
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>
#include <QSettings>
#include <QDir>

DesktopApplication::DesktopApplication(QString iconPath, int argc, char** argv)
	: QApplication(argc, argv)
	, serverName_(QFileInfo(QCoreApplication::applicationFilePath()).fileName())
	, systemIcon_(new QSystemTrayIcon(QIcon(iconPath)))
	, bRunning(false)
{
	initLocalConnection();
	setQuitOnLastWindowClosed(false);
	systemIcon_->show();
}

DesktopApplication::~DesktopApplication()
{
	systemIcon_->hide();
}

bool DesktopApplication::isRunning()
{
	return bRunning;
}

void DesktopApplication::initLocalConnection()
{
	bRunning = false;
	QLocalSocket socket;
	socket.connectToServer(serverName_);
	if (socket.waitForConnected(500))
	{
		bRunning = true;
		// �������������͵������
		QTextStream stream(&socket);
		QStringList args = QApplication::arguments();
		if (args.count() > 1)
			stream << args.last();
		else
			stream << QString();
		stream.flush();
		socket.waitForBytesWritten();
		QApplication::quit();
		return;
	}
	//���Ӳ��Ϸ��������ʹ���һ��
	newLocalServer();
}

bool DesktopApplication::notify(QObject* receiver, QEvent* event)
{
	bool done = true;
	try {
		done = QApplication::notify(receiver, event);
	}
	catch (const std::exception& ex) {
	}
	catch (...) {
	}
	return done;
}

void DesktopApplication::newLocalConnection()
{
	QLocalSocket* socket = localServer_->nextPendingConnection();
	if (!socket)
		return;
	socket->waitForReadyRead(1000);
	QTextStream stream(socket);
	//��������
	//if (mainWindow != NULL)
	//{
	//	//�����
	//	QString path = stream.readAll();
	//	DesignWindow::getInstance().file->importFile(path);
	//	mainWindow->raise();
	//	mainWindow->display();
	//}
	delete socket;
}

void DesktopApplication::newLocalServer()
{
	localServer_ = new QLocalServer(this);
	connect(localServer_, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
	if (!localServer_->listen(serverName_))
	{
		// ��ʱ����ʧ�ܣ������ǳ������ʱ,�������̷����µ�,�Ƴ�֮
		if (localServer_->serverError() == QAbstractSocket::AddressInUseError)
		{
			QLocalServer::removeServer(serverName_); // <-- �ص�
			localServer_->listen(serverName_); // �ٴμ���
		}
	}
}

void DesktopApplication::setAutoStart(bool bAutoStart)
{
	QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
				  QSettings::NativeFormat);
	QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
	QString strAppName = QFileInfo(strAppPath).baseName();
	if (bAutoStart)
		reg.setValue(strAppName, strAppPath + QString(" -AutoStart"));
	else
		reg.remove(strAppName);
}

bool DesktopApplication::isAutoStart()
{
	QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
				  QSettings::NativeFormat);
	QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
	QString strAppName = QFileInfo(strAppPath).baseName();
	return !reg.value(strAppName).toString().isEmpty();
}
